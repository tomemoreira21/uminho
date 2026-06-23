#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/func.h"
#include "../testesTarefa1/teste1.h"
#include "teste4.h"

void testa_ajudaUtilizador1 () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'A');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    t->tabuleiro[0][0] = 'b';
    ListaConflitos lista1 = verificaConflitos (t,NULL);

    CU_ASSERT_EQUAL (ajudaUtilizador (s,t,lista1,0),1);
    CU_ASSERT_EQUAL (t->tabuleiro[1][1],'#');

    liberaLista (lista1);
    ListaConflitos lista2 = verificaConflitos (t,NULL);
    CU_ASSERT_EQUAL (lista2,NULL);

    liberaLista (lista2);
    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_ajudaUtilizador2 () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    t->tabuleiro[0][0] = 'b';
    t->tabuleiro[1][0] = '#';
    t->tabuleiro[1][1] = 'A';
    ListaConflitos lista = verificaConflitos (t,NULL);

    CU_ASSERT_EQUAL (ajudaUtilizador (s,t,lista,0),1);
    CU_ASSERT_EQUAL (t->tabuleiro[0][0],'B'); // coloca os vizinhos pintados de branco
    CU_ASSERT_EQUAL (t->tabuleiro[0][1],'A'); // pinta de branco o (0,1) para não isolar a casa branca que está em (1,1)
    
    liberaLista (lista);
    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_ajudaUtilizador3 () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'A');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    t->tabuleiro[0][0] = 'B';
    t->tabuleiro[1][0] = 'B';
    ListaConflitos lista1 = verificaConflitos (t,NULL);

    CU_ASSERT_EQUAL (ajudaUtilizador (s,t,lista1,0),1);
    CU_ASSERT_EQUAL (t->tabuleiro[1][0],'#'); // resolve o problema de duplicado na mesma coluna
    liberaLista (lista1);

    ListaConflitos lista2 = verificaConflitos (t,NULL);
    CU_ASSERT_EQUAL (ajudaUtilizador (s,t,lista2,0),0); // não consegue fazer mais nada pois traz novos problemas 

    liberaLista (lista2);
    liberaTabuleiro (t);
    liberaStack (s);
}

void testa_devolveJogadaAjuda() {
    Tabuleiro t = criaTabuleiroDeTeste(3, 3, 'a'); 

    t->tabuleiro[1][2] = 'c'; 
    Jogada jog = devolveJogadaAjuda(t, 1, 2);
            
    CU_ASSERT_EQUAL(jog->l, 1);                   
    CU_ASSERT_EQUAL(jog->c, 2);                  
    CU_ASSERT_EQUAL(jog->letraAnterior, 'c');     

    free(jog);
    liberaTabuleiro(t);
}

void testa_permiteRiscar () {
    Tabuleiro t = criaTabuleiroDeTeste(3, 3, 'a');

    t->tabuleiro[1][1] = 'A'; 
    CU_ASSERT_EQUAL(permiteRiscar(t, 1, 1), 1);

    t->tabuleiro[1][2] = '#';
    CU_ASSERT_EQUAL(permiteRiscar(t, 1, 1), 0); // não permite pois tem um vizinho riscado

    liberaTabuleiro(t);
}

