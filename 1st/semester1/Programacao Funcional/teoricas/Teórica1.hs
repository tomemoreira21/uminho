module Aula1_teórica where
-- apenas funciona para números inteiros positivos (se for negativo dá erro)
factorial :: Int -> Int
factorial 0 = 1
factorial x = x * factorial (x-1)

-- import Prelude (algo redundante, pois já o próprio haskell faz o importe sozinho)

-- Notas da aula
-- Uma expressão ou é um valor ou resulta de aplicar funções a expressões
-- O interpretador ghci atua como uma calculadora: lẽ uma expressão, calcula o seu valor e apresenta o resultado
-- (not False = True)
--(exemplo: [1,2,3,4,5] = [1,2..5])
-- Vários tipos existentes (para saber o tipo usa-se o comando :t <operação>)
-- Tipos Básicos
-- Bool -> True or False
-- Int -> corresponde para números inteiros
-- Float -> corresponde para números decimais
-- Char -> corresponde para caracteres ("a","3")
-- Integer -> corresponde a inteiros de tamanho ilimitado
-- Tipos Compostos
-- Tuplos -> sequencias de tamanho fixo de elementos de diferentes tipos
-- ex: ("Pedro",19) :: (String,Int)
--     (True,19.8) :: (Bool,Float)
-- Listas -> sequencias de tamanho variavel de elementos de um mesmo tipo
-- ex: [1,2,3] :: [Int]
--     [True,False] :: [Bool]
-- Funções ->
-- ex: fact :: Int(domínio) -> Int(contradomínio)
-- even - testa se o número é par
-- odd - testa se o número é ímpar

-- Exemplo utilizando tuplos
somarTuplo :: (Int,Int) -> Int
somarTuplo (x,y) = x + y

-- Exemplos utilizando funções
somafunc :: Int -> Int -> Int
somafunc x y = x + y

mult :: Int -> Int -> Int -> Int
mult x y z = x*y*z

-- Nota: A soma de strings não é possível
--  (length :: [a] -> a (comprimento da lista))
-- (head :: [a] -> a (1ºelemento da lista))
-- (tail :: [a] -> [a] (lista sem o 1ºelemento))

-- Exemplo zip e take
-- zip ["a","b","c"] [1,2,3] - [("a",1),("b",2),("c",3)]
-- take 4 [1,2,3,10,5,6,7] - [1,2,3,10] (neste caso retira os 4 primeiros elementos da lista)


-- Exemplos de conetivos
-- Conjunção = &&; Disjunção = ||; Negação = not
-- Exponenciações com reais = ** 

-- DATA
-- data Veículo = Carro Marca Ano
             --  |Camiao Marca Ano

-- type Marca = String
-- type Ano = Int
-- Carro :: Marca -> Ano -> Veículo 

-- PADRÕES
-- Um padrão não pode ter variáveis repetidas 
