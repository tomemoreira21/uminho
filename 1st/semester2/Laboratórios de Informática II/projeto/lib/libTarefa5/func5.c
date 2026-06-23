#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../func.h"

int jogoResolvido (Tabuleiro t,ListaConflitos lista) {
    return (lista == NULL && contaMin (t) == 0 && existeCaminho (t));
}

Jogada copiaJogada(Jogada j) {
    Jogada nova = malloc(sizeof(struct jogada));
    if (nova == NULL) return NULL; 

    nova->c = j->c;
    nova->l = j->l;
    nova->letraAnterior = j->letraAnterior;

    return nova;
}

int letraRepeteNaLinhaOuColuna(Tabuleiro t, int i, int j) {
    char letra = t->tabuleiro[i][j];

    if (letra == '#') return 0; 

    for (int c = 0; c < t->colunas; c++) {
        if (c != j && t->tabuleiro[i][c] == letra) return 1;
    }

    for (int l = 0; l < t->linhas; l++) {
        if (l != i && t->tabuleiro[l][j] == letra) return 1;
    }

    return 0;
}

void backTrack (Tabuleiro t,StackJogadas s,int topoStackAntes) {
    while (s->sp > topoStackAntes) undoStack(t, s);
}


void desfazStack(StackJogadas s, Tabuleiro t) {
    while (s->sp > 0) {
        undoStack(t, s);
    }
}

int resolveJogo(Tabuleiro t, StackJogadas s) {
    int alteracoes = 1;
    ListaConflitos lista = NULL;

    while (alteracoes) {
        alteracoes = 0;

        for (int l = 0; l < t->linhas; l++) {
            for (int c = 0; c < t->colunas; c++) {
                char letra = t->tabuleiro[l][c];

                if (islower(letra) && letraRepeteNaLinhaOuColuna (t, l, c)) {
                    Jogada jog = devolveJogadaAjuda(t, l, c), copiaJ = copiaJogada (jog); 
                    int topoStackAntes = s->sp, jogadaFoiRiscada = 0;

                    pintarMaisPropagacao (t,s,jog,&alteracoes);
                    
                    if (possuiConflitos (t,&lista)) { 
                        liberaLista (lista),lista = NULL;

                        riscarMaisPropagacao (t,s,copiaJ,&alteracoes,&jogadaFoiRiscada,topoStackAntes);

                    } else if (jogoResolvido(t, lista)) {
                            liberaLista(lista),lista = NULL,free(copiaJ);
                            return 1;
                    }

                    if (!jogadaFoiRiscada) free(copiaJ); 

                } else if (islower (letra)) {
                    Jogada jog = devolveJogadaAjuda(t, l, c);
                    addMaiuscula (s,t,jog,s->grupoAtual),alteracoes = 1;
                 }

                }
            }
     }
    
     lista = verificaConflitos(t, lista);
     int resolvido = jogoResolvido(t, lista);
     liberaLista(lista);
     return resolvido;
}
    
int possuiConflitos (Tabuleiro t, ListaConflitos *lista) {
    *lista = verificaConflitos(t, *lista);
    return (*lista != NULL || !existeCaminho(t));
}

void pintarMaisPropagacao (Tabuleiro t,StackJogadas s,Jogada jog,int *alteracoes) {
    addMaiuscula (s,t,jog,s->grupoAtual);
    comandoA(s,t,1);  
    *alteracoes = 1;
}

void riscarMaisPropagacao (Tabuleiro t,StackJogadas s,Jogada jog,int *alteracoes,int *jogadaFoiRiscada,int topoStackAntes) {
    backTrack (t,s,topoStackAntes);
    addRiscar (s,t,jog,s->grupoAtual);
    comandoA(s,t,1);  
    *jogadaFoiRiscada = 1;
    *alteracoes = 1;
}

void recuperaTabuleiroInicial(Tabuleiro t, StackJogadas s) {
    for (int i = s->sp - 1; i >= 0; i--) {
        Jogada j = s->jogadas[i];
        t->tabuleiro[j->l][j->c] = j->letraAnterior;
    }
}

Tabuleiro copiaTabuleiro (Tabuleiro t) {
    Tabuleiro novo = malloc(sizeof(struct tabuleiro));
    novo->linhas = t->linhas;
    novo->colunas = t->colunas;

    novo->tabuleiro = malloc(novo->linhas * sizeof(char *));
    for (int i = 0; i < novo->linhas; i++) {
        novo->tabuleiro[i] = malloc(novo->colunas * sizeof(char));

        for (int j = 0; j < novo->colunas; j++) {
            novo->tabuleiro[i][j] = t->tabuleiro[i][j];
        }
    }

    return novo;
}

int resolveJogoEstadoInvalido(Tabuleiro t, StackJogadas s) {
    Tabuleiro tTemp = copiaTabuleiro(t);
    recuperaTabuleiroInicial (tTemp, s);
    
    StackJogadas sTemp = malloc (sizeof (struct stack));
    inicializaStack (sTemp);
    sTemp->grupoAtual = s->grupoAtual; 

    int resultado = resolveJogo(tTemp, sTemp);

    if (resultado == 1) {
        int novoMarcador = s->grupoAtual++;
        for (int i = 0; i < sTemp->sp; i++) {
            Jogada jTemp = sTemp->jogadas[i];
            Jogada jNova = devolveJogadaAjuda(t, jTemp->l, jTemp->c);

            jNova->marcador = novoMarcador;
            s->jogadas[s->sp++] = jNova;
            t->tabuleiro[jNova->l][jNova->c] = tTemp->tabuleiro[jNova->l][jNova->c];
        }
    }

    liberaStack(sTemp);
    liberaTabuleiro(tTemp);

    return resultado;
}

int contaMin (Tabuleiro t) {
    int c = 0;

    for (int j = 0; j < t->linhas; j++) {
        for (int i = 0; i < t->colunas; i++) {
            if (islower (t->tabuleiro[j][i])) c ++;
        }
    }

    return c;
}

void verificaEstadoJogo (Jogo jogo) {
    if (contaMin (jogo->tabuleiro) == 0)
        jogo->estadoJogo = 0;
    else
        jogo->estadoJogo = 1;
}

void verificaVitoria(Jogo j, ListaConflitos lista) {
    verificaEstadoJogo(j);

    if (j->estadoJogo == 0) {
        if (lista == NULL && existeCaminho (j->tabuleiro))
            j->venceu = 1;
        else
            j->venceu = 0;
    }
}
