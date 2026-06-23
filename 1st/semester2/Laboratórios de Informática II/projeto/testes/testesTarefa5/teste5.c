#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/func.h"
#include "../testesTarefa1/teste1.h"
#include "teste5.h"

void testa_jogoResolvido () {
    Tabuleiro t = criaTabuleiroDeTeste(5,5,'a');  
    ListaConflitos lista = NULL;

    t->tabuleiro[0][0] = 'E';
    t->tabuleiro[0][1] = '#';
    t->tabuleiro[0][2] = 'A';
    t->tabuleiro[0][3] = 'D';
    t->tabuleiro[0][4] = 'C';

    t->tabuleiro[1][0] = 'D';
    t->tabuleiro[1][1] = 'C';
    t->tabuleiro[1][2] = '#';
    t->tabuleiro[1][3] = 'E';
    t->tabuleiro[1][4] = '#';

    t->tabuleiro[2][0] = 'B';
    t->tabuleiro[2][1] = '#';
    t->tabuleiro[2][2] = 'D';
    t->tabuleiro[2][3] = 'C';
    t->tabuleiro[2][4] = 'E';

    t->tabuleiro[3][0] = 'C';
    t->tabuleiro[3][1] = 'D';
    t->tabuleiro[3][2] = 'E';
    t->tabuleiro[3][3] = '#';
    t->tabuleiro[3][4] = 'B';

    t->tabuleiro[4][0] = 'A';
    t->tabuleiro[4][1] = '#';
    t->tabuleiro[4][2] = 'C';
    t->tabuleiro[4][3] = 'B';
    t->tabuleiro[4][4] = '#';

    CU_ASSERT_EQUAL (jogoResolvido (t,lista),1);

    t->tabuleiro[0][0] = 'e'; // coloca uma mínuscula
    CU_ASSERT_EQUAL (jogoResolvido (t,lista),0);

    t->tabuleiro[0][0] = 'E';
    t->tabuleiro[1][0] = '#'; // deixa de haver caminho
    CU_ASSERT_EQUAL (jogoResolvido (t,lista),0);

    liberaTabuleiro(t);
    liberaLista (lista);
}

void testa_copiaJogada () {
    Jogada j = malloc(sizeof(struct jogada));
    j->l = 2;
    j->c = 3;
    j->letraAnterior = 'd';

    Jogada copia = copiaJogada(j);

    CU_ASSERT_PTR_NOT_NULL(copia);
    CU_ASSERT_EQUAL(copia->l, 2);
    CU_ASSERT_EQUAL(copia->c, 3);
    CU_ASSERT_EQUAL(copia->letraAnterior, 'd');

    free(j);
    free(copia);
}

void testa_letraRepeteNaLinhaOuColuna () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
    t->tabuleiro[0][0] = 'a';
    t->tabuleiro[0][1] = 'b';
    t->tabuleiro[1][1] = 'c';

    CU_ASSERT_EQUAL(letraRepeteNaLinhaOuColuna(t, 0, 0), 1); // repetido na mesma coluna

    t->tabuleiro[1][0] = 'd';
    t->tabuleiro[0][1] = 'a';
    CU_ASSERT_EQUAL(letraRepeteNaLinhaOuColuna(t, 0, 0), 1); // repetido na mesma linha

    t->tabuleiro[1][1] = '#';
    CU_ASSERT_EQUAL(letraRepeteNaLinhaOuColuna(t, 1, 1), 0);

    liberaTabuleiro (t);
}

