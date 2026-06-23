{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use foldr" #-}
{-# HLINT ignore "Use camelCase" #-}
{-# HLINT ignore "Redundant bracket" #-}
{-# HLINT ignore "Use :" #-}
{-# HLINT ignore "Redundant ==" #-}

type Poligonal = [Ponto]
type Ponto = (Double,Double)

data Hora = H Int Int deriving Show
type Etapa = (Hora,Hora)
type Viagem = [Etapa]

data Figura = Circulo Ponto Double 
            | Rectangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto 
            deriving (Show,Eq) 

dist :: (Double,Double) -> (Double,Double) -> Double
dist (x1,y1) (x2,y2) = sqrt ((x1-x2)^2 + (y1-y2)^2)
 
area :: Figura -> Double
area (Triangulo p1 p2 p3) =
    let a = dist p1 p2
        b = dist p2 p3
        c = dist p3 p1
        s = (a+b+c) / 2 
    in sqrt (s*(s-a)*(s-b)*(s-c))

-- 1 a) 
horavalida :: Hora -> Bool 
horavalida (H h m) = elem h [0..23] && elem m [0..59]
                             
construida :: Etapa -> Bool 
construida (H h1 m1,H h2 m2) = (h2,m2) > (h1,m1) && horavalida(H h1 m1) && horavalida(H h2 m2)
                             
-- 1 b) 
viagem_valida :: Viagem -> Bool 
viagem_valida [] = True 
viagem_valida [_] = True 
viagem_valida  ((tp,tc):(tp1,tp2):t) = construida (tp,tc) && construida(tc,tp1) && viagem_valida ((tp1,tp2):t)

-- 1 c) 
horapc :: Viagem -> Etapa 
horapc [] = (H 0 0,H 0 0)
horapc l = (fst(head l), snd (last l)) 

-- 1 d) 
viagem_efetiva :: Viagem -> Hora 
viagem_efetiva [] = H 0 0 
viagem_efetiva ((p1,p2):l) = let etapa_unica = minutos_totais p2 - minutos_totais p1
                             in minutos_horas (etapa_unica + minutos_totais(viagem_efetiva l))                             
        
minutos_totais :: Hora -> Int  
minutos_totais (H h1 m1) = h1*60 + m1

minutos_horas :: Int -> Hora 
minutos_horas m = H (div m 60) (mod m 60)

-- 1 e) 
tempo_espera :: Viagem -> Hora 
tempo_espera [] = H 0 0
tempo_espera [(p1,p2)] = H 0 0
tempo_espera ((p1,p2):(p3,p4):t) = let min_espera = minutos_totais p3 - minutos_totais p2
                                  in minutos_horas(min_espera + minutos_totais(tempo_espera ((p3,p4):t)))

-- 1 f) 
tempo_viagem :: Viagem -> Hora 
tempo_viagem [] = H 0 0
tempo_viagem [(p1,p2)] = viagem_efetiva [(p1,p2)]
tempo_viagem l = minutos_horas (minutos_totais(viagem_efetiva l) + minutos_totais(tempo_espera l))

-- 2 a)
comprimento :: Poligonal -> Double 
comprimento [] = 0
comprimento [p1] = 0
comprimento (p1:p2:t) = dist p1 p2 + comprimento t 

-- 2 b) 
-- True -> se for fechada 
-- False -> se for aberta
fechada_aberta :: Poligonal -> Bool 
fechada_aberta [] = False 
fechada_aberta [x] = False 
fechada_aberta ((x1,y1):t) = (x1,y1) == last(t)

-- 2 c) 
triangula :: Poligonal -> [Figura]
triangula [p1,p2,p3] = []
triangula (p1:p2:p3:t) = (Triangulo p1 p2 p3) : triangula (p1:p3:t) 

-- 2 d) 
areadelimitada :: Poligonal -> Double 
areadelimitada l |(length l<=3) = 0
areadelimitada l = let tr = triangula l 
                   in somaareas tr

