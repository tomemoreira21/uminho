-- |
-- Module      : Tempo
-- Description : Atualização do jogo em função do tempo
-- Copyright   : Tomé Francisco Amorim Moreira <a111907@alunos.uminho.pt>
--               Diogo Silva Fernandes <a110490@alunos.uminho.pt>
--
--
-- Módulo para a implementação da atualização temporal do projeto de LI1 em 2024/25.
module Tempo where

import ImmutableTowers
import LI12425
import Tarefa2
import Tarefa3

-- | Função que reage com o passar do tempo
--
-- Esta função realiza as seguintes operações:
--
-- * 1. Se o jogador ganhou o jogo, para a música atual, carrega a música de vitória e toca-a, atualizando o estado do ImmutableTowers para o ecrã de vitória
--
-- * 2. Caso contrário, se o jogador perdeu o jogo, realiza a mesma operação exceto que para o ecrã de derrota
--
-- * 3. Caso nenhum destes se aplique, chama @atualizaJogo@, permitindo ao jogador, efetivamente, jogar
reageTempo ::
  -- | Intervalo de tempo decorrido desde a última chamada desta função, corresponde a 1/frame-rate
  Tempo ->
  -- | Estado atual do ImmutableTowers
  ImmutableTowers ->
  -- | Estado atualizado do ImmutableTowers, fazendo uso de IO para reproduzir música
  IO ImmutableTowers
reageTempo t it = case estadoJogo it of
  Jogar ->
    if ganhouJogo (jogo it)
      then do
        paraMusica
        musicaChunk <- sdlInit "app/musica/Vitoria.flac"
        tocaMusica musicaChunk
        return $ it {estadoJogo = Fim Vitoria}
      else
        if perdeuJogo (jogo it)
          then do
            paraMusica
            musicaChunk <- sdlInit "app/musica/Derrota.flac"
            tocaMusica musicaChunk
            return $ it {estadoJogo = Fim Derrota}
          else return $ it {jogo = atualizaJogo t (jogo it)}
  _ -> return it
