-- |
-- Module      : Eventos
-- Description : Eventos do Jogo
-- Copyright   : Tomé Francisco Amorim Moreira <a111907@alunos.uminho.pt>
--               Diogo Silva Fernandes <a110490@alunos.uminho.pt>
--
--
-- Módulo para a implementação da reação a eventos da gloss no projeto de LI1 em 2024/25.
module Eventos where

import Desenhar
import Graphics.Gloss.Interface.Pure.Game
import ImmutableTowers
import LI12425
import System.Exit (exitSuccess)
import Tarefa1

-- | Função responsável por reagir aos eventos.
--
-- Esta função realiza as seguintes operações:
--
-- * 1. Guarda no estado gráfico do ImmutableTowers a posição do cursor, sempre que este é deslocado;
--
-- * 2. Sempre que o botão esquerdo do rato é pressionado, chama a função relevante:
--
-- * 2.(a) @reageMenu@, para reagir a escolhas efetuadas nos botões do menu;
--
-- * 2.(b) @reageEscolhaMapa@, para reagir à escolha do mapa no menu para esse efeito;
--
-- * 2.(c) @reageJogo@, que trata dos eventos de jogo, mais propriamente ditos;
--
-- * 2.(d) @reageRecomeco@, que trata de reiniciar o jogo quando o botão para este efeito é pressionado no ecrã de vitória ou derrota.
--
-- * 3. Ignora todos os outros eventos.
reageEventos ::
  -- | Evento da Gloss a reagir
  Event ->
  -- | Estado global do jogo ImmutableTowers atual
  ImmutableTowers ->
  -- | Estado global do ImmutableTowers atualizado, fazendo uso de IO para reproduzir música
  IO ImmutableTowers
reageEventos (EventMotion p) it = return $ it {estadoGrafico = e {cursor = p}}
  where
    e = estadoGrafico it
reageEventos (EventKey (MouseButton LeftButton) Down _ (px, py)) it =
  case estadoJogo it of
    Menu -> return $ reageMenu (px, py) it
    EscolhaMapa -> reageEscolhaMapa (px, py) it
    Jogar -> reageJogo (px, py) it
    Fim _ -> reageRecomeco (px, py) it
reageEventos _ it = return it

-- | Função responsável por reagir ao menu.
--
-- Esta função é responsável por atualizar o estado do jogo para o menu de seleção de mapa, quando o jogador clica no botão "START" no menu inicial.
reageMenu ::
  -- | Posição do cursor no menu
  (Float, Float) ->
  -- | Estado global do jogo ImmutableTowers atual
  ImmutableTowers ->
  -- | Estado global do jogo ImmutableTowers atualizado
  ImmutableTowers
reageMenu (px, py) it = if escolheStart (px, py) then it {estadoJogo = EscolhaMapa} else it

-- | Função responsável por verificar o mapa escolhido.
--
-- Esta função realiza as seguintes operações:
--
-- * 1. Atualiza o estado do ImmutableTowers para a fase de Jogo, carregando o jogo correspondente ao mapa selecionado pelo jogador, quando este pressiona o botão esquerdo do rato sobre a imagem de um dos mapas;
--
-- * 2. Para a música do menu atualmente a tocar, carrega a música de jogo e toca-a;
--
-- * 3. Ignora cliques em qualquer outra área da janela.
reageEscolhaMapa ::
  -- | Posição do cursor no menu de escolha do mapa
  (Float, Float) ->
  -- | Estado do ImmutableTowers atual
  ImmutableTowers ->
  -- | Estado atualizado do ImmutableTowers, fazendo uso de IO para reprodução de música
  IO ImmutableTowers
reageEscolhaMapa (px, py) it
  | escolheMapa01 (px, py) = do
      paraMusica
      musicaChunk <- sdlInit musica
      tocaMusica musicaChunk
      return it {estadoJogo = Jogar, jogo = jogoInicial01}
  | escolheMapa02 (px, py) = do
      paraMusica
      musicaChunk <- sdlInit musica
      tocaMusica musicaChunk
      return it {estadoJogo = Jogar, jogo = jogoInicial02}
  | escolheMapa03 (px, py) = do
      paraMusica
      musicaChunk <- sdlInit musica
      tocaMusica musicaChunk
      return it {estadoJogo = Jogar, jogo = jogoInicial03}
  | otherwise = return it
  where
    musica = "app/musica/Jogar.flac"

