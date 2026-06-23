-- |
-- Module      : Desenhar
-- Description : Representação visual do jogo
-- Copyright   : Tomé Francisco Amorim Moreira <a111907@alunos.uminho.pt>
--               Diogo Silva Fernandes <a110490@alunos.uminho.pt>
--
--
-- Módulo para a implementação da componente gráfica do projeto de LI1 em 2024/25.
module Desenhar where

import Graphics.Gloss
import ImmutableTowers
import LI12425

-- Dados utilizados

-- | Comprimento da janela
comprimento :: Int
comprimento = 1920

-- | Altura da janela
altura :: Int
altura = 1080

-- | Função responsável por desenhar todo o jogo
desenha :: ImmutableTowers -> Picture
desenha it = case estadoJogo it of
  Menu -> desenhaMenu (imagensExtra it)
  EscolhaMapa -> desenhaMenuMapa (imagensExtra it)
  Jogar -> Pictures [desenhaJogo (jogo it) (imagensJogo it) (imagensInimigos it), desenhaTorreSelecionada it]
  Fim cond -> case cond of
    Vitoria -> desenhaVitoria (imagensExtra it) (imagensJogo it)
    Derrota -> desenhaDerrota (imagensExtra it) (imagensJogo it)

-- | Função responsável por desenhar o jogo principal
desenhaJogo :: Jogo -> ImagemJogo -> ImagemInimigos -> Picture
desenhaJogo j imgsJogo imgsInimigos =
  Pictures
    [ desenhaMapaR j,
      desenhaInimigos j imgsInimigos,
      desenhaPortais j imgsJogo,
      desenhaBase j imgsJogo,
      desenhaTorres j imgsJogo,
      desenhaLoja imgsJogo,
      desenhaCreditos j imgsJogo,
      desenhaVidaBase j imgsJogo,
      desenhaExit imgsJogo
    ]

-- | Função que desenha a tela da derrota do jogador
desenhaDerrota :: ImagemExtra -> ImagemJogo -> Picture
desenhaDerrota imgsExtra imgsJogo = Pictures [imgLose, imgRecomeco, imgSair]
  where
    imgLose = imgDerrota imgsExtra
    imgRecomeco = Translate (-100) (-200) $ Scale 0.3 0.3 $ imgRestart imgsJogo
    imgSair = Translate 100 (-200) $ Scale 0.21 0.21 $ imgExit imgsJogo

-- | Função que desenha a tela de vitória do jogador
desenhaVitoria :: ImagemExtra -> ImagemJogo -> Picture
desenhaVitoria imgsExtra imgsJogo = Pictures [imgWin, imgRecomeco, imgSair]
  where
    imgWin = imgVitoria imgsExtra
    imgRecomeco = Translate (-100) (-200) $ Scale 0.3 0.3 (imgRestart imgsJogo)
    imgSair = Translate 100 (-200) $ Scale 0.21 0.21 (imgExit imgsJogo)

-- | Função que desenha o menu inicial do jogador
desenhaMenu :: ImagemExtra -> Picture
desenhaMenu imgs = Translate 0 0 imgMenu
  where
    imgMenu = imgInicial imgs

-- | Função que desenha o menu de escolha do mapa do jogador
desenhaMenuMapa :: ImagemExtra -> Picture
desenhaMenuMapa imgs = Translate 0 0 imgMapa
  where
    imgMapa = imgMapas imgs

-- | Função que desenha os créditos do jogador
desenhaCreditos :: Jogo -> ImagemJogo -> Picture
desenhaCreditos j imgs = Pictures [moedas, creditos]
  where
    creditosAtuais = creditosBase (baseJogo j)
    creditos
      | creditosAtuais < 1000 = Translate 650 400 $ Scale 0.6 0.6 $ Color white $ Text (show creditosAtuais)
      | otherwise = Translate 600 400 $ Scale 0.6 0.6 $ Color white $ Text (show creditosAtuais)
    moedas = Translate 850 430 $ Scale 0.4 0.4 (imgMoeda imgs)

-- | Função que desenha a vida da base do jogador
desenhaVidaBase :: Jogo -> ImagemJogo -> Picture
desenhaVidaBase j imgs = Pictures [imgVida, vida]
  where
    vidabase = vidaBase (baseJogo j)
    vida = Translate 650 260 $ Scale 0.6 0.6 $ Color white $ Text (show vidabase)
    imgVida = Translate 860 290 $ Scale 0.15 0.15 (imgCoracao imgs)

-- | Função que desenha o botão "Exit" do jogo
desenhaExit :: ImagemJogo -> Picture
desenhaExit imgs = Translate (-840) (-430) $ Scale 0.2 0.2 $ imgExit imgs

