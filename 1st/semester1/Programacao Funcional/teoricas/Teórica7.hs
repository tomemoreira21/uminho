-- Tipos de árvores 
-- balenceadas -> as alturas das sub-árvores da esquerda difere uma unidade das sub-árvores da direita
-- desbalenceadas -> 

-- Árvores irregulares (rose trees)
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use ==" #-}
data RTree a = R a [RTree a] 
             deriving Show

-- a -> representa o elemento que fica na raiz da árvore 
-- RTree a -> representa a lista das sub-árvores com que vai construir a árvore 
-- exemplo : 
{-
R 2 [R 3 [], R 4 [R 5 [], R 6 [], R 8 []]]
-}

-- Contar nodos de uma árvore 
contaRT :: RTree a -> Int 
contaRT (R x l) = 1 + sum (map contaRT l)

-- Altura da árvore 
alturaRT :: RTree a -> Int  
alturaRT (R x []) = 1 
alturaRT (R x l) = 1 + maximum (map alturaRT l)

-- Pertencer a uma árvore 
pertenceRT :: Eq a => a -> RTree a -> Bool 
pertenceRT x (R y l) = x==y || or (map (pertenceRT x) l)
-- pertenceRT 2 r3  =  False || or ([True,False])
--                  =  False || True 
--                  =  True 

-- Fazer uma travessia preorder uma árvore 
preorderRT :: RTree a -> [a]
preorderRT (R x l) = x : concat (map preorderRT l)

-- Converter uma árvore binária em rose tree 


-- Outras árvores 
-- Leaf trees -> árvores binárias em que a informação está apenas nas folhas de árvore. Os nós intermédios não tem informação 
data LTree a = Tip a 
             | Fork (LTree a) (LTree a)

-- exemplo : 1 2 3 4 5
lt1 :: LTree Int 
lt1 = Fork (Fork (Tip 1) 
                 (Tip 2))
           (Fork (Tip 3) (Fork (Tip 4)
                               (Tip 5) ))

-- Full trees -> árvores binárias que têm informação nos nós intermédios e nas folhas. A informação guardada nos nós e nas folhas pode ser de tipo diferente 
data FTree a b = Leaf b 
               | No a (FTree a b) (FTree a b)

lt2 :: FTree String Int  
lt2 = No "A" (No "B" (Leaf 1)
                     (Leaf 2))
             (No "C" (Leaf 3)
                     (No "D" (Leaf 4)
                             (Leaf 5)))
                 
-- Overloading 
-- Classes e instâncias 
class Num a where           -- definir o geral 
    (+) :: a -> a -> a 
    (*) :: a -> a -> a  

-- serve para especificar para cada tipo
instance Num Int where
    (+) = primPlusInt 
    (*) = primMultInt  

instance Num Float where 
    (+) = primPlusFloat 
    (*) = primMultFloat 

-- Tipos principais 
-- Tipo principal -> é o tipo mais geral de uma função 

class FigFechada a where 
    area :: a -> Float 
    perimetro :: a -> Float

areaTotal l = sum (map area l)

data Nat = Zero | Succ Nat 

class Eq a where 
    (==) :: a -> a -> Bool 
    (/=) :: a -> a -> Bool 
    x /= y = not (x==y)
    x == y = not (x/=y)

instance Eq Nat where 
    (Succ n) == (Succ m) = n == m 
    Zero == Zero = True 
    _ == _ = False 

-- exercicio 
data Time = AM Int Int | PM Int Int | Total Int Int 
-- defina uma função que converte para minutos um valor Time, e com base nela, declare Time como instacia da class Eq 
