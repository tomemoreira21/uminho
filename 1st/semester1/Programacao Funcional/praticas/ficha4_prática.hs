{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant list comprehension" #-}
import Data.Char 

-- 1
-- Com acumuladores 
digitAlpha :: String -> (String,String)
digitAlpha n = digitAlphaAc n [] [] 
    where 
        digitAlphaAc [] acLetras acNum = (acLetras,acNum)   
        digitAlphaAc (h:t) acLetras acNum |(isAlpha h) = digitAlphaAc t (acLetras ++ [h]) acNum 
                                          |(isDigit h) = digitAlphaAc t acLetras (acNum ++ [h])

-- Usando a recursividade
digitAlpha' :: String -> (String,String)
digitAlpha' [] = ([],[])
digitAlpha' (h:t) |(isAlpha h) = (h:le , ld )
                  |(isDigit h) = (le,h:ld)
                  |otherwise = (le,ld) 
                  where 
                    (le,ld) = digitAlpha' t 

-- 2 
-- Usando a recursividade
nzp :: [Int] -> (Int,Int,Int)
nzp [] = (0,0,0)
nzp (h:t) |(h<0) = (1+negativos,zeros,positivos)
          |(h==0) = (negativos, 1 + zeros, positivos)
          |otherwise = (negativos,zeros,positivos + 1)
          where 
            (negativos,zeros,positivos) = nzp t 

-- Usando acumuladores 
nzp' :: [Int] -> (Int,Int,Int)
nzp' l = nzpAc (0,0,0) l 
    where 
        nzpAc (n,z,p) [] = (n,z,p)
        nzpAc (n,z,p) (h:t) |(h<0) = nzpAc (n+1,z,p) t 
                            |(h==0) = nzpAc (n,z+1,p) t 
                            |otherwise = nzpAc (n,z,p+1) t 

-- 3 
-- Usando apenas a recursividade (fazendo funções auxiliares)
divMod' :: Integral a => a -> a -> (a,a)
divMod' n m = (myDiv n m , myMod n m) 

myMod :: Integral a => a -> a -> a 
myMod n m |(n<m) = n 
          |otherwise = myMod (n-m) m 

myDiv :: Integral a => a -> a -> a
myDiv n m |(n>m) = 1 + myDiv (n-m) m 
          |otherwise = 0

-- Usando apenas a recursividade (usando apenas 1 função) 
myDivMod :: Integral a => a -> a -> (a,a)
myDivMod n m |(n<m) = (0,n)
             |otherwise = (1+q,r)
             where 
                (q,r) = myDivMod (n-m) m 

-- Tentar com acumuladores 
divMod'' :: Integral a => a -> a -> (a,a)
divMod'' n m = divModAc n m (0,0)
    where 
        divModAc n m (div,rest) |(n<m) = (div,n)
                                |otherwise = divModAc (n-m) m (div + 1,rest)

-- 4 
-- 1ºforma 
fromDigits :: [Int] -> Int 
fromDigits l = fromDigitsAc l 0
    where 
        fromDigitsAc [] ac = ac 
        fromDigitsAc (h:t) ac = fromDigitsAc t (ac*10 + h) 

-- 2ºforma 
fromDigits' :: [Int] -> Int 
fromDigits' (h:t) = fromDigitsAc (h:t) (length t)
    where 
        fromDigitsAc [] _ = 0
        fromDigitsAc (x:xs) v = x*(10^v) + fromDigitsAc xs (v-1)

-- 5 
maxSumInit :: (Num a,Ord a) => [a] -> a
maxSumInit l = maxSumInitAc l 0 0 -- um guarda a soma até ao momento 
                                  -- outro guarda o maior
    where 
        maxSumInitAc [] max soma = max  
        maxSumInitAc (h:t) max soma 
            |(h+soma > max) = maxSumInitAc t (h+soma) (h+soma)
            |otherwise = maxSumInitAc t max (h+soma) 
            
-- 6 
fib :: Int -> Int 
fib 0 = 0 
fib n = fibAux 0 1 n -- 0 -> representa o n-ésimo termo    
    where            -- 1 -> representa o n+1-ésimo termo 
        fibAux n1 n2 0 = n1  
        fibAux n1 n2 n = fibAux  (n1+n2) n1 (n-1)

-- 7 
intToStr :: Integer -> String 
intToStr n = aux (converte n) []
    where
        aux :: [Integer] -> String -> String 
        aux [] ac = ac 
        aux (h:t) ac = aux t (ac ++ [intToDigit (fromIntegral h)])

-- recebe por exemplo 123 -> [1,2,3]
converte :: Integer -> [Integer]
converte n = aux n []
    where 
        aux 0 ac = ac 
        aux n ac = aux (div n 10) ((mod n 10):ac)

-- 8 
-- a) [6,12,18]
l1:: [Integer]
l1 = [x | x <- [1..20] , mod x 6 == 0]

-- b) [6,12,18]
l2 :: [Integer]
l2 = [x | x <- [1..20] , even x , mod x 3 == 0]

-- c) [(10,20),(11,19),(12,18),(13,17),(14,16),(15,15),(16,14),(17,13),(18,12),(19,11),(20,10)]
l3 :: [(Integer,Integer)]
l3 = filter (\(x,y) -> x+y == 30) [(x,y) | x<- [0..20] , y <- [0..20]]

-- d) 
duplica :: [Integer] -> [Integer]
duplica [] = []
duplica (h:t) = h:h : duplica t 

l4 :: [Integer]
l4 = duplica [x^2 | x <- [1..5]]

-- 9 
-- a) 
l5 :: [Integer]
l5 = [2^x | x <- [0..10]]

-- b) 
l6 :: [(Integer,Integer)]
l6 = [(x,6-x) | x <- [1..5]]

-- c) 
l7 :: [[Integer]]
l7 = [[1..x] | x <- [1..5]]

-- d) 
l8 :: [[Integer]]
l8 = [replicate n 1 | n <- [1..5]]

-- e) 
l9 :: [Integer]
l9 = [product [y| y <- [1..x]] | x <- [1..6]]

