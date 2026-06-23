-- Exemplos de árvores 
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant bracket" #-}
{-# HLINT ignore "Eta reduce" #-}
exampleTree1 :: Num a => BTree a
exampleTree1 = Node 10 
                (Node 5 
                    (Node 3 Empty Empty) 
                    (Node 7 Empty Empty)
                )
                (Node 15 
                    Empty 
                    (Node 18 Empty Empty)
                )

exampleTree2 :: Num a => BTree a  
exampleTree2 = Node 3 
                (Node 7 Empty Empty) 
                (Node 5              
                        (Node 4 Empty Empty) 
                        Empty)


-- Continuar BTree a 
data BTree a = Empty 
              | Node a (BTree a) (BTree a) 

zipWithBTree :: (a->b->c) -> BTree a -> BTree b -> BTree c 
zipWithBTree f (Node i1 e1 d1) (Node i2 e2 d2) = Node (f i1 i2) (zipWithBTree f e1 e2) (zipWithBTree f d1 d2)
zipWithBTree _ _ _ = Empty 

mapBTree :: (a->b) -> BTree a -> BTree b 
mapBTree f Empty = Empty 
mapBTree f (Node i e d) = Node (f i) (mapBTree f e) (mapBTree f d)  

bTreelist :: BTree a -> [a]
bTreelist Empty = []
bTreelist (Node i e d) = i : bTreelist e ++ bTreelist d

-- Alterar o Eq -> Serão iguais dependendo da soma dos nodos (podemos usar igual ou diferente)
sumBtree :: Num a => BTree a -> a 
sumBtree Empty = 0 
sumBtree t = sum (bTreelist t)

eqBTree :: (Num a,Eq a) => BTree a -> BTree a -> Bool 
eqBTree t1 t2 = sumBtree t1 == sumBtree t2 


instance (Num a,Eq a) => Eq (BTree a) where 
    (==) = eqBTree  

-- Alterar o Show (usar o show sempre :t show :: a -> String) 
showBTree :: Show a => BTree a -> String
showBTree Empty = "*"
showBTree (Node i e d) = "( " ++ showBTree e ++ ") < >" ++ (show i) ++ "( " ++ showBTree d ++ ")"

instance Show a => Show (BTree a) where 
    show = showBTree 

-- Alterar o Ord -> através do somatório (usamos sempre o (<=))
menorOuIgualBTree :: (Num a,Ord a) => BTree a -> BTree a -> Bool 
menorOuIgualBTree t1 t2 = sumBtree t1 <= sumBtree t2 

instance (Num a,Ord a) => Ord (BTree a) where 
    (<=) = menorOuIgualBTree

-- Alterar o Num -> temos de definir ((+),(*),(-),(abs),(singnum),(fromInteger))
somaBTree :: Num a => BTree a -> BTree a -> BTree a 
somaBTree t1 t2 = zipWithBTree (+) t1 t2 

multBTree :: Num a => BTree a -> BTree a -> BTree a 
multBTree t1 t2 = zipWithBTree (*) t1 t2 

subBTree :: Num a => BTree a -> BTree a -> BTree a 
subBTree t1 t2 = zipWithBTree (-) t1 t2 

absBTree :: Num a => BTree a -> BTree a
absBTree t = mapBTree abs t

-- abs t * signum t = t 
signumBTree :: Num a => BTree a -> BTree a 
signumBTree t = mapBTree signum t 

deInteiro :: Num a => Integer -> BTree a 
deInteiro i = Node (fromInteger i) Empty Empty 

instance Num a => Num (BTree a) where 
    (+) = somaBTree 
    (*) = multBTree 
    (-) = subBTree 
    abs = absBTree 
    signum = signumBTree 
    fromInteger = deInteiro 

-- Função read :: String -> a (faz o contrário do show)
-- Função scanr ex: scanr (+) 2 [4,7,10] -> [23,19,12,2]
scanr' :: (a->b->b) -> b -> [a] -> [b]
scanr' f ac [] = [ac]
scanr' f ac (h:t) = (f h (head rest)) : rest  
        where  
            rest = scanr' f ac t 

-- definir com foldr 
scanfoldr :: (a->b->b) -> b -> [a] -> [b]
scanfoldr f ac l = foldr f' [ac] l 
    where 
        f' x ac = f x (head ac) : ac 