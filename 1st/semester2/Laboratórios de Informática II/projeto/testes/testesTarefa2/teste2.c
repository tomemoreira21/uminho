#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/func.h"
#include "../testesTarefa1/teste1.h"
#include "teste2.h"

// Função auxiliar para verificar se a lista está ordenada corretamente
void verificaOrdem(ListaConflitos lista, int linhas[], int colunas[], TipoErro erros[], int N) {
    for (int i = 0; i < N; i++) {
        CU_ASSERT_PTR_NOT_NULL(lista);
        CU_ASSERT_EQUAL(lista->l, linhas[i]);
        CU_ASSERT_EQUAL(lista->c, colunas[i]);
        CU_ASSERT_EQUAL(lista->erro, erros[i]);
        lista = lista->prox;
    }
    CU_ASSERT_PTR_NULL(lista); 
}

// Função auxiliar para comparar listas elemento a elemento
int comparaListas(ListaConflitos lista1, ListaConflitos lista2) {   
    while (lista1 != NULL && lista2 != NULL) {
        if (lista1->l != lista2->l || lista1->c != lista2->c || lista1->erro != lista2->erro) {
            return 0;  
        }
        lista1 = lista1->prox;
        lista2 = lista2->prox;
    }

    if (lista1 != NULL || lista2 != NULL) {
        return 0;  
    }

    return 1;
}

void testa_verificaSemConflitos() {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');

    t->tabuleiro[0][0] = 'C';
    t->tabuleiro[0][1] = 'B';

    t->tabuleiro[1][0] = '#'; 
    t->tabuleiro[1][1] = 'A'; 

    ListaConflitos esperada = NULL; // Lista esperada vazia (sem erros)
    ListaConflitos resultado = verificaConflitos(t, NULL);
    
    CU_ASSERT(comparaListas(esperada, resultado));
    
    liberaLista(esperada);
    liberaLista(resultado);
    liberaTabuleiro(t);
}

void testa_verificaConflitos1 () {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'A';

    t->tabuleiro[1][0] = '#';
    t->tabuleiro[1][1] = 'b';

    ListaConflitos esperada = NULL;
    esperada = insereOrdenado(esperada, 0, 0, ERRO_DUPLICADO_BRANCO_LINHA);
    esperada = insereOrdenado(esperada, 0, 1, ERRO_DUPLICADO_BRANCO_LINHA);
    esperada = insereOrdenado(esperada, 1, 0, ERRO_VIZINHO_NAO_BRANCO);

    ListaConflitos resultado = verificaConflitos(t, NULL);

    CU_ASSERT(comparaListas(esperada, resultado)); 

    liberaLista(esperada);
    liberaLista(resultado);
    liberaTabuleiro(t);
}

void testa_verificaConflitos2 () {
    Tabuleiro t = criaTabuleiroDeTeste(3,3,'a');

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'A';
    t->tabuleiro[0][2] = '#';

    t->tabuleiro[1][0] = 'b';
    t->tabuleiro[1][1] = '#';
    t->tabuleiro[1][2] = 'B';

    t->tabuleiro[2][0] = '#';
    t->tabuleiro[2][1] = 'a';
    t->tabuleiro[2][2] = 'C';

    ListaConflitos esperada = NULL;
    esperada = insereOrdenado (esperada,0,0,ERRO_DUPLICADO_BRANCO_LINHA);
    esperada = insereOrdenado (esperada,0,1,ERRO_FALTA_RISCAR_COLUNA);
    esperada = insereOrdenado (esperada,0,1,ERRO_DUPLICADO_BRANCO_LINHA);
    esperada = insereOrdenado (esperada,1,1,ERRO_VIZINHO_NAO_BRANCO);
    esperada = insereOrdenado (esperada,1,2,ERRO_FALTA_RISCAR_LINHA);
    esperada = insereOrdenado (esperada,2,0,ERRO_VIZINHO_NAO_BRANCO);
   
    ListaConflitos resultado = verificaConflitos(t, NULL);

    CU_ASSERT(comparaListas(esperada, resultado)); 

    liberaLista(esperada);
    liberaLista(resultado);
    liberaTabuleiro(t);
}

