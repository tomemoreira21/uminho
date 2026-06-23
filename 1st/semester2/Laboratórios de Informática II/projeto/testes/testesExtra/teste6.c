#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/func.h"
#include "../testesTarefa1/teste1.h"
#include "teste6.h"

void testa_gravaStack () {
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    char nomeDoFicheiroVazio [] = "testes/testesExtra/stacks/stackVazia.txt";
    char nomeDoFicheiroInexistente [] = ".";

    CU_ASSERT_EQUAL (gravaStack (s,nomeDoFicheiroVazio,"tabuleiro1.txt"),0); 
    CU_ASSERT_EQUAL (gravaStack (s,nomeDoFicheiroInexistente,"tabuleiro1.txt"),1); 

    FILE *file = fopen(nomeDoFicheiroVazio, "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    int sp, grupo;
    CU_ASSERT_EQUAL(fscanf(file, "%d %d", &sp, &grupo), 2);
    CU_ASSERT_EQUAL(sp, s->sp);
    CU_ASSERT_EQUAL(grupo, s->grupoAtual);

    clearFicheiro (nomeDoFicheiroVazio);
    liberaStack (s);
}

void testa_restauraStack1 () {
    StackJogadas s = malloc(sizeof(struct stack));
    char nomeTabuleiro[1024];

    char nomeDoFicheiroInvalido1[] = "testes/testesExtra/stacks/stackInvalida1.txt";
    char nomeDoFicheiroInvalido2[] = "testes/testesExtra/stacks/stackInvalida2.txt";
    char nomeDoFicheiroInvalido3[] = "testes/testesExtra/stacks/stackInvalida3.txt";
    char nomeDoFicheiroInvalido4[] = "testes/testesExtra/stacks/stackInvalida4.txt";
    char nomeDoFicheiroInvalido5[] = "testes/testesExtra/stacks/stackInvalida5.txt";
    char nomeDoFicheiroVazio [] = "testes/testesExtra/stacks/stackVazia.txt";
    char nomeDoFicheiroInexistente[] = ".";

    s = malloc (sizeof (struct stack));
    inicializaStack(s);
    CU_ASSERT_EQUAL(restauraStack(s, nomeDoFicheiroVazio, nomeTabuleiro), 1);
    liberaStack(s);

    s = malloc (sizeof (struct stack));
    inicializaStack(s);
    CU_ASSERT_EQUAL(restauraStack(s, nomeDoFicheiroInvalido1, nomeTabuleiro), 1);
    liberaStack(s);

    s = malloc(sizeof(struct stack));
    inicializaStack(s);
    CU_ASSERT_EQUAL(restauraStack(s, nomeDoFicheiroInvalido2, nomeTabuleiro), 1);
    liberaStack(s);

    s = malloc(sizeof(struct stack));
    inicializaStack(s);
    CU_ASSERT_EQUAL(restauraStack(s, nomeDoFicheiroInvalido3, nomeTabuleiro), 1);
    liberaStack(s);

    s = malloc(sizeof(struct stack));
    inicializaStack(s);
    CU_ASSERT_EQUAL(restauraStack(s, nomeDoFicheiroInvalido4, nomeTabuleiro), 1);
    liberaStack(s);

    s = malloc(sizeof(struct stack));
    inicializaStack(s);
    CU_ASSERT_EQUAL(restauraStack(s, nomeDoFicheiroInvalido5, nomeTabuleiro), 1);
    liberaStack(s);

    s = malloc(sizeof(struct stack));
    inicializaStack(s);
    CU_ASSERT_EQUAL(restauraStack(s, nomeDoFicheiroInexistente, nomeTabuleiro), 1);
    liberaStack(s);
}

void testa_restauraStack2 () {
    StackJogadas s = malloc(sizeof(struct stack));
    inicializaStack(s);

    char nomeDoFicheiroValido[] = "testes/testesExtra/stacks/stackValida.txt";
    char nomeTabuleiro[1024];

    CU_ASSERT_EQUAL(restauraStack(s, nomeDoFicheiroValido, nomeTabuleiro), 0);

   
    CU_ASSERT_EQUAL(s->sp, 2); 
    CU_ASSERT_STRING_EQUAL(nomeTabuleiro, "tabuleiro1.txt");

    
    CU_ASSERT_EQUAL(s->jogadas[0]->marcador, 0);
    CU_ASSERT_EQUAL(s->jogadas[0]->l, 1);
    CU_ASSERT_EQUAL(s->jogadas[0]->c, 2);
    CU_ASSERT_EQUAL(s->jogadas[0]->letraAnterior, 'b');

    CU_ASSERT_EQUAL(s->jogadas[1]->marcador, 0);
    CU_ASSERT_EQUAL(s->jogadas[1]->l, 0);
    CU_ASSERT_EQUAL(s->jogadas[1]->c, 0);
    CU_ASSERT_EQUAL(s->jogadas[1]->letraAnterior, 'a');


    liberaStack(s);
}

