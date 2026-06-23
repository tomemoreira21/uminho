-- Exemplo de um tipo algébrico
-- data [a] = [] | (:) a [a]

-- Árvores binárias 
data BTree a = Empty -- árvore vazia -- :t Empty :: BTree a 
            |Node a (BTree a) (BTree a) -- :t Node :: a -> BTree a -> BTree a -> BTree a
            
-- Exemplo de uma árvore 
t :: BTree Int  
t = Node 3  -- raiz de t 
         (Node 7 Empty Empty) -- 7 e 4 são folhas (não tem descendentes (ver da forma de baixo para cima))
         (Node 5              -- 4 é filho de 5  
                (Node 4 Empty Empty) -- 3 é pai de 7 
                Empty
         )

-- Funções definidas
-- i(corresponde ao 3 no exemplo de cima) -> tipo a ; e -> tipo -> BTree a; d -> tipo BTree a  
contaNode :: BTree a -> Int 
contaNode Empty = 0 
contaNode (Node i e d) = 1 + contaNode e + contaNode d 

-- Soma
sumBT :: Num a => BTree a -> a 
sumBT Empty = 0 
sumBT (Node i e d) = i + sumBT e + sumBT d 

-- Altura da árvore (é 1 mais a altura da maior subárvore)
altura :: BTree a -> Int 
altura Empty = 0 
altura (Node _ e d) = 1 + max (altura e) (altura d)

-- Zip de árvores  
zipBT :: BTree a -> BTree b -> BTree (a,b)
zipBT (Node i1 e1 d1) (Node i2 e2 d2) = Node (i1,i2) (zipBT e1 e2)
                                                     (zipBT d1 d2)
zipBT _ _ = Empty

-- Map de árvores 
mapBT :: (a -> b) -> BTree a -> BTree b 
mapBT f Empty = Empty 
mapBT f (Node i e d) = Node (f i) (mapBT f e) -- (f i) -> tipo b; -- (mapBT f e) -> tipo BTree b ; -- (mapBT f d) -> tipo BTree b  
                                  (mapBT f d)

-- Travessias (começam pela árvore da esquerda depois vai à direita)
-- pai - esquerda - direita -> pre order 
-- esquerda - pai - direita -> in order 
-- esquerda - direita - pai -> pos order 

-- preOrder 
preOrder :: BTree a -> [a]
preOrder Empty = []
preOrder (Node i e d) = i : (preOrder e) ++ (preOrder d)

-- inOrder 
inOrder :: BTree a -> [a]
inOrder Empty = []
inOrder (Node i e d) = (inOrder e) ++ [i] ++ (inOrder d)

-- posOrder
posOrder :: BTree a -> [a]
posOrder Empty = []
posOrder (Node i e d) = (posOrder e) ++ (posOrder d) ++ [i]

-- Função elem 
elemBT :: Eq a => a -> BTree a -> Bool 
elemBT _ Empty = False 
elemBT x (Node i e d) = x == i || elemBT x e || elemBT x d

-- Árvores Binárias de Procura 
-- Todos os elementos da esquerda são menores que o pai 
-- Todos os elementos da direita são maiores que o pai 
-- Para todos os nodes da árvore!

-- elemABP 
elemABP :: Ord a => a -> BTree a -> Bool 
elemABP _ Empty = False 
elemABP x (Node i e d) |x==i = True 
                       |x>i = elemABP x d 
                       |otherwise = elemABP x e 

-- insereABP 
insereABP :: Ord a => a -> BTree a -> BTree a 
insereABP x Empty = Node x Empty Empty
insereABP x (Node i e d) |x==i = Node i e d
                         |x<i = Node i (insereABP x e) d 
                         |otherwise = Node i e (insereABP x d)

-- lookup normal 
-- >>> lookup "Joca" [("Joca",123),("Luis",56)]
-- Just 123

-- lookupABT 
lookupABT :: Ord a => a -> BTree (a,b) -> Maybe b 
lookupABT _ Empty = Nothing 
lookupABT x (Node (a,b) e d) |x == a = Just b
                             |x<a = lookupABT x e 
                             |otherwise = lookupABT x d 

    