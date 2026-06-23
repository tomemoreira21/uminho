#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "problemaE.h"

void imprimeResultado (Tabuleiro t,Casos casos) {
    int resultado;

    for (int i = 0; i < casos->numCasos; i++) {
        printf ("Caso %d\n",i+1);
        resultado = verificaTrajeto(t, casos->caso[i]);
        (resultado == 1) ? printf ("SIM\n") : printf ("NAO\n");
    }
}

Queue inicializaQueue () {
    Queue q = malloc (sizeof (struct queue));
    q->size = 64;
    q->frente = 0;
    q->atras = 0;
    q->valores = malloc (q->size *sizeof (struct posicao));

    return q;
}
 
int ***inicializaVisitados(int linhas, int colunas, int lenCaminho) {
    int ***visitados = malloc(linhas * sizeof(int **));

    for (int i = 0; i < linhas; i++) {
        visitados[i] = malloc(colunas * sizeof(int *));
        for (int j = 0; j < colunas; j++) {
            visitados[i][j] = malloc(lenCaminho * sizeof(int));
            for (int k = 0; k < lenCaminho; k++) {
                visitados[i][j][k] = 0; 
            }
        }
    }

    return visitados;
}

char *leCaminho() {
    char *linha = NULL;
    size_t tamanho = 0;

    if (getline(&linha, &tamanho, stdin) == -1) {
        free(linha);
        return NULL;
    }

    linha[strcspn(linha, "\n")] = '\0';

    return linha;
}

int queueVazia (Queue q) {
    return q->frente == q->atras;
}

void pushQueue (Queue q,Posicao p) {
    if ((q->atras + 1) % q->size == q->frente) {
        q->size *= 2;  
        q->valores = realloc(q->valores, q->size * sizeof(struct posicao));
    }
    
    q->valores[q->atras] = p;  
    q->atras = (q->atras + 1) % q->size;  
}

Posicao popQueue (Queue q) {
    if (queueVazia(q)) return NULL;
    
    Posicao p = q->valores[q->frente];
    q->frente = (q->frente + 1) % q->size;
    return p;
}

void repoeVisitados(int ***v, int linhas, int colunas, int lenCaminho) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            for (int k = 0; k < lenCaminho; k++) {
                v[i][j][k] = 0;  
            }
        }
    }
}

int dentroTabuleiro (Tabuleiro t,int l,int c) {
    return ((l >= 0 && l < t->linhas)) && (c >= 0 && c < t->colunas);
}

int geraMovimentosTriplo (Triplo triplo,int movimentos[8][2]) {
    int k = 0;

    if (triplo.L == 0 && triplo.C == 0) return 0; 

    // (L,C)
    int mov1[4][2] = {
        { triplo.L,  triplo.C},
        {-triplo.L,  triplo.C},
        { triplo.L, -triplo.C},
        {-triplo.L, -triplo.C}
    };

    //(C, L)
    int mov2[4][2] = {
        { triplo.C,  triplo.L},
        {-triplo.C,  triplo.L},
        { triplo.C, -triplo.L},
        {-triplo.C, -triplo.L}
    };

    for (int i = 0; i < 4; i++) {
        movimentos[k][0] = mov1[i][0];
        movimentos[k][1] = mov1[i][1];
        k++;
    }

    if (triplo.L != triplo.C) {
        for (int i = 0; i < 4; i++) {
            movimentos[k][0] = mov2[i][0];
            movimentos[k][1] = mov2[i][1];
            k++;
        }
    }

    return k;
}

int adicionaValido(Queue q, int nx, int ny, int proxIndice,Posicao p) {
    Posicao nova = malloc(sizeof(struct posicao));
    if (nova == NULL) return 0;
    nova->x = nx;
    nova->y = ny;
    nova->indiceLetra = proxIndice;
    memcpy(nova->visitadosLocais, p->visitadosLocais, sizeof(p->visitadosLocais));
    nova->visitadosLocais[nx][ny] = 1;
    pushQueue(q, nova);
    return 1;
}

int verificaPosicao (Tabuleiro t, Caso c, Queue q, int ***visitados, Posicao p) {
    char letraAtual = c->caminho[p->indiceLetra];    

    if (t->tabuleiro[p->x][p->y] != letraAtual) return 0;
    
    for (int j = 0; j < c->numTriplos;j++) {
        Triplo triplo = c->triplos[j];
        int movs[8][2];
        int numMovs = geraMovimentosTriplo (triplo,movs);

        for (int i = 0; i < numMovs;i++) {
            int nx = p->x + movs[i][0];
            int ny = p->y + movs[i][1];

            if (triplo.R == 1) {
                while (dentroTabuleiro(t, nx, ny) && p->indiceLetra + 1 < (int)strlen(c->caminho) ) {
                    if (!visitados[nx][ny][p->indiceLetra + 1] && t->tabuleiro[nx][ny] == c->caminho[p->indiceLetra + 1] && !p->visitadosLocais[nx][ny]) {
                        adicionaValido(q,nx, ny, p->indiceLetra + 1,p);
                        visitados[nx][ny][p->indiceLetra + 1] = 1;
                    }
                    nx += movs[i][0];
                    ny += movs[i][1];
                }
            } else {
                if (dentroTabuleiro (t,nx,ny) && p->indiceLetra + 1 < (int)strlen(c->caminho) && !visitados[nx][ny][p->indiceLetra + 1] && t->tabuleiro[nx][ny] == c->caminho[p->indiceLetra + 1] && !p->visitadosLocais[nx][ny]) {
                    adicionaValido (q, nx, ny, p->indiceLetra + 1,p);
                    visitados[nx][ny][p->indiceLetra + 1] = 1;
                }
            }
        }
    }
    return 0;
}