somaareas :: [Figura] -> Double 
somaareas [] = 0 
somaareas (x:xs) = area x + somaareas xs

-- 2 e) 
mover :: Poligonal -> Ponto -> Poligonal 
mover [(x,y)] (x1,y1) = [(x1,y1)]
mover (h:t) (x1,y1) = let (x,y) = h 
                          distX = x1 - x 
                          distY = y1 - y
                     in (x1,y1) : deslocamento t (distX,distY) 

deslocamento :: Poligonal -> Ponto -> Poligonal
deslocamento [] _ = []
deslocamento ((x,y):t) (dx,dy) = (x+dx,y+dy) : deslocamento t (dx,dy)

-- 2 f) 
zoom :: Double -> Poligonal -> Poligonal 
zoom _ [] = []
zoom _ [p1] = [p1]
zoom e (p1:t) = p1 : zoomAux e (p1:t)

zoomAux :: Double -> Poligonal -> Poligonal 
zoomAux _ [] = []
zoomAux _ [p1] = []
zoomAux e (p1:p2:t) = let (x1,y1) = p1 
                          (x2,y2) = p2 
                          distX = x2-x1 
                          distY = y2-y1 
                          novoX = x1 + distX*e
                          novoY = y1 + distY*e
                      in  (novoX,novoY) : zoomAux e (p2:t)

-- 3 
data Contacto = Casa Integer
              | Trab Integer
              | Tlm Integer
              | Email String
               deriving Show

type Nome = String
type Agenda = [(Nome, [Contacto])]

-- 3 a) 
acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail nome e [] = [(nome,[Email e])]
acrescEmail nome e ((n,contac):t) 
        |(nome == n) = (n,contac ++ [Email e]): t 
        |otherwise = (n,contac) : acrescEmail nome e t 

-- 3 b) 
verEmails :: Nome -> Agenda -> Maybe [String]
verEmails _ [] = Nothing 
verEmails n ((nome,contact):t) 
    |(n==nome) = Just (pegarEmails contact)
    |otherwise = verEmails n t 

pegarEmails :: [Contacto] -> [String] 
pegarEmails [] = []
pegarEmails ((Email x:xs)) = x: pegarEmails xs 
pegarEmails (_:xs) = pegarEmails xs 

-- 3 c) 
consTelefs :: [Contacto] -> [Integer]
consTelefs [] = []
consTelefs ((Casa x):xs) = x: consTelefs xs   
consTelefs ((Trab x):xs) = x: consTelefs xs 
consTelefs ((Tlm x):xs) = x: consTelefs xs 
consTelefs (_:xs) = consTelefs xs 

-- 3 d) 
casa :: Nome -> Agenda -> Maybe Integer 
casa _ [] = Nothing 
casa n ((nome,contac):t) 
    |(n==nome) = casaTelefs contac 
    |otherwise = casa n t 

casaTelefs :: [Contacto] -> Maybe Integer
casaTelefs [] = Nothing  
casaTelefs ((Casa x):t) = Just(x)  
casaTelefs ((_:t)) = casaTelefs t 

-- 4 
type Dia = Int
type Mes = Int
type Ano = Int
data Data = D Dia Mes Ano deriving Show
type TabDN = [(Nome,Data)]

-- 4 a) 
procura :: Nome -> TabDN -> Maybe Data 
procura _ [] = Nothing 
procura n ((nome,d):t) 
    |(n==nome) = Just d
    |otherwise = procura n t 

-- 4 b) 
idade :: Data -> Nome -> TabDN -> Maybe Int 
idade _ _ [] = Nothing 
idade dA nome ((n,d):t)
    |(nome==n) = idadeAux dA d 
    |otherwise = idade dA nome t 

idadeAux :: Data -> Data -> Maybe Int 
idadeAux (D d2 m2 a2) (D d1 m1 a1)
    |(a2,m2,d2) < (a1,m1,d1) = Nothing 
    |a2>a1 && (m2,d2) > (m1,d1) = Just (a2-a1)
    |a2>a1 && (m2,d2) < (m1,d1) = Just ((a2-a1) - 1)
    |otherwise = Just 0 

