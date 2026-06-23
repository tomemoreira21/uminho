#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/func.h"
#include "teste1.h"

Tabuleiro criaTabuleiroDeTeste(int linhas,int colunas,char valor) {
    Tabuleiro t = malloc(sizeof(struct tabuleiro));
    t->linhas = linhas;
    t->colunas = colunas;

    t->tabuleiro = malloc(t->linhas * sizeof(char *));
    for (int i = 0; i < t->linhas; i++) {
        t->tabuleiro[i] = malloc(t->colunas * sizeof(char));
        for (int j = 0; j < t->colunas; j++) {
            t->tabuleiro[i][j] = valor;
        }
    }

    return t;
}

void testa_leLinha() {
  CU_ASSERT_EQUAL(leLinha("a1"), 1);
  CU_ASSERT_EQUAL(leLinha("b10"), 10);
  CU_ASSERT_EQUAL(leLinha("c0"), 0);
  CU_ASSERT_EQUAL(leLinha("d123"), 123);
}

void testa_devolveJogada() {
  Tabuleiro t = criaTabuleiroDeTeste(5,5,'a'); 
  Jogada j = malloc(sizeof(struct jogada));    

  CU_ASSERT_EQUAL(devolveJogada(t, j, "a0"), 1); 
  CU_ASSERT_EQUAL(devolveJogada(t, j, "e4"), 1);  
  CU_ASSERT_EQUAL(devolveJogada(t, j, "c2"), 1);  

  CU_ASSERT_EQUAL(devolveJogada(t, j, "f0"), 0);  // coluna fora 
  CU_ASSERT_EQUAL(devolveJogada(t, j, "a5"), 0);  // linha fora 
  CU_ASSERT_EQUAL(devolveJogada(t, j, "z100"), 0); // completamente fora dos limites

  liberaTabuleiro(t);
  free(j);  
}

void testa_inicializaJogo () {
  Jogo j = malloc (sizeof (struct jogo));

  inicializaJogo (j);

  CU_ASSERT_EQUAL (j->estadoJogo,1);
  CU_ASSERT_EQUAL (j->venceu,0);
  CU_ASSERT_EQUAL (j->tabuleiro->tabuleiro,NULL);

  free (j->tabuleiro);
  free (j);
}

void testa_inicializaStack() {
  StackJogadas s = malloc (sizeof(struct stack));

  inicializaStack(s);

  CU_ASSERT_EQUAL(s->size, 100);
  CU_ASSERT_EQUAL(s->sp,0);
  CU_ASSERT_EQUAL(s->grupoAtual,1); 

  liberaStack (s);
}

void testa_ClearFicheiro () {
  Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
  char nomeDoFicheiro[] = "testes/testesTarefa1/tabuleiros/tabuleiroTesteLG.txt";
  char nomeDoFicheiroInexistente[] = ".";

  CU_ASSERT_EQUAL(gravarJogo(t,nomeDoFicheiro),0);

  CU_ASSERT_EQUAL(clearFicheiro(nomeDoFicheiro),0); 
  CU_ASSERT_EQUAL (clearFicheiro (nomeDoFicheiroInexistente),1);

  liberaTabuleiro(t);
}