-- | Função que reage ao Jogo.
--
-- Esta função realiza as seguintes operações:
--
-- * 1. Caso o jogador tenha clicado no botão de "Restart", para a música atualmente a tocar, carrega a música do menu e começa a tocá-la, limpando os parâmetros do estado gráfico relativo a torres atualmente em posicionamento e revertendo o jogo para a fase de escolha de mapa;
--
-- * 2. Caso o jogador tenha clicado no botão para encerrar o jogo, o programa é encerrado com @exitSuccess@, importado de @System.Exit@;
--
-- * 3. Caso o jogador tenha clicado numa das torres e não estiver nenhuma torre a ser posicionado (i.e., não está a imagem de nenhuma torre a ser arrastada no ecrã), então carrega os valores dessa torre em posicionamento para o estado gráfico, permitindo que a sua imagem seja arrastada pelo cursor;
--
-- * 4. Caso o jogador tenha clicado numa qualquer posição do ecrã com uma torre selecionada, se o jogo resultante do posicionamento dessa torre for válido, esta será adicionada à lista de torres do jogo, com a sua posição no centro do(a) isómero/célula do mapa em que o jogador clicou.
--   Para as condições que o jogo tem de obedecer, verifique a documentação referente ao ficheiro @Tarefa1.hs@;
--
-- * 5. Ignora qualquer outro evento de jogo.
reageJogo ::
  -- | Posição do cursor no ecrã de jogo
  (Float, Float) ->
  -- | Estado do ImmutableTowers atual
  ImmutableTowers ->
  -- | Estado do ImmutableTowers atualizado, fazendo uso de IO
  IO ImmutableTowers
reageJogo p it
  | escolheRestart p = do
      paraMusica
      musicaChunk <- sdlInit "app/musica/Menu.flac"
      tocaMusica musicaChunk
      return $ it {jogo = jogoInicial01, estadoJogo = EscolhaMapa, estadoGrafico = e {torreSelecionada = [], tipoTorre = []}}
  | escolheExit p = exitSuccess
  | botaoSelecionado it p && null (torreSelecionada e) = return $ it {estadoGrafico = e {torreSelecionada = [fst (selecionaTorre it p)], tipoTorre = [snd (selecionaTorre it p)]}}
  | not (null (torreSelecionada e)) =
      return $
        if validaJogo jogoAtualizado then it {estadoGrafico = eAtualizado, jogo = jogoAtualizado} else it {estadoGrafico = eAtualizado}
  | otherwise = return it
  where
    e = estadoGrafico it
    j = jogo it
    b = baseJogo j
    jogoAtualizado = j {torresJogo = torresJogo j ++ [colocaTorre it p], baseJogo = b {creditosBase = creditosBase b - procuraLoja (head $ tipoTorre e) (lojaJogo j)}}
    eAtualizado = e {torreSelecionada = [], tipoTorre = []}

-- | Função responsável por, dado um tipo de projétil/torre e a loja de jogo, procurar o preço da torre passada como argumento.
--
-- Uma vez que esta função só é chamada com um dos três tipos de torre no jogo, será sempre devolvido um preço, sendo desnecessário o uso de um tipo de dados Maybe.
procuraLoja ::
  -- | Tipo da torre/projétil cujo preço se pretende obter
  TipoProjetil ->
  -- | Loja do jogo
  Loja ->
  -- | Preço da torre obtido
  Creditos
procuraLoja tipo ((pr, t) : r) =
  case tipo of
    Fogo -> if torreFogo == t then fromIntegral pr else procuraLoja Fogo r
    Gelo -> if torreGelo == t then fromIntegral pr else procuraLoja Gelo r
    Resina -> if torreResina == t then fromIntegral pr else procuraLoja Resina r

-- | Função que reage ao recomeço do jogo.
--
-- Esta função realiza as seguintes operações:
--
-- * 1. Caso o jogador tenha clicado no botão de "Restart", para a música atualmente a tocar, carrega a música do menu e começa a tocá-la, limpando os parâmetros do estado gráfico relativo a torres atualmente em posicionamento e revertendo o jogo para a fase de escolha de mapa;
--
-- * 2. Caso o jogador tenha clicado no botão para encerrar o jogo, o programa é encerrado com @exitSuccess@, importado de @System.Exit@;
reageRecomeco ::
  -- | Posição do cursor
  (Float, Float) ->
  -- | Estado atual do ImmutableTowers
  ImmutableTowers ->
  -- | Estado do ImmutableTowers atualizado, fazendo uso de IO
  IO ImmutableTowers
reageRecomeco (px, py) it
  | escolheRecomeco (px, py) = do
      paraMusica
      musicaChunk <- sdlInit "app/musica/Menu.flac"
      tocaMusica musicaChunk
      return $ it {jogo = jogoInicial01, estadoJogo = EscolhaMapa, estadoGrafico = e {torreSelecionada = [], tipoTorre = []}}
  | escolheSair (px, py) = exitSuccess
  | otherwise = return it
  where
    e = estadoGrafico it

-- | Função responsável por colocar torres em jogo.
--
-- Esta função realiza as seguintes operações:
--
-- * 1. Converte as coordenadas do cursor para coordenadas de matriz, arrendonda-as com defeito e soma 0.5 a ambas as componentes;
--
-- * 2. Adiciona a torre atualmente selecionada à lista das torres do jogo, definindo a sua posição como o resultado do cálculo anterior.
colocaTorre ::
  -- | Estado do ImmutableTowers
  ImmutableTowers ->
  -- | Posição do cursor no ecrã
  (Float, Float) ->
  -- | Torre a adicionar
  Torre
