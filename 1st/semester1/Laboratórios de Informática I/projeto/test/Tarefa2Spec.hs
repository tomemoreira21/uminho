module Tarefa2Spec (testesTarefa2) where 
import Test.HUnit
import LI12425 
import Tarefa2

testesTarefa2 :: Test
testesTarefa2 = TestList [testeAlcance,testesSinergias,testesInimigo,testesTerminaJogo]

testesSinergias :: Test 
testesSinergias = TestList [testeDanoTorreFogo,testeVidaNaoNegativaGelo,
                            testesGeloFogo,testesResinaFogo,testesFogoResina,
                            testesIgual,testesGeloResina,testesGeloResinaFogo,testesSemProj]

testesInimigo :: Test 
testesInimigo = TestList [testeInimigoCorreto,testeInimigoAtualizado,testeAusenciaInimigos]

testesTerminaJogo :: Test 
testesTerminaJogo = TestList [testeGanhouJogo,testePerdeuJogo]

-- Testes inimigosNoAlcance 
-- Teste 1: Verificar a função inimigosNoAlcance 
testeAlcance :: Test 
testeAlcance = "Inimigos no alcance da torre" ~: 
    TestList [[] ~=? inimigosNoAlcance torre01 [inimigo02], -- Inimigo fora do alcance da Torre
              [inimigo01] ~=? inimigosNoAlcance torre01 [inimigo01] -- Inimigo dentro do alcance da Torre
              ]

-- Testes atingeInimigo
-- Teste 1: Verifica se o dano da torre de fogo reduz a vida do inimigo 
testeDanoTorreFogo :: Test
testeDanoTorreFogo =
  "Dano da torre de fogo" ~: 
  50 ~=? vidaInimigo (atingeInimigo torreFogo inimigo01)

-- Teste 2: Verifica se a vida do inimigo não fica negativa ao ser atingido por uma torre
testeVidaNaoNegativaGelo :: Test
testeVidaNaoNegativaGelo =
  "Vida nao negativa (gelo)" ~: 
  0 ~=? vidaInimigo (atingeInimigo torreGelo inimigo02)

-- Testes para as sinergias
-- Teste 1: Verifica o caso em que quando existe o Gelo e Fogo os mesmos se cancelam mutuamente 
testesGeloFogo :: Test 
testesGeloFogo = "Tipo do projétil da torre é Gelo e o inimigo encontra-se sobre o efeito de Fogo" ~:
                  [] ~=? atualizaProjeteis projGelo [projFogo]

-- Teste 2: Verifica o caso em que a torre tem um projétil do tipo Resina e o inimigo está sobre Fogo
testesResinaFogo :: Test 
testesResinaFogo = "Tipo do projétil da torre é Resina e o inimigo encontra-se sobre o efeito de Fogo" ~:
                    [projFogoDobroDuracao] ~=? atualizaProjeteis projResina [projFogo]

-- Teste 3: Verifica o caso em que a torre tem um projétil do tipo Fogo e o inimigo está sobre Resina 
testesFogoResina :: Test 
testesFogoResina = "Tipo do projétil da torre é Fogo e o inimigo encontra-se sobre o efeito de Resina" ~:
                    [projFogoDobroDuracao] ~=? atualizaProjeteis projFogo [projResina]

-- Teste 4: Verifica o caso em que a torre tem um projétil do mesmo tipo do projétil que está ativo no inimigo
testesIgual :: Test 
testesIgual = "Tipo do projétil da torre é igual ao tipo do projétil ativo no inimigo" ~: 
                [projGeloSomadaDuracao] ~=? atualizaProjeteis projGelo [projGelo] 

-- Teste 5: Verifica o caso da combinação de um projétil do tipo Gelo e outro do tipo Resina 
testesGeloResina :: Test 
testesGeloResina = "Combinação de um projétil do tipo Gelo e outro do tipo Resina" ~: 
                     [projGelo,projResina] ~=? atualizaProjeteis projGelo [projResina]

-- Teste 6: Verifica o caso em que o inimigo não contém projéteis ativos 
testesSemProj :: Test 
testesSemProj = "Inimigo não contém qualquer projétil ativo" ~: 
                 [projFogo] ~=? atualizaProjeteis projFogo []

-- Teste 7: Verifica o caso em que o inimigo se encontra sobre um projétil do tipo Gelo e outro do tipo Resina e é atingido por Fogo
testesGeloResinaFogo :: Test 
testesGeloResinaFogo = "Inimigo contém um projétil do tipo Gelo e outro do tipo Resina e é atingido por Fogo" ~:
                       [projResina] ~=? atualizaProjeteis projFogo [projGelo,projResina]

-- Testes para o ativoInimigo 
-- Teste 1: Verificar se o próximo inimigo é movido corretamente do portal para os inimigos ativos
testeInimigoCorreto :: Test
testeInimigoCorreto = "Deve mover o inimigo correto do portal para a lista de inimigos ativos" ~:
    (portalEsperado, [inimigo01]) ~=? ativaInimigo portalInicial []

-- Teste 2: Verificar se a lista de inimigos ativos é atualizada corretamente com inimigos já presentes
testeInimigoAtualizado :: Test
testeInimigoAtualizado = "Deve mover o inimigo e adicionar à lista já existente" ~:
    (portalEsperado, [inimigo02, inimigo01]) ~=? ativaInimigo portalInicial [inimigo02]

