{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant bracket" #-}
{-# HLINT ignore "Use concatMap" #-}

-- Exemplos 
rt :: Num a => RTree a 
rt = R 2 [R 3 [], R 4 [R 5 [], R 6 [], R 8 []]]

data RTree a = R a [RTree a]
data BTree a = Empty | Node a (BTree a) (BTree a)

-- 1 
preorderRT :: RTree a -> [a]
preorderRT (R x l) = x : concat (map preorderRT l)  

-- escrever com foldr 
preorderRT' :: RTree a -> [a]
preorderRT' (R x l) = x : foldr (\rt ac -> preorderRT' rt ++ ac) [] l 
    
-- 2 
foldrRTree :: (a->b->b) -> b -> RTree a -> b 
foldrRTree f ac rt = foldr f ac (preorderRT rt)  

-- 3
mapRTree :: (a->b) -> RTree a -> RTree b  
mapRTree f (R x l) = R (f x) (map (mapRTree f) l)

-- 4
-- Permite-me só com a instância fazer o sum,maximum,minimum,elem,length,product
instance Foldable RTree where 
    foldr = foldrRTree 

-- 5 
foldrBTree :: (a->b->b) -> b -> BTree a -> b 
foldrBTree f ac Empty = ac 
foldrBTree f ac (Node i e d) = f i (foldrBTree f (foldrBTree f ac d) e)

instance Foldable BTree where 
    foldr = foldrBTree



