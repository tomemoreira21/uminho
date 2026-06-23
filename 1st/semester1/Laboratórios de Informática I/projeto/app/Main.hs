-- |
-- Module      : Main
-- Description : Módulo principal do projeto
-- Copyright   : Tomé Francisco Amorim Moreira <a111907@alunos.uminho.pt>
--               Diogo Silva Fernandes <a110490@alunos.uminho.pt>
--
--
-- Módulo para a implementação principal do projeto de LI1 em 2024/25.
module Main where

import Desenhar
import Eventos
import Graphics.Gloss
import Graphics.Gloss.Interface.IO.Game
import ImmutableTowers
import Tempo

-- | Função responsável por carregar as imagens usados no jogo
carregarImagensJogo :: IO ImagemJogo
carregarImagensJogo = do
  portal <- loadBMP "app/imagens/portal.bmp"
  base <- loadBMP "app/imagens/base.bmp"
  torreGeloJogo <- loadBMP "app/imagens/torreGelo.bmp"
  torreFogoJogo <- loadBMP "app/imagens/torreFogo.bmp"
  torreResinaJogo <- loadBMP "app/imagens/torreResina.bmp"
  loja <- loadBMP "app/imagens/loja.bmp"
  vida <- loadBMP "app/imagens/vida.bmp"
  bordaFogo <- loadBMP "app/imagens/bordaFogo.bmp"
  bordaGelo <- loadBMP "app/imagens/bordaGelo.bmp"
  bordaResina <- loadBMP "app/imagens/bordaResina.bmp"
  moeda <- loadBMP "app/imagens/moeda.bmp"
  moedaPreco <- loadBMP "app/imagens/lojaMoedas.bmp"
  restart <- loadBMP "app/imagens/restart.bmp"
  exit <- loadBMP "app/imagens/exit.bmp"
  return $ ImagemJogo portal base torreGeloJogo torreFogoJogo torreResinaJogo loja vida bordaFogo bordaGelo bordaResina moeda moedaPreco restart exit

-- | Função responsável por carregar as imagens extra usadas no jogo
carregarImagensExtra :: IO ImagemExtra
carregarImagensExtra = do
  menuInicial <- loadBMP "app/imagensIniciais/imagemInicial.bmp"
  menuMapas <- loadBMP "app/imagensIniciais/imagemMapas.bmp"
  menuDerrota <- loadBMP "app/imagensIniciais/imagemDerrota.bmp"
  menuVitoria <- loadBMP "app/imagensIniciais/imagemVitoria.bmp"
  return $ ImagemExtra menuInicial menuMapas menuDerrota menuVitoria

-- | Função responsável por carregar as imagens dos inimigos usadas no jogo
carregarImagensInimigos :: IO ImagemInimigos
carregarImagensInimigos = do
  inimigoNorte <- loadBMP "app/imagensInimigos/inimigoNorte.bmp"
  inimigoNorteGelo <- loadBMP "app/imagensInimigos/inimigoNorteGelo.bmp"
  inimigoNorteFogo <- loadBMP "app/imagensInimigos/inimigoNorteFogo.bmp"
  inimigoNorteResina <- loadBMP "app/imagensInimigos/inimigoNorteResina.bmp"
  inimigoSul <- loadBMP "app/imagensInimigos/inimigoSul.bmp"
  inimigoSulGelo <- loadBMP "app/imagensInimigos/inimigoSulGelo.bmp"
  inimigoSulFogo <- loadBMP "app/imagensInimigos/inimigoSulFogo.bmp"
  inimigoSulResina <- loadBMP "app/imagensInimigos/inimigoSulResina.bmp"
  inimigoOeste <- loadBMP "app/imagensInimigos/inimigoOeste.bmp"
  inimigoOesteGelo <- loadBMP "app/imagensInimigos/inimigoOesteGelo.bmp"
  inimigoOesteFogo <- loadBMP "app/imagensInimigos/inimigoOesteFogo.bmp"
  inimigoOesteResina <- loadBMP "app/imagensInimigos/inimigoOesteResina.bmp"
  inimigoEste <- loadBMP "app/imagensInimigos/inimigoEste.bmp"
  inimigoEsteGelo <- loadBMP "app/imagensInimigos/inimigoEsteGelo.bmp"
  inimigoEsteFogo <- loadBMP "app/imagensInimigos/inimigoEsteFogo.bmp"
  inimigoEsteResina <- loadBMP "app/imagensInimigos/inimigoEsteResina.bmp"
  return $ ImagemInimigos inimigoNorte inimigoNorteGelo inimigoNorteFogo inimigoNorteResina inimigoSul inimigoSulGelo inimigoSulFogo inimigoSulResina inimigoOeste inimigoOesteGelo inimigoOesteFogo inimigoOesteResina inimigoEste inimigoEsteGelo inimigoEsteFogo inimigoEsteResina

-- | Características da janela do jogo
janela :: Display
janela = InWindow "Immutable Towers" (1920, 1080) (0, 0)

-- | Cor do background do jogo
fundo :: Color
fundo = makeColorI 63 124 180 255

-- | Frame rate do jogo
fr :: Int
fr = 60

-- | Estado gráfico inicial do jogo
grafismo :: ImmutableTowers -> EstadoGrafico
grafismo it =
  EstadoGrafico
    { dimensao = (1920, 1080),
      cursor = (0, 0),
      torreSelecionada = [],
      tipoTorre = [],
      verticeSuperior = defineVerticeSuperior (jogo it)
    }

-- | Função principal Main
main :: IO ()
main = do
  imagensDoJogo <- carregarImagensJogo
  imagensExtraJogo <- carregarImagensExtra
  imagensDosInimigos <- carregarImagensInimigos
  musicaChunk <- sdlInit "app/musica/Menu.flac"
  let it =
        ImmutableTowers
          { jogo = jogoInicial01,
            estadoJogo = Menu,
            imagensJogo = imagensDoJogo,
            imagensExtra = imagensExtraJogo,
            imagensInimigos = imagensDosInimigos,
            estadoGrafico = grafismo it
          }
  putStrLn "Hello from Immutable Towers!"
  tocaMusica musicaChunk
  playIO janela fundo fr it desenhaWrapper reageEventos reageTempo

-- | Função auxiliar que permite chamar @desenha@, que não desenvolve tipo IO (Picture) na função @playIO@, que o requer
desenhaWrapper :: ImmutableTowers -> IO Picture
desenhaWrapper it = return (desenha it)
