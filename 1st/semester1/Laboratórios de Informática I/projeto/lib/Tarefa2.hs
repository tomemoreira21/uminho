-- |
-- Module      : Tarefa2
-- Description : Auxiliares do Jogo
-- Copyright   : Tomé Francisco Amorim Moreira <a111907@alunos.uminho.pt>
--               Diogo Silva Fernandes <a110490@alunos.uminho.pt>
--
--
-- Módulo para a realização da Tarefa 2 de LI1 em 2024/25.
module Tarefa2 where

import LI12425
import Tarefa1 (dist)

-- | Função responsável por determinar os inimigos no alcance da Torre
inimigosNoAlcance ::
  -- | Torre presente no jogo
  Torre ->
  -- | Todos os inimigos presentes jogo
  [Inimigo] ->
  -- | Inimigos que estão no alcance da Torre
  [Inimigo]
inimigosNoAlcance _ [] = []
inimigosNoAlcance t (i : is)
  | dist posicao_torre posicao_inimigo <= alcance_torre = i : inimigosNoAlcance t is
  | otherwise = inimigosNoAlcance t is
  where
    alcance_torre = alcanceTorre t
    posicao_torre = posicaoTorre t
    posicao_inimigo = posicaoInimigo i

-- | Função responsável por determinar os inimigos fora do alcance da Torre
inimigosForaAlcance ::
  -- | Torre presente no jogo
  Torre ->
  -- | Todos os inimigos presentes jogo
  [Inimigo] ->
  -- | Inimigos que estão no alcance da Torre
  [Inimigo]
inimigosForaAlcance _ [] = []
inimigosForaAlcance t (i : is)
  | dist posicao_torre posicao_inimigo > alcance_torre = i : inimigosForaAlcance t is
  | otherwise = inimigosForaAlcance t is
  where
    alcance_torre = alcanceTorre t
    posicao_torre = posicaoTorre t
    posicao_inimigo = posicaoInimigo i

-- | Função que atualiza o estado do inimigo sendo que o mesmo acaba de ser atingido pelo projétil da Torre
atingeInimigo ::
  -- | Torre presente no jogo
  Torre ->
  -- | Estado inicial do inimigo
  Inimigo ->
  -- | Estado atualizado do inimigo, após ser atingido pelo projétil da Torre
  Inimigo
atingeInimigo t i = i {vidaInimigo = novaVida, projeteisInimigo = atualizaProjeteis projTorre projInimigo}
  where
    danoProvocado = danoTorre t
    novaVida = max 0 (vidaInimigo i - danoProvocado)
    projTorre = projetilTorre t
    projInimigo = projeteisInimigo i

-- | Função que atualiza a lista projetis ativos consoante as sinergias, ordenadas por precedência:
--
--  * 1. Fogo e Gelo cancelam-se mutuamente, ambos projéteis são removidos da lista de projéteis do inimigo
--  * 2. Fogo e Resina dobra a duração do fogo, pelo que na lista de projéteis do inimigo vai dobrar a duração do projétil Fogo e, caso necessário, remover o projétil Resina da lista
--  * 3. Projéteis iguais somam as suas durações
--  * 4. As restantes combinações de projéteis não resultam em sinergias logo o projétil que atingiu o inimigo será adicionado à lista dos projéteis ativos no inimigo
--  * 5. No caso em que o inimigo não contém projéteis ativos, o projétil que o atingiu deve ser incluído na lista
atualizaProjeteis ::
  -- | Projetil ativo na Torre
  Projetil ->
  -- | Lista de projetis ativos no inimigo
  [Projetil] ->
  -- | Lista de projetis ativos no inimigo atualizada consoante o tipo do projétil da Torre
  [Projetil]
atualizaProjeteis projTorre projInimigo =
  case tipoTorre of
    Gelo ->
      if existe Fogo projInimigo
        then filter (\p -> tipoProjetil p /= Fogo) projInimigo
        else
          if existe Gelo projInimigo
            then atualizaIguais projTorre projInimigo
            else projTorre : projInimigo
    Fogo ->
      if existe Gelo projInimigo
        then filter (\p -> tipoProjetil p /= Gelo) projInimigo
        else
          if existe Fogo projInimigo
            then atualizaIguais projTorre projInimigo
            else
              if existe Resina projInimigo
                then atualizaFogoResina projTorre projInimigo
                else projTorre : projInimigo
    Resina ->
      if existe Fogo projInimigo
        then atualizaResinaFogo projTorre projInimigo
        else
          if existe Resina projInimigo
            then atualizaIguais projTorre projInimigo
            else projTorre : projInimigo
  where
    tipoTorre = tipoProjetil projTorre

