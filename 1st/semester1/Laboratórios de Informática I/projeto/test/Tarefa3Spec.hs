module Tarefa3Spec (testesTarefa3) where

import LI12425
import Tarefa1 (proximoPasso)
import Tarefa3
import Test.HUnit

testesTarefa3 :: Test
testesTarefa3 = TestList [testesPortais, testesInimigos, testesTorres]

testesInimigos :: Test
testesInimigos =
  TestList
    [ testesAplicaProjetilInimigo,
      testeDuracaoInimigo,
      testesRemoveInimigo,
      testesEncontraBase,
      testeSemProjetéisAtivos,
      testeInimigoCongelado,
      testeInimigoFogo,
      testeInimigoResina,
      testeatualizaInimigos
    ]

testesPortais :: Test
testesPortais = TestList [testesAtualizaEntradaOnda, testeTempos, testeOndaSemInimigos, testePortalSemOnda, testeOndaAtivaInativa, testeLancaInimigosPortais]

testesTorres :: Test
testesTorres = TestList [testeForaAlcance, testeTempoTorre, testeRajadaTorre, testeFogoGelo, testeResinaGelo, testeResinaFogo]

-- Comportamento das torres
-- Teste 1: Verificar a função disparaTorre
-- Situação em que os inimigos estão fora do alcance da Torre (os inimigos permanecem iguais, atualizando a torre)
testeForaAlcance :: Test
testeForaAlcance =
  "Os inimigos estão fora do alcance da Torre"
    ~: ([inimigoSemProjeteis, inimigoFogo], torreAtualizada1)
    ~=? disparaTorre 0.1 [inimigoSemProjeteis, inimigoFogo] torreAtiva

torreAtiva :: Torre
torreAtiva =
  Torre
    { posicaoTorre = (0, 0),
      danoTorre = 10,
      alcanceTorre = 0.1,
      rajadaTorre = 1,
      cicloTorre = 2,
      tempoTorre = -1,
      projetilTorre = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}
    }

torreAtualizada1 :: Torre
torreAtualizada1 =
  Torre
    { posicaoTorre = (0, 0),
      danoTorre = 10,
      alcanceTorre = 0.1,
      rajadaTorre = 1,
      cicloTorre = 2,
      tempoTorre = 2, -- O tempoTorre atualiza para o cicloTorre
      projetilTorre = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}
    }

-- Situação em que o tempoTorre é superior a zero (a torre não deve disparar, permanecendo os inimigos iguais)
testeTempoTorre :: Test
testeTempoTorre =
  "A Torre tem um tempoTorre superior a zero"
    ~: ([inimigoSemProjeteis, inimigoFogo], torreAtualizada2)
    ~=? disparaTorre 0.1 [inimigoSemProjeteis, inimigoFogo] torreInativa

torreInativa :: Torre
torreInativa =
  Torre
    { posicaoTorre = (0, 0),
      danoTorre = 10,
      alcanceTorre = 0.1,
      rajadaTorre = 1,
      cicloTorre = 2,
      tempoTorre = 2,
      projetilTorre = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}
    }

torreAtualizada2 :: Torre
torreAtualizada2 =
  Torre
    { posicaoTorre = (0, 0),
      danoTorre = 10,
      alcanceTorre = 0.1,
      rajadaTorre = 1,
      cicloTorre = 2,
      tempoTorre = 2 - 0.1, -- O tempoTorre atualiza para dependedo do tempo
      projetilTorre = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}
    }

-- Situação que teste o parâmetro da rajadaTorre (o número de inimigos no alcance é maior que a rajadaTorre)
testeRajadaTorre :: Test
testeRajadaTorre =
  "O número de inimigos no alcance é menor que a rajadaTorre"
    ~: ([inimigoDentroAlcanceAtualizado1, inimigoDentroAlcance2], torreAtualizada1)
    ~=? disparaTorre 0.1 [inimigoDentroAlcance1, inimigoDentroAlcance2] torreAtiva -- apenas um deles é atingido

inimigoDentroAlcance1 :: Inimigo
inimigoDentroAlcance1 =
  Inimigo
    { posicaoInimigo = (0.05, 0.05),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = []
    }

inimigoDentroAlcance2 :: Inimigo
inimigoDentroAlcance2 =
  Inimigo
    { posicaoInimigo = (0.03, 0.03),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = []
    }

