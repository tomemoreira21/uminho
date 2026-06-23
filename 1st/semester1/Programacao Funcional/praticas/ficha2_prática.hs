{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use foldr" #-}
{-# HLINT ignore "Redundant bracket" #-}
{-# HLINT ignore "Use even" #-}
{-# HLINT ignore "Use foldl" #-}
{-# HLINT ignore "Eta reduce" #-}
{-# HLINT ignore "Use infix" #-}
{-# HLINT ignore "Use map" #-}
{-# HLINT ignore "Use camelCase" #-}
import Data.Char 
-- 1 a)
funA :: [Double] -> Double
funA [] = 0
funA (y:ys) = y^2 + (funA ys)

-- funA [2,3,5,1] = (2:[3,5,1]) 
-- = 2² + funA [3,5,1] = 2² + 3² + funA [5,1]
-- = 2² + 3² + 5² + funA [1] 
-- = 2² + 3² + 5² + 1² + funA []
-- = 2² + 3² + 5² + 1² + 0 = 39 

-- 1 b) 
funB :: [Int] -> [Int]
funB [] = []
funB (h:t) = if (mod h 2)==0 then h : (funB t)
                             else (funB t)

-- funB [8,5,12] = [8,12]: 
-- funB (8:[5,12]) = 8 : funB [5,12]
--                 = 8 : funB [12]
--                 = 8 : 12
--                 = [8,12]

-- 1 c) 
funC :: [a] -> [a]
funC (x:y:t) = funC t
funC [x] = [x]
funC [] = []

-- funC [1,2,3,4,5] = 1:2:[3,4,5] 
--                  = funC [3,4,5]
--                  = 3:4:[5]
--                  = funC [5]
--                  = [5]

-- 1 d) 
funD :: [a] -> [a]
funD l = g [] l
g :: [a] -> [a] -> [a]
g acc [] = acc
g acc (h:t) = g (h:acc) t 

-- funD "otrec" = g [] "otrec"
--              = g [] ('o':"trec")
--              = g ('o':[]) "trec"
--              = g "o" "trec"
--              = g "o" ('t':"rec")
--              = g "o" "t" "rec"
--              = vai dar "certo" 

-- 2 a) 
dobros :: [Float] -> [Float] 
dobros l = case l of 
            [] -> []
            (x:xs) -> 2*x : dobros xs 

-- 2 b) 
numOcorre :: Char -> String -> Int 
numOcorre ch [] = 0
numOcorre ch (x:xs) 
    |(elem ch (x:xs)) = if ch == x then 1 + numOcorre ch xs else numOcorre ch xs  
    |otherwise = 0

-- 2 c) 
positivos :: [Int] -> Bool 
positivos [] = True
positivos (x:xs) = x>0 && positivos xs  
    
-- 2 d) 
soPos :: [Int] -> [Int]
soPos [] = []
soPos (x:xs) 
    |(x<0) = soPos xs 
    |otherwise = x : soPos xs

-- 2 e) 
somaNeg :: [Int] -> Int 
somaNeg [] = 0
somaNeg (x:xs) 
    |(x<0) = x + somaNeg xs
    |otherwise = somaNeg xs

-- 2 f)
tresUlt :: [a] -> [a]
tresUlt [] = []
tresUlt (x:xs)
    |(length (x:xs) <= 3) = (x:xs)
    |otherwise = tresUlt xs

-- 2 g) 
segundos :: [(a,b)] -> [b]
segundos [] = []
segundos (x:xs) = snd x : segundos xs

-- 2 h) 
nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool 
nosPrimeiros n [] = False 
nosPrimeiros n (x:xs) = n == fst (x) || nosPrimeiros n xs

-- 2 i) 
sumTriplos :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos [] = (0,0,0)
sumTriplos l = (sum_primeiro l, sum_segundo l , sum_terceiro l)

sum_primeiro :: (Num a, Num b, Num c) => [(a,b,c)] -> a
sum_primeiro [] = 0
sum_primeiro ((a,b,c):t) = a + sum_primeiro t  

sum_segundo :: (Num a, Num b, Num c) => [(a,b,c)] -> b
sum_segundo [] = 0
sum_segundo ((a,b,c):t) = b + sum_segundo t  

sum_terceiro :: (Num a, Num b, Num c) => [(a,b,c)] -> c
sum_terceiro [] = 0
sum_terceiro ((a,b,c):t) = c + sum_terceiro t  

