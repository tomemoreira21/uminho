#include <stdio.h>
#include <stdlib.h>

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

void printABinInOrder(ABin a) {
    if (a == NULL) return;
    printABinInOrder(a->esq);        
    printf("%d ", a->valor);         
    printABinInOrder(a->dir);        
}

// 1
// a)
ABin removeMenor (ABin *a) {
    if (*a == NULL) return NULL;

    while ((*a)->esq != NULL) a = & ((*a)->esq);
    
    ABin res = *a;
    *a = (*a)->dir;

    return res;
}

// b)
void removeRaiz (ABin *a) {
    ABin raiz = *a;
    if ((*a)->esq == NULL) {
        *a = (*a)->dir;
        free (raiz);
    } else if ((*a)->dir == NULL) {
        *a = (*a)->esq;
        free (raiz);
    } else {
        ABin menorDir = removeMenor (& ((*a)->dir));
        (*a)->valor = menorDir->valor;
        free (menorDir);
    }
}

// c)
int removeElem (ABin *a,int x) {
    int res = -1;
    
    while (*a != NULL) {
        if ((*a)->valor == x) {
            removeRaiz (a);
            res = 0;
        } else if ((*a)->valor < x) {
            a = & ((*a)-> dir);
        } else 
            a = & ((*a)->esq);
    }

    return res;
}

// 2
void rodaEsquerda (ABin *a){
    ABin b = (*a)->dir;
    (*a)->dir = b->esq;
    b->esq = (*a);
    *a = b;
}

void rodaDireita (ABin *a){
    ABin b = (*a)->esq;
    (*a)->esq = b->dir;
    b->dir = *a;
    *a = b;
}

// d
void promoveMenor (ABin *a) {
    if (*a == NULL || (*a)->esq == NULL) return;

    ABin *p = a;

    while ((*p)->esq != NULL) {
        rodaDireita (p);
        p = a;
    }
    rodaDireita (a);
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

    removeElem (&a,3);

    printABinInOrder(a);
    printf("\n");


    return 0;
}