data BTree a = Empty
             | Node a (BTree a) (BTree a) deriving Show

-- teste 
exampleTree1 :: Num a => BTree a
exampleTree1 = Node 10 
                (Node 5 
                    (Node 3 Empty Empty) 
                    (Node 7 Empty Empty)
                )
                (Node 15 
                    Empty 
                    (Node 18 Empty Empty)
                )

exampleTree2 :: Num a => BTree a  
exampleTree2 = Node 3 
                (Node 7 Empty Empty) 
                (Node 5              
                        (Node 4 Empty Empty) 
                        Empty)

exampleTree3 :: Num a => BTree a 
exampleTree3 = Node 5 
                (Node 3 
                        (Node 2 Empty Empty)
                         Empty)
                (Node 6 Empty Empty)

exampleTree4 :: BTree (Int,String,Float)
exampleTree4 = Node (1,"A",1.5)
                    (Node (2,"B",1.4) Empty Empty)
                    (Node (3,"C",4.5) Empty Empty)

-- 1 
-- a) 
altura :: BTree a -> Int 
altura Empty = 0 
altura (Node i e d) = 1 + max (altura e) (altura d)

-- b) 
contaNodos :: BTree a -> Int 
contaNodos Empty = 0 
contaNodos (Node i e d) = 1 + contaNodos e + contaNodos d 

-- c) 
folhas :: BTree a -> Int 
folhas Empty = 0 
folhas (Node _ Empty Empty) = 1 
folhas (Node i e d) = folhas e + folhas d 

-- d) 
-- primeira interpretação 
prune :: Int -> BTree a -> BTree a 
prune _ Empty = Empty
prune 0 (Node i _ _) = Node i Empty Empty 
prune n (Node i e d) = Node i (prune (n-1) e) (prune (n-1) d)

-- segunda interpretação 
prune' :: Int -> BTree a -> BTree a 
prune' _ Empty = Empty 
prune' 0 _ = Empty 
prune' n (Node i e d) = Node i (prune' (n-1) e) (prune' (n-1) d)

-- e) 
path :: [Bool] -> BTree a -> [a]
path [] _ = []
path _ Empty = [] 
path (h:t) (Node i e d) |h = i: path t d 
                        |otherwise = i: path t e 

-- f) 
mirror :: BTree a -> BTree a
mirror Empty = Empty 
mirror (Node i e d) = Node i (mirror d) (mirror e) 

-- g) 
zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT f (Node i1 e1 d1) (Node i2 e2 d2) = Node (f i1 i2) (zipWithBT f e1 e2) (zipWithBT f d1 d2) 
zipWithBT f _ _ = Empty 

-- h) 
unzipBT :: BTree (a,b,c) -> (BTree a,BTree b,BTree c) 
unzipBT Empty = (Empty,Empty,Empty)
unzipBT (Node (a,b,c) e d) = let (eA,eB,eC) = unzipBT e 
                                 (dA,dB,dC) = unzipBT d 
                             in (Node a eA dA,Node b eB dB,Node c eC dC)

-- 2 
-- a) 
minimo :: Ord a => BTree a -> a 
minimo (Node i Empty _) = i 
minimo (Node i e d) = minimo e 

-- b) 
semMinimo :: Ord a => BTree a -> BTree a 
semMinimo (Node i Empty d) = d  
semMinimo (Node i e d) = Node i (semMinimo e) d 

-- c) 
minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin (Node i Empty d) = (i,d)
minSmin (Node i e d) = (m,Node i r d)
    where 
        (m,r) = minSmin e 

-- d) 
remove :: Ord a => a -> BTree a -> BTree a
remove _ Empty = Empty 
remove a (Node i e d) |(a<i) = Node i (remove a e) d 
                      |(a>i) = Node i e (remove a d) 
                      |a==i = case (e,d) of 
                        (Empty,d) -> d 
                        (e,Empty) -> e 
                        _ -> Node m e rest
                      where 
                        (m,rest) = minSmin d 

-- 3 
type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD | TE | MEL deriving (Show,Eq) -- ORD -> ordinário ; TE -> trabalhador-estudante ; MEL -> mobilidade estudantil livre
data Classificacao = Aprov Int
                    | Rep
                    | Faltou deriving (Show,Eq)