void testa_verificaConflitos3 () {
    Tabuleiro t = criaTabuleiroDeTeste(3,3,'a');

    t->tabuleiro[0][0] = 'B';
    t->tabuleiro[0][1] = '#';
    t->tabuleiro[0][2] = 'B';

    t->tabuleiro[1][0] = '#';
    t->tabuleiro[1][1] = 'C';
    t->tabuleiro[1][2] = 'B';

    t->tabuleiro[2][0] = '#';
    t->tabuleiro[2][1] = '#';
    t->tabuleiro[2][2] = 'c';

    ListaConflitos esperada = NULL;
    esperada = insereOrdenado(esperada, 0, 0, ERRO_DUPLICADO_BRANCO_LINHA);
    esperada = insereOrdenado(esperada, 0, 2, ERRO_DUPLICADO_BRANCO_LINHA_COLUNA);
    esperada = insereOrdenado (esperada,1, 0,ERRO_VIZINHO_RISCADO);
    esperada = insereOrdenado (esperada,1, 2,ERRO_DUPLICADO_BRANCO_COLUNA);
    esperada = insereOrdenado (esperada,2, 0,ERRO_VIZINHO_RISCADO);
    esperada = insereOrdenado (esperada,2, 1,ERRO_VIZINHO_RISCADO);
    esperada = insereOrdenado (esperada,2, 1,ERRO_VIZINHO_NAO_BRANCO);
    
    ListaConflitos resultado = verificaConflitos(t, NULL);

    CU_ASSERT(comparaListas(esperada, resultado)); 

    liberaLista(esperada);
    liberaLista(resultado);
    liberaTabuleiro(t);
}

void testa_verificaConflitos4 () {
    Tabuleiro t = criaTabuleiroDeTeste(3,3,'a');

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'b';
    t->tabuleiro[0][2] = 'A';

    t->tabuleiro[1][0] = '#';
    t->tabuleiro[1][1] = 'C';
    t->tabuleiro[1][2] = 'c';

    t->tabuleiro[2][0] = 'B';
    t->tabuleiro[2][1] = '#';
    t->tabuleiro[2][2] = 'b';

    ListaConflitos esperada = NULL;

    esperada = insereOrdenado(esperada, 0, 0, ERRO_DUPLICADO_BRANCO_LINHA);
    esperada = insereOrdenado(esperada, 0, 2, ERRO_DUPLICADO_BRANCO_LINHA);
    esperada = insereOrdenado(esperada, 1, 1,ERRO_FALTA_RISCAR_LINHA);
    esperada = insereOrdenado(esperada,2, 0,ERRO_FALTA_RISCAR_LINHA);
    esperada = insereOrdenado(esperada,2, 1,ERRO_VIZINHO_NAO_BRANCO);

    ListaConflitos resultado = verificaConflitos(t, NULL);

    CU_ASSERT(comparaListas(esperada, resultado));

    liberaLista(esperada);
    liberaLista(resultado);
    liberaTabuleiro(t);
}



void testa_insereOrdenado() {
    ListaConflitos lista = NULL;

    lista = insereOrdenado(lista, 2, 3, ERRO_DUPLICADO_BRANCO_LINHA);
    lista = insereOrdenado(lista, 1, 5, ERRO_DUPLICADO_BRANCO_COLUNA);
    lista = insereOrdenado(lista, 2, 2, ERRO_DUPLICADO_BRANCO_LINHA_COLUNA);
    lista = insereOrdenado(lista, 3, 1, ERRO_VIZINHO_RISCADO);

    int linhas[] = {1, 2, 2, 3};
    int colunas[] = {5, 2, 3, 1};
    TipoErro erros[] = {ERRO_DUPLICADO_BRANCO_COLUNA,ERRO_DUPLICADO_BRANCO_LINHA_COLUNA,ERRO_DUPLICADO_BRANCO_LINHA,ERRO_VIZINHO_RISCADO};

    verificaOrdem(lista, linhas, colunas, erros, 4);

    liberaLista (lista);
}

void testa_verificarRiscadas () {
    Tabuleiro t = criaTabuleiroDeTeste(2,2,'a');

    t->tabuleiro[0][0] = '#';
    t->tabuleiro[0][1] = '#';

    CU_ASSERT_EQUAL (verificarRiscadas (t,0,0),ERRO_VIZINHO_RISCADO);
    CU_ASSERT_EQUAL (verificarRiscadas (t,0,1),ERRO_VIZINHO_RISCADO);

    liberaTabuleiro (t);
}

void testa_verificarVizinhosBrancos () {
    Tabuleiro t = criaTabuleiroDeTeste (2,2,'a');

    t->tabuleiro[0][1] = '#';

    CU_ASSERT_EQUAL (verificarVizinhosBrancos (t,0,1),ERRO_VIZINHO_NAO_BRANCO);

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[1][1] = 'A';

    CU_ASSERT_EQUAL (verificarVizinhosBrancos (t,0,1),ERRO_NENHUM);

    liberaTabuleiro (t);
}

