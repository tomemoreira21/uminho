module Tarefa1Spec (testesTarefa1) where

import LI12425
import Tarefa1
import Test.HUnit

testesTarefa1 :: Test
testesTarefa1 = TestList [testesTerrenos, testesPortais, testesInimigos, testesTorres]

testesTerrenos :: Test
testesTerrenos = TestList [testeConverteCoor, testeTerrenoF, testeTerrenoI]

testesPortais :: Test
testesPortais = TestList [ondaAtiva, verificaPos, posBase, semCaminho, umCaminho, variosCaminhos, peloMenosUmCaminho]

testesInimigos :: Test
testesInimigos = TestList [posInimigo, velInimigo, normalizaProj1, normalizaProj2]

testesTorres :: Test
testesTorres = TestList [torresSobr, baseSobr, baseCredito]

-- Testes Terrenos
-- Teste 1: Verifica se a função terrenoCoor converte corretamente cada posição do mapa
testeConverteCoor :: Test
testeConverteCoor =
  "Conversão das coordenadas do mapa"
    ~: trEsperado
    -- Contador das posições do mapa começa em (1,1)
    ~=? terrenoCoor mapa01 (1, 1) terrenos

trEsperado :: Terrenos
trEsperado = Terrenos {relva = [(3, 1), (1, 2), (3, 2), (1, 3), (3, 3)], terra = [(1, 1), (2, 1), (2, 3)], agua = [(2, 2)]}

mapa01 :: Mapa
mapa01 =
  [ [Terra, Terra, Relva],
    [Relva, Agua, Relva],
    [Relva, Terra, Relva]
  ]

-- Teste 2: Verifica se a função validaTerreno funciona corretamente com posições float
testeTerrenoF :: Test
testeTerrenoF =
  "Verifica validaTerreno com float"
    ~: TestList
      [ True ~=? validaTerreno trEsperado "agua" (1.5, 1.5),
        True ~=? validaTerreno trEsperado "terra" (0.5, 0.5),
        False ~=? validaTerreno trEsperado "relva" (1.5, 2.5)
      ]

-- Teste 3: Verifica se a função validaTerreno funciona corretamente com posições int
testeTerrenoI :: Test
testeTerrenoI =
  "Verifica validaTerreno com int"
    ~: TestList
      [ True ~=? validaTerreno trEsperado "relva" (3, 1),
        False ~=? validaTerreno trEsperado "terra" (1, 2),
        True ~=? validaTerreno trEsperado "agua" (2, 2)
      ]

-- Testes Portais
-- Teste 1: Verificar se o funcionamento da função validaOnda no caso de haver mais de uma onda ativa por portal
ondaAtiva :: Test
ondaAtiva =
  "Mais de uma onda ativa por portal"
    ~: TestList
      [ False ~=? validaOnda portal1,
        True ~=? validaOnda portal2
      ]

portal1 :: Portal
portal1 =
  Portal
    { posicaoPortal = (1, 1),
      ondasPortal = [onda1, onda2]
    }

portal2 :: Portal
portal2 =
  Portal
    { posicaoPortal = (1.5, 1.5),
      ondasPortal = [onda2]
    }

onda1 :: Onda
onda1 =
  Onda
    { inimigosOnda = [inimigo1, inimigo2],
      cicloOnda = 10,
      tempoOnda = 12,
      entradaOnda = 0
    }

onda2 :: Onda
onda2 =
  Onda
    { inimigosOnda = [inimigo3],
      cicloOnda = 10,
      tempoOnda = 12,
      entradaOnda = 0
    }

-- Teste 2: Caso onde existem portais que não estão posicionados sobre Terra
verificaPos :: Test
verificaPos =
  "Portais posicionados fora da Terra"
    ~: TestList
      [ False ~=? validaPortais jogoPortaisForaTerra,
        True ~=? validaPortais jogoPortaisEmTerra
      ]

jogoPortaisEmTerra :: Jogo
jogoPortaisEmTerra =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (1, 1), -- Base sobre terra
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (2, 1), -- Portal válido sobre terra
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (3, 3), -- Portal válido sobre terra
              ondasPortal = []
            }
        ],
      torresJogo = [],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Terra, Terra]
        ],
      inimigosJogo = [],
      lojaJogo = []
    }

jogoPortaisForaTerra :: Jogo
jogoPortaisForaTerra =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (1.5, 0.5), -- Base sobre terra
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (1, 1), -- Portal válido sobre terra
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (2.5, 1.5), -- Portal inválido sobre água
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (3, 3), -- Portal válido sobre relva
              ondasPortal = []
            }
        ],
      torresJogo = [],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Terra, Terra]
        ],
      inimigosJogo = [],
      lojaJogo = []
    }

