{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use foldr" #-}
{-# HLINT ignore "Eta reduce" #-}
{-# HLINT ignore "Redundant bracket" #-}
module Ficha5 where 

-- 1 
-- all -> todos os elementos obdecem à condição
-- any -> algum elemento obdece à condição c 
-- a) 

-- 1º forma
any' :: (a->Bool) -> [a] -> Bool 
any' p l = let list = filter p l 
           in not (null list)

-- 2ºforma 
any'' :: (a->Bool) -> [a] -> Bool 
any'' p [] = False 
any'' p (x:xs) = p x || any'' p xs 

-- b) 
zipWith' :: (a->b->c) -> [a] -> [b] -> [c]
zipWith' p (x:xs) (y:ys) = p x y : zipWith' p xs ys 
zipWith' _ _ _ = []

-- c) 
takeWhile' :: (a->Bool) -> [a] -> [a]
takeWhile' _ [] = []
takeWhile' p (x:xs) |(p x) = x : takeWhile' p xs 
                    |otherwise = []

-- d) 
dropWhile' :: (a->Bool) -> [a] -> [a]
dropWhile' _ [] = []
dropWhile' p (x:xs) |p x = dropWhile' p xs 
                    |otherwise = (x:xs)

-- e) 
span' :: (a->Bool) -> [a] -> ([a],[a])
span' p l = spanAc ([],[]) l 
    where 
        spanAc (t,d) [] = (t,d)
        spanAc (t,d) (x:xs) |p x = spanAc (t++[x],d) xs 
                            |otherwise = (t,x:xs)  

-- f) 
deleteBy' :: (a -> a -> Bool) -> a -> [a] -> [a]
deleteBy' _ _ [] = []
deleteBy' f x (h:t) |(f x h) = t 
                    |otherwise = h : deleteBy' f x t 

-- g) 
sortOn' :: Ord b => (a -> b) -> [a] -> [a]
sortOn' _ [] = []
sortOn' f (x:xs) = insere x (sortOn' f xs)
    where 
        insere x [] = [x]
        insere x (h:t) |(f x < f h) = x:h:t
                       |otherwise = h : insere x t  

-- 2 
type Polinomio = [Monomio]
type Monomio = (Float,Int)

-- a) 
selgrau :: Int -> Polinomio -> Polinomio 
selgrau grau l = filter (\(c,e) -> grau == e) l 

-- b) 
conta :: Int -> Polinomio -> Int 
conta n p = foldr aux 0 p  
    where 
        aux (c,e) ac = if e == n then ac + 1 else ac

-- c) 
-- com map
grau :: Polinomio -> Int 
grau l = let list = map snd l 
         in maximum list  

-- com fodr
grau' :: Polinomio -> Int 
grau' ((_,e):t) = foldr (\(_,e1) ac -> max ac e1) e t 

-- d) 
deriv' :: Polinomio -> Polinomio
deriv' l = filter (\(c,e) -> c /= 0) (map (\(c,e) -> ((fromIntegral e)*c,e-1)) l)

-- e) 
-- 1ºforma
calcula :: Float -> Polinomio -> Float 
calcula x l = let list = map (\(c,e) -> c*(x^e)) l 
              in sum list 

-- 2ºforma 
calcular :: Float -> Polinomio -> Float 
calcular x l = foldr (\(c,e) r -> c*(x^e) + r) 0 l 

-- f) 
simp :: Polinomio -> Polinomio 
simp l = filter (\(c,e) -> e /= 0) l 

-- g) 
mult' :: Monomio -> Polinomio -> Polinomio
mult' (x,y) m = map (\(c,e) -> (x*c,y+e)) m 

-- h) 
-- 1ºforma
ordena :: Polinomio -> Polinomio 
ordena l = sortOn' snd l 

-- 2ºforma
ordenar :: Polinomio -> Polinomio 
ordenar [] = []
ordenar p = foldr insere [] p
    where 
        insere :: Monomio -> Polinomio -> Polinomio
        insere m [] =  [m]
        insere (x,y) ((c,e):t) |(y<e) = (x,y) : ((c,e):t)
                               |otherwise = (c,e) : insere (x,y) t 

-- i) 
normaliza :: Polinomio -> Polinomio 
normaliza [] = []
normaliza p = let po@((c,e):t) = ordena p 
                  (le,ld) = span (\(c1,e1) -> e1==e) po 
                  cf = sum (map fst le)
             in (cf,e) : normaliza ld  
 
-- j) 
soma :: Polinomio -> Polinomio -> Polinomio 
soma m1 m2 = normaliza (m1++m2)

-- k) 
produto :: Polinomio -> Polinomio -> Polinomio 
produto ((c,e):t) p = normaliza (mult' (c,e) p ++ produto t p)
produto _ _ = []

-- l ) 
equiv :: Polinomio -> Polinomio -> Bool 
equiv m1 m2 = normaliza m1 == normaliza m2 

-- 3 
type Mat a = [[a]]

-- a) 
dimOK :: Mat a -> Bool
dimOK [] = False 
dimOK (l:rm) = let n = length l 
               in all (\x -> length x == n) rm  

-- b) 
dimMat :: Mat a -> (Int,Int)
dimMat [] = (0,0)
dimMat l@(m:t) |dimOK l = (length m, length l)
               |otherwise = error "matriz invalida"

-- c)
-- 1ºforma  
addMat :: Num a => Mat a -> Mat a -> Mat a 
addMat (m1:mt1) (m2:mt2) = somalinhas m1 m2 : addMat mt1 mt2
addMat _ _ = []

somalinhas :: Num a => [a] -> [a] -> [a]
somalinhas l1 l2 = zipWith' (+) l1 l2 

-- 2ºforma
addMat' :: Num a => Mat a -> Mat a -> Mat a
addMat' m1 m2 = zipWith' (zipWith' (+)) m1 m2 

-- d) 
transposeM :: Mat a -> Mat a 
transposeM ([]:_) = []
transposeM m1 = (map head m1) : transposeM (map tail m1)

-- e)
multMat' :: Num a => Mat a -> Mat a -> Mat a
multMat' l [] = []
multMat' [] l = [] 
multMat' m1 m2 = multAux m1 m2' 
    where 
        m2' = transposeM m2 

multAux :: Num a => Mat a -> Mat a -> Mat a 
multAux [] _ = []
multAux (l1:m1) m2 = l' : multAux m1 m2 
    where 
        l' = multL l1 m2 
        multL :: Num a => [a] -> Mat a -> [a] 
        multL l m2 = foldr (\l2 acc -> (sum $ zipWith' (*) l l2) : acc) [] m2 

-- f) 
zipWMat :: (a -> b -> c) -> Mat a -> Mat b -> Mat c
zipWMat f m1 m2 = zipWith' (zipWith' f) m1 m2 

-- g) 
triSup :: (Num a,Eq a) => Mat a -> Bool 
triSup m = all (==0) abaixo_diagonal
    where 
        abaixo_diagonal = retira m 0 

retira :: Mat a -> Int -> [a]
retira [] _ = []
retira (x:xs) n = take n x ++ retira xs (n+1)

-- h) 
rotateLeft :: Mat a -> Mat a 
rotateLeft ([]:_) = []
rotateLeft m = map last m : rotateLeft (map init m)

