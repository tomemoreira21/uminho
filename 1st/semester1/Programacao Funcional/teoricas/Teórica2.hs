{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use camelCase" #-}
{-# HLINT ignore "Redundant bracket" #-}
{-# HLINT ignore "Use list literal" #-}
{-# HLINT ignore "Use foldr" #-}

-- Maybe 
-- data Maybe a = Nothing | Just a
-- 1ºforma
myDiv :: Int -> Int -> Maybe Int 
myDiv x y = if y==0 then Nothing else Just(div x y)

-- 2ºforma 
myDiv2 :: Int -> Int -> Maybe Int 
myDiv2 x 0 = Nothing 
myDiv2 x y = Just (div x y)

-- Somar valores do Maybe 
-- 1º forma
myAdd :: Maybe Int -> Maybe Int -> Maybe Int 
myAdd Nothing Nothing = Nothing 
myAdd Nothing (Just y) = Nothing 
myAdd (Just x) Nothing = Nothing
myAdd (Just x) (Just y) = Just (x+y)

-- 2º forma (mais simples)
myAdd2 :: Maybe Int -> Maybe Int -> Maybe Int 
myAdd2 (Just x) (Just y) = Just (x+y)
myAdd2 _ _ = Nothing 

-- Se for Nothing dá False senão se for Just dá True (1ºforma)
isJust2 :: Maybe a -> Bool 
isJust2 Nothing = False 
isJust2 (Just _) = True 

-- 2ºforma (usando o case ... of)
isJust3 :: Maybe a -> Bool 
isJust3 m = case m of 
                Nothing -> False 
                Just _ -> True 

-- Função fatorial com guardas ou sem
-- 1º forma 
fatorial :: Int -> Int
fatorial 0 = 1
fatorial n = n* fatorial(n-1)

-- 2º forma (com guardas)
fatorial2 :: Int -> Int 
fatorial2 0 = 1
fatorial2 n |(n>0) = n* fatorial2 (n-1)
            |otherwise = error "oops"
    
-- 3º forma (com maybe)
multComMaybe :: Int -> Maybe Int -> Maybe Int 
multComMaybe n (Just x) = Just (n*x)

fatorial3 :: Int -> Maybe Int 
fatorial3 0 = Just 1
fatorial3 n = if n>0 then multComMaybe n (fatorial3 (n-1)) else Nothing

-- Listas
-- Adicionar valores à lista
list :: [Int] -> [Int]
list [] = 1:2:3:[]

list_tuplas :: [Int] -> [(Int,Int)]
list_tuplas [] = (1,2):(4,5):[]

-- Funções simples de listas 
-- Definir o head 
head :: [a] -> a
head (x:xs) = x   -- x -> representa o primeiro elemento
                  -- xs -> é o restante da lista         

-- Definir o tail 
tail :: [a] -> [a]
tail (x:xs) = xs 

-- Definir o null (serve para testar se a lista está vazia) (1ºforma)
null :: [a] -> Bool 
null [] = True 
null (x:xs) = False 

-- Definir o null (usando o case ... of) (2ºforma)
null2 :: [a] -> Bool 
null2 l = case l of 
            [] -> True 
            (x:xs) -> False 
 
-- Definir a soma dos 3 primeiros elementos da lista (1ºforma)
soma3 :: [Int] -> Int 
soma3 (x:y:z:t) = x+y+z     -- x -> corresponde ao 1ºelemento da lista 
soma3 (x:y:t) = x+y         -- y -> corresponde ao 2ºelemento da lista 
soma3 (x:t) = x             -- z -> corresponde ao 3ºelemento da lista         
soma3 [] = 0                -- t -> é o restante da lista    

-- 2ºforma 
soma3_ :: [Int] -> Int 
soma3_ [x] = x             -- funciona para listas com exatamente 1 elemento
soma3_ [x,y] = x+y         -- funciona para listas com exatamente 2 elementos
soma3_ l = sum (take 3 l)  -- funciona para listas com exatamente 3 elementos

-- 3ªforma (usando o case ... of)
soma3__ :: [Int] -> Int 
soma3__ l = case l of 
                (x:y:z:t) -> x+y+z 
                (x:y:t) -> x+y 
                (x:t) -> x 
                [] -> 0 

-- Funções recursivas 
-- Definir o length 
length' :: [a] -> Int 
length' [] = 0 
length' (x:xs) = 1 + length' xs

-- Definir o sum 
sum' :: Num a => [a] -> a 
sum' [] = 0
sum' (x:xs) = x + sum' xs 

-- Definir o elem 
elem' :: Eq a => a -> [a] -> Bool 
elem' x [] = False 
elem' x (y:ys) |(x==y) = True 
               |otherwise = elem' x ys