-- Teste 3: Verificar o caso em que existem o portal e a base estão na mesma célula da matriz mas não exatamente nas mesmas coordenadas
posBase :: Test
posBase =
  "Sobreposicao do portal e da base"
    ~: TestList
      [ False ~=? validaTB [(1.5, 1.5)] [(1.8, 1.7)], -- o portal está sobreposto à base
        True ~=? validaTB [(1.5, 1.5), (4, 4)] [(2, 2), (4, 3), (1.5, 4)] -- o portal não está sobreposto à base
      ]

-- Teste 4: Verificar o caso onde não existe um caminho de terra ligando o portal à base
semCaminho :: Test
semCaminho =
  "Não existe caminho de terra ligando o portal à base"
    ~: False
    ~=? verificaCaminho
      (1.5, 0.5) -- Posição do portal
      (1.5, 2.5) -- Posição da base
      mapa02
      []

mapa02 :: Mapa
mapa02 =
  [ [Terra, Terra, Relva],
    [Relva, Agua, Relva],
    [Relva, Terra, Relva]
  ]

-- Teste 5: Verificar o caso onde existe um caminho de terra ligando o portal à base
umCaminho :: Test
umCaminho =
  "Existem um único caminho de terra ligando o portal à base"
    ~: True
    ~=? verificaCaminho (0.4, 0.6) (2.5, 2.5) mapa03 []

-- Teste 5: Verificar o caso onde existe pelo menos um caminho de terra ligando o portal à base
peloMenosUmCaminho :: Test
peloMenosUmCaminho =
  "Existe pelo menos um caminho de terra ligando o portal à base"
    ~: TestList
      [ True ~=? caminhosPortais jogo1,
        True ~=? caminhosPortais jogo2,
        True ~=? caminhosPortais jogo3
      ]

mapa03 :: Mapa
mapa03 =
  [ [Terra, Terra, Relva],
    [Agua, Terra, Relva],
    [Agua, Terra, Terra]
  ]

jogo1 :: Jogo
jogo1 =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (3, 3), -- Base sobre terra
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (1, 1), -- Portal válido sobre terra
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (1, 3), -- Portal válido sobre terra
              ondasPortal = []
            }
        ],
      torresJogo = [],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Terra, Terra]
        ],
      inimigosJogo = [],
      lojaJogo = []
    }

jogo2 :: Jogo
jogo2 =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (3, 1), -- Base sobre terra
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (1, 3), -- Portal válido sobre terra
              ondasPortal = []
            }
        ],
      torresJogo = [],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Agua, Relva]
        ],
      inimigosJogo = [],
      lojaJogo = []
    }

jogo3 :: Jogo
jogo3 =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (2.5, 1.5), -- Base sobre terra
            creditosBase = 500
          },
      portaisJogo =
        [ Portal
            { posicaoPortal = (0.5, 0.5), -- Portal válido sobre terra
              ondasPortal = []
            },
          Portal
            { posicaoPortal = (0.5, 2.5), -- Portal válido sobre terra
              ondasPortal = []
            }
        ],
      torresJogo = [],
      mapaJogo =
        [ [Terra, Agua, Terra],
          [Terra, Terra, Terra],
          [Terra, Agua, Relva]
        ],
      inimigosJogo = [],
      lojaJogo = []
    }

-- Teste 6: Verificar o caso onde existe mais de um caminho de terra ligando o portal à base
variosCaminhos :: Test
variosCaminhos =
  "Existem mais de um caminho de terra ligando o portal à base"
    ~: True
    ~=? verificaCaminho (1.5, 0.5) (1.5, 2.5) mapa04 []

mapa04 :: Mapa
mapa04 =
  [ [Terra, Terra, Terra],
    [Terra, Relva, Terra],
    [Terra, Terra, Terra]
  ]

-- Testes inimigos
-- Teste 1: Verificar o caso em que o inimigo por lançar não tem a posição do portal
posInimigo :: Test
posInimigo =
  "Posição de um dos inimigos por lançar é diferente da posição do portal"
    ~: False
    ~=? validaPorLancar ((0.5, 0.5), [inimigo1, inimigo2])

inimigo1 :: Inimigo
inimigo1 =
  Inimigo
    { posicaoInimigo = (0.5, 0.5),
      vidaInimigo = 100,
      projeteisInimigo = [],
      direcaoInimigo = Sul,
      velocidadeInimigo = 0,
      ataqueInimigo = 10,
      butimInimigo = 10
    }

inimigo2 :: Inimigo
inimigo2 =
  Inimigo
    { posicaoInimigo = (1.5, 1.5),
      vidaInimigo = 50,
      projeteisInimigo = [],
      direcaoInimigo = Sul,
      velocidadeInimigo = 10,
      ataqueInimigo = 10,
      butimInimigo = 10
    }

