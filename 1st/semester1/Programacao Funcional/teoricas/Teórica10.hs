import System.Random 

-- putStr :: String -> IO () 
-- traduz a string no ecrã
putStr' :: String -> IO ()
putStr' [] = return ()
putStr' (x:xs) = do putChar x 
                    putStr' xs

getLine' :: IO String 
getLine' = do x <- getChar
              if x == '\n'
              then return []
              else do xs <- getLine'
                      return (x:xs)

-- Dialogo vai devolver no ecrã a resposta dada 
dialogo :: String -> IO String 
dialogo s = do putStrLn s 
               x <- getLine 
               return x 

-- questionário ["p1","p2","p3"] -> ["r1","r2","r3"]
questionario :: [String] -> IO [String]
questionario [] = return []
questionario (p:ps) = do r <- dialogo p 
                         rs <- questionario ps 
                         return (p:ps) 

-- fibonnaci 
fib :: Integer -> Integer 
fib 0 = 0 
fib 1 = 1 
fib n = fib (n-1) + fib (n-2)

-- fibonnaci efeciente 
fibE :: Integer -> (Integer,Integer) -- (fib n, fib (n-1))
fibE 0 = (0,0)
fibE 1 = (1,0)
fibE n = (rf+ra,rf)
    where 
        (rf,ra) = fibE (n-1)

calcFib :: IO ()
calcFib = do x <- dialogo "Introduza o valor para o calcular o nº Fibonnaci:"
             let r = fst (fibE (read x)) -- read converte uma String em Int (faz o contrário do show)
             putStrLn ("O valor do Fib e: " ++ show r) 

-- Ler ficheiros 
type Notas = [(Integer,String,Int)]

lerFich :: IO Notas 
lerFich = do fich <- dialogo "Qual o nome do ficheiro?"
             s <- readFile fich 
             let notas = map words (lines s) 
                 notas' = map lista2Notas notas 
             return notas' 

lista2Notas [a,b,c] = (read a, b, read c)

-- Exercício Final 
advinha :: IO ()
advinha = do r <- randomRIO (1,20)
             putStrLn "Qual o numero de 0 a 20 que sugere?"
             x <- jogar r 1 
             putStrLn ("Acertou em " ++ show x ++ " tentativas!")

jogar :: Int -> Int -> IO Int 
jogar r n = do s <- getLine 
               v <- readIO s 
               if v == r then return n 
                         else if v > r then do putStrLn "É alto"
                                               jogar r (n+1)
                                       else do putStrLn "É baixo"
                                               jogar r (n+1)

