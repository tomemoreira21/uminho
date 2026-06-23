#include <stdio.h>
#include <stdlib.h>
#include "problemaD.h"

//Função auxiliar para reduzir a complexidade da main
int processaCasos(Tabuleiro *tabuleiros, Caso *casos,int j) {
    int T;

    casos[j].posicoes = NULL;

    if ((scanf("%d", &T) != 1) || T > 10) return 0;

    tabuleiros[j].numTriplos = T;
    tabuleiros[j].triplos = malloc(T * sizeof(Triplo));

    if (tabuleiros[j].triplos == NULL) return 0;

    for (int i = 0; i < T; i++) {
        if ((scanf ("%d %d %d",&tabuleiros[j].triplos[i].L,&tabuleiros[j].triplos[i].C,&tabuleiros[j].triplos[i].R) != 3) ||
            (tabuleiros[j].triplos[i].L < 0) || (tabuleiros[j].triplos[i].C < 0) || 
            ((tabuleiros[j].triplos[i].R != 1) && (tabuleiros[j].triplos[i].R != 0))) {
            return 0;
        }
    }

    if ((scanf ("%d %d",&tabuleiros[j].linhas,&tabuleiros[j].colunas) != 2) || 
        (tabuleiros[j].linhas > 40) || (tabuleiros[j].colunas > 40)) return 0;

    if (scanf ("%d %d",&tabuleiros[j].xInicial,&tabuleiros[j].yInicial) != 2) return 0;

    inicializaCaso(&casos[j], j + 1);
    geraCaso(&tabuleiros[j], &casos[j]);
    ordenaCaso(&casos[j]);

    return 1;
}

void imprimeCasos (Caso c[],int N) {
    for (int j = 0; j < N; j++) {
        printf ("Caso %d\n",c[j].caso);

        for (int i = 0; i < c[j].numElementos; i++) {
            printf ("%d %d\n",c[j].posicoes[i].x,c[j].posicoes[i].y);
    }
  }
}

void swap (Posicao p[],int x,int y) {
    Posicao temp;
    
    temp = p[x];
    p[x] = p[y];
    p[y] = temp;
}

int partition (Posicao p[],int N,Posicao *pnova) {
    int a = 0, b = 0;

    for (int i = 0; i < N; i++) {
        if ((p[b].x < pnova->x) || (p[b].x == pnova->x && p[b].y < pnova->y)) {
            swap (p,a,b);
            a++;b++;
        } else b++;
    } 

    return a;
}

void ordenaPosicoes (Posicao p[],int N) {
    int pi;

    if (N > 1) {
        pi = partition (p,N - 1,&p[N-1]);
        swap (p,pi,N-1);
        ordenaPosicoes (p,pi);
        ordenaPosicoes (p + pi + 1,N - pi - 1);
    }
}

void ordenaCaso (Caso *c) {
    ordenaPosicoes (c->posicoes,c->numElementos);
}

void inicializaCaso (Caso *c,int indice) {
    c->caso = indice;
    c->numElementos = 0;
    c->size = 64;
    c->posicoes = malloc(c->size * sizeof(Posicao));
}

int posicaoJaAdicionada (Caso *c,int x,int y) {
    for (int i = 0; i < c->numElementos;i++) {
        if (c->posicoes[i].x == x && c->posicoes[i].y == y) return 1;
    }

    return 0;
}

int dentroTabuleiro (Tabuleiro *t,int x,int y) {
    return ((x >= 1) && (x <= t->linhas) && (y >= 1) && (y <= t->colunas));
}

int adicionaPosicao (Caso *c,int x,int y) {
    Posicao *novo;
    
    if (c->size == c->numElementos) {
        c->size *= 2;
        novo = realloc(c->posicoes, c->size * sizeof(Posicao));
        if (novo == NULL) return 0; 
        
        c->posicoes = novo;
    }

    c->posicoes[c->numElementos].x = x;
    c->posicoes[c->numElementos].y = y;
    c->numElementos ++;

    return 1;
}

int geraPosicoes (Tabuleiro *t,Caso *c, Triplo triplo) {
    if (triplo.L == 0 && triplo.C == 0) return 0;

    int dx1[4] = {triplo.L,-triplo.L,triplo.L,-triplo.L};
    int dy1[4] = {triplo.C,triplo.C,-triplo.C,-triplo.C};

    int dx2[4] = {triplo.C,-triplo.C,triplo.C,-triplo.C};
    int dy2[4] = {triplo.L,triplo.L,-triplo.L,-triplo.L};

    int numMovimentos = (triplo.L == triplo.C) ? 1 : 2; 

    for (int tipo = 0; tipo < numMovimentos; tipo++) {
        int *dx = (tipo == 0) ? dx1 : dx2;
        int *dy = (tipo == 0) ? dy1 : dy2;

        for (int i = 0; i < 4; i++) {
            int x = t->xInicial + dx[i];
            int y = t->yInicial + dy[i];

            if (triplo.R == 1) {
                while (dentroTabuleiro (t,x,y)) {
                    if (!posicaoJaAdicionada (c,x,y)) adicionaPosicao (c,x,y);
                    x += dx[i];
                    y += dy[i];
                }
            } else {
                if (dentroTabuleiro (t,x,y)) {
                    if (!posicaoJaAdicionada (c,x,y)) adicionaPosicao (c,x,y);
                }
            }
        }
    }

    return 1;
}

    
void geraCaso (Tabuleiro *t,Caso *c) {
    for (int i = 0; i < t->numTriplos; i++) {
        geraPosicoes (t,c,t->triplos[i]);
    }
}

void libertaTabuleiros(Tabuleiro *t, int N) {
    for (int i = 0; i < N; i++) {
        if (t[i].triplos != NULL) {
            free(t[i].triplos);
        }
    }
    free(t);
}

void libertaCasos(Caso *c, int N) {
    for (int j = 0; j < N; j++) {
        if (c[j].posicoes != NULL) {
            free(c[j].posicoes);
        }
    }
    free(c);
}