inimigoDentroAlcanceAtualizado1 :: Inimigo
inimigoDentroAlcanceAtualizado1 =
  Inimigo
    { posicaoInimigo = (0.05, 0.05),
      direcaoInimigo = Norte,
      vidaInimigo = 100 - 10, -- Retira o dano da Torre
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = [Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}]
    }

-- Verificar se atualiza corretamente as sinergias
-- Caso que o inimigo está sobre Gelo e a torre tem um projétil do tipo Fogo (devem-se cancelar mutuamente)
testeFogoGelo :: Test
testeFogoGelo =
  "Inimigo está sobre Gelo e a torre tem um projétil do tipo Fogo"
    ~: ([inimigoSobreGeloAtualizado1], torreAtualizada1)
    ~=? disparaTorre 0.1 [inimigoSobreGelo] torreAtiva

inimigoSobreGelo :: Inimigo
inimigoSobreGelo =
  Inimigo
    { posicaoInimigo = (0.05, 0.05),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = [Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 3}]
    }

inimigoSobreGeloAtualizado1 :: Inimigo
inimigoSobreGeloAtualizado1 =
  Inimigo
    { posicaoInimigo = (0.05, 0.05),
      direcaoInimigo = Norte,
      vidaInimigo = 100 - 10, -- Sofre o dano da Torre
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = [] -- Cancelam-se mutuamente
    }

-- Caso que o inimigo está sobre Gelo e a torre tem um projétil do tipo Resina (devem permanecer ambos no inimigo)
testeResinaGelo :: Test
testeResinaGelo =
  "Inimigo está sobre Gelo e a torre tem um projétil do tipo Resina"
    ~: ([inimigoSobreGeloAtualizado2], torreResinaAtualizada)
    ~=? disparaTorre 0.1 [inimigoSobreGelo] torreResina

torreResina :: Torre
torreResina =
  Torre
    { posicaoTorre = (0, 0),
      danoTorre = 10,
      alcanceTorre = 0.1,
      rajadaTorre = 1,
      cicloTorre = 2,
      tempoTorre = -1,
      projetilTorre = Projetil {tipoProjetil = Resina, duracaoProjetil = Infinita}
    }

torreResinaAtualizada :: Torre
torreResinaAtualizada =
  Torre
    { posicaoTorre = (0, 0),
      danoTorre = 10,
      alcanceTorre = 0.1,
      rajadaTorre = 1,
      cicloTorre = 2,
      tempoTorre = 2, -- Atualizada o tempoTorre
      projetilTorre = Projetil {tipoProjetil = Resina, duracaoProjetil = Infinita}
    }

inimigoSobreGeloAtualizado2 :: Inimigo
inimigoSobreGeloAtualizado2 =
  Inimigo
    { posicaoInimigo = (0.05, 0.05),
      direcaoInimigo = Norte,
      vidaInimigo = 100 - 10, -- Sofre o dano da Torre
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo =
        [ Projetil {tipoProjetil = Resina, duracaoProjetil = Infinita},
          Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 3} -- Ambos os projéteis são adicionados
        ]
    }

-- Caso que o inimigo está sobre Fogo e a torre tem um projétil do tipo Resina (deve dobrar o a duração do Fogo)
testeResinaFogo :: Test
testeResinaFogo =
  "Inimigo está sobre Fogo e a torre tem um projétil do tipo Resina"
    ~: ([inimigoSobreFogoAtualizado], torreResinaAtualizada)
    ~=? disparaTorre 0.1 [inimigoSobreFogo] torreResina

inimigoSobreFogo :: Inimigo
inimigoSobreFogo =
  Inimigo
    { posicaoInimigo = (0.05, 0.05),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = [Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}]
    }

inimigoSobreFogoAtualizado :: Inimigo
inimigoSobreFogoAtualizado =
  Inimigo
    { posicaoInimigo = (0.05, 0.05),
      direcaoInimigo = Norte,
      vidaInimigo = 100 - 10, -- Sofre o dano da Torre
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = [Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 6}] -- Dobra a duração do Fogo e adiciona a Resina
    }

