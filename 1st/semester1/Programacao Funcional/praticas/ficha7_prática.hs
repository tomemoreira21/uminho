-- 1 
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use concatMap" #-}
data ExpInt = Const Int
            | Simetrico ExpInt
            | Mais ExpInt ExpInt
            | Menos ExpInt ExpInt
            | Mult ExpInt ExpInt

e1 :: ExpInt
e1 = Mais (Const 5) (Const 3)

e2 :: ExpInt
e2 = Menos (Const 5) e1 

e3 :: ExpInt 
e3 = Simetrico e1 

-- a) 
calcula :: ExpInt -> Int 
calcula k = case k of 
            Const x -> x 
            Simetrico e -> - calcula e 
            Mais e1 e2 -> calcula e1 + calcula e2 
            Menos e1 e2 -> calcula e1 - calcula e2 
            Mult e1 e2 -> calcula e1 * calcula e2 

-- b) 
infixa :: ExpInt -> String 
infixa k = case k of 
            Const x -> show x 
            Simetrico e -> "-" ++ infixa e 
            Mais e1 e2 -> "(" ++ infixa e1 ++ " + " ++ infixa e2 ++ ")"
            Menos e1 e2 -> "(" ++ infixa e1 ++ " - " ++ infixa e2 ++ ")"
            Mult e1 e2 -> "(" ++ infixa e1 ++ " * " ++ infixa e2 ++ ")"

-- c) 
posfixa :: ExpInt -> String 
posfixa k = case k of 
            Const x -> show x ++ " "
            Simetrico e -> posfixa e ++ "- "
            Mais e1 e2 -> posfixa e1 ++ posfixa e2 ++ "+ "
            Menos e1 e2 -> posfixa e1 ++ posfixa e2 ++ "- "
            Mult e1 e2 -> posfixa e1 ++ posfixa e2 ++ "* "

-- 2 
data RTree a = R a [RTree a] deriving (Show)

ex1 :: Num a => RTree a 
ex1 = R 2 [R 3 [], R 4 [R 5 [], R 6 [], R 8 []]]

ex2 :: Num a => RTree a 
ex2 = R 1 [ R 2 [ R 4 [], R 5 []], R 3 [ R 6 [], R 7 []]]
                      
ex3 :: Num a => RTree a 
ex3 = R 5 [R 7 [],R 3 [R 4 [],R 2 []],R 8 []]             
            
-- a) 
soma :: Num a => RTree a -> a 
soma (R x []) = x
soma (R x l) = x + sum (map soma l)

-- b) 
altura :: RTree a -> Int 
altura (R x []) = 1 
altura (R x l) = 1 + maximum (map altura l)

-- c) 
prune :: Int -> RTree a -> RTree a 
prune 0 (R x _) = R x []
prune _ (R x []) = R x []
prune n (R x l) = R x (map (prune (n-1)) l)

-- d) 
mirror :: RTree a -> RTree a 
mirror (R x l) = R x (reverse (map mirror l)) 

-- e) 
postorder :: RTree a -> [a]
postorder (R x []) = [x]
postorder (R x l) = concat (map postorder l) ++ [x]

-- 3 
data LTree a = Tip a | Fork (LTree a) (LTree a)

t1 :: Num a => LTree a 
t1 = Fork (Fork (Tip 5) (Tip 3)) (Tip 4)

t2 :: Num a => LTree a
t2 = Fork (Tip 7) (Fork (Tip 2) (Tip 9))

t3 :: Num a => LTree a
t3 = Fork (Fork (Tip 1) (Fork (Tip 6) (Tip 8))) (Tip 3)

-- a) 
ltSum :: Num a => LTree a -> a
ltSum (Tip x) = x 
ltSum (Fork e d) = ltSum e + ltSum d

-- b) 
listaLT :: LTree a -> [a]
listaLT (Tip x) = [x]
listaLT (Fork e d) = listaLT e ++ listaLT d 

-- c) 
ltHeight :: LTree a -> Int
ltHeight (Tip _) = 1 
ltHeight (Fork e d) = 1 + max (ltHeight e) (ltHeight d)

-- 4 
data FTree a b = Leaf b | No a (FTree a b) (FTree a b)
data BTree a = Empty |Node a (BTree a) (BTree a) 
-- a) 
splitFTree :: FTree a b -> (BTree a, LTree b)
splitFTree (Leaf x) = (Empty, Tip x)
splitFTree (No x e d) = (Node x leBT ldBT, Fork leLT ldLT)
    where 
        (leBT,leLT) = splitFTree e 
        (ldBT,ldLT) = splitFTree d 

-- converte uma full Tree em árvore binária 
converteBT :: FTree a b -> BTree a 
converteBT (Leaf x) = Empty
converteBT (No x e d) = Node x (converteBT e) (converteBT d)

-- converte uma full tree em leaf tree
converteFT :: FTree a b -> LTree b 
converteFT (Leaf x) = Tip x 
converteFT (No x e d) = Fork (converteFT e) (converteFT d)

-- b) 
joinTrees :: BTree a -> LTree b -> Maybe (FTree a b)
joinTrees Empty (Tip x) = Just (Leaf x)
joinTrees Empty _ = Nothing 
joinTrees _ (Tip x) = Nothing 
joinTrees (Node x e d) (Fork e' d') = case fte of 
                                        Nothing -> Nothing 
                                        Just fte' -> case ftd of 
                                                Nothing -> Nothing 
                                                Just ftd' -> Just (No x fte' ftd') 
                                      where 
                                          fte = joinTrees e e' 
                                          ftd = joinTrees d d' 
                                                    