void testa_ajudaIsolarNaoBranco () {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = '#';

    CU_ASSERT_EQUAL (ajudaIsolarNaoBranco (s,t), 1); // pinta de branco o (1,0) pois dessa forma não fica isolado a casa branca (0,0)
    CU_ASSERT_EQUAL (t->tabuleiro[1][0],'A');

    t->tabuleiro[0][1] = 'A';
    t->tabuleiro[1][0] = 'a';

    CU_ASSERT_EQUAL (ajudaIsolarNaoBranco (s,t), 0); // não existe qualquer casa branca em perigo de se isolar

    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_ajudaPintarVizinhosNaoBranco() {
    Tabuleiro t = criaTabuleiroDeTeste(3, 3, 'a');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    t->tabuleiro[0][0] = 'A';  
    t->tabuleiro[0][1] = 'b';  
    t->tabuleiro[0][2] = 'c';  
    t->tabuleiro[1][0] = 'd';  
    t->tabuleiro[1][1] = 'e';  
    t->tabuleiro[1][2] = '#';  
    t->tabuleiro[2][0] = 'a';  
    t->tabuleiro[2][1] = 'd'; 
    t->tabuleiro[2][2] = 'D'; 

    CU_ASSERT_EQUAL (ajudaPintarVizinhosNaoBranco(s, t, 1, 2),1); 

    CU_ASSERT_EQUAL(t->tabuleiro[0][2], 'C'); 
    CU_ASSERT_EQUAL(t->tabuleiro[1][1], 'E'); 
    CU_ASSERT_EQUAL(t->tabuleiro[2][2], 'D'); 

    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_addBrancoRiscar() {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    t->tabuleiro[0][0] = 'B';
    Jogada j1 = devolveJogadaAjuda(t, 0, 0);
    int resultado = addBrancoRiscar(s, t, j1,1);

    CU_ASSERT_EQUAL(resultado, 1);
    CU_ASSERT_EQUAL(t->tabuleiro[0][0], '#');
    CU_ASSERT_EQUAL(s->jogadas[0]->l, 0);
    CU_ASSERT_EQUAL(s->jogadas[0]->c, 0);
    CU_ASSERT_EQUAL(s->jogadas[0]->letraAnterior, 'B');

    t->tabuleiro[1][1] = 'b'; 
    Jogada j2 = devolveJogadaAjuda(t, 1, 1);
    resultado = addBrancoRiscar(s, t, j2,2);

    CU_ASSERT_EQUAL(resultado, 0);
    CU_ASSERT_NOT_EQUAL(t->tabuleiro[1][1], '#'); // continua igual porque não permite pintar em cima de minusculas

    t->tabuleiro[1][0] = '#'; 
    Jogada j3 = devolveJogadaAjuda(t, 1, 0);
    resultado = addBrancoRiscar(s, t, j3,3);

    CU_ASSERT_EQUAL(resultado, 0);

    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_ajudaRiscarDuplicadosLinhaColuna () {
    Tabuleiro t = criaTabuleiroDeTeste(3, 3, 'a');
    StackJogadas s = malloc (sizeof (struct stack));
    inicializaStack (s);

    t->tabuleiro[0][0] = 'B';
    t->tabuleiro[0][1] = 'A';
    t->tabuleiro[0][2] = 'A';
    t->tabuleiro[1][1] = 'A';  

    CU_ASSERT_EQUAL(ajudaRiscarDuplicadosLinhaColuna(s, t, 0, 1), 1); 
    CU_ASSERT_EQUAL(t->tabuleiro[0][2],'#'); 
    CU_ASSERT_EQUAL(t->tabuleiro[1][1],'#'); 

    t->tabuleiro[0][0] = '#';  
    t->tabuleiro[0][1] = 'A';
    t->tabuleiro[0][2] = 'A';
    t->tabuleiro[1][1] = 'b';
    t->tabuleiro[1][2] = 'A';

    CU_ASSERT_EQUAL(ajudaRiscarDuplicadosLinhaColuna(s, t, 0, 0), 0); // não consegue pois se risca (0,1) fica com dois vizinhos riscados
    
    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'A';
    t->tabuleiro[1][0] = 'A';
    t->tabuleiro[1][1] = 'b';

    CU_ASSERT_EQUAL(ajudaRiscarDuplicadosLinhaColuna(s, t, 0, 0), 0); // não consegue pois se risca (0,1) e (1,0) fica a casa branca (0,0) isolada

    liberaTabuleiro(t);
    liberaStack(s);
}


void testa_ajudaRiscarLinhaColuna () {
    Tabuleiro t = criaTabuleiroDeTeste(3, 3, 'a');
    StackJogadas s = malloc (sizeof (struct stack));
    inicializaStack (s);

    t->tabuleiro[0][0] = 'B';
    t->tabuleiro[0][1] = 'A';
    t->tabuleiro[1][1] = 'C';  

    CU_ASSERT_EQUAL(ajudaRiscarLinhaColuna(s, t, 0, 1), 1); 
    CU_ASSERT_EQUAL(t->tabuleiro[2][1],'#'); 
    CU_ASSERT_EQUAL(t->tabuleiro[0][2],'#'); 

    t->tabuleiro[0][0] = 'A';  
    t->tabuleiro[0][1] = 'a';
    t->tabuleiro[0][2] = '#';
    t->tabuleiro[2][0] = 'B';

    CU_ASSERT_EQUAL(ajudaRiscarLinhaColuna(s, t, 0, 0), 0); // não consegue pois se risca (0,1) fica com dois vizinhos riscados
    
    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'a';
    t->tabuleiro[0][2] = 'a';
    t->tabuleiro[1][0] = 'a';
    t->tabuleiro[2][0] = 'C';
    t->tabuleiro[2][1] = '#';

    CU_ASSERT_EQUAL(ajudaRiscarLinhaColuna(s, t, 0, 0), 0); // não consegue pois se risca (1,0) fica a casa branca (2,0) isolada

    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_ajudaRiscarDuplicadosColuna() {
    Tabuleiro t = criaTabuleiroDeTeste(3, 3, 'a');
    StackJogadas s = malloc (sizeof (struct stack));
    inicializaStack (s);

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[1][0] = 'A';  
    t->tabuleiro[2][0] = 'b';

    CU_ASSERT_EQUAL(ajudaRiscarDuplicadosColuna(s, t, 0, 0), 1);  
    CU_ASSERT_EQUAL(t->tabuleiro[1][0],'#'); 

    t->tabuleiro[1][0] = 'A';  
    t->tabuleiro[2][0] = '#';
    CU_ASSERT_EQUAL (ajudaRiscarDuplicadosColuna (s, t, 0, 0),0); // não risca a (1,0) pois ficaria dois vizinhos riscados 
    CU_ASSERT_EQUAL(t->tabuleiro[1][0],'A'); 
    
    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_ajudaRiscarColuna () {
    Tabuleiro t = criaTabuleiroDeTeste(3, 3, 'a');
    StackJogadas s = malloc (sizeof (struct stack));
    inicializaStack (s);

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[1][0] = 'a';
    t->tabuleiro[2][0] = 'c';

    CU_ASSERT_EQUAL (ajudaRiscarColuna (s,t,0,0),1);
    CU_ASSERT_EQUAL(t->tabuleiro[1][0],'#'); 

    t->tabuleiro[1][0] = 'a';
    t->tabuleiro[2][0] = '#';
    CU_ASSERT_EQUAL(ajudaRiscarColuna(s, t, 0, 0), 0); // não risca a (1,0) pois ficaria dois vizinhos riscados  
    CU_ASSERT_EQUAL(t->tabuleiro[1][0],'a');

    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_ajudaRiscarDuplicadosLinha() {
    Tabuleiro t = criaTabuleiroDeTeste(3, 3, 'a');
    StackJogadas s = malloc (sizeof (struct stack));
    inicializaStack (s);

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'A';  
    t->tabuleiro[0][2] = 'b';

    CU_ASSERT_EQUAL(ajudaRiscarDuplicadosLinha(s, t, 0, 0), 1);  
    CU_ASSERT_EQUAL(t->tabuleiro[0][1],'#'); 

    t->tabuleiro[0][1] = 'A';
    t->tabuleiro[0][2] = '#';
    CU_ASSERT_EQUAL(ajudaRiscarDuplicadosLinha(s, t, 0, 0), 0); // não risca a (0,1) pois ficaria dois vizinhos riscados  
    CU_ASSERT_EQUAL(t->tabuleiro[0][1],'A'); 
    
    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_ajudaRiscarLinha () {
    Tabuleiro t = criaTabuleiroDeTeste(3, 3, 'a');
    StackJogadas s = malloc (sizeof (struct stack));
    inicializaStack (s);

    t->tabuleiro[0][0] = 'a';
    t->tabuleiro[0][1] = 'A';
    t->tabuleiro[0][2] = '#';

    CU_ASSERT_EQUAL (ajudaRiscarLinha (s,t,0,1),1);
    CU_ASSERT_EQUAL(t->tabuleiro[0][0],'#'); 

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'a';
    CU_ASSERT_EQUAL(ajudaRiscarLinha(s, t, 0, 0), 0); // não risca a (0,1) pois ficaria dois vizinhos riscados  
    CU_ASSERT_EQUAL(t->tabuleiro[0][1],'a');

    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_comandoA1 () {
    Tabuleiro t = criaTabuleiroDeTeste (5,5,'a');
    StackJogadas s = malloc (sizeof (struct stack));
    inicializaStack (s);

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

    CU_ASSERT_EQUAL(comandoA(s,t,0),0); // não consegue ajudar sem nenhuma jogada feita

    comandoB (s,t,"a1",0);
    comandoB (s,t,"b1",0);
    comandoB (s,t,"a3",0);
    comandoB (s,t,"b3",0);
    
    CU_ASSERT_EQUAL(comandoA(s,t,0),1);
    CU_ASSERT_EQUAL(t->tabuleiro[0][1],'#');
    CU_ASSERT_EQUAL(t->tabuleiro[1][1],'C');
    CU_ASSERT_EQUAL(t->tabuleiro[0][0],'E');
    CU_ASSERT_EQUAL(t->tabuleiro[1][0],'D');
    CU_ASSERT_EQUAL(t->tabuleiro[0][2],'A');
    CU_ASSERT_EQUAL(t->tabuleiro[0][3],'D');
    CU_ASSERT_EQUAL(t->tabuleiro[1][3],'E');
    CU_ASSERT_EQUAL(t->tabuleiro[0][4],'C');
    CU_ASSERT_EQUAL(t->tabuleiro[1][4],'#');
    CU_ASSERT_EQUAL(t->tabuleiro[2][4],'E');

    liberaTabuleiro(t);
    liberaStack(s);
}

void testa_comandoA2 () {
    Tabuleiro t = criaTabuleiroDeTeste (2,3,'a');
    StackJogadas s = malloc (sizeof (struct stack));
    inicializaStack (s);

    t->tabuleiro[0][0] = 'a';
    t->tabuleiro[0][1] = 'b';
    t->tabuleiro[0][2] = 'a';
    t->tabuleiro[1][0] = 'c';
    t->tabuleiro[1][1] = 'b';
    t->tabuleiro[1][2] = 'b';

    comandoB (s,t,"b0",0);
    comandoB (s,t,"b2",0);

    CU_ASSERT_EQUAL(comandoA(s,t,0),-1); // não ajuda pois irá piorar o estado do tabuleiro

    liberaTabuleiro(t);
    liberaStack(s);
}
