#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} * ABin;

ABin newABin (int r, ABin e, ABin d) {
    ABin a = malloc (sizeof(struct nodo));
    if (a != NULL) 
        a->valor = r; a->esq = e; a->dir = d;
    
    return a;
}

// 1
// a)
int altura (ABin a) {
    int r;

    if (a == NULL) return 0;
    else {
        int hD = 1 + altura (a->dir);
        int hE = 1 + altura (a->esq);
        r = (hD > hE) ? hD :hE;
    }

    return r;
}

// b)
int nFolhas (ABin a) {
    if (a == NULL) return 0;
    else if (a->dir == NULL && a->esq == NULL) return 1;
    else return (nFolhas (a->esq) + nFolhas (a->dir));
}

// c)
ABin maisEsquerda (ABin a) {
    while (a != NULL && a->esq != NULL) a = a->esq;

    return a;
}

// d)
void imprimeNivel (ABin a,int l) {
    if (l == 0) {
        printf ("%d\n",a->valor);
    } else {
        imprimeNivel (a->esq,l-1);
        imprimeNivel (a->dir,l-1);
    }
}

// e)
// 1 -> se existir o elemento , 0 caso contrário
int procuraE (ABin a,int x) {
    if (a == NULL) return 0;
    else if (a->valor == x) return 1;
    else return (procuraE (a->esq,x) || procuraE (a->dir,x));
}

// 2
// f)
struct nodo *procura (ABin a,int x) {
    while (a != NULL) {
        if (a->valor == x) return a;
        else if (a->valor > x) a = a->esq;
        else a = a->dir;
    }

    return NULL;
}

// g)
// com recursividade
int nivel (ABin a,int x) {
    if (a == NULL) return -1;
    else if (a->valor == x) return 0;
    else if (a->valor > x) { 
        int nivelE = 1 + nivel (a->esq,x);
        if (nivelE > 0) return nivelE;
    } else {
        int nivelD = 1 + nivel (a->dir,x);
        if (nivelD > 0) return nivelD;
    }

    return -1;
}

// sem recursividade
int nivel2 (ABin a,int x) {
    int nivel = 0;

    while (a != NULL) {
        if (a->valor == x) return nivel;
        else if (a->valor < x) a = a->dir;
        else a = a->esq;
        nivel++;
    }

    return -1;
}


// h)
void imprimeAte (ABin a,int x) {
    if (a == NULL) return;
    else if (a->valor < x) {
        imprimeAte (a->esq,x);
        printf ("%d\n",a->valor);
        imprimeAte (a->dir,x);
    } else {
        imprimeAte (a->esq,x);
    }
}

int main () {
    ABin a = newABin(5,
        newABin(3,
            newABin(1, NULL, NULL),
            newABin(4, NULL, NULL)
        ),
        newABin(8,
            NULL,
            newABin(9, NULL, NULL)
        )
    );

    printf ("Altura: %d\n",altura (a));
    printf ("Nº de folhas: %d\n",nFolhas (a));
    imprimeNivel (a,1);
    printf ("Existe o elemento 8: %d\n",procuraE (a,8));
    printf ("Existe o elemento 2: %d\n",procuraE (a,2));

    printf ("Nivel do 8: %d\n",nivel (a,8));
    printf ("Nivel do 2: %d\n",nivel (a,2));

    imprimeAte (a,8);
    return 0;
}