-- Comportamento dos inimigos
-- Teste 1: Verificar a função aplicaProjetilInimigo
testesAplicaProjetilInimigo :: Test
testesAplicaProjetilInimigo =
  "Aplica os efeitos de cada um dos projéteis"
    ~: TestList
      [ inimigoGelo ~=? aplicaProjetilInimigo inimigoGelo 0.1,
        inimigoFogoAtingido ~=? aplicaProjetilInimigo inimigoFogo 0.1,
        inimigoResinaAtingido ~=? aplicaProjetilInimigo inimigoResina 0.1
      ]

inimigoGelo :: Inimigo
inimigoGelo =
  Inimigo
    { posicaoInimigo = (0, 0),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = [Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 3}]
    }

inimigoFogo :: Inimigo
inimigoFogo =
  Inimigo
    { posicaoInimigo = (0.5, 0.5),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = [Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}]
    }

inimigoFogoAtingido :: Inimigo
inimigoFogoAtingido =
  Inimigo
    { posicaoInimigo = (0.5, 0.5),
      direcaoInimigo = Norte,
      vidaInimigo = 100 - 3 * 0.1,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = [Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}]
    }

inimigoResina :: Inimigo
inimigoResina =
  Inimigo
    { posicaoInimigo = (0.5, 0.5),
      direcaoInimigo = Sul,
      vidaInimigo = 100,
      velocidadeInimigo = 2,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = [Projetil {tipoProjetil = Resina, duracaoProjetil = Infinita}]
    }

inimigoResinaAtingido :: Inimigo
inimigoResinaAtingido =
  Inimigo
    { posicaoInimigo = (0.5, 0.5),
      direcaoInimigo = Sul,
      vidaInimigo = 100,
      velocidadeInimigo = 2, -- permanece com a mesma velocidade visto já ter o efeito da resina aplicado
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = [Projetil {tipoProjetil = Resina, duracaoProjetil = Infinita}]
    }

-- Teste 2: Verificar a função atualizaDuracaoInimigo
testeDuracaoInimigo :: Test
testeDuracaoInimigo =
  "Remove os projéteis do inimigo cuja duração é <= 0 e se atualiza corretamente a duração dos projéteis"
    ~: inimigoAtualizado
    ~=? atualizaDuracaoInimigo inimigoProjNegativos 0.1

inimigoProjNegativos :: Inimigo
inimigoProjNegativos =
  Inimigo
    { posicaoInimigo = (0.5, 0.5),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = [Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 3}, Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita (-1)}]
    }

inimigoAtualizado :: Inimigo
inimigoAtualizado =
  Inimigo
    { posicaoInimigo = (0.5, 0.5),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = [Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita (3 - 0.1)}]
    }

-- Teste 3: Verificar a função removerInimigo
testesRemoveInimigo :: Test
testesRemoveInimigo =
  "Remove os inimigos cuja a vida é igual ou inferior a 0 e se atualiza a base"
    ~: TestList
      [ ([], novaBase) ~=? removerInimigo [inimigoVidaNegativa] base, -- Inimigo com uma vida negativa
        ([inimigoVidaPosiva], base) ~=? removerInimigo [inimigoVidaPosiva] base -- Inimigo com uma vida positiva
      ]

inimigoVidaNegativa :: Inimigo
inimigoVidaNegativa =
  Inimigo
    { posicaoInimigo = (0.5, 0.5),
      direcaoInimigo = Norte,
      vidaInimigo = -1,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = []
    }

base :: Base
base =
  Base
    { vidaBase = 50,
      posicaoBase = (2.5, 2.5),
      creditosBase = 50
    }

novaBase :: Base
novaBase =
  Base
    { vidaBase = 50,
      posicaoBase = (2.5, 2.5),
      creditosBase = 50 + 10 -- Adicionar o butim do Inimigo
    }

inimigoVidaPosiva :: Inimigo
inimigoVidaPosiva =
  Inimigo
    { posicaoInimigo = (0.5, 0.4),
      direcaoInimigo = Sul,
      vidaInimigo = 50,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = [Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 3}]
    }

-- Teste 4: Verificar a função encontraBase
testesEncontraBase :: Test
testesEncontraBase =
  "Remove os inimigos que atingem a base e se atualiza a base"
    ~: TestList
      [ ([], baseAtualizada) ~=? encontraBase [inimigoAtingeBase] base, -- Inimigo alcança a base
        ([inimigoForaBase], base) ~=? encontraBase [inimigoForaBase] base -- Inimigo não alcança a base
      ]