void testa_comandoB() {
  Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
  StackJogadas s = malloc (sizeof (struct stack));
  inicializaStack (s);

  comandoR (s,t,"a1",0);

  CU_ASSERT_EQUAL(comandoB(s,t,"a0",0), 0);
  CU_ASSERT_EQUAL(t->tabuleiro[0][0], 'A');
  CU_ASSERT_EQUAL(t->tabuleiro[0][1], 'a');
  CU_ASSERT_EQUAL(t->tabuleiro[1][0], '#');
  CU_ASSERT_EQUAL(t->tabuleiro[1][1], 'a');

  CU_ASSERT_EQUAL (comandoB (s,t,"b0",0), 0);
  CU_ASSERT_EQUAL(t->tabuleiro[0][0], 'A');
  CU_ASSERT_EQUAL(t->tabuleiro[0][1], 'A');
  CU_ASSERT_EQUAL(t->tabuleiro[1][0], '#');
  CU_ASSERT_EQUAL(t->tabuleiro[1][1], 'a');
  
  CU_ASSERT_EQUAL (comandoB (s,t,"a1",0),1); // tenta pintar a branco onde já está riscado
  CU_ASSERT_EQUAL (comandoB (s,t,"a0",0),1); // tenta pintar onde já está pintado
  CU_ASSERT_EQUAL(comandoB(s,t,"b3",0), 1); // linha inválida
  CU_ASSERT_EQUAL(comandoB(s,t,"h1",0), 1); // coluna inválida
  CU_ASSERT_EQUAL (comandoB(s,t,"11",0), 1); // coordenada complemente inválida

  liberaTabuleiro (t);
  liberaStack (s);
}

void testa_comandoR() {
  Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
  StackJogadas s = malloc (sizeof (struct stack));
  inicializaStack (s);

  comandoB (s,t,"a1",0);

  CU_ASSERT_EQUAL(comandoR(s,t,"a0",0), 0);
  CU_ASSERT_EQUAL(t->tabuleiro[0][0], '#');
  CU_ASSERT_EQUAL(t->tabuleiro[0][1], 'a');
  CU_ASSERT_EQUAL(t->tabuleiro[1][0], 'A');
  CU_ASSERT_EQUAL(t->tabuleiro[1][1], 'a');

  CU_ASSERT_EQUAL (comandoR (s,t,"b0",0), 0);
  CU_ASSERT_EQUAL(t->tabuleiro[0][0], '#');
  CU_ASSERT_EQUAL(t->tabuleiro[0][1], '#');
  CU_ASSERT_EQUAL(t->tabuleiro[1][0], 'A');
  CU_ASSERT_EQUAL(t->tabuleiro[1][1], 'a');

  CU_ASSERT_EQUAL (comandoR (s,t,"a1",0),1); // tenta riscar onde já está pintado a branco
  CU_ASSERT_EQUAL (comandoR (s,t,"a0",0),1); // tenta riscar onde já está riscado
  CU_ASSERT_EQUAL(comandoR (s,t,"b3",0), 1); // linha inválida
  CU_ASSERT_EQUAL(comandoR(s,t,"f0",0), 1); // coluna inválida
  CU_ASSERT_EQUAL (comandoR(s,t,"12",0), 1); // coordenada complemente inválida

  liberaTabuleiro (t);
  liberaStack (s);
}

void testa_comandoG(){
  Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
  char nomeDoFicheiroValido[] = "testes/testesTarefa1/tabuleiros/tabuleiroTesteLG.txt";
  char nomeDoFicheiroInexistente[] = ".";

  CU_ASSERT_EQUAL(comandoG(t,nomeDoFicheiroValido), 0); //grava num ficheiro existente
  CU_ASSERT_EQUAL(comandoG(t,nomeDoFicheiroInexistente), 1); //tenta gravar num ficheiro que não existe

  liberaTabuleiro (t);

  clearFicheiro(nomeDoFicheiroValido);
}

