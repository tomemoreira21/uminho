-- |
-- Module      : ImmutableTowers
-- Description : Funções e tipos necessários ao jogo
-- Copyright   : Tomé Francisco Amorim Moreira <a111907@alunos.uminho.pt>
--               Diogo Silva Fernandes <a110490@alunos.uminho.pt>
--
--
-- Módulo para a implementação de tipos de dados e funções necessárias ao projeto de LI1 em 2024/25.
module ImmutableTowers where

import Graphics.Gloss
import LI12425
import SDL qualified
import SDL.Mixer qualified as Mixer

-- | Função que inicializa o SDL, carrega uma música de um ficheiro e devolve a música carregada
sdlInit ::
  -- | Nome ou caminho do ficheiro de música a carregar
  String ->
  -- | Música carregada devolvida
  IO Mixer.Chunk
sdlInit s = do
  SDL.initialize [SDL.InitAudio]
  Mixer.openAudio Mixer.defaultAudio 256
  Mixer.load s

-- | Esta função recebe a música carregada por @sdlInit@ e começa a tocá-la em loop infinito
tocaMusica ::
  -- | Música carregada por @sdlInit@
  Mixer.Chunk ->
  -- | Efeito colateral: tocar a música
  IO ()
tocaMusica m = do
  Mixer.playForever m

-- | Função que para a música atualmente a tocar
paraMusica ::
  -- | Efeito colateral: para a música
  IO ()
paraMusica = do
  Mixer.haltMusic
  Mixer.closeAudio
  SDL.quit

-- | Gera uma sequência de ondas de inimigos, definindo a quantidade e tipos de inimigos, ciclo, e entrada de cada onda.
geraOndas ::
  -- | Portal a que as ondas pertencem
  Portal ->
  -- | Número de ondas a gerar
  Int ->
  -- | Número de inimigos a acrescentar a cada onda
  Int ->
  -- | Lista de pares com cada tipo de inimigo e o número de cada um destes a gerar na primeira onda
  [(Inimigo, Int)] ->
  -- | Ciclo de cada onda
  Tempo ->
  -- | Entrada de cada onda
  Tempo ->
  -- | Lista de ondas
  [Onda]
geraOndas _ _ _ [] _ _ = []
geraOndas _ 0 _ _ _ _ = []
geraOndas p n s li c e =
  Onda
    { inimigosOnda = isOnda,
      cicloOnda = c,
      tempoOnda = c,
      entradaOnda = e
    }
    : geraOndas p (n - 1) s (map (\(i, ni) -> (i, ni + s)) li) c (e + stepEntrada * 2)
  where
    isOnda = geraInimigosOnda p li
    stepEntrada = fromIntegral (length isOnda) * c

-- | Função auxiliar responsável por gerar uma lista com um certo número de inimigos de determinado tipo, para um portal específico
geraInimigosOnda ::
  -- | Portal no qual a onda a gerar por @geraOndas@ será inserida
  Portal ->
  -- | Lista de pares contendo o tipo de inimigos e o número destes de cada tipo respetivo a gerar
  [(Inimigo, Int)] ->
  -- | Lista com os inimigos gerados
  [Inimigo]
geraInimigosOnda _ [] = []
geraInimigosOnda p ((i, n) : r) = geraInimigos n i p ++ geraInimigosOnda p r

-- | Função auxiliar responsável por gerar um certo número de inimigos de um mesmo tipo
geraInimigos ::
  -- | Número de inimigos a gerar
  Int ->
  -- | Tipo de inimigos a gerar
  Inimigo ->
  -- | Portal ao qual os inimigos gerados pertencerão
  Portal ->
  -- | Lista de inimigos gerados
  [Inimigo]
geraInimigos 0 _ _ = []
geraInimigos n i p = i {posicaoInimigo = posicaoPortal p} : geraInimigos (n - 1) i p

-- | Tipo de dados corresponde ao estado global do jogo ImmutableTowers
data ImmutableTowers = ImmutableTowers
  { -- | Tipo correspondente ao jogo em si
    jogo :: Jogo,
    -- | Tipo correspondente ao estado do ImmutableTowers
    estadoJogo :: EstadoJogo,
    -- | Tipo que armazena as imagens do jogo
    imagensJogo :: ImagemJogo,
    -- | Tipo que armazena as imagens adicionais
    imagensExtra :: ImagemExtra,
    -- | Tipo que armazena as imagens dos inimigos em jogo
    imagensInimigos :: ImagemInimigos,
    -- | Tipo que guarda o estado gráfico do ImmutableTowers
    estadoGrafico :: EstadoGrafico
  }

