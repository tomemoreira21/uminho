{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use replicateM" #-}
import Data.List 
import System.Random 
-- 1 
-- a) 
bingo :: IO ()
bingo = bingoAux [] 10 
        
bingoAux :: [Int] -> Int -> IO ()
bingoAux l 0 = return ()
bingoAux l n = do 
                  k <- randomRIO (1 :: Int,10 :: Int)
                  if elem k l then bingoAux l n 
                              else do 
                                   putStrLn (show k)
                                   x <- getChar -- obriga a paragem de clicar novamente 
                                   bingoAux (k:l) (n-1) 

-- b) 
mastermind :: IO ()
mastermind = do 
    ls <- leNumerosSorteados
    putStrLn (show ls)
    lj <- leNumerosJogador 
    let lp = zip ls lj 
        (lcpc,rl) = parte lp 
        ncpc = length lcpc 
        (lj',ls') = unzip rl
        ncpi = conta lj' ls' 
    putStrLn ("Números certos na posição correta: " ++ show ncpc)
    putStrLn ("Números certos na posição incorreta: " ++ show ncpi)

conta :: [Int] -> [Int] -> Int 
conta [] _ = 0 
conta (x:xs) ls 
    |elem x ls = 1 + conta xs (delete x ls) 
    |otherwise = conta xs ls 

parte :: [(Int,Int)] -> ([(Int,Int)],[(Int,Int)])
parte [] = ([],[])
parte ((x,y):t) = if x == y then ((x,y):lcpc,rl) else (lcpc,(x,y):rl)
    where
        (lcpc,rl) = parte t 

leNumerosSorteados :: IO [Int]
leNumerosSorteados = sequence $ replicate 4 (randomRIO (0,9))

leNumerosJogador :: IO [Int]
leNumerosJogador = do x1 <- getLine 
                      x2 <- getLine 
                      x3 <- getLine 
                      x4 <- getLine 
                      let l = map read [x1,x2,x3,x4]
                      return l 

-- 2 
data Aposta = Ap [Int] (Int,Int) 

-- a) 
valida :: Aposta -> Bool 
valida (Ap n e) = condEstrelas e && condNumeros n  

condEstrelas :: (Int,Int) -> Bool 
condEstrelas (e1,e2) = e1 >= 1 && e1<=9 && e2 >= 1 && e2<=9 && e2 /= e1 

condNumeros :: [Int] -> Bool 
condNumeros l = all (\x -> x >=1 && x<= 50) l && dif l  

dif :: [Int] -> Bool 
dif [] = False 
dif (x:y:ys) = x /= y && dif (y:ys)