-- | Função responsável por desenhar as torres do jogo
desenhaTorres :: Jogo -> ImagemJogo -> Picture
desenhaTorres j imgs = Pictures $ map (\t -> desenhaTorre j t imgs) (torresJogo j)

-- | Função responsável por desenhar uma única torre do jogo
desenhaTorre :: Jogo -> Torre -> ImagemJogo -> Picture
desenhaTorre j tr imgs = case tipoProjetil (projetilTorre tr) of
  Gelo -> Translate x' (y' + 37.5) $ scale 0.2 0.2 (imgTorreGelo imgs)
  Fogo -> Translate x' (y' + 37.5) $ scale 0.2 0.2 (imgTorreFogo imgs)
  Resina -> Translate x' (y' + 37.5) $ scale 0.2 0.2 (imgTorreResina imgs)
  where
    (x', y') = moveIsometrico (posicaoTorre tr) (defineVerticeSuperior j)

-- | Função responsável por desenhar a base do jogo
desenhaBase :: Jogo -> ImagemJogo -> Picture
desenhaBase j imgs = Translate x' (y' + 10) $ scale 0.3 0.3 baseImg
  where
    baseImg = imgBase imgs
    (x', y') = moveIsometrico (posicaoBase (baseJogo j)) (defineVerticeSuperior j)

-- | Função responsável por desenhar os portais do jogo
desenhaPortais :: Jogo -> ImagemJogo -> Picture
desenhaPortais j imgs = Pictures $ map (\p -> desenhaPortal j p imgs) (portaisJogo j)

-- | Função responsável por desenhar um único portal
desenhaPortal :: Jogo -> Portal -> ImagemJogo -> Picture
desenhaPortal j p imgs = Translate x' (y' + 30) $ scale 0.4 0.4 portalImg
  where
    portalImg = imgPortal imgs
    (x', y') = moveIsometrico (posicaoPortal p) (defineVerticeSuperior j)

-- | Função responsável por desenhar os inimigos do jogo
desenhaInimigos :: Jogo -> ImagemInimigos -> Picture
desenhaInimigos j imgs = Pictures $ map (\p -> desenhaInimigo j p imgs) (inimigosJogo j)

-- | Função responsável por desenhar um único inimigo
desenhaInimigo :: Jogo -> Inimigo -> ImagemInimigos -> Picture
desenhaInimigo j i imgs
  | atingidoPorGelo = desenhaInimigoGelo j i imgs
  | atingidoPorFogo = desenhaInimigoFogo j i imgs
  | atingidoPorResina = desenhaInimigoResina j i imgs
  | otherwise = desenhaInimigoBasico j i imgs
  where
    atingidoPorGelo = any (\t -> tipoProjetil t == Gelo) (projeteisInimigo i)
    atingidoPorFogo = any (\t -> tipoProjetil t == Fogo) (projeteisInimigo i)
    atingidoPorResina = any (\t -> tipoProjetil t == Resina) (projeteisInimigo i)

-- | Função responsável por desenhar um único inimigo que não contém projéteis ativos
desenhaInimigoBasico :: Jogo -> Inimigo -> ImagemInimigos -> Picture
desenhaInimigoBasico j i imgs = case direcaoInimigo i of
  Norte -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoNorte imgs
  Sul -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoSul imgs
  Oeste -> Translate x' (y' + 20) $ scale 0.1 0.1 $ imgInimigoOeste imgs
  Este -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoEste imgs
  where
    (x',y') = moveIsometrico (posicaoInimigo i) (defineVerticeSuperior j)

-- | Função responsável por desenhar um único inimigo que contém Gelo nos projéteis ativos
desenhaInimigoGelo :: Jogo -> Inimigo -> ImagemInimigos -> Picture
desenhaInimigoGelo j i imgs = case direcaoInimigo i of
  Norte -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoNorteGelo imgs
  Sul -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoSulGelo imgs
  Oeste -> Translate x' (y' + 20) $ scale 0.1 0.1 $ imgInimigoOesteGelo imgs
  Este -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoEsteGelo imgs
  where
    (x', y') = moveIsometrico (posicaoInimigo i) (defineVerticeSuperior j)

-- | Função responsável por desenhar um único inimigo que contém Fogo nos projéteis ativos
desenhaInimigoFogo :: Jogo -> Inimigo -> ImagemInimigos -> Picture
desenhaInimigoFogo j i imgs = case direcaoInimigo i of
  Norte -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoNorteFogo imgs
  Sul -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoSulFogo imgs
  Oeste -> Translate x' (y' + 20) $ scale 0.1 0.1 $ imgInimigoOesteFogo imgs
  Este -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoEsteFogo imgs
  where
    (x', y') = moveIsometrico (posicaoInimigo i) (defineVerticeSuperior j)