inimigoAtingeBase :: Inimigo
inimigoAtingeBase =
  Inimigo
    { posicaoInimigo = (2.5, 2.5),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = []
    }

inimigoForaBase :: Inimigo
inimigoForaBase =
  Inimigo
    { posicaoInimigo = (1.5, 1.5),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = []
    }

baseAtualizada :: Base
baseAtualizada =
  Base
    { vidaBase = 50 - 15, -- Retirar à vida da base o dano que o inimigo inflige
      posicaoBase = (2.5, 2.5),
      creditosBase = 50
    }

-- Teste 5: Verificar a atualizarPosicaoInimigo
-- Inimigo sem Projéteis ativos
testeSemProjetéisAtivos :: Test
testeSemProjetéisAtivos =
  "Inimigo sem projéteis ativos se move naturalmente"
    ~: proximoPasso (vizinhosTerraInimigo inimigoSemProjeteis mapa01 0.1) (posicaoBase base)
    ~=? posicaoInimigo (atualizarPosicaoInimigo 0.1 inimigoSemProjeteis mapa01 base)

inimigoSemProjeteis :: Inimigo
inimigoSemProjeteis =
  Inimigo
    { posicaoInimigo = (0.5, 0.5),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 15,
      butimInimigo = 10,
      projeteisInimigo = []
    }

-- Inimigo afetado por Gelo (deve manter a mesma posicao)
testeInimigoCongelado :: Test
testeInimigoCongelado =
  "Inimigo afetado pelo Gelo se mantém parado"
    ~: posicaoInimigo inimigoGelo
    ~=? posicaoInimigo (atualizarPosicaoInimigo 0.1 inimigoGelo mapa01 base)

-- Inimigo afetado por Fogo (deve mover-se da mesma forma quando está sem qualquer Projétil)
testeInimigoFogo :: Test
testeInimigoFogo =
  "Inimigo afetado por Fogo se move naturalmente"
    ~: proximoPasso (vizinhosTerraInimigo inimigoFogo mapa01 0.1) (posicaoBase base)
    ~=? posicaoInimigo (atualizarPosicaoInimigo 0.1 inimigoFogo mapa01 base)

-- Inimigo afetado por Resina (deve mover-se de forma mais lenta)
testeInimigoResina :: Test
testeInimigoResina =
  "Inimigo afetado por Resina se move de forma mais lenta"
    ~: proximoPasso (vizinhosTerraInimigo inimigoResinaAtingido mapa01 0.1) (posicaoBase base)
    ~=? posicaoInimigo (atualizarPosicaoInimigo 0.1 inimigoResina mapa01 base)

-- Teste 6: Verifica a atualizaInimigos
-- Funcionamento Geral correto da função, tendo as várias situações possiveis
testeatualizaInimigos :: Test
testeatualizaInimigos =
  "Atualização dos inimigos"
    ~: ([inimigoGeloAtualizado, inimigoFogoAtualizado, inimigoResinaAtualizado], baseCorreta)
    ~=? atualizaInimigos 0.1 [inimigoGelo, inimigoFogo, inimigoResina, inimigoAtingeBase, inimigoVidaNegativa] mapa01 base

-- Base atualizada
baseCorreta :: Base
baseCorreta =
  Base
    { vidaBase = 50 - 15, -- Reduz a vida sendo retirado o dano que o inimigo que atingiu a base inflige
      posicaoBase = (2.5, 2.5),
      creditosBase = 50 + 10 -- Adicionado o butim do inimigo com vida negativa
    }

-- Inimigo afetado por Gelo (deve manter a mesma posição)
inimigoGeloAtualizado :: Inimigo
inimigoGeloAtualizado =
  Inimigo
    { posicaoInimigo = (0, 0), -- Mantém a mesma posição
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = [Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita (3 - 0.1)}] -- Atualiza a duração
    }

-- Inimigo afetado por Fogo (deve mover-se naturalmente e ir alterando a sua vida)
inimigoFogoAtualizado :: Inimigo
inimigoFogoAtualizado =
  Inimigo
    { posicaoInimigo = (0.6, 0.5), -- Move-se naturalmente
      direcaoInimigo = Este, -- Altera a direção
      vidaInimigo = 100 - 3 * 0.1, -- Sofre dano de 3 unidades por segundo
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = [Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita (3 - 0.1)}] -- Atualiza a duração
    }

