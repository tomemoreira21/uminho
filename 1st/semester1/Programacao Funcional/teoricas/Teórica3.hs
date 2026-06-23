-- Funções recursivas
-- Sum 
sum' :: Num a => [a] -> a
sum' [] = 0
sum' (x:xs) = x + sum' xs

-- Last 
last' :: [a] -> a
last' [x] = x
last' (x:xs) = last' xs 
 
-- Init 
init' :: [a] -> [a]
init' [x] = []
init' (x:xs) = x: init' xs

-- Tail 
tail' :: [a] -> [a]
tail' [x] = [x]
tail' (x:xs) = xs 

-- Concatenar 
concat' :: [a] -> [a] -> [a]
concat' [] l = l
concat' (x1:xs1) l = x1: concat' xs1 l  

-- Reverse
reverse' :: [a] -> [a]
reverse' [] = []
reverse' (x:xs) = reverse' xs ++ [x]

-- Posição (!!)
pos' :: [a] -> Int -> a 
pos' (x:xs) n |n==0 = x
              |(n>0)= pos' xs (n-1)

-- Zip 
zip' :: [a] -> [b] -> [(a,b)]
zip' [] _ = []
zip' _ [] = []
zip' (x1:xs1) (x2:xs2) = (x1,x2) : zip' xs1 xs2 

-- Unzip 
unzip' :: [(a,b)] -> ([a],[b]) 
unzip' [] = ([],[])
unzip' ((x,y):t) = let (e,d) = unzip' t
                   in (x:e,y:d)

-- Recebe uma lista de inteiros [(a1,b1),(a2,b2),(a3,b3)] -> (a1+a2+a3,b1+b2+b3)
-- 1º forma
somas :: [(Int,Int)] -> (Int,Int)
somas [] = (0,0)
somas ((x,y):t) = let (sx,sy) = somas t 
                  in (x+sx,y+sy)

-- 2º forma 
somas' :: [(Int,Int)] -> (Int,Int)
somas' l = (sumfst l, sumsnd l)

sumfst :: [(Int,Int)] -> Int 
sumfst [] = 0
sumfst ((x,y):t) = x + sumfst t

sumsnd :: [(Int,Int)] -> Int 
sumsnd [] = 0
sumsnd ((x,y):t) = y + sumsnd t
 
-- Recebe uma lista ordenada e inserimos um elemento na lista >>> insert 7 [1,2,9] -> [1,2,7,9]
insert :: Ord a => a -> [a] -> [a]
insert n [] = [n]
insert n (x:xs) |(n<x) = n: (x:xs) 
                |otherwise = x: insert n xs 

-- Recebe uma lista e ordena a lista >>> isort [3,5,1] -> [1,3,5]
isort :: Ord a => [a] -> [a]
isort [] = []
isort (x:xs) = insert x (isort xs) 

-- Funcionamento : >>> partes 5 [3,4,8,3,7,1,9] -> ([3,4,3,1],[8,7,9])
partes :: Ord a => a -> [a] -> ([a],[a])
partes _ [] = ([],[])
partes n (x:xs) |(x<n) =  (x:as,ab)
                |otherwise = (as,x:ab)
                where 
                    (as,ab) = partes n xs

-- QuickSort
qsrt :: Ord a => [a] -> [a]
qsrt [] = []
qsrt (x:xs) = qsrt e ++ [x] ++ qsrt d
    where
        (e,d) = partes x xs

-- Dadas duas listas ordenadas produz uma única lista ordenada
merge :: Ord a => [a] -> [a] -> [a]
merge [] l = l 
merge l [] = l
merge (x1:xs1) (x2:xs2) |x1<x2 = x1: merge xs1 (x2:xs2)
                        |otherwise = x2 : merge (x1:xs1) xs2 

-- Ordenar listas 
msort :: Ord a => [a] -> [a]
msort [] = []
msort [x] = [x]
msort l = merge (msort e) (msort d) 
    where 
        (e,d) = splitAt (div (length l) 2) l  