type Turma = BTree Aluno

-- testes 
turma1 :: Turma
turma1 = Node (1, "Alice", ORD, Aprov 14)
            (Node (0, "Luis", MEL, Rep) Empty Empty)
            (Node (2, "Carolina", TE, Faltou) Empty Empty)

turma2 :: Turma
turma2 = Node (5, "Joao", ORD, Aprov 12)
            (Node (3, "David", TE, Aprov 16)
                (Node (1, "Tome", MEL, Rep) Empty Empty)
                (Node (4, "Frank", ORD, Faltou) Empty Empty)
            )
            (Node (8, "Ana", MEL, Aprov 10)
                (Node (6, "Ivo", TE, Rep) Empty Empty)
                (Node (9, "José", ORD, Aprov 18) Empty Empty)
            )

-- a) 
inscNum :: Numero -> Turma -> Bool
inscNum _ Empty = False
inscNum n (Node (num,nom,r,c) e d) |n==num = True 
                                   |n<num = inscNum n e 
                                   |otherwise = inscNum n d 
        
-- b) 
inscNome :: Nome -> Turma -> Bool
inscNome _ Empty = False 
inscNome n (Node (num,nom,r,c) e d) |(n==nom) = True 
                                    |otherwise = (inscNome n e) || (inscNome n d)
 
-- c) 
trabEst :: Turma -> [(Numero,Nome)]
trabEst Empty = []
trabEst (Node (num,nom,r,c) e d) 
    |r==TE = (num,nom) : rest
    |otherwise = rest     
    where 
        rest = trabEst e ++ trabEst d

-- d) 
nota :: Numero -> Turma -> Maybe Classificacao
nota _ Empty = Nothing 
nota n (Node (num,nom,r,c) e d) 
    |(n==num) = Just c 
    |n<num = nota n e 
    |otherwise = nota n d 

-- e) 
percFaltas :: Turma -> Float
percFaltas Empty = 0 
percFaltas t = let (n_falta,n_alunos) = contaFA t 
               in if n_alunos == 0 then 0 else (n_falta / n_alunos) * 100 

-- devolve (nºde faltas,nºde alunos)
contaFA :: Turma -> (Float,Float)
contaFA Empty = (0,0)
contaFA (Node (num,nom,r,c) e d) = if c == Faltou then (1+faltaT,1+alunoT) else (faltaT,1+alunoT)
        where 
            (faltaE,alunoE) = contaFA e  
            (faltaD,alunoD) = contaFA d
            (faltaT,alunoT) = (faltaE + faltaD,alunoE + alunoD)
 
-- f) 
mediaAprov :: Turma -> Float
mediaAprov Empty = 0 
mediaAprov t = let list = retiraNum t 
               in sum list / fromIntegral (length list)

-- devolve uma lista com as notas dos alunos aprovados
retiraNum :: Turma -> [Float]  
retiraNum Empty = []
retiraNum (Node (num,nom,r,c) e d) = case c of 
                                     Aprov x -> fromIntegral x : rest 
                                     _ -> rest 
                                     where 
                                        rest = retiraNum e ++ retiraNum d  

-- g) 
-- rácio -> (Número de alunos aprovados​/ Número de alunos avaliados)
-- Número de alunos aprovados -> considerei apenas que tem Aprov
-- Número de alunos avaliados -> considerei todos que tenham Aprov Rep Faltou
aprovAv :: Turma -> Float 
aprovAv Empty = 0 
aprovAv t = let (ap,av) = aprov t 
            in if av == 0 then 0 else ap / av 
            where
                aprov :: Turma -> (Float,Float)
                aprov Empty = (0,0)
                aprov (Node (num,nome,r,c) e d) = case c of 
                                                    Aprov _ -> (1 + aprovT, 1 + avalT)
                                                    _ -> (aprovT, 1 + avalT)
                                                    where 
                                                        (aprovE,avalE) = aprov e 
                                                        (aprovD,avalD) = aprov d 
                                                        (aprovT,avalT) = (aprovE + aprovD,avalE + avalD) 