-- Teste 2: Verificar o caso em que a velocidade do inimigo é nula
velInimigo :: Test
velInimigo =
  "Velocidade do inimigo é nula"
    ~: True
    ~=? validaVelocidade [inimigo1, inimigo2]

-- Teste 3: Verificar o caso em que a lista de projéteis possui mais do que um projétil do mesmo tipo
normalizaProj1 :: Test
normalizaProj1 =
  "A lista de projéteis do inimigo possui mais do que um projétil do mesmo tipo"
    ~: False
    ~=? validaProjeteis inimigo3

inimigo3 :: Inimigo
inimigo3 =
  Inimigo
    { posicaoInimigo = (1, 1),
      vidaInimigo = 75,
      projeteisInimigo = [projetilGelo, projetilGelo],
      direcaoInimigo = Sul,
      velocidadeInimigo = 10,
      ataqueInimigo = 10,
      butimInimigo = 10
    }

projetilGelo :: Projetil
projetilGelo = Projetil {tipoProjetil = Gelo, duracaoProjetil = Finita 3}

projetilFogo :: Projetil
projetilFogo = Projetil {tipoProjetil = Fogo, duracaoProjetil = Finita 2}

-- Teste 4: Verificar o caso em que existem projéteis ou mesmo tempo um projétil do tipo Fogo e outro do tipo Gelo
normalizaProj2 :: Test
normalizaProj2 =
  "A lista de projéteis do inimigo possui ao mesmo tempo um projétil do tipo Fogo e outro do tipo Gelo"
    ~: False
    ~=? validaProjeteis inimigo4

inimigo4 :: Inimigo
inimigo4 =
  Inimigo
    { posicaoInimigo = (1, 1),
      vidaInimigo = 75,
      projeteisInimigo = [projetilFogo, projetilGelo],
      direcaoInimigo = Sul,
      velocidadeInimigo = 10,
      ataqueInimigo = 10,
      butimInimigo = 10
    }

-- Testes torres
-- Teste 1: Verificar o caso em que as existem torres sobrepostas
torresSobr :: Test
torresSobr =
  "Torres sobrepostas"
    ~: TestList
      [ False ~=? sobrepoeTorres [(1.5, 1.5), (2.5, 3.5), (1.5, 1.5)], -- Está sobreposto estando exatamente na mesma posição
        True ~=? sobrepoeTorres [(1, 1), (2, 2), (3, 3)],
        False ~=? sobrepoeTorres [(1, 1), (1.9, 2), (1.5, 1.5)], -- Não está exatamente na mesma posição, mas está na mesma célula da matriz
        True ~=? sobrepoeTorres [(1, 1), (5, 2), (1.5, 3.5), (2, 2)],
        True ~=? sobrepoeTorres [(1, 1)]
      ]

-- Teste 2: Verificar o caso em que a base está sobreposta a uma torre/portal
baseSobr :: Test
baseSobr =
  "Bases sobrepostas"
    ~: TestList
      [ False ~=? sobrepoeObjetos (0.5, 0.5) [(0.8, 0.8), (2, 2)] [(3, 3)], -- Está na mesma célula da matriz
        True ~=? sobrepoeObjetos (5, 5) [(0.8, 0.8), (2, 2)] [(3, 3)],
        False ~=? sobrepoeObjetos (1, 1) [(1, 1), (2, 2)] [(3, 3)] -- Está exatamente na mesma posição
      ]

-- Teste 3: Verificar o caso em que o crédito é negativo
baseCredito :: Test
baseCredito =
  "Creditos da base"
    ~: TestList
      [ False ~=? validaBase jogoCreditoNegativo,
        True ~=? validaBase jogoCreditoNulo,
        True ~=? validaBase jogoCreditoPositivo
      ]

jogoCreditoNegativo :: Jogo
jogoCreditoNegativo =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (1, 1), -- Base sobre terra
            creditosBase = -1
          },
      portaisJogo = [],
      torresJogo = [],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Agua, Relva]
        ],
      inimigosJogo = [],
      lojaJogo = []
    }

jogoCreditoNulo :: Jogo
jogoCreditoNulo =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (3, 1), -- Base sobre terra
            creditosBase = 0
          },
      portaisJogo = [],
      torresJogo = [],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Agua, Relva]
        ],
      inimigosJogo = [],
      lojaJogo = []
    }

jogoCreditoPositivo :: Jogo
jogoCreditoPositivo =
  Jogo
    { baseJogo =
        Base
          { vidaBase = 100,
            posicaoBase = (3, 1), -- Base sobre terra
            creditosBase = 50
          },
      portaisJogo = [],
      torresJogo = [],
      mapaJogo =
        [ [Terra, Terra, Terra],
          [Terra, Relva, Agua],
          [Terra, Agua, Relva]
        ],
      inimigosJogo = [],
      lojaJogo = []
    }