-- Teste 3: Verificar o comportamento do portal quando não há inimigos na primeira onda
testeAusenciaInimigos :: Test 
testeAusenciaInimigos = "Deve remover essa mesma onda quando a lista de inimigos vazio e permanecer o resto inalterado" ~:
    (portalAtualizado, [inimigo02]) ~=? ativaInimigo portalEsperado [inimigo02]

onda1 :: Onda 
onda1 = Onda 
      {inimigosOnda = [inimigo01],
       cicloOnda = 2,
       tempoOnda = 1,
       entradaOnda = 1}
  
onda2 :: Onda 
onda2 = Onda 
       {inimigosOnda = [inimigo02],
        cicloOnda = 1,
        tempoOnda = 2,
        entradaOnda = 1}

portalInicial :: Portal 
portalInicial = Portal 
          {posicaoPortal = (1,1),
           ondasPortal = [onda1,onda2]
          }

onda1Esperada :: Onda
onda1Esperada = Onda 
    {inimigosOnda = [], -- Lança o Inimigo 
     cicloOnda = 2,
     tempoOnda = 2, -- Atualiza o tempoOnda igualando-o ao cicloOnda
     entradaOnda = 1} 

portalEsperado :: Portal 
portalEsperado = Portal 
          {posicaoPortal = (1,1),
           ondasPortal = [onda1Esperada,onda2]}
    
portalAtualizado :: Portal 
portalAtualizado = Portal 
          {posicaoPortal = (1,1),
           ondasPortal = [onda2]}

-- Testes terminaJogo
-- Teste 1: Verifica se venceu o jogo, cumprindo todos os requisitos que caracterizam a sua vitória
testeGanhouJogo :: Test 
testeGanhouJogo = "Venceu o jogo" ~: True ~=? ganhouJogo jogoVitoria

baseVitoria :: Base 
baseVitoria = Base 
          {vidaBase = 50, -- Vida Base positiva
           posicaoBase = (1,1),
           creditosBase = 100
          }

jogoVitoria :: Jogo 
jogoVitoria = Jogo 
          {baseJogo = baseVitoria,
           portaisJogo = [portalSemInimigos], -- Ausência de inimigos por lançar
           torresJogo = [],
           mapaJogo = [[Terra,Terra],[Terra,Terra]],
           inimigosJogo = [], -- Ausência de inimigos ativos
           lojaJogo = []}

portalSemInimigos :: Portal 
portalSemInimigos = Portal
          {posicaoPortal = (0.5,0.5),
           ondasPortal = []
          }

-- Teste 2: Verifica se perde o jogo, cumprindo todos os requisitos que caracterizam a sua derrota
testePerdeuJogo :: Test 
testePerdeuJogo = "Perdeu o jogo" ~: True ~=? perdeuJogo jogoDerrota 

jogoDerrota :: Jogo 
jogoDerrota = Jogo 
          {baseJogo = baseDerrota,  
           portaisJogo = [], 
           torresJogo = [],
           mapaJogo = [[Terra,Terra],[Terra,Terra]],
           inimigosJogo = [], 
           lojaJogo = []}

baseDerrota :: Base 
baseDerrota = Base 
        { vidaBase = -1, -- Vida Base Negativa
          posicaoBase = (1,1),
          creditosBase = 100
        }

projGelo :: Projetil 
projGelo = Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 3}

projGeloSomadaDuracao :: Projetil 
projGeloSomadaDuracao = Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 6}

projFogo :: Projetil 
projFogo = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}

projResina :: Projetil 
projResina = Projetil {tipoProjetil = Resina, duracaoProjetil = Infinita}

projFogoDobroDuracao :: Projetil 
projFogoDobroDuracao = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 6}

-- Torre de Gelo 
torreGelo :: Torre
torreGelo = Torre
  { posicaoTorre = (0, 0),
    danoTorre = 25,
    alcanceTorre = 10,
    rajadaTorre = 1,
    cicloTorre = 2,
    tempoTorre = 0,
    projetilTorre = Projetil { tipoProjetil = Gelo, duracaoProjetil = Finita 3 }
  }

-- Torre de Fogo 
torreFogo :: Torre
torreFogo = Torre
  { posicaoTorre = (1, 1),
    danoTorre = 50,
    alcanceTorre = 8,
    rajadaTorre = 1,
    cicloTorre = 3,
    tempoTorre = 0,
    projetilTorre = Projetil { tipoProjetil = Fogo, duracaoProjetil = Finita 2 }
  }

torre01 :: Torre 
torre01 = Torre 
    {posicaoTorre = (2,0),
     danoTorre = 25,
     alcanceTorre = 1,
     rajadaTorre = 1,
     cicloTorre = 2,
     tempoTorre = 0,
     projetilTorre = Projetil { tipoProjetil = Gelo, duracaoProjetil = Finita 3 }
        }

inimigo01 :: Inimigo
inimigo01 = Inimigo
  { posicaoInimigo = (1,0),
    direcaoInimigo = Norte,
    vidaInimigo = 100,
    velocidadeInimigo = 2,
    ataqueInimigo = 15,
    butimInimigo = 10,
    projeteisInimigo = []
  }

inimigo02 :: Inimigo
inimigo02 = Inimigo
  { posicaoInimigo = (3,1),
    direcaoInimigo = Sul,
    vidaInimigo = 10,
    velocidadeInimigo = 4,
    ataqueInimigo = 10,
    butimInimigo = 5,
    projeteisInimigo = []
  }