-- Inimigo afetado por Resina (apenas deve se mover mais lentamente)
inimigoResinaAtualizado :: Inimigo
inimigoResinaAtualizado = atualizarPosicaoInimigo 0.1 inimigoResinaAtingido mapa01 base -- Altera a posicao e a direção

mapa01 :: Mapa
mapa01 =
  [ [Terra, Terra, Relva],
    [Relva, Terra, Relva],
    [Relva, Terra, Terra]
  ]

-- Comportamento dos portais
-- Teste 1 : Verificar a função atualizaEntradaOnda
testesAtualizaEntradaOnda :: Test
testesAtualizaEntradaOnda =
  "Verificar o funcionamento da função que a atualizaEntradaOnda"
    ~: TestList
      [ [ondaSemInimigosAtualizada] ~=? atualizaEntradaOnda 0.1 [ondaSemInimigos],
        [ondaComInimigosAtualizada] ~=? atualizaEntradaOnda 0.1 [ondaComInimigos],
        [ondaSemInimigosAtualizada, ondaComInimigosAtualizada] ~=? atualizaEntradaOnda 0.1 [ondaSemInimigos, ondaComInimigos]
      ]

ondaSemInimigos :: Onda
ondaSemInimigos =
  Onda
    { inimigosOnda = [],
      cicloOnda = 2,
      tempoOnda = 2,
      entradaOnda = 2
    }

ondaComInimigos :: Onda
ondaComInimigos =
  Onda
    { inimigosOnda = [inimigo1],
      cicloOnda = 2,
      tempoOnda = 2,
      entradaOnda = 1
    }

ondaSemInimigosAtualizada :: Onda
ondaSemInimigosAtualizada =
  Onda
    { inimigosOnda = [],
      cicloOnda = 2,
      tempoOnda = 2,
      entradaOnda = 2 - 0.1 -- Atualiza o tempoEntrada da Onda (retirando o tempo)
    }

ondaComInimigosAtualizada :: Onda
ondaComInimigosAtualizada =
  Onda
    { inimigosOnda = [inimigo1],
      cicloOnda = 2,
      tempoOnda = 2,
      entradaOnda = 1 - 0.1 -- Atualiza o tempoEntrada da Onda (retirando o tempo)
    }

-- Teste 2: Verificar a função lancaInimigosPortal
-- Verificar apenas a relação tempoOnda, cicloOnda e entradaOnda
testeTempos :: Test
testeTempos =
  "Testar as relações entre os tempos das ondas"
    ~: TestList
      [ ([], portal01Esperado) ~=? lancaInimigosPortal 0.1 [] portal01, -- inimigo1 ainda não está pronto a ser lançado (tempoOnda > 0), mantendo os mesmos inimigos em Jogo
        ([inimigo1], portal02Esperado) ~=? lancaInimigosPortal 0.1 [] portal02, -- inimigo1 deve ser lançado (tempoOnda <= 0)
        ([], portal03Esperado) ~=? lancaInimigosPortal 0.1 [] portal03 -- a única onda do portal não se encontra ativa
      ]

portal01 :: Portal
portal01 =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [ondaAtiva01]
    }

portal01Esperado :: Portal
portal01Esperado =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [ondaAtivaAtualizada01]
    }

ondaAtiva01 :: Onda
ondaAtiva01 =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 2,
      tempoOnda = 2, -- tempoOnda > 0
      entradaOnda = -1 -- Onda ativa
    }

ondaAtivaAtualizada01 :: Onda
ondaAtivaAtualizada01 =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 2,
      tempoOnda = 2 - 0.1, -- Atualiza o tempoOnda (retirando o tempo)
      entradaOnda = -1 -- Onda ativa
    }

portal02 :: Portal
portal02 =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [ondaAtiva02]
    }

portal02Esperado :: Portal
portal02Esperado =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [ondaAtivaAtualizada02]
    }

ondaAtiva02 :: Onda
ondaAtiva02 =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 2,
      tempoOnda = 0, -- tempoOnda <= 0
      entradaOnda = -1 -- Onda ativa
    }