-- | Função responsável por desenhar um único inimigo que contém Fogo nos projéteis ativos
desenhaInimigoResina :: Jogo -> Inimigo -> ImagemInimigos -> Picture
desenhaInimigoResina j i imgs = case direcaoInimigo i of
  Norte -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoNorteResina imgs
  Sul -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoSulResina imgs
  Oeste -> Translate x' (y' + 20) $ scale 0.1 0.1 $ imgInimigoOesteResina imgs
  Este -> Translate x' (y' + 15) $ scale 0.1 0.1 $ imgInimigoEsteResina imgs
  where
    (x', y') = moveIsometrico (posicaoInimigo i) (defineVerticeSuperior j)

-- | Função responsável por desenhar a torre selecionada pelo jogador e que é arrastada pelo mapa
desenhaTorreSelecionada :: ImmutableTowers -> Picture
desenhaTorreSelecionada it = Translate x y $ Pictures (torreSelecionada e)
  where
    e = estadoGrafico it
    (x, y) = cursor e

-- | Função responsável por desenhar a loja do jogo
desenhaLoja :: ImagemJogo -> Picture
desenhaLoja imgs =
  Pictures
    [ retanguloLateral,
      quadradoFogo,
      quadradoGelo,
      quadradoResina,
      torreGelo,
      torreFogo,
      torreResina,
      texto,
      tabelaPreco,
      botaoRestart
    ]
  where
    texto = Translate (-850) 460 $ Scale 0.5 0.5 $ imgLoja imgs
    retanguloLateral = Translate (-860) 450 $ color (makeColorI 63 124 180 255) $ rectangleSolid 250 900
    quadradoGelo =
      Pictures
        [ Translate (-850) 350 $ color (makeColorI 121 194 210 255) $ rectangleSolid 120 120,
          Translate (-850) 350 $ Scale 0.5 0.5 $ imgBordaGelo imgs
        ]
    quadradoFogo =
      Pictures
        [ Translate (-850) 220 $ color (makeColorI 240 116 116 255) $ rectangleSolid 120 120,
          Translate (-850) 220 $ Scale 0.5 0.5 $ imgBordaFogo imgs
        ]
    quadradoResina =
      Pictures
        [ Translate (-850) 90 $ color (makeColorI 241 255 142 255) $ rectangleSolid 120 120,
          Translate (-850) 90 $ Scale 0.5 0.5 $ imgBordaResina imgs
        ]
    torreGelo = Translate (-850) 350 $ Scale 0.2 0.2 $ imgTorreGelo imgs
    torreFogo = Translate (-850) 220 $ Scale 0.2 0.2 $ imgTorreFogo imgs
    torreResina = Translate (-850) 90 $ Scale 0.2 0.2 $ imgTorreResina imgs
    tabelaPreco = Translate (-760) 210 (imgMoedaPreco imgs)
    botaoRestart = Translate (-840) (-300) $ Scale 0.3 0.3 $ imgRestart imgs

-- | Estrutura base para a formação do mapa
isomero :: Picture
isomero = Scale 30 30 $ Pictures $ [Polygon [(0, 0), (0, 0.25), (2, 1.25), (2, 1)], Polygon [(0, 0), (0, 0.25), (-2, 1.25), (-2, 1)], Polygon [(0, 0.25), (2, 1.25), (0, 2.25), (-2, 1.25)]]

-- | Bloco de relva em perspectiva isométrica
relva :: Picture
relva =
  Scale 30 30 $
    Pictures $
      [ color (makeColorI 81 127 71 255) $ Polygon [(0, 0), (0, 0.25), (-2, 1.25), (-2, 1)],
        color (makeColorI 61 97 53 255) $ Polygon [(0, 0), (0, 0.25), (2, 1.25), (2, 1)],
        color (makeColorI 91 142 80 255) $ Polygon [(0, 0.25), (2, 1.25), (0, 2.25), (-2, 1.25)]
      ]

-- | Bloco de água em perspectiva isométrica
agua :: Picture
agua =
  Scale 30 30 $
    Pictures $
      [ color (makeColorI 143 204 217 255) $ Polygon [(0, 0), (0, 0.25), (-2, 1.25), (-2, 1)],
        color (makeColorI 121 194 210 255) $ Polygon [(0, 0), (0, 0.25), (2, 1.25), (2, 1)],
        color (makeColorI 154 209 221 255) $ Polygon [(0, 0.25), (2, 1.25), (0, 2.25), (-2, 1.25)]
      ]

