{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use foldr" #-}
-- 1 
-- com recursividade
porImpares :: [a] -> [a] 
porImpares [] = []
porImpares [x] = []
porImpares (x:y:xs) = y : porImpares xs

-- com zip 
porImpares' :: [a] -> [a]
porImpares' l = map fst (filter (\(x,y) -> odd y) list) 
    where 
        list = zip l [0..]

-- 2
-- Usando take  
isPrefixOf' :: Eq a => [a] -> [a] -> Bool 
isPrefixOf' l1 l2 = l1 == i 
    where 
        i = take (length l1) l2 

-- Com recursividade 
isPrefixOf'' :: Eq a => [a] -> [a] -> Bool 
isPrefixOf'' [] _ = True 
isPrefixOf'' _ [] = False 
isPrefixOf'' (x1:xs1) (x2:xs2) = x1 == x2 && isPrefixOf'' xs1 xs2 

-- Com zip 
isPrefixOf''' :: Eq a => [a] -> [a] -> Bool 
isPrefixOf''' xs ys = all (\(x,y) -> x == y) list && length xs <= length ys 
    where 
        list = zip xs ys  

-- 3 
type Mat a = [[a]]

-- a) 
zeros :: (Eq a,Num a) => Mat a -> Int 
zeros [] = 0 
zeros (x:xs) = contazeros x + zeros xs 

contazeros :: (Num a,Eq a) => [a] -> Int
contazeros [] = 0 
contazeros (x:xs) = if x == 0 then 1 + contazeros xs else contazeros xs 

-- b) 
addMat :: Num a => Mat a -> Mat a -> Mat a 
addMat [] _ = []
addMat _ [] = []
addMat (x:xs) (y:ys) = zipWith (+) x y : addMat xs ys 

-- c) 
transpose :: Mat a -> Mat a 
transpose ([]:_) = []
transpose m = map head m : transpose (map tail m)

-- 4 
data BTree a = Empty | Node a (BTree a) (BTree a) 

ex :: BTree Int 
ex = Node 3 (Node 4 Empty Empty) (Node 3 Empty Empty) 

-- Substitui todas as ocorrências de x por y na árvore 
replace :: Eq a => BTree a -> a -> a -> BTree a 
replace Empty _ _ = Empty 
replace (Node i e d) v nv 
    |i == v = Node nv (replace e v nv) (replace d v nv)  
    |otherwise = Node i (replace e v nv) (replace d v nv)

-- 5 
-- Árvores binárias de procura 
insere :: Int -> String -> BTree (Int,String) -> BTree (Int,String)
insere n nome Empty = Node (n,nome) Empty Empty
insere n nome (Node (num,name) e d)
    |n == num = Node (num,nome) e d 
    |n<num = Node (num,name) (insere n nome e) d 
    |otherwise = Node (num,name) e (insere n nome d)