ondaAtivaAtualizada02 :: Onda
ondaAtivaAtualizada02 =
  Onda
    { inimigosOnda = [inimigo2], -- Remover o inimigo1 da onda
      cicloOnda = 2,
      tempoOnda = 2, -- Atualiza o tempoOnda para o cicloOnda
      entradaOnda = -1 - 0.1 -- Atualiza a entradaOnda dependendo do tempo
    }

portal03 :: Portal
portal03 =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [ondaInativa03]
    }

portal03Esperado :: Portal
portal03Esperado =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [ondaInativaAtualizada03]
    }

ondaInativa03 :: Onda
ondaInativa03 =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 2,
      tempoOnda = 1,
      entradaOnda = 2
    }

ondaInativaAtualizada03 :: Onda
ondaInativaAtualizada03 =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 2,
      tempoOnda = 1,
      entradaOnda = 2 - 0.1 -- Atualiza a entradaOnda da onda
    }

-- Teste 3: Caso particular em que o portal não tem ondas (mantém exatamente tudo igual)
testePortalSemOnda :: Test
testePortalSemOnda =
  "O portal não possui ondas"
    ~: ([], portalSemOndas)
    ~=? lancaInimigosPortal 0.1 [] portalSemOndas

portalSemOndas :: Portal
portalSemOndas =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = []
    }

-- Teste 4: Caso particular em que a onda ativa no portal não possui inimigos
testeOndaSemInimigos :: Test
testeOndaSemInimigos =
  "A onda ativa no portal não possui inimigos"
    ~: ([inimigo3, inimigo4], portal04Esperado)
    ~=? lancaInimigosPortal 0.1 [inimigo3, inimigo4] portal04

portal04 :: Portal
portal04 =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [ondaAtivaSemInimigos, ondaInativa03]
    }

portal04Esperado :: Portal
portal04Esperado =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [ondaInativaAtualizada03] -- Remove a onda sem inimigos e atualiza a ondaInativa03
    }

ondaAtivaSemInimigos :: Onda
ondaAtivaSemInimigos =
  Onda
    { inimigosOnda = [],
      cicloOnda = 2,
      tempoOnda = 0,
      entradaOnda = -1 -- Onda ativa
    }

-- Teste 4: Caso particular em que o portal possui duas ondas, uma ativa com Inimigos e outra inativa
testeOndaAtivaInativa :: Test
testeOndaAtivaInativa =
  "A onda ativa no portal possui inimigos"
    ~: ([inimigo3, inimigo4, inimigo1], portal05Esperado)
    ~=? lancaInimigosPortal 0.1 [inimigo3, inimigo4] portal05

portal05 :: Portal
portal05 =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [ondaAtiva02, ondaInativa03]
    }

portal05Esperado :: Portal
portal05Esperado =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [ondaAtivaAtualizada02, ondaInativaAtualizada03]
    }

-- Teste 5: Funcionamento geral da função lancaInimigosPortais
testeLancaInimigosPortais :: Test
testeLancaInimigosPortais =
  "Testar lancaInimigosPortais com múltiplos cenários"
    ~: (inimigosEsperados, portaisEsperados)
    ~=? lancaInimigosPortais 0.1 [inimigo3, inimigo4] portaisIniciais

portaisIniciais :: [Portal]
portaisIniciais = [portalSemOndas, portal01, portal02, portal03, portal04]

inimigosEsperados :: [Inimigo]
inimigosEsperados = [inimigo3, inimigo4, inimigo1]

portaisEsperados :: [Portal]
portaisEsperados =
  [ portalSemOndas, -- Sem alterações, pois não tem ondas
    portal01Esperado, -- Atualiza a ondaAtiva01 (não lança inimigos)
    portal02Esperado, -- Lança inimigo1 e atualiza ondaAtiva02
    portal03Esperado, -- Atualiza ondaInativa03
    portal04Esperado -- Remove a onda vazia e atualiza a outra
  ]

inimigo1 :: Inimigo
inimigo1 =
  Inimigo
    { posicaoInimigo = (0, 0),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = []
    }

inimigo2 :: Inimigo
inimigo2 =
  Inimigo
    { posicaoInimigo = (1, 1),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = []
    }

inimigo3 :: Inimigo
inimigo3 =
  Inimigo
    { posicaoInimigo = (3, 3),
      direcaoInimigo = Sul,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = []
    }