void testa_backTrack () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    comandoB (s,t,"b0",0);
    comandoR (s,t,"a0",0);
    int topoStackAntes = s->sp;
    comandoB (s,t,"a1",0);
    comandoR (s,t,"b1",0);
    
    backTrack(t, s, topoStackAntes);
    CU_ASSERT_EQUAL(s->sp, topoStackAntes); // verifica se o sp é igual ao inicial 

    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_desfazStack () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    comandoB (s,t,"b0",0);
    comandoR (s,t,"a0",0);
    comandoB (s,t,"a1",0);

    desfazStack (s,t);
    CU_ASSERT_EQUAL (s->sp,0);

    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_resolveJogo1 () {
    Tabuleiro t = criaTabuleiroDeTeste(5,5,'a');  
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);
    
    t->tabuleiro[0][0] = 'E';
    t->tabuleiro[0][1] = '#';
    t->tabuleiro[0][2] = 'A';
    t->tabuleiro[0][3] = 'D';
    t->tabuleiro[0][4] = 'C';

    t->tabuleiro[1][0] = 'D';
    t->tabuleiro[1][1] = 'C';
    t->tabuleiro[1][2] = '#';
    t->tabuleiro[1][3] = 'E';
    t->tabuleiro[1][4] = '#';

    t->tabuleiro[2][0] = 'B';
    t->tabuleiro[2][1] = '#';
    t->tabuleiro[2][2] = 'D';
    t->tabuleiro[2][3] = 'C';
    t->tabuleiro[2][4] = 'E';

    t->tabuleiro[3][0] = 'C';
    t->tabuleiro[3][1] = 'D';
    t->tabuleiro[3][2] = 'E';
    t->tabuleiro[3][3] = '#';
    t->tabuleiro[3][4] = 'B';

    t->tabuleiro[4][0] = 'A';
    t->tabuleiro[4][1] = '#';
    t->tabuleiro[4][2] = 'C';
    t->tabuleiro[4][3] = 'B';
    t->tabuleiro[4][4] = '#';

    CU_ASSERT_EQUAL (resolveJogo (t,s),1); // tabuleiro já se encontra resolvido

    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_resolveJogo2 () {
    Tabuleiro t = criaTabuleiroDeTeste(2,2,'a');  
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    t->tabuleiro[1][1] = 'b';

    CU_ASSERT_EQUAL (resolveJogo (t,s),1); 

    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_resolveJogo3 () {
    Tabuleiro t = criaTabuleiroDeTeste(5,5,'a');  
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    t->tabuleiro[0][0] = 'e';
    t->tabuleiro[0][1] = 'c';
    t->tabuleiro[0][2] = 'a';
    t->tabuleiro[0][3] = 'd';
    t->tabuleiro[0][4] = 'c';

    t->tabuleiro[1][0] = 'd';
    t->tabuleiro[1][1] = 'c';
    t->tabuleiro[1][2] = 'd';
    t->tabuleiro[1][3] = 'e';
    t->tabuleiro[1][4] = 'c';

    t->tabuleiro[2][0] = 'b';
    t->tabuleiro[2][1] = 'd';
    t->tabuleiro[2][2] = 'd';
    t->tabuleiro[2][3] = 'c';
    t->tabuleiro[2][4] = 'e';

    t->tabuleiro[3][0] = 'c';
    t->tabuleiro[3][1] = 'd';
    t->tabuleiro[3][2] = 'e';
    t->tabuleiro[3][3] = 'e';
    t->tabuleiro[3][4] = 'b';

    t->tabuleiro[4][0] = 'a';
    t->tabuleiro[4][1] = 'c';
    t->tabuleiro[4][2] = 'c';
    t->tabuleiro[4][3] = 'b';
    t->tabuleiro[4][4] = 'b';

    CU_ASSERT_EQUAL (resolveJogo (t,s),1); 

    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_resolveJogo4 () {
    Tabuleiro t = criaTabuleiroDeTeste(2,2,'a');  
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    CU_ASSERT_EQUAL (resolveJogo (t,s),0); // tabuleiro impossível de ser resolvido

    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_resolveJogoEstadoInvalido1 () {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    t->tabuleiro[0][0] = 'b';
    t->tabuleiro[1][1] = 'c';

    comandoB (s,t,"a0",0);
    comandoR (s,t,"a1",0);
    comandoR (s,t,"b0",0);
    comandoB (s,t,"b1",0);

    int res = resolveJogoEstadoInvalido(t, s);

    CU_ASSERT_EQUAL(res, 1);          // consegue resolver

    CU_ASSERT_EQUAL (t->tabuleiro[0][0],'B');
    CU_ASSERT_EQUAL (t->tabuleiro[0][1],'A');
    CU_ASSERT_EQUAL (t->tabuleiro[1][0],'A');
    CU_ASSERT_EQUAL (t->tabuleiro[1][1],'C');

    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_resolveJogoEstadoInvalido2 () {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    comandoB (s,t,"a0",0);
    comandoB (s,t,"b1",0);

    int res = resolveJogoEstadoInvalido(t, s);

    CU_ASSERT_EQUAL(res, 0);          // tabuleiro não tem solução

    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_possuiConflitos1 () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
    ListaConflitos lista = NULL;

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = '#';
    t->tabuleiro[1][0] = '#';
    t->tabuleiro[1][1] = 'B';

    CU_ASSERT_EQUAL (possuiConflitos (t,&lista),1); // nao possui um caminho entre as brancas

    liberaLista (lista);
    liberaTabuleiro (t);
}

void testa_possuiConflitos2 () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
    ListaConflitos lista = NULL;

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'A';
    t->tabuleiro[1][0] = 'C';
    t->tabuleiro[1][1] = 'B';

    CU_ASSERT_EQUAL (possuiConflitos (t,&lista),1); // possui duas duplicadas na mesam linha

    liberaLista (lista);
    liberaTabuleiro (t);
}

void testa_possuiConflitos3 () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
    ListaConflitos lista = NULL;

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'B';
    t->tabuleiro[1][0] = 'B';
    t->tabuleiro[1][1] = 'A';

    CU_ASSERT_EQUAL (possuiConflitos (t,&lista),0);

    liberaLista (lista);
    liberaTabuleiro (t);
}

void testa_pintarMaisPropagacao () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
    StackJogadas s = malloc(sizeof(struct stack));
    Jogada jog = devolveJogadaAjuda (t,0,0);
    inicializaStack(s);
    int alteracoes = 0;

    t->tabuleiro[0][1] = 'B';
    t->tabuleiro[1][1] = 'C';

    pintarMaisPropagacao (t,s,jog,&alteracoes);
    CU_ASSERT_EQUAL (t->tabuleiro[0][0],'A');
    CU_ASSERT_EQUAL (t->tabuleiro[1][0],'#');
    CU_ASSERT_EQUAL (alteracoes,1);

    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_riscarMaisPropagacao () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
    StackJogadas s = malloc(sizeof(struct stack));
    Jogada jog = devolveJogadaAjuda (t,0,0);
    inicializaStack(s);
    int alteracoes = 0, jogadaFoiRiscada = 0;

    t->tabuleiro[0][1] = 'B';
    t->tabuleiro[1][1] = 'C';

    riscarMaisPropagacao (t,s,jog,&alteracoes,&jogadaFoiRiscada,0);
    CU_ASSERT_EQUAL (t->tabuleiro[0][0],'#');
    CU_ASSERT_EQUAL (t->tabuleiro[1][0],'A');
    CU_ASSERT_EQUAL (alteracoes,1);
    CU_ASSERT_EQUAL (jogadaFoiRiscada,1);

    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_recuperaTabuleiroInicial() {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    comandoB(s, t, "a0", 0); 
    comandoB(s, t, "a1", 0); 
    comandoB(s, t, "b0", 0); 

    Tabuleiro copia = copiaTabuleiro(t);
    recuperaTabuleiroInicial(copia, s);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            CU_ASSERT_EQUAL(copia->tabuleiro[i][j], 'a'); 

    liberaTabuleiro(t);
    liberaTabuleiro(copia);
    liberaStack(s);
}

void testa_copiaTabuleiro() {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
    t->tabuleiro[0][0] = 'a';
    t->tabuleiro[0][1] = 'b';
    t->tabuleiro[1][0] = 'c';
    t->tabuleiro[1][1] = 'd';

    Tabuleiro copia = copiaTabuleiro(t);

    CU_ASSERT_EQUAL(copia->tabuleiro[0][0], 'a');
    CU_ASSERT_EQUAL(copia->tabuleiro[0][1], 'b');
    CU_ASSERT_EQUAL(copia->tabuleiro[1][0], 'c');
    CU_ASSERT_EQUAL(copia->tabuleiro[1][1], 'd');

    t->tabuleiro[0][0] = 'A';
    CU_ASSERT_EQUAL(copia->tabuleiro[0][0], 'a'); // a copia permanece igual

    liberaTabuleiro(t);
    liberaTabuleiro(copia);
}

void testa_contaMin1 () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');

    t->tabuleiro[0][0] = '#';
    t->tabuleiro[0][1] = '#';
    t->tabuleiro[1][0] = '#';
    t->tabuleiro[1][1] = '#';

    CU_ASSERT_EQUAL(contaMin (t), 0);

    liberaTabuleiro (t);
}

void testa_contaMin2 () {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2,'a');

    t->tabuleiro[0][0] = 'a';
    t->tabuleiro[0][1] = 'B';
    t->tabuleiro[1][0] = 'c';
    t->tabuleiro[1][1] = '#';

    CU_ASSERT_EQUAL(contaMin (t), 2);

    liberaTabuleiro (t);
}

