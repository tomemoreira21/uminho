{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Eta reduce" #-}
{-# HLINT ignore "Use foldr" #-}

-- Soma pares [(1,2),(2,2),(3,2)] -> [3,4,5]
somaPares :: [(Int,Int)] -> [Int]
somaPares l = map cond l 
    where 
        cond (x,y) = x+y

-- Função anónima
somaPares' :: [(Int,Int)] -> [Int]
somaPares' l = map (\(x,y) -> x+y) l 

-- Quadrados [(1,2),(2,2),(3,2)] -> [1,4,9]
quadrados :: [(Int,Int)] -> [Int]
quadrados l = map cond l 
    where 
        cond (x,y) = x^y

-- Função anónima 
quadrados' :: [(Int,Int)] -> [Int]
quadrados' l = map (\(x,y) -> x^y) l 

-- Ficar apenas com os pares cuja soma > 5
pares :: [(Int,Int)] -> [(Int,Int)]
pares l = filter cond l 
    where 
        cond (x,y) = (x+y) > 5

-- Função anónima
pares' :: [(Int,Int)] -> [(Int,Int)]
pares' l = filter (\(x,y) -> x+y > 5) l

-- Função zipWith 
zipWith' :: (a->b->c) -> [a] -> [b] -> [c]
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys 
zipWith' _ _ _ = [] 

-- Função takeWhile takeWhile (>3) [8,10,3,7,2] -> [8,10]
takeWhile' :: (a->Bool) -> [a] -> [a]
takeWhile' f [] = []
takeWhile' f (x:xs) |(f x) = x: takeWhile' f xs 
                    |otherwise = []

-- retirar até obdece a condição de ser maior que 3 
list :: (Num a,Ord a) => [a] -> [a]
list l = takeWhile' (>3) l 

-- Função dropWhile dropWhile (>3) [7,8,1,10] -> [1,10] ; dropWhile (>9) [7,8,1,10] -> [7,8,1,10]
dropWhile' :: (a->Bool) -> [a] -> [a]
dropWhile' f [] = []
dropWhile' f (x:xs) |(f x) = dropWhile' f xs 
                    |otherwise = x:xs

-- Função span
span' :: (a->Bool) -> [a] -> ([a],[a])
span' f l = (takeWhile' f l, dropWhile' f l)

-- Função and 
and' :: [Bool] -> Bool 
and' [] = True 
and' (x:xs) = x && and' xs -- mesma coisa que (&&) x (and' xs)

-- Função sum 
sum' :: [Int] -> Int 
sum' [] = 0 
sum' (x:xs) = x + sum' xs -- mesma coisa que (+) x (sum' xs)

-- Função concat 
concat' :: [[a]] -> [a]
concat' [] = []
concat' (x:xs) = x ++ concat' xs 

-- Outra forma de definir com o foldr (utiliza a associatividade da direita para a esquerda)
foldr' :: (a->b->b) -> b -> [a] -> b 
foldr' f c [] = c 
foldr' f c (x:xs) = f x (foldr' f c xs ) 

-- Definindo o and com foldr 
and'' :: [Bool] -> Bool 
and'' l = foldr (&&) True l 

-- Definindo o sum com foldr 
sum'' :: [Int] -> Int 
sum'' l = foldr (+) 0 l 

-- Definindo o concat com foldr 
concat'' :: [[a]] -> [a]
concat'' l = foldr (++) [] l 

-- raciocinio do foldr 
{- 
sum [1,2,3] -> (+) 1 (foldr (+) 0 [2,3])
            -> 1 + ((+) 2 (foldr (+) [3]))
            -> 1 + (2 + ((+) 3 (foldr 0 [] ))
            -> 1 + (2 + (3+0)) 
            -> 1 +2 +3 = 6  

-}

-- Somatório da 2ºcomponente do par com foldr 
somar :: [(Int,Int)] -> Int 
somar l = foldr (\(x,y) r -> y + r) 0 l -- o r é o resultado da soma até ao 1ºmembro 

-- Length de uma lista com foldr 
length' :: [Int] -> Int 
length' l = foldr (\x r -> 1 + r) 0 l 

-- Reverse de uma lista com foldr 
reverse' :: [a] -> [a]
reverse' l = foldr (\x r -> r ++ [x]) [] l 

-- map -> aplicar uma função a todos os elementos da lista não alterando o tamanho da lista (podendo alterar o tipo) 
-- filter -> devolve uma lista do mesmo tipo, mas com um menor número de elementos 
-- foldr -> calcular um valor apenas através de uma lista 
-- foldl -> utilizar em funções recursivas que usam acumuladores

-- Função foldl (usa a associatividade da esquerda para a direita)
foldl' :: (b -> a -> b) -> b -> [a] -> b 
foldl' f c [] = c 
foldl' f c (x:xs) = foldl' f (f c x) xs  -- (f c x) -> vai funcionar como acumulador 

-- Função sum com foldl vai ser igual a fazer a soma com foldr pois a adição é associativa 
-- Raciocínio com foldl 
{-
sum [1,2,3] -> foldl (+) 0 [1,2,3]
            -> foldl (+) ((+) 0 1) [2,3]
            -> foldl (+) ((+) (0+1) (2)) [3]
            -> foldl (+) ((+) (0+1+2) (3)) []
            -> (((0+1) + 2) +3) 
            -> 6  
-}

-- Função reverse com acumulador 
reverseAc :: [a] -> [a]
reverseAc l = reverseAux l [] 
    where 
        reverseAux [] ac = ac 
        reverseAux (x:xs) ac = reverseAux xs (x:ac)  

-- Função reverse com foldl 
reverse'' :: [a] -> [a]
reverse'' l = foldl (\ac x -> x:ac) [] l -- ac -> representa o acumulador 
                                         -- x -> representa o elemento à cabeça da lista 