void testa_comandoL() {
  Tabuleiro t = malloc(sizeof(struct tabuleiro));
  t->tabuleiro = NULL;
  char nomeDoFicheiroValido1 [] = "testes/testesTarefa1/tabuleiros/j4.txt";
  char nomeDoFicheiroValido2 [] = "testes/testesTarefa1/tabuleiros/j1.txt";
  char nomeDoFicheiroValido3 [] = "testes/testesTarefa1/tabuleiros/j2.txt";
  char nomeDoFicheiroValido4 [] = "testes/testesTarefa1/tabuleiros/j3.txt";
  char nomeDoFicheiroInvalido1 [] = "testes/testesTarefa1/tabuleiros/tabuleiroInvalido1.txt";
  char nomeDoFicheiroInvalido2 [] = "testes/testesTarefa1/tabuleiros/tabuleiroInvalido2.txt";
  char nomeDoFicheiroInvalido3 [] = "testes/testesTarefa1/tabuleiros/tabuleiroInvalido3.txt";
  char nomeDoFicheiroVazio [] = "testes/testesTarefa1/tabuleiros/tabuleiroVazio.txt";
  char nomeDoFicheiroInexistente [] = ".";

  CU_ASSERT_EQUAL(comandoL(t,nomeDoFicheiroValido1), 0);
  liberaTabuleiro(t);  

  t = malloc(sizeof(struct tabuleiro));  
  t->tabuleiro = NULL;
  CU_ASSERT_EQUAL(comandoL(t,nomeDoFicheiroValido2),0);
  liberaTabuleiro(t);

  t = malloc(sizeof(struct tabuleiro));
  t->tabuleiro = NULL;
  CU_ASSERT_EQUAL(comandoL(t, nomeDoFicheiroValido3), 0);
  liberaTabuleiro(t);

  t = malloc(sizeof(struct tabuleiro));
  t->tabuleiro = NULL;
  CU_ASSERT_EQUAL(comandoL(t, nomeDoFicheiroValido4), 0);
  liberaTabuleiro(t);

  t = malloc(sizeof(struct tabuleiro));
  t->tabuleiro = NULL;
  CU_ASSERT_EQUAL(comandoL(t, nomeDoFicheiroInvalido1), 1);
  liberaTabuleiro(t);

  t = malloc(sizeof(struct tabuleiro));
  t->tabuleiro = NULL;
  CU_ASSERT_EQUAL(comandoL(t, nomeDoFicheiroInvalido2), 1);
  liberaTabuleiro(t);

  t = malloc(sizeof(struct tabuleiro));
  t->tabuleiro = NULL;
  CU_ASSERT_EQUAL(comandoL(t, nomeDoFicheiroInvalido3), 1);
  liberaTabuleiro(t);

  t = malloc(sizeof(struct tabuleiro));
  t->tabuleiro = NULL;
  CU_ASSERT_EQUAL(comandoL(t, nomeDoFicheiroVazio), 1);
  liberaTabuleiro(t);

  t = malloc(sizeof(struct tabuleiro));
  t->tabuleiro = NULL;
  CU_ASSERT_EQUAL(comandoL(t, nomeDoFicheiroInexistente), 1);
  liberaTabuleiro(t);
}

void testa_gravarJogo () {
  Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
  char nomeDoFicheiroValido [] = "testes/testesTarefa1/tabuleiros/j4.txt";
  char nomeDoFicheiroInexistente [] = ".";

  CU_ASSERT_EQUAL(gravarJogo(t,nomeDoFicheiroValido), 0);
  CU_ASSERT_EQUAL(gravarJogo(t,nomeDoFicheiroInexistente), 1); 

  liberaTabuleiro (t);
}

void testa_coordValida() {
  CU_ASSERT_EQUAL(coordValida(5, 5, 0, 0), 1);  
  CU_ASSERT_EQUAL(coordValida(5, 5, 4, 4), 1);  
  CU_ASSERT_EQUAL(coordValida(5, 5, 2, 3), 1);  

  CU_ASSERT_EQUAL(coordValida(5, 5, -1, 0), 0); // linha negativa
  CU_ASSERT_EQUAL(coordValida(5, 5, 0, -1), 0); // coluna negativa
  CU_ASSERT_EQUAL(coordValida(5, 5, 5, 0), 0);  // linha fora
  CU_ASSERT_EQUAL(coordValida(5, 5, 0, 5), 0);  // coluna fora
}