void testa_verificaEstadoJogo1 () {
    Jogo j = malloc(sizeof(struct jogo));
    Tabuleiro t = criaTabuleiroDeTeste(2,2,'a');  
    j->estadoJogo = 1;
    j->venceu = 0; 
   
    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'B';
    t->tabuleiro[1][0] = 'C';
    t->tabuleiro[1][1] = 'D';

    j->tabuleiro = t;
    
    verificaEstadoJogo(j);
    CU_ASSERT_EQUAL(j->estadoJogo, 0);

    liberaTabuleiro(t);
    free(j);
}

void testa_verificaEstadoJogo2 () {
    Jogo j = malloc(sizeof(struct jogo));
    Tabuleiro t = criaTabuleiroDeTeste(5,5,'a');  
    j->estadoJogo = 1;
    j->venceu = 0; 
   
    t->tabuleiro[0][0] = 'E';
    t->tabuleiro[0][1] = '#';
    t->tabuleiro[0][2] = 'A';
    t->tabuleiro[0][3] = 'D';
    t->tabuleiro[0][4] = 'C';

    t->tabuleiro[1][0] = 'D';
    t->tabuleiro[1][1] = 'C';
    t->tabuleiro[1][2] = '#';
    t->tabuleiro[1][3] = 'E';
    t->tabuleiro[1][4] = '#';

    t->tabuleiro[2][0] = 'B';
    t->tabuleiro[2][1] = '#';
    t->tabuleiro[2][2] = 'D';
    t->tabuleiro[2][3] = 'C';
    t->tabuleiro[2][4] = 'E';

    t->tabuleiro[3][0] = 'C';
    t->tabuleiro[3][1] = 'D';
    t->tabuleiro[3][2] = 'E';
    t->tabuleiro[3][3] = '#';
    t->tabuleiro[3][4] = 'B';

    t->tabuleiro[4][0] = 'A';
    t->tabuleiro[4][1] = '#';
    t->tabuleiro[4][2] = 'C';
    t->tabuleiro[4][3] = 'B';
    t->tabuleiro[4][4] = '#';

    j->tabuleiro = t;
    
    verificaEstadoJogo(j);
    CU_ASSERT_EQUAL(j->estadoJogo, 0);

    liberaTabuleiro(t);
    free(j);
}