inimigo4 :: Inimigo
inimigo4 =
  Inimigo
    { posicaoInimigo = (0, 0),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = []
    }

{-
onda1 :: Onda
onda1 =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 2,
      tempoOnda = 2,
      entradaOnda = 10
    }

onda1Esperada :: Onda
onda1Esperada =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 2,
      tempoOnda = 2,
      entradaOnda = 9
    }

onda2 :: Onda
onda2 =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 2,
      tempoOnda = 2,
      entradaOnda = 0
    }

onda2Esperada :: Onda
onda2Esperada =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 2,
      tempoOnda = 1,
      entradaOnda = 0
    }

onda3 :: Onda
onda3 =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 2,
      tempoOnda = 0,
      entradaOnda = 0
    }

onda3Esperada :: Onda
onda3Esperada =
  Onda
    { inimigosOnda = [inimigo2],
      cicloOnda = 2,
      tempoOnda = 2,
      entradaOnda = 0
    }

onda4 :: Onda
onda4 =
  Onda
    { inimigosOnda = [],
      cicloOnda = 2,
      tempoOnda = 2,
      entradaOnda = 10
    }

portal1 :: Portal
portal1 =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [onda1]
    }

portal1Esperado :: Portal
portal1Esperado =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [onda1Esperada]
    }

portal2 :: Portal
portal2 =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [onda2]
    }

portal2Esperado :: Portal
portal2Esperado =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [onda2Esperada]
    }

portal3 :: Portal
portal3 =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [onda3]
    }

portal3Esperado :: Portal
portal3Esperado =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [onda3Esperada]
    }

portal4 :: Portal
portal4 =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = [onda4]
    }

portal4Esperado :: Portal
portal4Esperado =
  Portal
    { posicaoPortal = (0, 0),
      ondasPortal = []
    }

jogo01 :: Jogo
jogo01 =
  Jogo
    { inimigosJogo = [],
      portaisJogo = [portal1]
    }

jogo01Esperado =
  Jogo
    { inimigosJogo = [],
      portaisJogo = [portal1Esperado]
    }

inimigo5 :: Inimigo
inimigo5 =
  Inimigo
    { posicaoInimigo = (1, 1),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = []
    }

inimigo6 :: Inimigo
inimigo6 =
  Inimigo
    { posicaoInimigo = (3, 3),
      direcaoInimigo = Sul,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = []
    }

inimigo7 :: Inimigo
inimigo7 =
  Inimigo
    { posicaoInimigo = (4, 5),
      direcaoInimigo = Norte,
      vidaInimigo = 100,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = []
    }

torre1 :: Torre
torre1 =
  Torre
    { posicaoTorre = (0, 0),
      danoTorre = 10,
      alcanceTorre = 3,
      rajadaTorre = 1,
      cicloTorre = 2,
      tempoTorre = 1,
      projetilTorre = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}
    }

torre1Esperada :: Torre
torre1Esperada =
  Torre
    { posicaoTorre = (0, 0),
      danoTorre = 10,
      alcanceTorre = 3,
      rajadaTorre = 1,
      cicloTorre = 2,
      tempoTorre = 0,
      projetilTorre = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}
    }

torre2 :: Torre
torre2 =
  Torre
    { posicaoTorre = (1, 1),
      danoTorre = 10,
      alcanceTorre = 3,
      rajadaTorre = 2,
      cicloTorre = 2,
      tempoTorre = 0,
      projetilTorre = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}
    }

torre2Esperada :: Torre
torre2Esperada =
  Torre
    { posicaoTorre = (1, 1),
      danoTorre = 10,
      alcanceTorre = 3,
      rajadaTorre = 2,
      cicloTorre = 2,
      tempoTorre = 2,
      projetilTorre = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}
    }

torre3 :: Torre
torre3 =
  Torre
    { posicaoTorre = (3, 3),
      danoTorre = 5,
      alcanceTorre = 5,
      rajadaTorre = 3,
      cicloTorre = 2,
      tempoTorre = 0,
      projetilTorre = Projetil {tipoProjetil = Resina, duracaoProjetil = Infinita}
    }

torre3Esperada :: Torre
torre3Esperada =
  Torre
    { posicaoTorre = (3, 3),
      danoTorre = 5,
      alcanceTorre = 5,
      rajadaTorre = 3,
      cicloTorre = 2,
      tempoTorre = 2,
      projetilTorre = Projetil {tipoProjetil = Resina, duracaoProjetil = Infinita}
    }

