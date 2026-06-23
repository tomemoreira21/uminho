-- |
-- Module      : Tarefa1
-- Description : Invariantes do Jogo
-- Copyright   : Tomé Francisco Amorim Moreira <a111907@alunos.uminho.pt>
--               Diogo Silva Fernandes <a110490@alunos.uminho.pt>
--
--
-- Módulo para a realização da Tarefa 1 de LI1 em 2024/25.
module Tarefa1 where

import Data.List (nub)
import LI12425

data Terrenos = Terrenos
  { relva :: [(Float, Float)],
    terra :: [(Float, Float)],
    agua :: [(Float, Float)]
  }
  deriving (Show, Eq)

-- | Função para inicializar um estado vazio de Terrenos
terrenos :: Terrenos
terrenos = Terrenos {relva = [], terra = [], agua = []}

-- | Função responsável por validar um dado estado do jogo
validaJogo :: Jogo -> Bool
validaJogo j =
  validaPortais j
    && validaInimigos j
    && validaTorres j
    && validaBase j

-- | Função responsável por verificar se os portais são válidos, com base nos seguintes critérios:
--
--  * 1. Existe pelo menos um portal em jogo
--  * 2. Portais estão posicionados sobre a terra
--  * 3. Existe pelo menos um caminho (de terra) ligando um portal à base
--  * 4. Os portais não estão sobrepostos às torres nem às bases
--  * 5. Há ,no máximo, uma onda ativa por portal
validaPortais :: Jogo -> Bool
validaPortais j =
  n_portais >= 1
    && all validaPosicao posicoes_portais
    && validaTB posicoes_portais (posicao_base : posicoes_torres)
    && all validaOnda (portaisJogo j)
    && caminhosPortais j
  where
    n_portais = length (portaisJogo j)
    posicoes_portais = map posicaoPortal (portaisJogo j)
    tr = terrenoCoor (mapaJogo j) (1, 1) terrenos
    validaPosicao = validaTerreno tr "terra"
    posicao_base = posicaoBase (baseJogo j)
    posicoes_torres = map posicaoTorre (torresJogo j)

-- | Função que verifica se no máximo está ativa uma onda no portal
validaOnda :: Portal -> Bool
validaOnda p = length ondasAtivas <= 1
  where
    ondasAtivas = filter (\o -> entradaOnda o <= 0) (ondasPortal p)

-- | Função que verifica se nenhuma das posições da primeira lista está sobreposta a qualquer posição da segunda lista
validaTB :: [Posicao] -> [Posicao] -> Bool
validaTB ((xi, yi) : is) t = notElem (floor xi, floor yi) (map (\(a, b) -> (floor a, floor b)) t) && validaTB is t
validaTB _ _ = True

-- | Função que percorre o mapa e converte cada posição do mapa (x,y) em uma lista de coordenadas associadas aos diferentes tipos de terreno.
terrenoCoor ::
  -- | Mapa do jogo
  Mapa ->
  -- | Coordenada inicial no formato (x,y)
  (Float, Float) ->
  -- | Record que armazena todas as posições (em coordenadas de matriz) de cada tipo de terreno
  Terrenos ->
  -- | Record já com todas as posições de cada tipo de terreno armazenadas
  Terrenos
terrenoCoor [] _ tr = tr
terrenoCoor (linhaMapa : restoMapa) (x, y) tr =
  let trAtualizado = terrenoLinha linhaMapa (x, y) tr
   in terrenoCoor restoMapa (1, y + 1) trAtualizado

-- | Função que percorre uma linha do mapa, identificando as coordenadas de cada tipo de terreno (terra, relva, água)
terrenoLinha ::
  -- | Linha do mapa a ser percorrida
  [Terreno] ->
  -- | Coordenada inicial no formato (x,y)
  (Float, Float) ->
  -- | Record que armazena todas as posições (em coordenadas de matriz) de cada tipo de terreno
  Terrenos ->
  -- | Record já com todas as posições de cada tipo de terreno armazenadas
  Terrenos
terrenoLinha [] _ tr = tr
terrenoLinha (h : rest) (x, y) tr
  | h == t = terrenoLinha rest (x + 1, y) (tr {terra = terra tr ++ [(x, y)]})
  | h == r = terrenoLinha rest (x + 1, y) (tr {relva = relva tr ++ [(x, y)]})
  | h == a = terrenoLinha rest (x + 1, y) (tr {agua = agua tr ++ [(x, y)]})
  | otherwise = terrenoLinha rest (x + 1, y) tr
  where
    t = Terra
    r = Relva
    a = Agua