int verificaTrajeto(Tabuleiro t, Caso c) {
    int ***visitados = inicializaVisitados (t->linhas,t->colunas,strlen (c->caminho));

    if (c->xInicial == c->xFinal && c->yInicial == c->yFinal && (strlen(c->caminho) == 1)) {
        liberaVisitados (visitados,t->linhas,t->colunas);
        return 1;
    }
    
    repoeVisitados(visitados, t->linhas, t->colunas,strlen (c->caminho));

    Queue q = inicializaQueue();

    Posicao posInicial = malloc(sizeof(struct posicao));
    posInicial->x = c->xInicial;
    posInicial->y = c->yInicial;
    posInicial->indiceLetra = 0;
    memset(posInicial->visitadosLocais, 0, sizeof(posInicial->visitadosLocais));
    posInicial->visitadosLocais[c->xInicial][c->yInicial] = 1;

    pushQueue(q, posInicial);
    visitados[c->xInicial][c->yInicial][0] = 1;

    while (!queueVazia(q)) {
        Posicao pos = popQueue(q);
        if (pos->indiceLetra == (int)strlen(c->caminho) - 1 && pos->x == c->xFinal && pos->y == c->yFinal) {
            free(pos);
            liberaQueue(q);
            liberaVisitados(visitados, t->linhas, t->colunas);
            return 1;
        }

        verificaPosicao(t, c, q, visitados, pos);
            
        free (pos);
    }
    
    liberaQueue(q);
    liberaVisitados (visitados,t->linhas,t->colunas);
    return 0;
}

int leTabuleiro(Tabuleiro t) {
    if ((scanf("%d %d", &t->linhas, &t->colunas) != 2) ||
        (t->linhas > 40) || (t->colunas > 40)) return 0;

    t->tabuleiro = malloc(t->linhas * sizeof(char *));
    if (t->tabuleiro == NULL) return 0;

    char temp [t->colunas + 1];
    for (int j = 0; j < t->linhas; j++) {
        if (scanf ("%s",temp) != 1) {
            liberaTabuleiro (t);
            return 0;
        }


        t->tabuleiro[j] = malloc(t->colunas * sizeof(char));
        if (t->tabuleiro[j] == NULL) {
            liberaTabuleiro (t);
            return 0;
        }

        for (int i = 0; i < t->colunas; i++) {
            if (!isupper(temp[i])) {  
                liberaTabuleiro(t);
                return 0;
            }
            t->tabuleiro[j][i] = temp[i]; 
        }
    }

    return 1;
}

int processaCaso (Caso c) {
    if ((scanf ("%d",&c->numTriplos) != 1) || c->numTriplos > 10) return 0;

    c->triplos = malloc(c->numTriplos * sizeof(Triplo));
    if (c->triplos == NULL) return 0;

    for (int i = 0; i < c->numTriplos; i++) {
        if ((scanf ("%d %d %d",&c->triplos[i].L,&c->triplos[i].C,&c->triplos[i].R) != 3) ||
            (c->triplos[i].L < 0) || (c->triplos[i].C < 0) || (c->triplos[i].R != 0 && c->triplos[i].R != 1)) return 0;
    }

    if (scanf ("%d %d",&c->xInicial,&c->yInicial) != 2) return 0;
    if (scanf ("%d %d",&c->xFinal,&c->yFinal) != 2) return 0;

    c->xInicial -= 1;
    c->yInicial -= 1;
    c->xFinal -= 1;
    c->yFinal -= 1;

    getchar();  
    c->caminho = leCaminho();
    if (c->caminho == NULL) return 0;

    return 1;
}

int processaCasos (Casos c) {
    for (int i = 0; i < c->numCasos;i++) {
        if (!processaCaso (c->caso[i])) return 0;
    }

    return 1;
}

Casos inicializaCasos(int N) {
    Casos c = malloc(sizeof(struct casos));
    c->numCasos = N;
    c->size = N;
    c->caso = malloc(N * sizeof(Caso));

    for (int i = 0; i < N; i++) {
        c->caso[i] = malloc(sizeof(struct caso)); 
    }

    return c;
}

void liberaQueue (Queue q) {
    free (q->valores);
    free (q);
}

void liberaValoresQueue (Queue q) {
    while (!queueVazia(q)) {
        Posicao p = popQueue(q);
        if (p != NULL) free(p);
    }
}

void liberaCasos (Casos c) {
    
    for (int i = 0; i < c->numCasos; i++) {
        if (c->caso[i] != NULL) {
            free(c->caso[i]->triplos);  
            free(c->caso[i]->caminho);  
            free(c->caso[i]);          
        }
    }

    free(c->caso);
    free(c);
}

void liberaTabuleiro(Tabuleiro t) {
    for (int i = 0; i < t->linhas; i++) {
        free(t->tabuleiro[i]);
    }
    free(t->tabuleiro);
    free(t);
}

void liberaVisitados(int ***visitados, int linhas,int colunas) {
    for (int i = 0; i < linhas; i++) {
        if (visitados[i] != NULL) {
            for (int j = 0; j < colunas; j++) { 
                free(visitados[i][j]); 
            }
            free(visitados[i]); 
        }
    }

    free(visitados);
}