-- 2 i) (2ºforma mais simples)
sumTriplos' :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos' [] = (0,0,0)
sumTriplos' ((x,y,z):t) = let (sx,sy,sz) = sumTriplos' t 
                          in (x+sx,y+sy,z+sz) 

-- 2 i) (com acumulador)
sumTriplos2 :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
c :: (Num a, Num b, Num c) => (a, b, c) -> [(a, b, c)] -> (a, b, c)
sumTriplos2 l = c (0,0,0) l 
c (sx,sy,sz) [] = (sx,sy,sz)
c (sx,sy,sz) ((x,y,z):t) = c (sx+x,sy+y,sz+z) t       

-- 3 a) 
soDigitos :: [Char] -> [Char]
soDigitos [] = []
soDigitos (x:xs) = if (ord x>=48 && ord x<=57) then x : soDigitos xs else soDigitos xs

-- 3 b) 
minusculas :: [Char] -> Int 
minusculas [] = 0
minusculas (x:xs) 
    |(ord x>=97 && ord x<=122) = 1 + minusculas xs 
    |otherwise = minusculas xs 

-- 3 c)
nums :: String -> [Int] 
nums "" = []
nums (x:xs) 
    |(ord x >= 48 && ord x<=57) = n : nums xs 
    |otherwise = nums xs  
    where 
        n = ord(x) - 48

-- 4 
type Polinomio = [Monomio]
type Monomio = (Float,Int) -- (coeficiente,expoente)

-- 4 a) 
conta :: Int -> Polinomio -> Int 
conta n [] = 0 
conta n ((x,y):t) = if n == y then 1 + conta n t else conta n t 

-- 4 b) 
grau :: Polinomio -> Int
grau [] = 0
grau ((x,y):t) = let resto_valores = grau t 
                 in max y resto_valores

-- 4 c) 
selgrau :: Int -> Polinomio -> Polinomio 
selgrau _ [] = []
selgrau n ((x,y):t) = if n == y then (x,y) : selgrau n t else selgrau n t 

-- 4 d) 
deriv :: Polinomio -> Polinomio
deriv [] = []
deriv ((x,y):t) 
    |(y==0) = (0,0) : deriv t 
    |otherwise = (x_novo,y_novo) : deriv t 
    where 
        x_novo = x*(fromIntegral y) 
        y_novo = y - 1

-- 4 e) 
calcula :: Float -> Polinomio -> Float
calcula n [] = 0
calcula n ((x,y):t) = let soma_outros = calcula n t 
                      in x*(n^y) + soma_outros 

-- 4 f) 
simp :: Polinomio -> Polinomio 
simp [] = []
simp ((x,y):t) = if x == 0 then simp t else (x,y) : simp t 

-- 4 g) 
mult :: Monomio -> Polinomio -> Polinomio 
mult _ [] = []
mult (c1,e1) ((x,y):t) = (c1*x,e1 + y) : mult (c1,e1) t 

-- 4 h) 
normaliza :: Polinomio -> Polinomio 
normaliza [] = []
normaliza p@((x,y):t) = let lista_mesmograu = selgrau y p 
                            lista_graudiferentes = grau_diferentes y p
                            c1 = somacoef lista_mesmograu 
                        in if c1/=0 then (c1,y) : normaliza lista_graudiferentes else normaliza lista_graudiferentes

somacoef :: Polinomio -> Float 
somacoef [] = 0
somacoef ((x,y):t) = x + somacoef t  

grau_diferentes :: Int -> Polinomio -> Polinomio 
grau_diferentes n [] = []
grau_diferentes n ((x,y):t) = if n == y then grau_diferentes n t else (x,y) : grau_diferentes n t 

-- 4 i) 
soma :: Polinomio -> Polinomio -> Polinomio 
soma l1 l2  = normaliza (l1++l2)

-- 4 j) 
produto :: Polinomio -> Polinomio -> Polinomio
produto [] _ = [] 
produto (m:ms) l = normaliza (mult m l ++ produto ms l) 

-- 4 k) 
ordena :: Polinomio -> Polinomio 
ordena [] = []
ordena ((x,y):t) = insert (x,y) (ordena t) 


insert :: Monomio -> Polinomio -> Polinomio 
insert m [] = [m]
insert (c,e) p@((x,y):t_ordenada) |(e<=y) = (c,e) : p 
                                  |otherwise = (x,y) : insert (c,e) t_ordenada 

-- 4 l)
equiv :: Polinomio -> Polinomio -> Bool 
equiv [] _ = False 
equiv _ [] = False 
equiv p1 p2 = ordena(normaliza p1) == ordena(normaliza p2)

