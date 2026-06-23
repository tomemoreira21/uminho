{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use map" #-}
{-# HLINT ignore "Eta reduce" #-}
import Data.Char (toUpper, isLower)
{-# HLINT ignore "Move guards forward" #-}

-- Funções com parâmetros de acumulação
-- Função sum 
sum :: [Int] -> Int 
sum l = sumAc l 0 -- 0 corresponde ao valor inicial do acumulador 
    where 
        sumAc [] ac = ac
        sumAc (x:xs) ac = sumAc xs (x+ac)

-- Função reverse 
reverse :: [a] -> [a]
reverse l = reverseAc l []
    where 
        reverseAc [] ac = ac
        reverseAc (x:xs) ac = reverseAc xs (x:ac)

-- Função máximo 
maximo :: Ord a => [a] -> a 
maximo (h:t) = maximoAc t h 
    where 
        maximoAc [] ac = ac 
        maximoAc (x:xs) ac |x>ac = maximoAc xs x  
                           |otherwise = maximoAc xs ac  

-- Função fatorial 
factorial :: Integer -> Integer 
factorial n = factorialAc n 1
    where 
        factorialAc 0 ac = 1 
        factorialAc n ac |(n>0) = factorialAc (n-1) (n*ac)

-- Listas em compreensão 
-- exemplo de {1,3,7}
l1 :: [Integer]
l1 = [x | x <- [1,3,7]]

-- exemplo de {-3,4,8} intersetar com 0<=n<=10
l2 :: [Integer]
l2 = [n | n <- [3,-4,8], n >= 0 , n <=10]      -- ',' funciona como interseção

-- Faz o seguinte : [(1,1),(1,2),(2,1),(2,2),(3,1),(3,2)]
l3 :: [(Integer, Integer)]
l3 = [(x,y) | x <- [1,2,3], y <- [1,2]]

-- Faz o reverse normal 
reverse' :: [Int] -> [Int]
reverse' l = [l !! (length l - x) | x <- [1..length l]]

-- Faz o qsort 
qsort' :: Ord a => [a] -> [a]
qsort' [] = []
qsort' (x:xs) = qsort' [a | a <- xs, a<x] ++ [x] ++ qsort' [b | b <- xs, b>=x]

-- Faz a lista dos divisores de um número n
divisores :: Int -> [Int]
divisores n = [x | x <- [1..n], mod n x == 0]

-- Verifica se é primo, ou seja, lista divisores = [n,1]
primo :: Int -> Bool
primo n = divisores n == [1,n]

-- Dá os primos de 1 até n 
primosAte :: Int -> [Int]
primosAte n = [x | x <-[1..n], primo x]

-- Funções de Ordem Superior 
-- faz o seguinte : [1,2,3] -> [2,3,4]
incremento :: [Int] -> [Int]
incremento [] = []
incremento (x:xs) = (x+1): incremento xs 

-- faz o seguinte : "abbc" -> "ABBC"
maiusculas :: String -> String 
maiusculas [] = []
maiusculas (x:xs) = toUpper x : maiusculas xs 

-- faz o seguinte : [(1,2),(3,4),(5,5)] -> [3,7,10]
somaPares :: [(Int,Int)] -> [Int] 
somaPares [] = []
somaPares (x:xs) = aux x : somaPares xs 
    where 
        aux (a,b) = a + b

-- Função map (map (<para aplicar>) lista)
map' :: (a -> b) -> [a] -> [b]
map' f [] = []
map' f (x:xs) = f x : map' f xs

-- Rescrever as funções 
incremento' :: [Int] -> [Int]
incremento' l = map' (+1) l 

maiusculas' :: String -> String 
maiusculas' l = map' (toUpper) l 

somaPares' :: [(Int,Int)] -> [Int]
somaPares' l = map' aux l 
        where 
            aux (x,y) = x + y

-- Reescrever as funções
-- faz o seguinte : [1,-4,0-7,8] -> [1,8] 
positivos :: [Int] -> [Int]
positivos [] = []
positivos (x:xs) |(x>0) = x: positivos xs
                 |otherwise = positivos xs 

-- faz o seguinte "AbbA" -> "bb"
minusculas :: String -> String 
minusculas [] = []
minusculas (x:xs) |(isLower x) = x: minusculas xs 
                  |otherwise = minusculas xs 

-- Função filter (filter (<condição>) lista)
filter' :: (a -> Bool) -> [a] -> [a]
filter' f [] = []
filter' f (x:xs) |f x = x : filter' f xs 
                 |otherwise = filter' f xs 

positivos' :: [Int] -> [Int]
positivos' l = filter' (>0) l 

minusculas' :: String -> String 
minusculas' l = filter' (isLower) l 

-- Funções anónimas 
-- filtra triplos de inteiros cuja a a soma seja maior do que 20 
-- Forma antiga 
triplos' :: [(Int,Int,Int)] -> [(Int,Int,Int)] 
triplos' [] = []
triplos' ((x,y,z):xs) |(x+y+z > 20) = (x,y,z) : triplos' xs 
                      |otherwise = triplos' xs 
   
-- Forma nova 
triplos :: [(Int,Int,Int)] -> [(Int,Int,Int)]
triplos [] = []
triplos l = filter' (\(a,b,c) -> a+b+c > 20) l 

-- Funções de ordem superior 