-- | Record que armazena as imagens de jogo
data ImagemJogo = ImagemJogo
  { -- | Imagem do portal
    imgPortal :: Picture,
    -- | Imagem da base
    imgBase :: Picture,
    -- | Imagem da torre de Gelo
    imgTorreGelo :: Picture,
    -- | Imagem da torre de Fogo
    imgTorreFogo :: Picture,
    -- | Imagem da torre de Resina
    imgTorreResina :: Picture,
    -- | Imagem da loja
    imgLoja :: Picture,
    -- | Imagem do coração usado na vida da base
    imgCoracao :: Picture,
    -- | Textura para a loja da torre de Fogo
    imgBordaFogo :: Picture,
    -- | Textura para a loja da torre de Gelo
    imgBordaGelo :: Picture,
    -- | Textura para  a loja da torre de Resina
    imgBordaResina :: Picture,
    -- | Textura de uma moeda
    imgMoeda :: Picture,
    -- | Imagem com o preço de cada uma das torres
    imgMoedaPreco :: Picture,
    -- | Imagem do botão de Restart
    imgRestart :: Picture,
    -- | Imagem do botão de Exit
    imgExit :: Picture
  }

-- | Record que armazena imagens extra ao jogo
data ImagemExtra = ImagemExtra
  { -- | Tela inicial do jogo
    imgInicial :: Picture,
    -- | Tela de escolha do mapa do jogo
    imgMapas :: Picture,
    -- | Tela da derrota do jogo
    imgDerrota :: Picture,
    -- | Tela da vitória do jogo
    imgVitoria :: Picture
  }

-- | Record que contém as imagens dos inimigos em jogo
data ImagemInimigos = ImagemInimigos
  { -- | Imagem do inimigo sem projéteis ativos no movimento para Norte
    imgInimigoNorte :: Picture,
    -- | Imagem do inimigo sobre Gelo no movimento para Norte
    imgInimigoNorteGelo :: Picture,
    -- | Imagem do inimigo sobre Fogo no movimento para Norte
    imgInimigoNorteFogo :: Picture,
    -- | Imagem do inimigo sobre Resina no movimento para Norte
    imgInimigoNorteResina :: Picture,
    -- | Imagem do inimigo sem projéteis ativos no movimento para Sul
    imgInimigoSul :: Picture,
    -- | Imagem do inimigo sobre Gelo no movimento para Sul
    imgInimigoSulGelo :: Picture,
    -- | Imagem do inimigo sobre Fogo no movimento para Sul
    imgInimigoSulFogo :: Picture,
    -- | Imagem do inimigo sobre Resina no movimento para Sul
    imgInimigoSulResina :: Picture,
    -- | Imagem do inimigo sem projéteis ativos no movimento para Oeste
    imgInimigoOeste :: Picture,
    -- | Imagem do inimigo sobre Gelo no movimento para Oeste
    imgInimigoOesteGelo :: Picture,
    -- | Imagem do inimigo sobre Fogo no movimento para Oeste
    imgInimigoOesteFogo :: Picture,
    -- | Imagem do inimigo sobre Resina no movimento para Oeste
    imgInimigoOesteResina :: Picture,
    -- | Imagem do inimigo sem projéteis ativos no movimento para Este
    imgInimigoEste :: Picture,
    -- | Imagem do inimigo sobre Gelo no movimento para Este
    imgInimigoEsteGelo :: Picture,
    -- | Imagem do inimigo sobre Fogo no movimento para Este
    imgInimigoEsteFogo :: Picture,
    -- | Imagem do inimigo sobre Resina no movimento para Este
    imgInimigoEsteResina :: Picture
  }

-- | Record que armazena o estado gráfico do ImmutableTowers
data EstadoGrafico = EstadoGrafico
  { -- | Dimensão da janela
    dimensao :: (Int, Int),
    -- | Posição do cursor
    cursor :: (Float, Float),
    -- | Imagem da torre em posicionamento
    torreSelecionada :: [Picture],
    -- | Tipo do projétil disparado pela torre em posicionamento
    tipoTorre :: [TipoProjetil],
    -- | Ordenada do vértice superior do mapa
    verticeSuperior :: Float
  }

-- | Tipo de dados que visa representar o estado ou fase atual do ImmutableTowers
data EstadoJogo
  = -- | Momento em que se encontra no menu inicial
    Menu
  | -- | Momento de escolha do mapa
    EscolhaMapa
  | -- | Momento em que se encontra a jogar
    Jogar
  | -- | Momento em que o jogo se encerra
    Fim Resultado
  deriving (Eq, Show)