torre4 :: Torre
torre4 =
  Torre
    { posicaoTorre = (3, 4),
      danoTorre = 3,
      alcanceTorre = 2,
      rajadaTorre = 2,
      cicloTorre = 2,
      tempoTorre = 0,
      projetilTorre = Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 2}
    }

torre4Esperada :: Torre
torre4Esperada =
  Torre
    { posicaoTorre = (3, 4),
      danoTorre = 3,
      alcanceTorre = 2,
      rajadaTorre = 2,
      cicloTorre = 2,
      tempoTorre = 2,
      projetilTorre = Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 2}
    }

jogo02 :: Jogo
jogo02 =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (1, 1),
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (2, 1),
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (3, 3),
              ondasPortal = []
            }
        ],
      torresJogo = [torre1, torre2, torre3, torre4],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Terra, Terra]
        ],
      inimigosJogo = [],
      lojaJogo = []
    }

jogo02Esperado :: Jogo
jogo02Esperado =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (1, 1),
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (2, 1),
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (3, 3),
              ondasPortal = []
            }
        ],
      torresJogo = [torre1Esperada, torre2Esperada, torre3Esperada, torre4Esperada],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Terra, Terra]
        ],
      inimigosJogo = [],
      lojaJogo = []
    }

inimigo4FogoEsperado :: Inimigo
inimigo4FogoEsperado =
  Inimigo
    { posicaoInimigo = (0, 0),
      direcaoInimigo = Norte,
      vidaInimigo = 90,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = [Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}]
    }

inimigo5FogoEsperado :: Inimigo
inimigo5FogoEsperado =
  Inimigo
    { posicaoInimigo = (1, 1),
      direcaoInimigo = Norte,
      vidaInimigo = 90,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = [Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}]
    }

inimigo6FogoEsperado :: Inimigo
inimigo6FogoEsperado =
  Inimigo
    { posicaoInimigo = (3, 3),
      direcaoInimigo = Sul,
      vidaInimigo = 90,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = [Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 3}]
    }

jogo03 :: Jogo
jogo03 =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (1, 1),
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (2, 1),
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (3, 3),
              ondasPortal = []
            }
        ],
      torresJogo = [torre1],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Terra, Terra]
        ],
      inimigosJogo = [inimigo4, inimigo5, inimigo6],
      lojaJogo = []
    }

jogo03Esperado :: Jogo
jogo03Esperado =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (1, 1),
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (2, 1),
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (3, 3),
              ondasPortal = []
            }
        ],
      torresJogo = [torre1Esperada],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Terra, Terra]
        ],
      inimigosJogo = [inimigo4, inimigo5, inimigo6],
      lojaJogo = []
    }

jogo04 :: Jogo
jogo04 =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (1, 1),
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (2, 1),
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (3, 3),
              ondasPortal = []
            }
        ],
      torresJogo = [torre2],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Terra, Terra]
        ],
      inimigosJogo = [inimigo4, inimigo5, inimigo6, inimigo7, inimigo4],
      lojaJogo = []
    }

jogo04Esperado :: Jogo
jogo04Esperado =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (1, 1),
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (2, 1),
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (3, 3),
              ondasPortal = []
            }
        ],
      torresJogo = [torre2Esperada],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Terra, Terra]
        ],
      inimigosJogo = [inimigo4FogoEsperado, inimigo5FogoEsperado, inimigo6, inimigo4, inimigo7],
      lojaJogo = []
    }

inimigo4ResinaEsperado :: Inimigo
inimigo4ResinaEsperado =
  Inimigo
    { posicaoInimigo = (0, 0),
      direcaoInimigo = Norte,
      vidaInimigo = 95,
      velocidadeInimigo = 1,
      ataqueInimigo = 10,
      butimInimigo = 5,
      projeteisInimigo = []
    }

testeComportamentoTorres :: Test
testeComportamentoTorres =
  "Comportamento das torres"
    ~: TestList
      [ jogo02Esperado ~=? atualizaTorres 1 jogo02,
        jogo03Esperado ~=? atualizaTorres 1 jogo03,
        jogo04Esperado ~=? atualizaTorres 1 jogo04
      ]
-}