-- | Bloco de terra em perspectiva isométrica
terra :: Picture
terra =
  Scale 30 30 $
    Pictures $
      [ color (makeColorI 167 125 83 255) $ Polygon [(0, 0), (0, 0.25), (-2, 1.25), (-2, 1)],
        color (makeColorI 129 96 62 255) $ Polygon [(0, 0), (0, 0.25), (2, 1.25), (2, 1)],
        color (makeColorI 186 140 93 255) $ Polygon [(0, 0.25), (2, 1.25), (0, 2.25), (-2, 1.25)]
      ]

-- | Função responsável por desenhar o bloco dependendo do terreno
desenhaIsomero :: Terreno -> Picture
desenhaIsomero t =
  case t of
    Terra -> terra
    Relva -> relva
    Agua -> agua

-- | Função que desenha uma linha do mapa
desenhaLinha :: [Terreno] -> (Float, Float) -> [Picture]
desenhaLinha [] _ = []
desenhaLinha (t : ts) (x, y) = (Translate (x * largura) (y * (altura / 2)) $ desenhaIsomero t) : desenhaLinha ts (x + 1, y - 1)
  where
    (largura, altura) = (60, 60)

-- | Função que desenha o mapa do jogo
desenhaMapa ::
  -- | Mapa do jogo
  Mapa ->
  -- | Tuplo no formato (linha,coluna)
  (Float, Float) ->
  -- | Tuplo no formato (x,y)
  (Float, Float) ->
  -- | Lista de picture
  [Picture]
desenhaMapa [] _ _ = []
desenhaMapa (ln : lns) (l, c) (x, y) = (Translate (x * dimX) (y * dimY) $ Pictures $ desenhaLinha ln (l, c)) : desenhaMapa lns (l, c) (x + 1, y + 1)
  where
    (dimX, dimY) = (-60, -30)

-- | Função que desenha o mapa do jogo já redimensionado
desenhaMapaR :: Jogo -> Picture
desenhaMapaR e = Translate 0 translacao $ Pictures $ desenhaMapa mapa (0, 0) (0, 0)
  where
    mapa = mapaJogo e
    (linhas, colunas) = (length mapa, length (head mapa))
    dimensao = max linhas colunas
    (dimX, dimY) = (60, 60)
    translacao = if even dimensao then (((fromIntegral dimensao / 2) - 1) * dimY) else (((fromIntegral (dimensao + 1) / 2) - 1) * dimY)

-- | Função que permite obter o valor em pixeis do vértice superior do mapa, informação usada para permitir a conversão de coordenadas de matriz em pixeis
defineVerticeSuperior :: Jogo -> Float
defineVerticeSuperior e = verticeSup
  where
    mapa = mapaJogo e
    (linhas, colunas) = (length mapa, length (head mapa))
    dimensao = max linhas colunas
    (dimX, dimY) = (60, 60)
    verticeSup = if even dimensao then ((fromIntegral dimensao / 2) * dimY) + 7.5 else (fromIntegral (dimensao + 1) / 2) * dimY + 7.5

-- | Função que, dada a abcissa de uma posição em coordenadas de matriz, gera um vetor deslocação em pixeis
vetorX :: Float -> (Float, Float)
vetorX x = (x * 60, x * (-30))

-- | Função que, dada uma posição em pixeis, a converte para a abcissa correspondente em coordenadas de matriz
matrizX :: (Float, Float) -> Float
matrizX (x, y) = ((x / 60) + (y / (-30))) / 2

-- | Função que, dada a ordenada de uma posição em coordenadas de matriz, gera um vetor deslocação em pixeis
vetorY :: Float -> (Float, Float)
vetorY y = (y * (-60), y * (-30))

-- | Função que, dada uma posição em pixeis, a converte para a abcissa correspondente em coordenadas de matriz
matrizY :: (Float, Float) -> Float
matrizY (x, y) = ((x / (-60)) + (y / (-30))) / 2

-- | Esta função permite converter coordenadas de matriz em coordenadas de gloss
moveIsometrico ::
  -- | Coordenadas em matriz
  (Float, Float) ->
  -- | Coordenadas do vértice superior
  Float ->
  -- | Coordenadas em pixeis
  (Float, Float)
moveIsometrico (x, y) vSup = (x1 + x2, vSup + y1 + y2)
  where
    (x1, y1) = vetorX x
    (x2, y2) = vetorY y

-- | Esta função permite converter as coordenadas de pixeis em coordenadas de matriz
converteCoords :: (Float, Float) -> Float -> (Float, Float)
converteCoords (x, y) vSup = (matrizX (x, y - vSup), matrizY (x, y - vSup))