-- | Função que verifica se um dado tipo de projétil existe na lista de projéteis do inimigo
existe :: TipoProjetil -> [Projetil] -> Bool
existe t p = any (\pro -> tipoProjetil pro == t) p

-- | Função que verifica o caso particular em que o tipo de projétil da torre é Resina e do inimigo é Fogo em que deve dobrar a duração do projétil Fogo no inimigo
atualizaResinaFogo :: Projetil -> [Projetil] -> [Projetil]
atualizaResinaFogo _ [] = []
atualizaResinaFogo p (h : t) = case tipoProjetil h of
  Fogo -> h {duracaoProjetil = addTempo (duracaoProjetil h) (duracaoProjetil h)} : t
  _ -> h : atualizaResinaFogo p t

-- | Função que verifica o caso particular em que o tipo de projétil da torre é Fogo e o do inimigo é Resina em que deve remover a Resina da lista dos projéteis ativos no inimigo dobrando a duração do efeito do projétil Fogo
atualizaFogoResina :: Projetil -> [Projetil] -> [Projetil]
atualizaFogoResina _ [] = []
atualizaFogoResina projFogo (h : t) = case tipoProjetil h of
  Resina -> h {tipoProjetil = Fogo, duracaoProjetil = addTempo (duracaoProjetil projFogo) (duracaoProjetil projFogo)} : t
  _ -> h : atualizaFogoResina projFogo t

-- | Função que verifica o caso particular em que o tipo de projetil da torre é igual ao tipo de projetil ativo no inimigo
atualizaIguais :: Projetil -> [Projetil] -> [Projetil]
atualizaIguais _ [] = []
atualizaIguais projTorre (h : t)
  | tipoTorre == tipoInimigo = h {duracaoProjetil = addTempo (duracaoProjetil projTorre) (duracaoProjetil h)} : t
  | otherwise = h : atualizaIguais projTorre t
  where
    tipoTorre = tipoProjetil projTorre
    tipoInimigo = tipoProjetil h

-- | Função responsável por adicionar duas durações
addTempo :: Duracao -> Duracao -> Duracao
addTempo t d = case (d, t) of
  (Finita x, Finita y) -> Finita (x + y)
  _ -> Infinita

-- | Função que coloca o próximo inimigo a ser lançado por um portal em jogo
ativaInimigo ::
  -- | Portal presente no jogo
  Portal ->
  -- | Lista de inimigos atualmente em jogo
  [Inimigo] ->
  -- | Novo portal resultante de perder aquele inimigo que será incluído na lista de inimigos ativos
  (Portal, [Inimigo])
ativaInimigo p li = case ondasPortal p of
  [] -> (p, li) -- Se não houver ondas, não faz nada
  (primeiraOnda : restoOndas) ->
    case inimigosOnda primeiraOnda of
      [] -> (p {ondasPortal = restoOndas}, li) -- Se não houver inimigos na onda remove essa mesma Onda
      (novoInimigo : inimigosPorLancar) ->
        let novaOnda = primeiraOnda {inimigosOnda = inimigosPorLancar, tempoOnda = cicloOnda primeiraOnda}
         in (p {ondasPortal = novaOnda : restoOndas}, li ++ [novoInimigo])

-- | Função que decide de um jogo terminou, ou seja, se o jogador ganhou ou perdeu o jogo
terminouJogo :: Jogo -> Bool
terminouJogo j = ganhouJogo j || perdeuJogo j

-- | Função que verifica se o jogador ganhou o jogo com base nos seguintes critérios:
--
--  * 1. Ausência de inimigos ativos ou inativos (por lançar) simultaneamente
--  * 2. Nível de vida da base positivo
ganhouJogo :: Jogo -> Bool
ganhouJogo j = null inimigosTotais && vidaBase (baseJogo j) > 0
  where
    inimigosTotais = inimigosPorLancar ++ inimigosJogo j
    inimigosPorLancar = concatMap inimigosOnda (concatMap ondasPortal (portaisJogo j))

-- | Função que verifica se o jogador perdeu o jogo,ou seja, se o nível de vida da base é inferior ou igual a 0
perdeuJogo :: Jogo -> Bool
perdeuJogo j = vidaBase (baseJogo j) <= 0
