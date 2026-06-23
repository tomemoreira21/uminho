{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
import Data.Char (toUpper)
import Data.List (sortOn)
{-# HLINT ignore "Eta reduce" #-}
data Frac = F Integer Integer
-- 1 
-- a) 
normaliza :: Frac -> Frac 
normaliza (F n d) = F (s*n') d' 
    where
        n' = div (abs n) m 
        d' = div (abs d) m 
        m = mdc (abs n) (abs d) 
        s = if n*d<0 then -1 else 1  
        
-- y/=0 e x,y > 0   
mdc :: Integer -> Integer -> Integer 
mdc x y |x==0 || y == 0 = 1  
        |x==y = x 
        |x < y = mdc x (y-x)
        |x > y = mdc (x-y) y 

-- b) 
eqFrac :: Frac -> Frac -> Bool 
eqFrac t1 t2 = n1 == n2 && d1 == d2 
    where 
        (F n1 d1) = normaliza t1 
        (F n2 d2) = normaliza t2  

instance Eq Frac where 
    (==) = eqFrac 

-- c) 
ordFrac :: Frac -> Frac -> Bool 
ordFrac (F n1 d1) (F n2 d2) = let (F n1' d1') = normaliza (F n1 d1) 
                                  (F n2' d2') = normaliza (F n2 d2) 
                              in n1'*d2' <= n2'*d1' 

instance Ord Frac where 
    (<=) = ordFrac

-- d) 
instance Show Frac where 
    show (F n 1) = show n 
    show (F n d) = show n ++ "/" ++ show d 

-- e) 
instance Num Frac where 
    (F n1 d1) + (F n2 d2) = normaliza (F (n1*d2 + n2*d1) (d1*d2))
    (F n1 d1) * (F n2 d2) = normaliza (F (n1*n2) (d1*d2))
    (F n1 d1) - (F n2 d2) = normaliza (F (n1*d2 - n2*d1) (d1*d2))
    abs (F n d) = F (abs n) (abs d)
    signum (F n d) |n==0 = F 0 1 
                   |n*d < 0 = F (-1) 1 
                   |n*d > 0 = F 1 1 
    fromInteger n = F n 1 

-- f) 
maioresDobro :: Frac -> [Frac] -> [Frac]
maioresDobro f l = filter (\f' -> f' > 2*f) l

-- 2 
data Exp a = Const a
            | Simetrico (Exp a)
            | Mais (Exp a) (Exp a)
            | Menos (Exp a) (Exp a)
            | Mult (Exp a) (Exp a)

-- a) 
instance Show a => Show (Exp a) where
    show (Const a) = show a 
    show (Simetrico l) = "-" ++ show l 
    show (Mais l1 l2) = "(" ++ show l1 ++ " + " ++ show l2 ++ ")"
    show (Menos l1 l2) = "(" ++ show l1 ++ " - " ++ show l2 ++ ")" 
    show (Mult l1 l2) = "(" ++ show l1 ++ " * " ++ show l2 ++ ")" 

-- b) 
instance (Num a,Eq a) => Eq (Exp a) where 
    t1 == t2 = calcula t1 == calcula t2 

calcula :: (Eq a,Num a) => Exp a -> a 
calcula k = case k of 
            Const x -> x 
            Simetrico e -> (-1) * calcula e 
            Mais e1 e2 -> calcula e1 + calcula e2 
            Menos e1 e2 -> calcula e1 - calcula e2 
            Mult e1 e2 -> calcula e1 * calcula e2 

-- c) 
instance (Eq a ,Num a) => Num (Exp a) where 
    t1 + t2 = Const (calcula t1 + calcula t2) 
    t1 - t2 = Const (calcula t1 - calcula t2)
    t1 * t2 = Const (calcula t1 * calcula t2)
    signum e = Const (signum (calcula e)) 
    abs e = Const (abs (calcula e))
    fromInteger n = Const (fromInteger n) 

-- 3 
data Movimento = Credito Float | Debito Float
data Data = D Int Int Int -- dia, mes e ano
data Extracto = Ext Float [(Data, String, Movimento)]

-- a) 
instance Eq Data where 
    (==) (D d1 m1 a1) (D d2 m2 a2) = (a1,m1,d1) == (a2,m2,d2)

instance Ord Data where 
    (<=) (D d1 m1 a1) (D d2 m2 a2) = (a1,m1,d1) <= (a2,m2,d2)

-- b) 
instance Show Data where 
    show (D d m a) |(m<10) = show d ++ "/0" ++ show m ++ "/" ++ show a 
                   |otherwise = show d ++ "/" ++ show m ++ "/" ++ show a 

-- c) 
ordena :: Extracto -> Extracto 
ordena (Ext si lm) = Ext si (sortOn (\(dat,_,_) -> dat) lm)  

-- d)
e :: Extracto
e = Ext 300 [(D 11 8 2012,"Deposito",Credito 2000),
              (D 10 8 2012,"Compra",Debito 37.5),
              (D 1 9 2010,"Lev",Debito 60),
              (D 7 1 2011,"Juros",Credito 100), 
              (D 22 1 2011,"Anuidade",Debito 8)
             ]

saldoInicial :: Extracto -> String 
saldoInicial (Ext i _) = "Saldo anterior: " ++ show i 

cabecalho :: Extracto -> String 
cabecalho e = d ++ replicate (15 - length d) ' ' ++ desc ++ replicate (15 - length desc) ' ' ++ c ++ replicate (15 - length c) ' ' ++ deb ++ replicate (15 - length deb) ' ' 
            where 
                d = "Data"
                desc = "Descricao"
                c = "Credito"
                deb = "Debito"

descricao :: String -> String 
descricao d = let str = if length d > 15 then take 8 d ++ "..." ++ replicate 4 ' ' else d ++ replicate (15-length d) ' '
              in map toUpper str 

aux :: (Data,String,Movimento) -> String 
aux (d,desc,mov) = show d ++ replicate (15-length (show d)) ' ' ++ descricao desc ++ cond mov ++ "\n"
    where 
        cond :: Movimento -> String 
        cond k = case k of 
            Credito x -> show x ++ replicate (15-length (show x)) ' ' ++ replicate 15 ' ' 
            Debito x -> replicate 15 ' ' ++ show x ++ replicate (15-length (show x)) ' '

conteudo :: Extracto -> String 
conteudo (Ext i e) = concat (map aux e) 

aux2 :: Extracto -> Float 
aux2 (Ext i e) = foldr f' i e 
    where 
        f' (d,desc,mov) acc = case mov of 
                Credito x -> acc + x
                Debito x -> acc - x  
                    
saldoFinal :: Extracto -> String 
saldoFinal e = "Saldo actual: " ++ show (aux2 e)  

showExtracto :: Extracto -> String 
showExtracto e = saldoInicial e ++ "\n"
                 ++ replicate 60 '-' ++ "\n"
                 ++ cabecalho e ++ "\n"
                 ++ replicate 60 '-' ++ "\n"
                 ++ conteudo e 
                 ++ replicate 60 '-' ++ "\n"
                 ++ saldoFinal e 

instance Show Extracto where 
    show = showExtracto