colocaTorre it p
  | tipoP == [Fogo] = torreFogo {posicaoTorre = pF}
  | tipoP == [Gelo] = torreGelo {posicaoTorre = pF}
  | tipoP == [Resina] = torreResina {posicaoTorre = pF}
  where
    e = estadoGrafico it
    vSup = verticeSuperior e
    tipoP = tipoTorre e
    (xM, yM) = converteCoords p vSup
    pF@(xF, yF) = (fromIntegral (floor xM) + 0.5, fromIntegral (floor yM) + 0.5)

-- | Função que verifica se o jogar clicou no botão da torre de fogo.
botaoFogo :: (Float, Float) -> Bool
botaoFogo (px, py) = (px >= -910 && px <= -790) && (py >= 160 && py <= 280)

-- | Função que verifica se o jogar clicou no botão da torre de gelo.
botaoGelo :: (Float, Float) -> Bool
botaoGelo (px, py) = (px >= -910 && px <= -790) && (py >= 290 && py <= 410)

-- | Função que verifica se o jogar clicou no botão da torre de resina.
botaoResina :: (Float, Float) -> Bool
botaoResina (px, py) = (px >= -910 && px <= -790) && (py >= 30 && py <= 150)

-- | Função que verifica se o jogador clicou no botão correspondente a uma das torres e se não há nenhuma torre atualmente selecionada.
botaoSelecionado :: ImmutableTowers -> (Float, Float) -> Bool
botaoSelecionado it p = (botaoFogo p || botaoGelo p || botaoResina p) && (null (torreSelecionada e))
  where
    e = estadoGrafico it

-- | Função auxiliar que devolve a imagem e tipo de uma torre selecionada, que serão guardados no estado gráfico do ImmutableTowers.
selecionaTorre :: ImmutableTowers -> (Float, Float) -> (Picture, TipoProjetil)
selecionaTorre it p
  | botaoFogo p = (geraTorreFogo it, Fogo)
  | botaoGelo p = (geraTorreGelo it, Gelo)
  | botaoResina p = (geraTorreResina it, Resina)

-- | Função que gera a imagem da torre de fogo, com a deslocação e escala corretas.
geraTorreFogo :: ImmutableTowers -> Picture
geraTorreFogo it = Translate 0 37.5 $ Scale 0.2 0.2 $ imgTorreFogo (imagensJogo it)

-- | Função que gera a imagem da torre de gelo, com a deslocação e escala corretas.
geraTorreGelo :: ImmutableTowers -> Picture
geraTorreGelo it = Translate 0 37.5 $ Scale 0.2 0.2 $ imgTorreGelo (imagensJogo it)

-- | Função que gera a imagem da torre de resina, com a deslocação e escala corretas.
geraTorreResina :: ImmutableTowers -> Picture
geraTorreResina it = Translate 0 37.5 $ Scale 0.2 0.2 $ imgTorreResina (imagensJogo it)

-- | Função que verifica se o jogador escolheu o botão "Restart" no menu de vitória/derrota.
escolheRecomeco :: (Float, Float) -> Bool
escolheRecomeco (px, py) = (px >= -150 && px <= -40) && (py >= -260 && py <= -140)

-- | Função que verifica se o jogador escolheu o botão de finalizar o jogo no menu de vitória/derrota.
escolheSair :: (Float, Float) -> Bool
escolheSair (px, py) = (px >= 40 && px <= 160) && (py >= -260 && py <= -150)

-- | Função que verifica se o jogador escolheu o botão "Start".
escolheStart :: (Float, Float) -> Bool
escolheStart (px, py) = (px >= -390 && px <= 335) && (py >= -230 && py <= -15)

-- | Função que verifica se o jogador escolheu o botão de finalizar o jogo.
escolheExit :: (Float, Float) -> Bool
escolheExit (px, py) = (px >= -900 && px <= -780) && (py >= -470 && py <= -370)

-- | Função que verifica se o jogador escolheu o botão "Restart" no menu de jogo.
escolheRestart :: (Float, Float) -> Bool
escolheRestart (px, py) = (px >= -900 && px <= -780) && (py >= -360 && py <= -240)

-- | Função que verifica se o jogador escolheu o mapa01.
escolheMapa01 :: (Float, Float) -> Bool
escolheMapa01 (px, py) = (px >= -770 && px <= -410) && (py >= 170 && py <= 285) || (px >= -780 && px <= -370) && (py >= -300 && py <= 140)

-- | Função que verifica se o jogador escolheu o mapa02.
escolheMapa02 :: (Float, Float) -> Bool
escolheMapa02 (px, py) = (px >= -180 && px <= 180) && (py >= 170 && py <= 285) || (px >= -210 && px <= 200) && (py >= -300 && py <= 140)

-- | Função que verifica se o jogador escolheu o mapa03.
escolheMapa03 :: (Float, Float) -> Bool
escolheMapa03 (px, py) = (px >= 410 && px <= 770) && (py >= 170 && py <= 285) || (px >= 370 && px <= 780) && (py >= -300 && py <= 140)
