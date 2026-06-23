-- |
-- Module      : Tarefa3
-- Description : Mecânica do Jogo
-- Copyright   : Tomé Francisco Amorim Moreira <a111907@alunos.uminho.pt>
--               Diogo Silva Fernandes <a110490@alunos.uminho.pt>
--
--
-- Módulo para a realização da Tarefa 3 de LI1 em 2024/25.
module Tarefa3 where

import Data.List (mapAccumL)
import LI12425
import Tarefa1
import Tarefa2

-- | Função responsável por atualizar o jogo em função do tempo
atualizaJogo :: Tempo -> Jogo -> Jogo
atualizaJogo t j = j {inimigosJogo = inimigosAfetados, baseJogo = baseAtualizada, torresJogo = torresAtualizadas, portaisJogo = portaisAtualizados}
  where
    (inimigosLancados, portaisAtualizados) = lancaInimigosPortais t (inimigosJogo j) (portaisJogo j)
    (inimigosAtualizados, baseAtualizada) = atualizaInimigos t inimigosLancados (mapaJogo j) (baseJogo j)
    (inimigosAfetados, torresAtualizadas) = mapAccumL (disparaTorre t) inimigosAtualizados (torresJogo j)

-- | Função que simula o disparo de uma torre, com base nas condições definidas:
--
-- * 1. A torre só dispara se o tempo de disparo for menor ou igual a 0
-- * 2. A torre só dispara sobre inimigos no seu alcance.
-- * 3. A torre dispara sobre tantos inimigos quantos o parâmetro @rajadaTorre@ permite
disparaTorre :: Tempo -> [Inimigo] -> Torre -> ([Inimigo], Torre)
disparaTorre t is tr
  | tempoTorre tr > 0 = (is, tr {tempoTorre = tempoTorre tr - t})
  | otherwise = (map (atingeInimigo tr) isAtingidos ++ isRestantes, tr {tempoTorre = cicloTorre tr})
  where
    (isAlcance, isFora) = (inimigosNoAlcance tr is, inimigosForaAlcance tr is)
    (isAtingidos, isRestantes) = (take (rajadaTorre tr) isAlcance, drop (rajadaTorre tr) isAlcance ++ isFora)

-- | Função responsável por atualizar o estado dos inimigos e base, nomeadamente:
--
--  * 1. Os inimigos devem-se mover dependendo dos projéteis que se encontram ativos nos mesmos
--  * 2. Os inimigos com um nível de vida igual ou inferior a 0 são removidos da lista de inimigos ativos,,sendo o seu butim adicionado aos créditos da base do jogador
--  * 3. Os inimigos que atingem a base são removidos da lista de inimigos ativos, sendo que a base irá perder uma quantidade de vida equivalente ao dano que o inimigo inflige
atualizaInimigos ::
  -- | Tempo decorrido desde a última atualização
  Tempo ->
  -- | Lista de inimigos ativos
  [Inimigo] ->
  -- | Mapa do jogo
  Mapa ->
  -- | Base do jogo
  Base ->
  -- | Tuplo com os inimigos e a base do jogo atualizadas
  ([Inimigo], Base)