-- 4 c) 
anterior :: Data -> Data -> Bool 
anterior (D d2 m2 a2) (D d1 m1 a1) = (a2,m2,d2) < (a1,m1,d1)

-- 4 d) 
ordena :: TabDN -> TabDN 
ordena [] = []
ordena (x:xs) = inserir x (ordena xs)

inserir :: (Nome,Data) -> TabDN -> TabDN
inserir (x,y) [] = [(x,y)]
inserir (n,d) ((nome,dat):t)
    |(anterior d dat) = (n,d) : ((nome,dat):t)
    |otherwise = (nome,dat) : inserir (n,d) t 

-- 4 e) 
porIdade :: Data -> TabDN -> [(Nome,Int)]
porIdade _ [] = []
porIdade dA ((nome,dat):t) = let list_idades = (nome,idadeAux' dA dat) : porIdade dA t
                             in ordenar list_idades

ordenar :: [(Nome,Int)] -> [(Nome,Int)]
ordenar [] = []
ordenar (((nome,idade):t)) = insere (nome,idade) (ordenar t)
idadeAux' :: Data -> Data -> Int 
idadeAux' (D d2 m2 a2) (D d1 m1 a1)
    |a2>a1 && (m2,d2) > (m1,d1) = a2-a1
    |a2>a1 && (m2,d2) < (m1,d1) = (a2-a1) - 1
    |otherwise = 0

insere :: (Nome,Int) -> [(Nome,Int)] -> [(Nome,Int)]
insere (x,y) [] = [(x,y)]
insere (n,i) ((nome,idade):t)
    |(i<idade) = (n,i): ((nome,idade):t)
    |otherwise = (nome,idade) : insere (n,i) t

-- 5 
data Movimento = Credito Float | Debito Float  deriving Show
data Datas = D1 Int Int Int deriving Show
data Extracto = Ext Float [(Datas, String, Movimento)]  deriving Show
            
-- 5 a) 
extValor :: Extracto -> Float -> [Movimento]
extValor (Ext si []) _ = []
extValor (Ext si ((d,descr,q):t)) valor 
    |(pegarquantia q > valor) = q: extValor (Ext si t) valor  
    |otherwise = extValor (Ext si t) valor 

pegarquantia :: Movimento -> Float 
pegarquantia (Credito x) = x 
pegarquantia (Debito x) = x 

-- 5 b) 
filtro :: Extracto -> [String] -> [(Datas,Movimento)]
filtro (Ext si []) _ = []
filtro (Ext si ((d,descr,q):t)) l@(x:xs) 
    |(x==descr) = (d,q) : filtro (Ext si t) xs 
    |otherwise = filtro (Ext si t) l 
 
-- 5 c) 
creDeb :: Extracto -> (Float,Float)
creDeb l = (numerocredito l,numerodebito l)

numerocredito :: Extracto -> Float
numerocredito (Ext si []) = 0 
numerocredito (Ext si ((d,descr,q):t)) = case q of 
                                        Credito x -> 1 + numerocredito (Ext si t) 
                                        _ -> numerocredito (Ext si t)

numerodebito :: Extracto -> Float  
numerodebito (Ext si [] ) = 0 
numerodebito (Ext si ((d,descr,q):t)) = case q of 
                                        Debito x -> 1 + numerodebito (Ext si t)
                                        _ -> numerodebito (Ext si t )

-- 5 d) 
saldo :: Extracto -> Float 
saldo (Ext si l) = let valores_gastos = somavaloresgastos l 
                   in si - valores_gastos

somavaloresgastos :: [(Datas, String, Movimento)] -> Float 
somavaloresgastos [] = 0
somavaloresgastos ((d,descr,q):t) = pegarquantia q + somavaloresgastos t