-- | Função responsável por verificar se os inimigos tomam parâmetros válidos, com base nos seguintes critérios:
--
--  * 1. Todos os inimigos por lançar têm a posição do respetivo portal, nível de vida positivo, e lista de projéteis ativos vazia
--  * 2. Todos os inimigos em jogo encontram-se sobre terra
--  * 3. Os inimigos não podem estar sobrepostos a torres
--  * 4. A velocidade dos inimigos não pode ser negativa
--  * 5. A lista de projéteis ativos deve encontrar-se normalizada,ou seja: não pode conter mais do que um projétil do mesmo tipo e não pode conter, simultaneamente, projéteis do tipo Fogo e Resina, nem Fogo e Gelo
validaInimigos :: Jogo -> Bool
validaInimigos j =
  all validaPorLancar isPortal
    && all validaPosicao posInimigosEmJogo
    && validaTB posInimigosEmJogo posTorres
    && validaVelocidade (inimigosJogo j)
    && all validaProjeteis (inimigosJogo j)
  where
    portais = portaisJogo j
    tr = terrenoCoor (mapaJogo j) (1, 1) terrenos
    validaPosicao = validaTerreno tr "terra"
    posTorres = map posicaoTorre (torresJogo j)
    posInimigosEmJogo = map posicaoInimigo (inimigosJogo j)
    isPortal = map (\p -> (posicaoPortal p, concat $ map inimigosOnda (ondasPortal p))) portais

-- | Função responsável por verificar um conjunto de critérios:
--
--  * 1. Todos os inimigos por lançar têm a posição do respetivo portal
--  * 2. Todos possuem um nível de vida positivo
--  * 3. A lista de projéteis ativos vazia
validaPorLancar ::
  -- | Tuplo que contém na primeira componente a posição do respetivo portal e na segunda a lista de inimigos
  (Posicao, [Inimigo]) ->
  -- | Valor de verdade da verificação
  Bool
validaPorLancar (_, []) = True
validaPorLancar (pos, (i : is)) =
  posicaoInimigo i == pos
    && vidaInimigo i > 0
    && null (projeteisInimigo i)
    && validaPorLancar (pos, is)

-- | Função que verifica se a velocidade de cada um dos inimigos é não negativa
validaVelocidade :: [Inimigo] -> Bool
validaVelocidade l = all (\i -> velocidadeInimigo i >= 0) l

-- | Função que verifica se a lista de projéteis do inimigo encontra-se normalizada, ou seja, não contém mais do que um projétil de cada tipo e não contém, em simultâneo, projéteis do tipo Fogo e Resina, nem do tipo Fogo e Gelo
validaProjeteis :: Inimigo -> Bool
validaProjeteis i =
  not (elem Fogo projTipo && elem Gelo projTipo)
    && not (elem Fogo projTipo && elem Resina projTipo)
    && f <= 1
    && g <= 1
    && r <= 1
  where
    projInimigo = projeteisInimigo i
    projTipo = map tipoProjetil projInimigo
    (f, g, r) = contaProjeteis projTipo

-- | Função que devolve a tripla com a contagem de ocorrências de cada tipo numa lista
contaProjeteis ::
  -- | Lista com os tipos de projéteis ativos
  [TipoProjetil] ->
  -- | Tripla onde as componentes indicam, respectivamente, as quantidades de projéteis dos tipos Fogo, Gelo e Resina
  (Int, Int, Int)
contaProjeteis l = foldr aux (0, 0, 0) l
  where
    aux p (f, g, r) = case p of
      Fogo -> (f + 1, g, r)
      Gelo -> (f, g + 1, r)
      Resina -> (f, g, r + 1)

-- | Função que determina a distância entre duas posições
dist :: Posicao -> Posicao -> Float
dist (x1, y1) (x2, y2) = sqrt ((x2 - x1) ^ 2 + (y2 - y1) ^ 2)

-- | Função que verifica se o estado das torres em jogo é válido, com base nos seguintes critérios:
--
--  * 1. Estão posicionadas sobre a relva
--  * 2. O seu alcance é um valor positivo
--  * 3. A rajada é um valor positivo
--  * 4. O ciclo é um valor não negativo
--  * 5. As torres não podem estar sobrepostas
validaTorres :: Jogo -> Bool
validaTorres j =
  all validaPosicao posTorres
    && maiorZero alcanceTorre
    && maiorZero rajadaTorre
    && maiorIgualZero cicloTorre
    && sobrepoeTorres posTorres
  where
    torres = torresJogo j
    tr = terrenoCoor (mapaJogo j) (1, 1) terrenos
    validaPosicao = validaTerreno tr "relva"
    posTorres = map posicaoTorre torres
    maiorIgualZero f = all (>= 0) (map f torres)
    maiorZero f = all (> 0) (map f torres)

-- | Função que aproxima por defeito as coordenadas de uma lista de posições
truncaPares :: [Posicao] -> [Posicao]
truncaPares [] = []
truncaPares ((x, y) : r) = (fromIntegral (floor x), fromIntegral (floor y)) : truncaPares r