void testa_comandoRBValido() {
  Tabuleiro t = criaTabuleiroDeTeste (3,3,'a');
  
  t->tabuleiro[1][1] = 'B';  
  t->tabuleiro[2][2] = '#';  
  
  CU_ASSERT_EQUAL(comandoRBValido(t, 1, 1), 0);  // está pintada a branco
  CU_ASSERT_EQUAL(comandoRBValido(t, 2, 2), 0);  // está riscada

  CU_ASSERT_EQUAL(comandoRBValido(t, -1, 0), 0); // fora do tabuleiro
  CU_ASSERT_EQUAL(comandoRBValido(t, 0, 3), 0);  // fora do tabuleiro

  liberaTabuleiro (t);
}

void testa_pushJogada() {
  StackJogadas s = malloc(sizeof(struct stack));
  inicializaStack(s);  

  Jogada j = malloc(sizeof(struct jogada));
  j->l = 0;
  j->c = 1;
  j->letraAnterior = 'x';

  pushJogada(s, j);

  CU_ASSERT_EQUAL(s->sp, 1);
  CU_ASSERT_PTR_EQUAL(s->jogadas[0], j);
  CU_ASSERT_EQUAL(s->jogadas[0]->l, 0);
  CU_ASSERT_EQUAL(s->jogadas[0]->c, 1);
  CU_ASSERT_EQUAL(s->jogadas[0]->letraAnterior, 'x');

  liberaStack(s);
}

void testa_addMaiuscula() {
  Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
  StackJogadas s = malloc(sizeof(struct stack));
  inicializaStack(s);

  Jogada jValida = malloc(sizeof(struct jogada));
  jValida->l = 0;
  jValida->c = 1;
  jValida->letraAnterior = 'a';

  CU_ASSERT_EQUAL (addMaiuscula(s, t, jValida,0),1); 

  CU_ASSERT_EQUAL(t->tabuleiro[0][1], 'A');
  CU_ASSERT_EQUAL(t->tabuleiro[0][0], 'a');
  CU_ASSERT_EQUAL(t->tabuleiro[1][0], 'a');
  CU_ASSERT_EQUAL(t->tabuleiro[1][1], 'a');

  Jogada jInvalida = malloc(sizeof(struct jogada));
  jInvalida->l = 10;
  jInvalida->c = 10;
  jInvalida->letraAnterior = 'a';

  CU_ASSERT_EQUAL (addMaiuscula(s, t, jInvalida,0),0); // tenta pintar de branco fora da coordenadas

  free(jInvalida);
  liberaTabuleiro(t); 
  liberaStack(s);
}


void testa_addRiscar() {
  Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
  StackJogadas s = malloc(sizeof(struct stack));
  inicializaStack(s);

  Jogada jValida = malloc(sizeof(struct jogada));
  jValida->l = 0;
  jValida->c = 1;
  jValida->letraAnterior = 'a';

  CU_ASSERT_EQUAL (addRiscar(s, t, jValida,0),1); 

  CU_ASSERT_EQUAL(t->tabuleiro[0][1], '#');
  CU_ASSERT_EQUAL(t->tabuleiro[0][0], 'a');
  CU_ASSERT_EQUAL(t->tabuleiro[1][0], 'a');
  CU_ASSERT_EQUAL(t->tabuleiro[1][1], 'a');

  Jogada jInvalida = malloc(sizeof(struct jogada));
  jInvalida->l = 10;
  jInvalida->c = 10;
  jInvalida->letraAnterior = 'a';

  CU_ASSERT_EQUAL (addRiscar(s, t, jInvalida,0),0); // tenta riscar fora da coordenadas

  free (jInvalida);
  liberaTabuleiro (t);
  liberaStack (s);
}

void testa_liberaTabuleiro() {
  Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
  liberaTabuleiro(t);
  CU_ASSERT(1); 
}

void testa_liberaJogadas() {
  StackJogadas s = malloc(sizeof(struct stack));
  inicializaStack(s);

  liberaJogadas(s);
  CU_ASSERT_EQUAL(s->sp, 0); 
  free(s->jogadas);
  free(s);
}

void testa_liberaStack() {
  StackJogadas s = malloc(sizeof(struct stack));
  inicializaStack(s);
  liberaStack (s);
  CU_ASSERT(1); 
}
