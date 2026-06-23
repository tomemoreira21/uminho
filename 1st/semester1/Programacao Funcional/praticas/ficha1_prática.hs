{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use camelCase" #-}
{-# HLINT ignore "Redundant bracket" #-}
{-# HLINT ignore "Use guards" #-}
{-# HLINT ignore "Use max" #-}
{-# HLINT ignore "Eta reduce" #-}
{-# HLINT ignore "Use record patterns" #-}

module Ficha1 where 
import Data.Char 

-- 1 (a)
perimetro1 :: Double -> Double
perimetro1 r = 2*pi*r

-- 1 (b)
dist :: (Double,Double) -> (Double,Double) -> Double
dist (x1,y1) (x2,y2) = sqrt ((x1-x2)^2 + (y1-y2)^2)

-- 1 (c)
primUlt :: [a] -> (a,a)
primUlt list1 = (head (list1),last (list1))

-- 1 (d) primeira forma
multiplo :: Int -> Int -> String
multiplo m n =
    if mod m n == 0
    then "True"
    else "False"

-- 1 (d) segunda forma
multiplo2 :: Int -> Int -> Bool
multiplo2 m1 n1 = mod m1 n1 == 0

-- 1 (e)
truncaImpar :: [a] -> [a]
truncaImpar lista1 =
    if odd (length lista1)
    then tail lista1
    else lista1

-- 1 (f)
max2 :: Int -> Int -> Int
max2 n1 n2 =
    if n1 > n2 then n1 else n2

-- 1 (g) sem usar max2
max3 :: Int -> Int -> Int -> Int
max3 a b c =
    if a>b then (if a>c then a else c)
           else(if b>c then b else c)

-- 1 (g) usando max2
max3' :: Int -> Int -> Int -> Int
max3' x y z = max2 (max2 x y) z

-- 2 (a) 1ºversão
nRaizes :: Double -> Double -> Double -> Int
nRaizes a1 b1 c1 =
    let delta = b1^2 - 4*a1*c1
    in if delta > 0 then 2 else if delta<0 then 0 else 1

-- 2 (a) 2ºversão (com guardas)
nRaizes' :: Double -> Double -> Double -> Int
nRaizes' x1 y1 z1
    | d>0 = 2
    | d==0 = 1
    | d<0 = 0
    where d = y1^2 -4*x1*z1

-- 2 (b)
raizes :: Double -> Double -> Double -> [Double]
raizes a' b' c'
    | nRaizes' a' b' c'==0 = []
    | nRaizes' a' b' c'==1 = [r]
    | nRaizes' a' b' c'==2 = [r1,r2]
    where
        r = -b'/(2*a')
        r1 = (-b' + sqrt (b'^2 - 4*a'*c'))/(2*a')
        r2 = (-b' - sqrt (b'^2 - 4*a'*c'))/(2*a')

-- 3 (a)
type Hora = (Int,Int)
hora_válida :: Hora -> Bool 
hora_válida (h,m) = (h>=0 && h<=23) && (m>=0 && m<60) 
   

-- 3 (b)
-- Dá True se o 1º é maior
-- Dá False caso contrário
comp_hora :: Hora -> Hora -> Bool
comp_hora (h1,m1) (h2,m2)
    |(h1==h2) = m1>m2    
    |otherwise = h1>h2

-- 3 (c)
hora_minuto :: Hora -> Int
hora_minuto (h,m) = h*60 + m
    
-- 3 (d)
minuto_hora :: Int -> Hora 
minuto_hora m = (div m 60, mod m 60)

-- 3 (e)
dif_hora :: Hora -> Hora -> Int 
dif_hora (h1,m1) (h2,m2) = abs(hora_minuto(h1,m1) - hora_minuto(h2,m2))    

-- 3 (f)
add_min :: Hora -> Int -> Hora
add_min (h,m) minu = minuto_hora (totalminu)
    where 
        totalminu = hora_minuto (h,m) + minu
        
-- 4. (a)
data Hora_Novo = H Int Int deriving (Show,Eq)
hora_válida2 :: Hora_Novo -> Bool 
hora_válida2 (H h m) = (h>=0 && h<24) && (m>=0 && m<60) 


-- 4 (b)
-- Dá True se o 1º é maior
-- Dá False caso contrário
comp_hora2 :: Hora_Novo -> Hora_Novo -> Bool 
comp_hora2 (H h1 m1) (H h2 m2) 
        |(h1 == h2) = m1 > m2 
        |otherwise = h1>h2 

-- 4 (c)
hora_minuto2 :: Hora_Novo -> Int  
hora_minuto2 (H h m) = h*60 + m 

-- 4 (d)
minuto_hora2 :: Int -> Hora_Novo 
minuto_hora2 m = H (div m 60) (mod m 60)

-- 4 (e)
dif_hora2 :: Hora_Novo -> Hora_Novo -> Int  
dif_hora2 (H h1 m1) (H h2 m2) = abs(hora_minuto2(H h1 m1) - hora_minuto2(H h2 m2))

-- 4 (f)
add_min2 :: Hora_Novo -> Hora_Novo -> Hora_Novo  
add_min2 (H h1 m1) (H h2 m2) = H (div todomin 60) (mod todomin 60)
    where 
        todomin = hora_minuto2(H h1 m1) + hora_minuto2(H h2 m2)

-- 5. (a)
data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq)
next :: Semaforo -> Semaforo 
next Verde = Amarelo 
next Amarelo = Vermelho 
next Vermelho = Verde    

-- 5. (b) 
stop :: Semaforo -> Bool 
stop Vermelho = True 
stop _        = False 

-- 5. (c) 
safe :: Semaforo -> Semaforo -> Bool 
safe m o = stop m || stop o
    
-- 6.
data Ponto = Cartesiano Double Double |
             Polar Double Double deriving (Show,Eq)

-- 6. (a)
posx :: Ponto -> Double 
posx (Cartesiano x y) = abs(x)
posx (Polar l ang) = abs(cos(ang) * l)

-- 6 (b)
posy :: Ponto -> Double 
posy (Cartesiano x y) = abs(y)
posy (Polar l ang) = abs(sin(ang) * l) 

-- 6 (c)
raio :: Ponto -> Double 
raio (Cartesiano x y) = sqrt(x^2 + y^2)
raio (Polar l ang) = l 

-- 6 (d)
angulo :: Ponto -> Double 
angulo (Cartesiano x y) = atan2 y x 
angulo (Polar l ang) = ang 

-- 6 (e)
dist2 :: Ponto -> Ponto -> Double 
dist2 (Cartesiano x1 y1) (Cartesiano x2 y2) = sqrt ((x1-x2)^2 + (y1-y2)^2)
dist2 (Polar l ang1) (Cartesiano x1 y1) = sqrt ((x1-l*cos(ang1))^2 + (y1-l*sin(ang1))^2)
dist2 (Cartesiano x1 y1) (Polar l ang1) = sqrt ((x1-l*cos(ang1))^2 + (y1-l*sin(ang1))^2) 
dist2 (Polar l1 ang1) (Polar l2 ang2) = sqrt ((l1*cos(ang1) - l2*cos(ang2))^2 + (l1*sin(ang1)-l2*sin(ang2))^2) 

-- 7. 
data Figura = Circulo Ponto Double 
            | Rectangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto 
            deriving (Show,Eq) 

-- 7. (a)
poligono :: Figura -> Bool 
poligono (Circulo _ _ ) = False
poligono (Rectangulo _ _ ) = True 
poligono (Triangulo _ _ _) = True 

-- 7. (b)
vertices :: Figura -> [Ponto] 
vertices (Circulo _ _) = []
vertices (Rectangulo p1 p2) = [p1,p2]
vertices (Triangulo p1 p2 p3) = [p1,p2,p3]

-- 7. (c)
area :: Figura -> Double
area (Triangulo p1 p2 p3) =
    let a = dist2 p1 p2
        b = dist2 p2 p3
        c = dist2 p3 p1
        s = (a+b+c) / 2 
    in sqrt (s*(s-a)*(s-b)*(s-c))
area (Circulo p1 r) = pi*r*r 
--area (Rectangulo p1 p2) = 
    
-- 7. (d)
perimetro :: Figura -> Double 
perimetro (Circulo c r) = 2*pi*r 
perimetro (Triangulo p1 p2 p3) = (dist2 p1 p2) + (dist2 p1 p3) + (dist2 p2 p3)
-- perimetro (Rectangulo p1 p2) = 
    
-- 8. (a)
isLower' :: Char -> Bool 
isLower' c = ord c >=97 && ord c<=122 

-- 8 (b)
isDigit' :: Char -> Bool 
isDigit' c = ord c >=48 && ord c<=57

-- 8 (c)
isAlpha' :: Char -> Bool 
isAlpha' c =  (ord c>=65 && ord c<=90) || (ord c>=97 && ord c<=122)

-- 8 (d)
toUpper' :: Char -> Char 
toUpper' c = chr (letra_min - 32)
    where 
        letra_min = ord c 

-- 8 (e)
intToDigit' :: Int -> Char 
intToDigit' n =  chr(ord(chr n) + 48)
 
-- 8 (f)
digitToInt' :: Char -> Int 
digitToInt' d = ord(d) - 48
