#include <stdlib.h>
#include <stdio.h>

// 1
void swap (int v[],int x,int y) {
    int temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

int partition (int v[],int N,int x) {
    int a = 0, b = 0;

    for (int i = 0; i < N; i++) {
        if (v[b] <= x) {
            swap (v,a,b);
            a++;b++;
        } else {
            b++;
        } 
    }
    
    return a;
}

void ordenaArray (int v[],int N) {
    if (N > 1) {
        int p = partition (v,N-1,v[N-1]);
        swap (v,p,N-1);
        ordenaArray (v,p);
        ordenaArray (v + p + 1, N - p - 1);
    }   

}   

int sumhtpo (int n) {
    int r = 0, c = 0,v[1024];
    
    while (n != 1) {
        r += n;
        v[c++] = r;
        if (n % 2 == 0) n = n / 2; else n = 1 + (3*n);
    }

    ordenaArray (v,c);
    return (c < 100) ? -1 : v[99];
}

// 2
int moda (int v[],int N,int *m) {
    if (N == 0) return 0;

    int freq = 1,freqMax = 0,multimodal = 0,maisFreq = v[0], i;

    ordenaArray (v,N);

    for (i = 1; i < N; i++) {
        if (v[i-1] == v[i]) {
            freq++;
        } else {
            if (freq > freqMax) {
                freqMax = freq;
                maisFreq = v[i-1];
                multimodal = 0;
            } else if (freq == freqMax) {
                multimodal = 1;
            }
            freq = 1;
        }
    }

    if (freq > freqMax) {
        freqMax = freq;
        maisFreq = v[i-1];
        multimodal = 0;
    } else if (freq == freqMax) {
        multimodal = 1;
    }

    *m = maisFreq;

    return (freqMax = 0 || multimodal == 1) ? 0 : freqMax;
}

// 3
typedef struct lligada {
    int valor;
    struct lligada *prox;
} *LInt ;

int procura (LInt *l,int x) {
    LInt *p = l;

    while (*p != NULL) {
        if ((*p)->valor == x) { 
            LInt nodo = *p;
            *p = nodo->prox;

            nodo->prox = *l;
            *l = nodo;

            return 1;
        }
        p = & ((*p)->prox);
    }

    return 0;
} 


// 4
typedef struct nodo {
    int valor;
    struct nodo *pai, *esq, *dir;
} *ABin;

int freeAB(ABin a) {
    if (a == NULL) return 0;

    ABin esq = a->esq,dir = a->dir;
    free (a);

    return (1 + freeAB (esq) + freeAB (dir));
}

// 5
void caminho(ABin a) {
    if (a == NULL || a->pai == NULL) return;
    
    int pai = a->pai->valor;
    if (a->valor < pai) {
        printf ("esq\n");
    } else {
        printf ("dir\n");
    }

    caminho (a->pai);

}

// 6
int maxCresc (int v[],int N) {
    int c = 0,freq = 1,freqMax = 1;

    for (int j = 0; j < N - 1; j++) {
        for (int i = j + 1; i < N; i++) {
            int valorAnt = v[i-1];
            int valorAtual = v[i];

            if (valorAtual > valorAnt) {
                freq++;
            } else {
                if (freq > freqMax) {
                    freqMax = freq;
                }

                freq = 1;
                break;
            }
        }

        if (freq > freqMax) {
            freqMax = freq;
            freq = 1;
        }
    }

    return freqMax;
}


// Funções auxiliares
void imprimeLista (LInt l) {

    putchar ('[');
    while (l != NULL) {
        printf ("%d%c",l->valor,(l->prox == NULL) ? ']' : ',');
        l = l->prox;
    }
    putchar ('\n');

}

LInt newLInt (LInt l,int x) {
    LInt novo = malloc (sizeof (struct lligada));
    novo->valor = x;
    novo->prox = l;

    return novo;
}


int main () {
    // 3
    LInt lista = NULL;

    lista = newLInt (lista, 10);
    lista = newLInt (lista, 20);
    lista = newLInt (lista, 30);
    lista = newLInt (lista, 40);

    // 40 -> 30 -> 20 -> 10 -> NULL
    printf ("Procura: %d\n",procura (&lista,10));
    imprimeLista (lista);
    
    // 6
    int v1[5] = {1,2,10,-1,2},v2[3] = {-1,2,3},v3[7] = {-1,1,2,3,10,-5,2};
    printf ("Maxcresc: %d\n",maxCresc (v1,5));
    printf ("Maxcresc: %d\n",maxCresc (v2,3));
    printf ("Maxcresc: %d\n",maxCresc (v3,7));

}