void testa_verificarRepeticoes () {
    Tabuleiro t = criaTabuleiroDeTeste(3,3,'a');

    t->tabuleiro[0][0] = 'A';
    t->tabuleiro[0][1] = 'A';

    CU_ASSERT_EQUAL (verificarRepeticoes (t,0,0,'A'),ERRO_DUPLICADO_BRANCO_LINHA);
    CU_ASSERT_EQUAL (verificarRepeticoes (t,0,1,'A'),ERRO_DUPLICADO_BRANCO_LINHA);

    t->tabuleiro[1][0] = 'A';
    t->tabuleiro[0][1] = 'a';

    CU_ASSERT_EQUAL (verificarRepeticoes (t,0,0,'A'),ERRO_DUPLICADO_BRANCO_COLUNA);
    CU_ASSERT_EQUAL (verificarRepeticoes (t,1,0,'A'),ERRO_DUPLICADO_BRANCO_COLUNA);

    t->tabuleiro[0][1] = 'A';

    CU_ASSERT_EQUAL (verificarRepeticoes (t,0,0,'A'),ERRO_DUPLICADO_BRANCO_LINHA_COLUNA);
    CU_ASSERT_EQUAL (verificarRepeticoes (t,1,0,'A'),ERRO_DUPLICADO_BRANCO_COLUNA);
    CU_ASSERT_EQUAL (verificarRepeticoes (t,0,1,'A'),ERRO_DUPLICADO_BRANCO_LINHA);

    CU_ASSERT_EQUAL (verificarRepeticoes (t,2,2,'A'),ERRO_NENHUM);

    liberaTabuleiro (t);
}

void testa_verificarFaltaRiscar () {
    Tabuleiro t = criaTabuleiroDeTeste(2,2,'a');

    t->tabuleiro[1][1] = 'A';  
    CU_ASSERT_EQUAL (verificarFaltaRiscar(t,1,1,'A'),ERRO_FALTA_RISCAR_LINHA_COLUNA);

    t->tabuleiro[1][0] = '#';
    CU_ASSERT_EQUAL (verificarFaltaRiscar(t,1,1,'A'),ERRO_FALTA_RISCAR_COLUNA);

    t->tabuleiro[1][0] = 'a';
    t->tabuleiro[0][1] = '#';
    CU_ASSERT_EQUAL (verificarFaltaRiscar(t,1,1,'A'),ERRO_FALTA_RISCAR_LINHA);

    liberaTabuleiro(t);
}

void testa_liberaLista() {
    ListaConflitos lista = NULL;

    lista = insereOrdenado(lista, 2, 3, ERRO_DUPLICADO_BRANCO_LINHA);
    lista = insereOrdenado(lista, 1, 5, ERRO_DUPLICADO_BRANCO_COLUNA);
    lista = insereOrdenado(lista, 2, 2, ERRO_DUPLICADO_BRANCO_LINHA_COLUNA);
    lista = insereOrdenado(lista, 3, 1, ERRO_VIZINHO_RISCADO);

    liberaLista(lista);
    CU_ASSERT(1);
}

void testa_undoStack() {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
    StackJogadas s = malloc (sizeof (struct stack));
    inicializaStack (s);

    comandoB (s,t,"a0",0);
    comandoB (s,t,"a1",0);

    undoStack (t,s);

    CU_ASSERT_EQUAL(t->tabuleiro[0][1], 'a');
    CU_ASSERT_EQUAL(s->sp, 1);

    undoStack (t,s);

    CU_ASSERT_EQUAL(t->tabuleiro[0][0], 'a');
    CU_ASSERT_EQUAL(t->tabuleiro[0][1], 'a');
    CU_ASSERT_EQUAL(s->sp, 0);

    liberaTabuleiro (t);
    liberaStack (s);
}


void testa_comandoD() {
    Tabuleiro t = criaTabuleiroDeTeste(2, 2, 'a');
    StackJogadas s = malloc (sizeof (struct stack));
    inicializaStack (s);
  
    CU_ASSERT_EQUAL (comandoD (t,s),1); // tenta dar undo quando não tem nenhuma jogada feita
    
    comandoB (s,t,"a0",0);
    CU_ASSERT_EQUAL (t->tabuleiro[0][0],'A');
    CU_ASSERT_EQUAL(comandoD(t,s), 0); // dar undo após pintar de branco
    CU_ASSERT_EQUAL (t->tabuleiro[0][0],'a'); // verifica se a letra atualiza após dar o undo

    comandoR (s,t,"a0",0);
    CU_ASSERT_EQUAL (t->tabuleiro[0][0],'#');
    CU_ASSERT_EQUAL (comandoD (t,s),0); // dar undo após riscar
    CU_ASSERT_EQUAL (t->tabuleiro[0][0],'a');

    comandoB (s,t,"a0",0);
    comandoR (s,t,"b1",0);

    // dar undo consecutivos
    CU_ASSERT_EQUAL (comandoD (t,s),0); 
    CU_ASSERT_EQUAL (comandoD (t,s),0);

    CU_ASSERT_EQUAL (t->tabuleiro[0][0],'a');
    CU_ASSERT_EQUAL (t->tabuleiro[0][1],'a');
    CU_ASSERT_EQUAL (t->tabuleiro[1][0],'a');
    CU_ASSERT_EQUAL (t->tabuleiro[1][1],'a');
    
    liberaTabuleiro (t);
    liberaStack (s);
}

