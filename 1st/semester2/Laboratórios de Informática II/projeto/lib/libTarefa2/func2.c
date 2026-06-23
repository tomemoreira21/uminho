#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../func.h"

ListaConflitos insereOrdenado(ListaConflitos lista, int linha, int coluna, TipoErro erro) {
    ListaConflitos nova = malloc(sizeof(struct lista));
    nova->l = linha;
    nova->c = coluna;
    nova->erro = erro;
    nova->prox = NULL;

    if (lista == NULL || linha < lista->l || (linha == lista->l && coluna < lista->c)) {
        nova->prox = lista;
        return nova;
    }

    ListaConflitos atual = lista;
    while (atual->prox && (atual->prox->l < linha || (atual->prox->l == linha && atual->prox->c < coluna))) {
        atual = atual->prox;
    }

    nova->prox = atual->prox;
    atual->prox = nova;
    return lista;
}

ListaConflitos verificaConflitos (Tabuleiro t,ListaConflitos lista) {

    for (int i = 0; i < t->linhas; i++) {
        for (int j = 0; j < t->colunas; j++) {
            char atual = t->tabuleiro[i][j];

            if (isupper (atual)) {
                TipoErro erroR = verificarFaltaRiscar (t,i,j,atual);
                TipoErro erroB = verificarRepeticoes (t,i,j,atual);
                if (erroR != ERRO_NENHUM && erroB != ERRO_NENHUM) {
                    lista = insereOrdenado (lista,i,j,erroR);
                    lista = insereOrdenado (lista,i,j,erroB);
                }

                else if (erroR != ERRO_NENHUM) {
                    lista = insereOrdenado (lista,i,j,erroR);
                }

                else if (erroB != ERRO_NENHUM) {
                    lista = insereOrdenado (lista,i,j,erroB);
                }
            }

            else if (atual == '#') {
                    TipoErro erroR = verificarRiscadas (t,i,j);
                    TipoErro erroB = verificarVizinhosBrancos (t,i,j);
                    if (erroR != ERRO_NENHUM && erroB != ERRO_NENHUM) {
                        lista = insereOrdenado (lista,i,j,erroR);
                        lista = insereOrdenado (lista,i,j,erroB);
                    }

                    else if (erroR != ERRO_NENHUM) {
                        lista = insereOrdenado (lista,i,j,erroR);
                    }

                    else if (erroB != ERRO_NENHUM) {
                        lista = insereOrdenado (lista,i,j,erroB);
                    }
            }
        }
    }
    return lista;
}

TipoErro verificarRiscadas (Tabuleiro t,int i,int j) {
    TipoErro erro = ERRO_NENHUM;

    if ((i > 0 && t->tabuleiro[i-1][j] == '#') ||    // baixo     
        (i < t->linhas - 1 && t->tabuleiro[i+1][j] == '#') || // cima
        (j > 0 && t->tabuleiro[i][j-1] == '#') ||          // esquerda
        (j < t->colunas - 1 && t->tabuleiro[i][j+1] == '#')) {  // direita
        erro = ERRO_VIZINHO_RISCADO;
    }
    return erro;
}

TipoErro verificarVizinhosBrancos (Tabuleiro t,int i,int j) {
    TipoErro erro = ERRO_NENHUM;

    if ((i > 0 && !isupper (t->tabuleiro[i-1][j]) && t->tabuleiro[i-1][j] != '#') ||    // baixo     
        (i < t->linhas - 1 && !isupper (t->tabuleiro[i+1][j]) && t->tabuleiro[i+1][j] != '#') || // cima
        (j > 0 && !isupper (t->tabuleiro[i][j-1]) && t->tabuleiro[i][j-1] != '#') ||          // esquerda
        (j < t->colunas - 1 && !isupper (t->tabuleiro[i][j+1]) && t->tabuleiro[i][j+1] != '#')) {  // direita
        erro = ERRO_VIZINHO_NAO_BRANCO;
    }

    return erro;
}

TipoErro verificarRepeticoes(Tabuleiro t, int i, int j, char atual) {
    int repetidaLinha = 0;
    int repetidaColuna = 0;
    TipoErro erro = ERRO_NENHUM;

    for (int c = 0; c < t->colunas; c++) {
        if (c != j && t->tabuleiro[i][c] == atual) {
            repetidaLinha = 1; 
        }
    }

    for (int l = 0; l < t->linhas; l++) {
        if (l != i && t->tabuleiro[l][j] == atual) {
            repetidaColuna = 1;  
        }
    }

    if (repetidaLinha && repetidaColuna) erro = ERRO_DUPLICADO_BRANCO_LINHA_COLUNA;
    else if (repetidaLinha) erro = ERRO_DUPLICADO_BRANCO_LINHA;
    else if (repetidaColuna) erro = ERRO_DUPLICADO_BRANCO_COLUNA;
     
    return erro; 
}

TipoErro verificarFaltaRiscar(Tabuleiro t, int i, int j, char atual) {
    int faltaRiscoLinha = 0;
    int faltaRiscoColuna = 0;
    char minuscula = tolower(atual);
    TipoErro erro = ERRO_NENHUM;

    for (int c = 0; c < t->colunas; c++) {
        if (c != j && t->tabuleiro[i][c] == minuscula) {
            faltaRiscoLinha = 1;
        }
    }

    for (int l = 0; l < t->linhas; l++) {
        if (l != i && t->tabuleiro[l][j] == minuscula) {
            faltaRiscoColuna = 1;
        }
    }

    if (faltaRiscoLinha && faltaRiscoColuna) erro = ERRO_FALTA_RISCAR_LINHA_COLUNA;
    else if (faltaRiscoLinha) erro = ERRO_FALTA_RISCAR_LINHA;
    else if (faltaRiscoColuna) erro = ERRO_FALTA_RISCAR_COLUNA;

    return erro;
}

void liberaLista(ListaConflitos lista) {
    ListaConflitos temp;

    while (lista != NULL) {
        temp = lista;
        lista = lista->prox;  
        free(temp);  
    }
}

void undoStack(Tabuleiro t, StackJogadas s) {
    if (s->sp > 0) {
        Jogada j = s->jogadas[s->sp - 1];
        t->tabuleiro[j->l][j->c] = j->letraAnterior;
        free(j);  
        s->sp--;
    }
}

int comandoD (Tabuleiro t,StackJogadas s){
    if (s->sp <= 0) return 1;

    if (s->jogadas[s->sp - 1]->marcador) {
        int m = s->jogadas[s->sp - 1]->marcador; 
        while (s->sp > 0 && s->jogadas[s->sp - 1]->marcador == m) 
            undoStack(t,s);
    }

    else undoStack(t,s);
                
    return 0;
}