atualizaInimigos t inimigos m b = (inimigosRestantes, baseAtualizada)
  where
    inimigosAtualizados = atualizaEstadoInimigos inimigos t
    inimigosMovimentados = map (\i -> atualizarPosicaoInimigo t i m b) inimigosAtualizados
    (inimigosVivos, baseAtualizada') = removerInimigo inimigosMovimentados b
    (inimigosRestantes, baseAtualizada) = encontraBase inimigosVivos baseAtualizada'

-- | Função responsável por determinar a nova posição para o qual o inimigo se deve mover
atualizarPosicaoInimigo ::
  -- | Tempo decorrido desde a última atualização
  Tempo ->
  -- | Inimigo em causa
  Inimigo ->
  -- | Mapa do jogo
  Mapa ->
  -- | Base do Jogo
  Base ->
  -- | Inimigo já com a nova posição para a qual se deve mover
  Inimigo
atualizarPosicaoInimigo t inimigo m base
  | atingeBase = inimigo {posicaoInimigo = posicaoBase base}
  | otherwise = inimigo {posicaoInimigo = novaPosicao, direcaoInimigo = novaDirecao}
  where
    (xi, yi) = posicaoInimigo inimigo
    (xf, yf) = posicaoBase base
    atingidoPorGelo = any (\p -> tipoProjetil p == Gelo) (projeteisInimigo inimigo)
    atingeBase = (floor xi == floor xf) && (floor yi == floor yf)
    novaDirecao = alteraDirecao inimigo novaPosicao
    novaPosicao =
      if not atingidoPorGelo
        then proximoPasso (vizinhosTerraInimigo inimigo m t) (posicaoBase base)
        else posicaoInimigo inimigo

-- | Função responsável por alterar a direção do inimigo após ser tomado o próximo passo
alteraDirecao ::
  -- | Inimigo antes de tomar o próximo passo
  Inimigo ->
  -- | Posição do inimigo após ser tomado o próximo passo
  Posicao ->
  -- | Nova direção do inimigo
  Direcao
alteraDirecao i (xf, yf)
  | (xi, yi) == (xf, yf) = direcaoInimigo i
  | xi == xf = if yf > yi then Sul else Norte
  | yi == yf = if xf > xi then Este else Oeste
  | otherwise = direcaoInimigo i
  where
    (xi, yi) = posicaoInimigo i

-- | Função devolve as posições válidas,ou seja, que se encontram sobre Terra e não possuem direção oposta à do inimigo, ao redor da posição atual do inimigo
vizinhosTerraInimigo ::
  -- | Estado atual do inimigo
  Inimigo ->
  -- | Mapa do jogo
  Mapa ->
  -- | Tempo decorrido desde a última atualização (necessário para calcular a distância que pode percorrer)
  Tempo ->
  -- | Lista de posições válidas ao redor da posição atual do inimigo
  [Posicao]
vizinhosTerraInimigo inimigo m t = map fst $ filter (\(pos, dir) -> validaTerreno tr "terra" pos && not (direcaoOposta direcao dir)) vizinhosComDirecoes
  where
    vizinhosComDirecoes = [((x - d, y), Oeste), ((x + d, y), Este), ((x, y - d), Norte), ((x, y + d), Sul)]
    tr = terrenoCoor m (1, 1) terrenos
    (x, y) = posicaoInimigo inimigo
    d = velocidadeInimigo inimigo * t
    direcao = direcaoInimigo inimigo

-- | Função que recebe duas direções e devolve o valor booleano dependendo de serem direções opostas
direcaoOposta :: Direcao -> Direcao -> Bool
direcaoOposta Norte Sul = True
direcaoOposta Sul Norte = True
direcaoOposta Oeste Este = True
direcaoOposta Este Oeste = True
direcaoOposta _ _ = False

-- | Função responsável por atualizar a lista de inimigos no momento em que algum atinge a base devendo ser eliminado da lista de inimigos ativos, e a base deve perder uma quantidade de vida equivalente ao dano que o inimigo inflige
encontraBase ::
  -- | Lista de inimigos inicial
  [Inimigo] ->
  -- | Base inicial
  Base ->
  -- | Tuplo com os inimigos e a base já atualizadas
  ([Inimigo], Base)
encontraBase [] base = ([], base)
encontraBase (i : is) base
  | atingeBase = (is, novaBase)
  | otherwise = (i : inimigosAtualizados, baseAtualizada)
  where
    (inimigosAtualizados, baseAtualizada) = encontraBase is base
    (xf, yf) = posicaoBase base
    atingeBase = (floor xi == floor xf) && (floor yi == floor yf)
    (xi, yi) = posicaoInimigo i
    novaBase = base {vidaBase = vidaBase base - ataqueInimigo i}

-- | Função responsável por remover os inimigos cujo nível de vida é zero ou um valor inferior,sendo o seu butim adicionado aos créditos da base do jogador
removerInimigo ::
  -- | Lista de inimigos inicial
  [Inimigo] ->
  -- | Base inicial
  Base ->
  -- | Tuplo com os inimigos e a base já atualizadas
  ([Inimigo], Base)
removerInimigo [] base = ([], base)
removerInimigo (i : is) base
  | vidaInimigo i <= 0 = (is, novaBase)
  | otherwise = (i : inimigosAtualizados, baseAtualizada)
  where
    (inimigosAtualizados, baseAtualizada) = removerInimigo is base
    novaBase = base {creditosBase = creditosBase base + butimInimigo i}

-- | Função responsável por atualizar a duração dos projéteis ativos nos inimigos e aplicar o efeito do projétil nos inimigos com base nos seguintes efeitos:
--   * 1. Resina -> reduz a velocidade 50% no momento do impacto do projétil
--   * 2. Gelo -> torna a velocidade do inimigo nula
--   * 3. Fogo -> aplica 3 unidades de dano por segundo no inimigo
atualizaEstadoInimigos :: [Inimigo] -> Tempo -> [Inimigo]
atualizaEstadoInimigos inimigos tempo = map (`atualizaDuracaoInimigo` tempo) atualizadoInimigos
  where
    atualizadoInimigos = map (`aplicaProjetilInimigo` tempo) inimigos

-- | Função responsável por ao longo do tempo ir atualizando a duração dos projéteis no inimigo,atendendo a dois parâmetros:
--
--  * 1. Remover os projéteis cuja a duração é menor ou igual a 0
--  * 2. Ir ao longo do tempo atualizar a duração dos projéteis
atualizaDuracaoInimigo ::
  -- | Estado atual do inimigo
  Inimigo ->
  -- | Tempo decorrido desde a última atualização (necessário para ir atualizando a duração de cada projétil)
  Tempo ->
  -- | Estado final do inimigo já com a lista de projeteis atualizada
  Inimigo
atualizaDuracaoInimigo inimigo t = inimigo {projeteisInimigo = projAtualizados}
  where
    projAtualizados = excluirDuracaoNula $ map (\proj -> proj {duracaoProjetil = subtraiDuracoes (duracaoProjetil proj) (Finita t)}) (projeteisInimigo inimigo)

-- | Função responsável por aplicar os efeitos dos projéteis no inimigo
aplicaProjetilInimigo :: Inimigo -> Tempo -> Inimigo
aplicaProjetilInimigo i tempo = foldl aplicarEfeito i (projeteisInimigo i)
  where
    aplicarEfeito :: Inimigo -> Projetil -> Inimigo
    aplicarEfeito inimigo proj = case tipoProjetil proj of
      Gelo -> inimigo
      Resina -> aplicarEfeitoResina inimigo 0.5
      Fogo -> aplicarEfeitoFogo inimigo 3 tempo

-- | Função responsável por aplicar o efeito da Resina no inimigo que será a redução da sua velocidade em 50% no momento do impacto do projétil
aplicarEfeitoResina :: Inimigo -> Float -> Inimigo
aplicarEfeitoResina i fator
  | atingidoResina = i
  | otherwise = i {velocidadeInimigo = velocidadeInimigo i * (1 - fator)}
  where
    atingidoResina = any (\p -> tipoProjetil p == Resina) (projeteisInimigo i)

-- | Função responsável por aplicar o efeito do Fogo no inimigo que será a redução da sua vida a uma taxa de 3 unidades de dano por segundo
aplicarEfeitoFogo :: Inimigo -> Float -> Tempo -> Inimigo
aplicarEfeitoFogo i dano t = i {vidaInimigo = vidaInimigo i - (dano * t)}

-- | Função responsável por atualizar a lista de projéteis nomeadamente remover aqueles cuja a duração é <= 0
excluirDuracaoNula :: [Projetil] -> [Projetil]
excluirDuracaoNula p = filter remove p
  where
    remove proj = case duracaoProjetil proj of
      Finita x -> x > 0
      _ -> True

-- | Função responsável por subtrair duas durações
subtraiDuracoes :: Duracao -> Duracao -> Duracao
subtraiDuracoes d1 d2 = case (d1, d2) of
  (Finita x, Finita y) -> Finita (x - y)
  _ -> Infinita

-- | Função que aplica @lancaInimigosPortal@ a todos os portais
lancaInimigosPortais :: Tempo -> [Inimigo] -> [Portal] -> ([Inimigo], [Portal])
lancaInimigosPortais t is ps = mapAccumL (lancaInimigosPortal t) is ps

-- | Função que se encarrega de lançar os inimigos de um portal para jogo, respeitando os tempos de entrada dos inimigos e das ondas e atualizando-os
-- em função do tempo decorrido
lancaInimigosPortal ::
  -- | Tempo decorrido desde a última atualização
  Tempo ->
  -- | Lista de inimigos atualmente em jogo
  [Inimigo] ->
  -- | Portal do qual se pretende lançar inimigos
  Portal ->
  -- | Tuplo que contém a lista de inimigos em jogo atualizada e o portal com as ondas atualizadas
  ([Inimigo], Portal)
lancaInimigosPortal t is p
  | null ondas = (is, p)
  | null (inimigosOnda primeiraOnda) = (is, p {ondasPortal = atualizaEntradaOnda t resto})
  | entradaOnda primeiraOnda <= 0 && tempoOnda primeiraOnda > 0 = (is, p {ondasPortal = primeiraOnda {tempoOnda = tempoOnda primeiraOnda - t} : (atualizaEntradaOnda t resto)})
  | entradaOnda primeiraOnda <= 0 && tempoOnda primeiraOnda <= 0 = (inimigosAtualizados, portalAtualizado {ondasPortal = atualizaEntradaOnda t (ondasPortal portalAtualizado)})
  | otherwise = (is, p {ondasPortal = atualizaEntradaOnda t ondas})
  where
    ondas = ondasPortal p
    (primeiraOnda : resto) = ondas
    (portalAtualizado, inimigosAtualizados) = ativaInimigo p is

-- | Função que decrementa o tempo de entrada das ondas com base no tempo decorrido
atualizaEntradaOnda :: Tempo -> [Onda] -> [Onda]
atualizaEntradaOnda t lo = map (\o -> o {entradaOnda = entradaOnda o - t}) lo
