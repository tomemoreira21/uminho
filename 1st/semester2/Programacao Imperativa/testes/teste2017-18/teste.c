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

// PARTE A
// 1
int retiraNeg (int v[],int N) {
    int j = 0;

    for (int i = 0; i < N; i++) {
        if (v[i] >= 0) v[j++] = v[i];
    }

    return j;
}

// 2
int difConsecutivos(char s[]) {
    int max = 0, inicio = 0;
    int pos[256] = {-1};

    for (int i = 0; s[i] != '\0'; i++) {
        if (pos[s[i]] >= inicio) {
            inicio = pos[s[i]] + 1;
        }
        pos[s[i]] = i;

        int len = i - inicio + 1;
        if (len > max) max = len;
    }

    return max;
}

// 3
int maximo (LInt l) {
    int maior = l->valor;
    l = l->prox;

    while (l != NULL) {
        if (l->valor > maior) maior = l->valor;
        l = l->prox;
    }

    return maior;
}

// 4
int removeAll (LInt *l,int x) {
    int c = 0;

    while (*l != NULL) {
        if ((*l)->valor == x) {
            LInt temp = *l;
            *l = (*l)->prox;
            free (temp);    
            c++;
        } else 
            l = & ((*l)->prox);
    }

    return c;
}

// 5
LInt arrayToList (int v[],int N) {
    LInt r = NULL, *ptr = &r;

    for (int i = 0; i < N; i++) {
        LInt novo = malloc (sizeof (struct slist));
        novo->valor = v[i];
        novo->prox = NULL;
        *ptr = novo;

        ptr = & ((*ptr)->prox);
    }

    return r;
}

// PARTE B
// 1
int minheapOK (ABin a) {
    if (a == NULL) return 1;
    if (a->esq != NULL && a->esq->valor < a->valor) return 0;
    if (a->dir != NULL && a->dir->valor < a->valor) return 0;

    return (minheapOK(a->esq) && minheapOK(a->dir));
}

// 2
int maxHeap (ABin a) {
    if (a->esq == NULL && a->dir == NULL) return a->valor;

    if (a->esq != NULL && a->dir != NULL) {
        int vE = a->esq->valor;
        int vD = a->dir->valor;

        if (vE > vD) {
            return maxHeap (a->esq);
        } else 
            return maxHeap (a->dir);
    } else {
        if (a->esq == NULL) return maxHeap (a->dir);
        else return maxHeap (a->esq);
    }
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
    LInt novo = malloc (sizeof (struct slist));
    novo->valor = x;
    novo->prox = l;

    return novo;
}

ABin novoNodo(int valor) {
    ABin novo = malloc(sizeof(struct nodo));
    novo->valor = valor;
    novo->esq = novo->dir = NULL;
    return novo;
}

LInt criaLista1() {
    LInt l = NULL;
    l = newLInt(l, 1);
    l = newLInt(l, 2);
    l = newLInt(l, 3);
    l = newLInt(l, 10);
    return l; // Resultado: 10 -> 3 -> 2 -> 1 -> NULL
}

LInt criaLista2() {
    LInt l = NULL;
    l = newLInt(l, 12);
    l = newLInt(l, 2);
    l = newLInt(l, 3);
    l = newLInt(l, 5);
    return l; // Resultado: 5 -> 3 -> 2 -> 12 -> NULL
}

LInt criaLista3() {
    LInt l = NULL;
    l = newLInt(l, 12);
    l = newLInt(l, 2);
    l = newLInt(l, 3);
    l = newLInt(l, 5);
    l = newLInt(l, 12);
    return l; // Resultado: 12 -> 5 -> 3 -> 2 -> 12 -> NULL
}

ABin criaArvore () {
    ABin raiz = novoNodo(20);
    raiz->esq = novoNodo(35);
    raiz->dir = novoNodo(22);
    raiz->dir->dir = novoNodo(25);
    raiz->dir->esq = novoNodo(23);
    raiz->esq->dir = novoNodo(43);
    raiz->esq->esq = novoNodo(80);

    return raiz;
}

int main () {
    // PARTE A
    // 1
    int v[5] = {7,2,-9,-10,3};
    int j = retiraNeg (v,5);
    printf ("Elementos não retirados: %d\n",j);
    for (int i = 0; i < j; i++) 
        printf ("%d ",v[i]);
    putchar ('\n');

    // 2
    printf ("DifConsecutivos: %d\n",difConsecutivos ("aabcccaac"));
    printf ("DifConsecutivos: %d\n",difConsecutivos ("abcaadeh"));

    // 3
    LInt lista1 = criaLista1 (), lista2 = criaLista2 ();
    printf ("Maior valor: %d\n",maximo (lista1));
    printf ("Maior valor: %d\n",maximo (lista2));

    // 4
    LInt lista3 = criaLista3 ();
    int r = removeAll (&lista3,12);
    printf ("Removidos: %d\n",r);
    imprimeLista (lista3);

    // 5
    int v1[5] = {1,2,3,4,5};
    LInt res = arrayToList (v1,5);
    imprimeLista (res);

    // PARTE B
    // 1
    ABin arv = criaArvore ();
    printf ("Verdade: %d\n",minheapOK (arv));

    // 2
    printf ("Maximo: %d\n",maxHeap (arv));

    return 0;
}