-- | Tipo de dados representante do resultado do jogo
data Resultado
  = -- | Jogo resulta em vitória para o jogador
    Derrota
  | -- | Jogo resulta em derrota para o jogador
    Vitoria
  deriving (Eq, Show)

-- NOTA: Definição de valores de jogo para os jogos 1, 2 e 3, que se encontram dispostos por ordem crescente de dificuldade

-- Características do jogo01 (nível fácil)
mapa01 :: Mapa
mapa01 =
  [ [t, t, t, r, r, r, a, a, a, a, a, a],
    [r, r, t, r, r, r, a, a, a, a, a, a],
    [r, r, t, r, r, r, a, a, a, a, a, a],
    [r, r, t, r, r, r, a, a, a, a, a, a],
    [r, r, t, r, r, r, a, a, r, r, r, r],
    [r, r, t, r, r, r, a, a, r, r, r, r],
    [r, r, t, t, t, t, t, t, t, t, t, t],
    [r, r, t, r, r, r, a, a, r, r, r, r],
    [r, r, t, r, r, r, a, a, r, r, r, r],
    [r, r, t, r, r, r, a, a, r, r, r, r],
    [r, r, t, r, r, r, a, a, r, r, r, r],
    [t, t, t, a, a, a, a, a, a, a, a, a]
  ]
  where
    t = Terra
    r = Relva
    a = Agua

baseJogo01 :: Base
baseJogo01 =
  Base
    { vidaBase = 50,
      posicaoBase = (11.5, 6.5),
      creditosBase = 100
    }

portal1Jogo01 :: Portal
portal1Jogo01 =
  Portal
    { posicaoPortal = (0.5, 0.5),
      ondasPortal = geraOndas portal1Jogo01 5 2 [(inimigoBasico, 2), (inimigoLento, 1)] 1 3
    }

portal2Jogo01 :: Portal
portal2Jogo01 =
  Portal
    { posicaoPortal = (0.5, 11.5),
      ondasPortal = geraOndas portal2Jogo01 3 3 [(inimigoRapido, 3)] 1 3
    }

jogoInicial01 :: Jogo
jogoInicial01 =
  Jogo
    { baseJogo = baseJogo01,
      portaisJogo = [portal1Jogo01, portal2Jogo01],
      torresJogo = [],
      mapaJogo = mapa01,
      inimigosJogo = [],
      lojaJogo = lojaDoJogo
    }

-- Características do jogo02 (nível médio)
mapa02 :: Mapa
mapa02 =
  [ [t, t, t, t, t, t, t, t, t, t, t, t],
    [r, t, r, r, r, r, r, a, a, a, a, a],
    [r, t, r, r, r, r, r, a, a, a, a, a],
    [r, t, r, r, r, r, r, a, a, a, a, a],
    [r, t, r, r, r, r, r, r, r, r, r, r],
    [r, t, r, r, r, r, r, r, r, r, r, r],
    [r, t, r, r, r, r, r, r, r, r, r, r],
    [r, t, r, r, r, r, r, r, r, r, r, r],
    [a, t, a, a, a, r, a, a, a, a, a, a],
    [a, t, a, a, a, r, a, a, a, a, a, a],
    [a, t, r, r, r, r, r, r, r, r, r, r],
    [a, t, t, t, t, t, t, t, t, t, t, t]
  ]
  where
    t = Terra
    r = Relva
    a = Agua

baseJogo02 :: Base
baseJogo02 =
  Base
    { vidaBase = 50,
      posicaoBase = (1.5, 11.5),
      creditosBase = 100
    }

portal1Jogo02 :: Portal
portal1Jogo02 =
  Portal
    { posicaoPortal = (0.5, 0.5),
      ondasPortal = geraOndas portal1Jogo02 3 5 [(inimigoLento, 5)] 1 2
    }

portal2Jogo02 :: Portal
portal2Jogo02 =
  Portal
    { posicaoPortal = (11.5, 0.5),
      ondasPortal = geraOndas portal2Jogo02 5 2 [(inimigoRapido, 3), (inimigoBasico, 5), (inimigoRapido, 3)] 1 3
    }

portal3Jogo02 :: Portal
portal3Jogo02 =
  Portal
    { posicaoPortal = (11.5, 11.5),
      ondasPortal = geraOndas portal3Jogo02 6 3 [(inimigoBasico, 5)] 0.5 1
    }

jogoInicial02 :: Jogo
jogoInicial02 =
  Jogo
    { baseJogo = baseJogo02,
      portaisJogo = [portal1Jogo02, portal2Jogo02, portal3Jogo02],
      torresJogo = [],
      mapaJogo = mapa02,
      inimigosJogo = [],
      lojaJogo = lojaDoJogo
    }