void testa_verificaEstadoJogo3 () {
    Jogo j = malloc(sizeof(struct jogo));
    Tabuleiro t =  criaTabuleiroDeTeste(3,3,'a'); 
    j->estadoJogo = 1;
    j->venceu = 0;     

    t->tabuleiro[0][0] = 'a';
    t->tabuleiro[0][1] = 'b';
    t->tabuleiro[0][2] = 'c';

    t->tabuleiro[1][0] = 'd';
    t->tabuleiro[1][1] = 'e';
    t->tabuleiro[1][2] = 'f';

    t->tabuleiro[2][0] = 'g';
    t->tabuleiro[2][1] = 'h';
    t->tabuleiro[2][2] = 'i';

    j->tabuleiro = t;
    
    verificaEstadoJogo(j);
    CU_ASSERT_EQUAL(j->estadoJogo, 1);

    liberaTabuleiro(t);
    free(j);
}

void testa_verificaVitoria1() {
   Jogo j = malloc(sizeof(struct jogo));
   Tabuleiro t = criaTabuleiroDeTeste(2,2,'A');
   j->estadoJogo = 1;
   j->venceu = 0; 
    
   t->tabuleiro[0][0] = 'A';
   t->tabuleiro[0][1] = 'B';
   t->tabuleiro[1][0] = 'C';
   t->tabuleiro[1][1] = 'D';

   j->tabuleiro = t;

   verificaVitoria(j, NULL);
   CU_ASSERT_EQUAL(j->venceu, 1);

   liberaTabuleiro(t);
   free(j);
}

void testa_verificaVitoria2() {
   Jogo j = malloc(sizeof(struct jogo));
   Tabuleiro t = criaTabuleiroDeTeste(2,2,'A');
   j->estadoJogo = 1;
   j->venceu = 0; 
    
   t->tabuleiro[0][0] = 'A';
   t->tabuleiro[0][1] = 'A';
   t->tabuleiro[1][0] = 'C';
   t->tabuleiro[1][1] = 'D';

   j->tabuleiro = t;

   ListaConflitos lista = verificaConflitos (j->tabuleiro,NULL);

   verificaVitoria(j,lista);
   CU_ASSERT_EQUAL(j->venceu, 0);

   liberaLista (lista);
   liberaTabuleiro(t);
   free(j);
}

void testa_verificaVitoria3() {
   Jogo j = malloc(sizeof(struct jogo));
   Tabuleiro t = criaTabuleiroDeTeste(2,2,'a');
   j->estadoJogo = 1;
   j->venceu = 0; 

   t->tabuleiro[0][1] = 'B';
   t->tabuleiro[1][0] = 'C';
   t->tabuleiro[1][1] = 'D';
   
   j->tabuleiro = t;
    
   verificaVitoria(j, NULL);
   CU_ASSERT_EQUAL(j->venceu, 0); 
   
   liberaTabuleiro(t);
   free(j);
}