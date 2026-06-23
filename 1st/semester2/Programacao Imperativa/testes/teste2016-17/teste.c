#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct slist {
    int valor;
    struct slist *prox;
} *LInt;

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

// 1
int limpaEspacos (char t[]) {
    int j = 1;

    for (int i = 1; t[i] != '\0';i++) {
        if (t[i] != ' ') t[j++] = t[i];
        else if (t[i] == ' ' && t[i-1] != ' ') 
            t[j++] = t[i];
    }   

    t[j] = '\0';
    return j;
}

// 2
void transposta (int N,float m [N][N]) {
    for (int j = 0; j < N-1; j++) {
        for (int i = j + 1; i < N; i++) {
            float temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
}

// 3
LInt cloneL (LInt l) {
    LInt r = NULL, *ptr = &r;

    while (l != NULL) {
        LInt novo = malloc (sizeof (struct slist));
        novo->valor = l->valor;
        novo->prox = NULL;
        *ptr = novo;

        ptr = & ((*ptr)->prox);
        l = l->prox;
    }

    return r;
}

// 4
int nivelV (ABin a, int n, int v[]) {
    if (a ==  NULL) return 0;
    if (n == 1) {
        v[0] = a->valor;
        return 1;
    } else {
        int pE = nivelV (a->esq,n-1,v);
        int pD = nivelV (a->dir,n-1,v + pD);
        return pE+pD;
    }
}


// 5
void removeMaiorA (ABin *a) {
    if (*a == NULL) return;
    
    while ((*a)->dir != NULL) {
        a = & ((*a)->dir);
    }

    ABin maior = *a;
    *a = (*a)->esq;
    free (maior);

}

// Funções auxiliares
void imprimeMatriz (int N,float m [N][N]) {

    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            printf ("%.2f ",m[j][i]);
        }
        putchar ('\n');
    }

    putchar ('\n');
}

void imprimeLista (LInt l) {

    putchar ('[');
    while (l != NULL) {
        printf ("%d%c",l->valor,(l->prox == NULL) ? ']' : ',');
        l = l->prox;
    }
    putchar ('\n');

}

LInt newLInt (LInt l,int x) {
    LInt novo = malloc (sizeof (struct slist));
    novo->valor = x;
    novo->prox = l;

    return novo;
}


int main () {
    // 1
    char t[] = "  omsaomsa osoma    oasosa  ";
    printf ("%d\n",limpaEspacos (t));
    printf ("%s\n",t);

    // 2
    float m [3][3] = {{1,2,3},{4,6,8},{5,7,9}};
    transposta (3,m);
    imprimeMatriz (3,m);

    // 3
    LInt lista = NULL;

    lista = newLInt (lista, 10);
    lista = newLInt (lista, 20);
    lista = newLInt (lista, 30);
    lista = newLInt (lista, 40);

    LInt res = cloneL (lista);
    imprimeLista (res);

    return 0;
}