-- Características do jogo03 (nível difícil)
mapa03 :: Mapa
mapa03 =
  [ [r, r, r, r, r, r, r, t, t, t, t, t],
    [r, r, r, r, r, r, r, t, a, a, a, a],
    [r, r, r, r, r, r, r, t, a, a, a, a],
    [t, t, t, t, t, t, t, t, t, t, t, t],
    [t, r, r, r, r, r, r, r, r, r, r, r],
    [t, r, r, r, r, r, r, r, r, r, r, r],
    [t, r, r, r, r, r, r, r, r, r, r, r],
    [t, r, r, r, r, r, r, r, r, r, r, r],
    [t, a, a, a, a, a, a, a, a, a, a, a],
    [t, a, a, a, a, a, a, a, a, a, a, a],
    [t, a, a, a, a, a, a, a, a, a, a, a],
    [t, t, t, t, t, t, t, r, r, r, r, r]
  ]
  where
    t = Terra
    r = Relva
    a = Agua

baseJogo03 :: Base
baseJogo03 =
  Base
    { vidaBase = 50,
      posicaoBase = (0.5, 3.5),
      creditosBase = 100
    }

portal1Jogo03 :: Portal
portal1Jogo03 =
  Portal
    { posicaoPortal = (11.5, 0.5),
      ondasPortal = geraOndas portal1Jogo03 5 3 [(inimigoLento, 4), (inimigoBasico, 4)] 1 1
    }

portal2Jogo03 :: Portal
portal2Jogo03 =
  Portal
    { posicaoPortal = (11.5, 3.5),
      ondasPortal = geraOndas portal2Jogo03 8 2 [(inimigoRapido, 5)] 0.5 1
    }

portal3Jogo03 :: Portal
portal3Jogo03 =
  Portal
    { posicaoPortal = (6.5, 11.5),
      ondasPortal = geraOndas portal3Jogo03 8 5 [(inimigoBasico, 10)] 0.2 1
    }

jogoInicial03 :: Jogo
jogoInicial03 =
  Jogo
    { baseJogo = baseJogo03,
      portaisJogo = [portal1Jogo03, portal2Jogo03, portal3Jogo03],
      torresJogo = [],
      mapaJogo = mapa03,
      inimigosJogo = [],
      lojaJogo = lojaDoJogo
    }

-- Características da torres
torreGelo :: Torre
torreGelo =
  Torre
    { posicaoTorre = (0, 0), -- Posição deve se ignorada
      danoTorre = 25,
      alcanceTorre = 3,
      rajadaTorre = 5,
      cicloTorre = 3,
      tempoTorre = 2,
      projetilTorre = Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 2}
    }

torreFogo :: Torre
torreFogo =
  Torre
    { posicaoTorre = (0, 0), -- Posição deve se ignorada
      danoTorre = 50,
      alcanceTorre = 3,
      rajadaTorre = 5,
      cicloTorre = 3,
      tempoTorre = 2,
      projetilTorre = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}
    }

torreResina :: Torre
torreResina =
  Torre
    { posicaoTorre = (0, 0), -- Posição deve se ignorada
      danoTorre = 50,
      alcanceTorre = 3,
      rajadaTorre = 5,
      cicloTorre = 3,
      tempoTorre = 2,
      projetilTorre = Projetil {tipoProjetil = Resina, duracaoProjetil = Infinita}
    }

lojaDoJogo :: Loja
lojaDoJogo = [(50, torreGelo), (60, torreFogo), (40, torreResina)]

-- Tipos de inimigos
-- Inimigo rápido mas com menos vida
inimigoRapido :: Inimigo
inimigoRapido =
  Inimigo
    { posicaoInimigo = (0, 0), -- posição deve ser ignorada
      direcaoInimigo = Este,
      vidaInimigo = 75,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 10,
      projeteisInimigo = []
    }

-- Inimigo lento mas com mais vida
inimigoLento :: Inimigo
inimigoLento =
  Inimigo
    { posicaoInimigo = (0, 0), -- posição deve ser ignorada
      direcaoInimigo = Este,
      vidaInimigo = 125,
      velocidadeInimigo = 0.5,
      ataqueInimigo = 20,
      butimInimigo = 10,
      projeteisInimigo = []
    }

-- Inimigo normal
inimigoBasico :: Inimigo
inimigoBasico =
  Inimigo
    { posicaoInimigo = (0, 0), -- posição deve ser ignorada
      direcaoInimigo = Este,
      vidaInimigo = 100,
      velocidadeInimigo = 0.75,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = []
    }