-- | Função que verifica se as torres não estão sobrepostas umas às outras
sobrepoeTorres :: [Posicao] -> Bool
sobrepoeTorres l = length truncadas == length (nub truncadas)
  where
    truncadas = truncaPares l

-- | Função que valida o estado da base do jogador, com base nos seguintes critérios:
--
--  * 1. Está colocada sobre a terra
--  * 2. Não tem crédito negativo
--  * 3. Não está sobreposta a uma torre ou portal
validaBase :: Jogo -> Bool
validaBase j =
  validaPosicao (posicaoBase b)
    && creditosBase b >= 0
    && sobrepoeObjetos (posicaoBase b) posTorres posPortais
  where
    b = baseJogo j
    tr = terrenoCoor (mapaJogo j) (1, 1) terrenos
    validaPosicao = validaTerreno tr "terra"
    posTorres = map posicaoTorre (torresJogo j)
    posPortais = map posicaoPortal (portaisJogo j)

-- | Função que verifica se a posição da base do jogador não está sobreposta a uma torre ou a portal
sobrepoeObjetos ::
  -- | Posição da base do jogador
  Posicao ->
  -- | Lista com as posições das torres no jogo
  [Posicao] ->
  -- | Lista com as posições dos portais no jogo
  [Posicao] ->
  -- | Valor de verdade da verificação
  Bool
sobrepoeObjetos (xb, yb) [] lp@(p : ps) = (fromIntegral (floor xb), fromIntegral (floor yb)) `notElem` (truncaPares lp) && sobrepoeObjetos (xb, yb) [] ps
sobrepoeObjetos (xb, yb) lt@(t : ts) [] = (fromIntegral (floor xb), fromIntegral (floor yb)) `notElem` (truncaPares lt)
sobrepoeObjetos (xb, yb) lt@(t : ts) lp@(p : ps) =
  (fromIntegral (floor xb), fromIntegral (floor yb)) `notElem` (truncaPares lt)
    && (fromIntegral (floor xb), fromIntegral (floor yb)) `notElem` (truncaPares lp)
    && sobrepoeObjetos (xb, yb) ts ps
sobrepoeObjetos _ _ _ = True

-- | Função que verifica se uma dada posição em coordenadas de matriz (x,y) se encontra num dado terreno
validaTerreno ::
  -- | Record que armazena todas as posições (em coordenadas de matriz) de cada tipo de terreno
  Terrenos ->
  -- | Identificador do tipo de terreno que se pretende verificar
  String ->
  -- | Posição que se pretende verificar, dada em coordenadas de matriz
  Posicao ->
  -- | Valor de verdade da verificação
  Bool
validaTerreno tr s (x, y)
  | s == "relva" = any f' (relva tr)
  | s == "terra" = any f' (terra tr)
  | s == "agua" = any f' (agua tr)
  | otherwise = False
  where
    f' (l, c) = x > l - 1 && x <= l && y > c - 1 && y <= c

-- | Função que verifica se existe pelo menos um caminho de terra ligando um portal à base
caminhosPortais ::
  -- | Estado atual do jogo
  Jogo ->
  -- | Validade da verificação
  Bool
caminhosPortais j = any (\p -> verificaCaminho p posBase mapa []) posPortais
  where
    posPortais = map posicaoPortal (portaisJogo j)
    posBase = posicaoBase (baseJogo j)
    mapa = mapaJogo j

-- | Função que verifica se existe um caminho válido entre duas posições no jogo, evitando posições já visitadas e respeitando as regras do terreno
verificaCaminho ::
  -- | Posição atual
  Posicao ->
  -- | Posição final/objetivo
  Posicao ->
  -- | Mapa do jogo
  Mapa ->
  -- | Lista dos visitados
  [Posicao] ->
  -- | Valor de verdade de verificação
  Bool
verificaCaminho (xi, yi) (xf, yf) m visitados
  | (floor xi == floor xf) && (floor yi == floor yf) = True
  | otherwise = case filter (`notElem` visitados) (vizinhosTerra (xi, yi) m) of
      [] -> False
      l -> verificaCaminho (proximoPasso l (xf, yf)) (xf, yf) m ((xi, yi) : visitados)

-- | Função que indica a próxima posição no caminho
proximoPasso ::
  -- | Lista de posições a analisar
  [Posicao] ->
  -- | Posição final
  Posicao ->
  -- | Posição escolhida
  Posicao
proximoPasso [p] _ = p
proximoPasso (p1 : p2 : ps) pf
  | dist p1 pf < dist p2 pf = proximoPasso (p1 : ps) pf
  | otherwise = proximoPasso (p2 : ps) pf

-- | Função que devolve os blocos de terra na vizinhança da posição dada
vizinhosTerra :: Posicao -> Mapa -> [Posicao]
vizinhosTerra (x, y) m = filter (\(a, b) -> validaTerreno tr "terra" (a, b)) vizinhos
  where
    vizinhos = [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]
    tr = terrenoCoor m (1, 1) terrenos
