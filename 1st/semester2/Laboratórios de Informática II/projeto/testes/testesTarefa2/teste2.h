#ifndef TESTE2_H
#define TESTE2_H
#include "../../lib/func.h"

void verificaOrdem(ListaConflitos lista, int linhas[], int colunas[], TipoErro erros[], int N);
int comparaListas(ListaConflitos lista1, ListaConflitos lista2);
void testa_verificaConflitos1();
void testa_verificaConflitos2();
void testa_verificaConflitos3();
void testa_verificaConflitos4();
void testa_verificaSemConflitos();
void testa_insereOrdenado();
void testa_verificarRiscadas();
void testa_verificarVizinhosBrancos();
void testa_verificarRepeticoes();
void testa_verificarFaltaRiscar();
void testa_liberaLista();
void testa_undoStack();
void testa_comandoD();


#endif