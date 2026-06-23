#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct lligada {
    int valor;
    struct lligada *prox;
    } *LInt;

// Funcoes auxiliares
LInt criaLista (int arr[],int N) {
    LInt r = NULL;

    for (int i = N - 1; i >= 0; i --) {
        LInt novo = malloc (sizeof (struct lligada));
        novo->valor = arr[i];
        novo->prox = r;
        r = novo;
    }

    return r; 
}

// 1 
int length (LInt l) {
    int c = 0;

    while (l != NULL) {
        c++;
        l = l->prox;
    }

    return c;
}

// 2
void freeL (LInt l) {
    LInt temp;

    while (l != NULL) {
        temp = l->prox;
        free (l);
        l = temp;
    }
}

// 3 
void imprimeL (LInt l) {
    while (l != NULL) {
        printf ("%d\n",l->valor);
        l = l->prox;
    }
}

// 4
LInt reverseL (LInt l) {
    LInt t = NULL,temp;

    while (l != NULL) {
        temp = l->prox;
        l->prox = t; t = l; l = temp;
    }

    return t;
}

// 5
void insertOrd (LInt *l, int v) {
    LInt novo = malloc (sizeof (struct lligada));
    novo->valor = v;

    while (*l != NULL && (*l)->valor <= v) {
        l = & ((*l)->prox);
    }

    novo->prox = *l;
    *l = novo;
}

// 6
int removeOneOrd (LInt *l,int v) {
    while (*l != NULL && (*l)->valor < v) {
        l = & ((*l)->prox);
    }

    while (*l != NULL && (*l)->valor == v) {
        LInt temp = *l;
        *l = (*l)->prox;
        free (temp);
        return 1;
    }
        
    return 0;

}

// 7
void merge (LInt *r,LInt a,LInt b) {
    *r = NULL;

    while (a != NULL && b != NULL) {
        if (a->valor <= b->valor) {
            *r = a; a = a->prox;
        } else {
            *r = b; b = b->prox;
        }

        r = & ((*r)->prox);
    }

    if (a == NULL) *r = b; else *r = a;

}

// 8
void splitQS (LInt l, int x, LInt *mx, LInt *Mx) {
    *mx = NULL;
    *Mx = NULL;

    LInt *pmx = mx;  
    LInt *pMx = Mx; 

    while (l != NULL) {
        if (l->valor < x) {
            *pmx = l;
            pmx = & ((*pmx)->prox);
        } else {
            *pMx = l;
            pMx = & ((*pMx)->prox);
        }

        l = l->prox;
    }

    *pmx = NULL;
    *pMx = NULL;
}

// 9
LInt parteAmeio (LInt *l) {
    if (*l == NULL) return NULL;

    int meio = length (*l)/2;

    if (meio == 0) {
        LInt primeira = *l;
        *l = NULL;
        return primeira;
    }

    LInt atual = *l;
    for (int i = 1; i < meio; i++) {
        atual = atual->prox;
    }

    LInt segunda = atual->prox;
    atual->prox = NULL;

    LInt primeira = *l;
    *l = segunda;

    return primeira;
}

// 10
int removeAll (LInt *l, int v) {
    int r = 0;

    if (*l == NULL) return 0;

    while (*l != NULL){
        if ((*l)->valor == v) {
            LInt temp = *l;
            *l = (*l)->prox;
            free (temp);
            r++;
        }
        else l = &((*l)->prox);
    }

    return r;
}

// 11 
int removeDups (LInt *l) {
    int r = 0;
    LInt atual = *l;

    while (atual != NULL) {
        LInt *proximo = &(atual->prox);
        while (*proximo != NULL) {
            if ((*proximo)->valor == atual->valor) {
                LInt temp = *proximo;
                *proximo = (*proximo)->prox;
                free (temp);
                r++;
            } else proximo = &((*proximo)->prox);
        }

        atual = atual->prox;
    }

    return r;
}

// 12 
int removeMaiorL (LInt *l) {
    LInt atual = *l;
    int maior = atual->valor;
    atual = atual->prox;

   while (atual != NULL) {
        if (atual->valor > maior) maior = atual->valor;
        atual = atual -> prox;
   }

   LInt *p = l;
   while (*p != NULL && (*p)->valor != maior) p = &((*p)->prox);

   if (*p != NULL) {
       LInt temp = *p;
       *p = (*p)->prox;
       free (temp);
   }

   return maior;
}

// 13
void init (LInt *l) {
    while ((*l)->prox != NULL) l = & ((*l)->prox);

    LInt temp = *l;
    *l = (*l)->prox;
    free (temp);

}

// 14
void appendL (LInt *l, int v) {
    LInt novo = malloc (sizeof (struct lligada));
    novo->valor = v;
    novo->prox = NULL;

    while (*l != NULL) l = & ((*l)->prox);

    *l = novo;
}

// 15
void concatL (LInt *a,LInt b) {
    while (*a != NULL) a = & ((*a)->prox);

    *a = b;
}

// 16
LInt cloneL (LInt l) {
    LInt r = NULL;

    while (l != NULL) {
        appendL (&r,l->valor);
        l = l->prox;
    }

    return r;
}

// 17
void newLInt (LInt *l,int v) {
    LInt novo = malloc (sizeof (struct lligada));
    novo->valor = v;

    LInt prox = *l;
    *l = novo;
    (*l)->prox = prox;
}

LInt cloneRev (LInt l) {
    LInt r = NULL;

    while (l != NULL) {
        newLInt (&r,l->valor);
        l = l->prox;
    }

    return r;
}

// 18
int maximo (LInt l) {
    int maior = l->valor;
    l = l->prox;

    while (l != NULL) {
        if (l->valor > maior) maior = l->valor;
        l = l->prox;
    }

    return maior;
}

// 19
int take (int n,LInt *l) {
    int i = 0;

    while (*l != NULL && i < n) {
        l = & ((*l)->prox);
        i++;
    }

    while (*l != NULL) {
        LInt temp = *l;
        *l = (*l)->prox;
        free (temp);
    }

    return i;
}

// 20
int drop (int n,LInt *l) {
    int i = 0;

    while (*l != NULL && i < n) {
        LInt temp = *l;
        *l = (*l)->prox;
        free (temp);
        i++;
    }

    return i;
}

// 21
LInt Nforward(LInt l, int N) {
    if (l == NULL) return NULL;  

    for (int i = 0; i < N; i++) {
        l = l->prox;  
        if (l == NULL) {
            l = l->prox;
        }
    }

    return l;
}


// 22
int listToArray (LInt l,int v[],int N) {
    int i = 0;

    while (l != NULL && i < N) {
        v[i++] = l->valor;
        l = l->prox;
    }

    return i;
}

// 23
LInt arrayToList (int v[],int N) {
    LInt r = NULL;

    for (int i = N - 1; i >= 0; i--) {
        LInt novo = malloc (sizeof (struct lligada));
        novo->valor = v[i];
        novo->prox = r;

        r = novo;
    }

    return r;
}
 
// 24
LInt somasAcL (LInt l) {
    LInt r = NULL;  
    int soma = 0;

    while (l != NULL) {
        soma += l->valor;
        appendL (&r,soma);
        l = l->prox;
    } 

    return r;
}

// 25
void remreps (LInt l) {
    while (l != NULL && l->prox != NULL) {
        if (l->valor == l->prox->valor) {
            LInt temp = l->prox;
            l->prox = l->prox->prox;
            free (temp);
        } else l = l->prox;
    }
}

// 26
LInt rotateL (LInt l) {
    if (l == NULL || l->prox == NULL) return l;
    
    LInt inicio = l;
    l = l->prox;
    
    LInt atual = l;
    while (atual->prox != NULL) atual = atual->prox;

    atual->prox = inicio;
    inicio->prox = NULL;

    return l;
}

// 27
LInt parte (LInt l) {
    LInt pares = NULL, *ptr = &pares, *ptrl = &l;

    while (*ptrl != NULL && (*ptrl)->prox != NULL) {
        LInt temp = (*ptrl)->prox;
        (*ptrl)->prox = temp->prox;
        temp->prox = NULL;
        *ptr = temp;
        ptr = & (temp->prox);
        ptrl = & ((*ptrl)->prox);
    }

    return pares;
}

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
    } *ABin;

// Função auxiliar
ABin criaArvore() {
    ABin a = malloc(sizeof(struct nodo));
    a->valor = 5;

    a->esq = malloc(sizeof(struct nodo));
    a->esq->valor = 3;

    a->dir = malloc(sizeof(struct nodo));
    a->dir->valor = 8;

    a->esq->esq = malloc(sizeof(struct nodo));
    a->esq->esq->valor = 1;
    a->esq->esq->esq = NULL;
    a->esq->esq->dir = NULL;

    a->esq->dir = malloc(sizeof(struct nodo));
    a->esq->dir->valor = 4;
    a->esq->dir->esq = NULL;
    a->esq->dir->dir = NULL;

    a->dir->esq = NULL;

    a->dir->dir = malloc(sizeof(struct nodo));
    a->dir->dir->valor = 10;
    a->dir->dir->esq = NULL;
    a->dir->dir->dir = NULL;

    return a;
}

void imprimeABin (ABin a) {
    if (a == NULL) return;

    printf("Raíz: %d\n", a->valor);

    printf("Sub-Árvore Esquerda de %d:\n", a->valor);
    imprimeABin(a->esq);

    printf("Sub-Árvore Direita de %d:\n", a->valor);
    imprimeABin(a->dir);
}

// 28
int altura (ABin a) {
    int alturaE,alturaD,r;
    
    if (a == NULL) return 0;
    else {
        alturaE = 1 + altura (a->esq);
        alturaD = 1 + altura (a->dir);
        r = (alturaE > alturaD) ? alturaE : alturaD;
    } 
    
    return r;
}

// 29
ABin cloneAB (ABin a) {
    if (a == NULL) return NULL;

    ABin novo = malloc (sizeof (struct nodo));
    novo->valor = a->valor;
    novo->esq = cloneAB (a->esq);
    novo->dir = cloneAB (a->dir);

    return novo;
}

// 30
void mirror (ABin *a) {
    if (*a == NULL) return;

    ABin temp = (*a)->esq;
    (*a)->esq = (*a)->dir;
    (*a)->dir = temp;

    mirror (&((*a)->esq));
    mirror (&((*a)->dir));
}

// 31
void inorder (ABin a,LInt *l) {
    if (a == NULL) return;

    inorder (a->esq,l);

    *l = malloc (sizeof (struct nodo));
    (*l)->valor = a->valor;
    (*l)->prox = NULL;
    l = & ((*l)->prox);

    inorder (a->dir,l);
}

//32
void preorder (ABin a,LInt *l) {
    if (a == NULL) return;

    *l = malloc (sizeof (struct nodo));
    (*l)->valor = a->valor;
    (*l)->prox = NULL;
    l = & ((*l)->prox);

    preorder (a->esq,l);
    preorder (a->dir,l);
}

// 33
void posorder (ABin a,LInt *l) {
    if (a == NULL) return;

    posorder (a->esq,l);
    posorder (a->dir,l);

    *l = malloc (sizeof (struct nodo));
    (*l)->valor = a->valor;
    (*l)->prox = NULL;
}

// 34
int depth (ABin a, int x) {
    int r;

    if (a == NULL) return -1;
    else if (a->valor == x) return 1;
    else {
        int existeE = depth (a->esq,x);
        int existeD = depth (a->dir,x);

        if (existeE == -1 && existeD == -1) r = -1;
        else if (existeE == -1) 
            r = 1 + existeD;
        else if (existeD == -1)
            r = 1 + existeE;
        else 
            r = 1 + (existeE < existeD) ? existeE : existeD;
    }

    return r;
}

// 35
int freeAB (ABin a) {
    int l = 0;

    if (a != NULL) {
        int lE = freeAB (a->esq);
        int lD = freeAB (a->dir);
        free (a);
        l = 1 + lE + lD;
    }

    return l;
}

// 36
int pruneAB (ABin *a, int l) {
    int r = 0;

    if (*a == NULL) return 0;

    if (l == 0) {
        r = freeAB (*a);
        *a = NULL;
    } else {
        r += pruneAB (& ((*a)->esq),l - 1);
        r += pruneAB (& ((*a)->dir),l - 1);
    }

    return r;
}

// 37
int iguaisAB (ABin a,ABin b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL) return 0;
    if (a->valor != b->valor) return 0;
    
    return (iguaisAB (a->esq,b->esq) && iguaisAB (a->dir,b->dir));
}

// 38
LInt nivelL (ABin a, int n) {
    LInt r = NULL;
    
    if (a == NULL) return NULL;

    if (n == 1) {
        LInt novo = malloc (sizeof (struct lligada));
        novo->valor = a->valor;
        novo->prox = NULL;
        r = novo;
    } else {
        LInt rE = nivelL (a->esq,n-1);
        LInt rD = nivelL (a->dir,n-1);
        concatL (&rE,rD);
        r = rE;
    }

    return r;
}

// 39
int nivelV (ABin a, int n, int v[]) {
    int i = 0;
    if (a == NULL) return 0;

    if (n == 1) {
        v[i++] = a->valor;
    } else {
        int pE = nivelV (a->esq,n-1,v);
        int pD = nivelV (a->dir,n-1,v+pE);
        i = pE + pD;
    }
    
    return i;
}

// 40
int dumpAbin (ABin a,int v[],int N) {
    int r1 = 0,r2 = 0;

    if (a == NULL || N <= 0) return 0;

    r1 = dumpAbin (a->esq,v,N);
    if (r1 < N) {
        v[r1] = a->valor;
        r2 = dumpAbin (a->dir,v + r1 + 1,N - r1 - 1); 
    }

    return (1 + r1 + r2);
}

// 41
ABin somasAcA (ABin a) {
    if (a == NULL) return NULL;

    ABin novo = malloc (sizeof (struct nodo));
    novo->esq = somasAcA (a->esq);
    novo->dir = somasAcA (a->dir);

    int soma = a->valor;
    if (a->esq != NULL) soma += novo->esq->valor;
    if (a->dir != NULL) soma+= novo->dir->valor;
    
    novo->valor = soma;

    return novo;
}

// 42
int contaFolhas (ABin a) {
    if (a == NULL) return 0;
    if (a->esq == NULL && a->dir == NULL) return 1;

    return (contaFolhas (a->esq) + contaFolhas (a->dir));
}

// 43
ABin cloneMirror (ABin a) {
    if (a == NULL) return NULL;

    ABin novo = malloc (sizeof (struct nodo));
    novo->valor = a->valor;
    novo->esq = cloneMirror (a->dir);
    novo->dir = cloneMirror (a->esq);

    return novo;
}

// 44
int addOrd (ABin *a,int x) {
    ABin novo = malloc (sizeof (struct nodo));
    novo->valor = x;
    novo->dir = NULL;
    novo->esq = NULL;

    while (*a != NULL) {
        if ((*a)->valor == x) {
            free (novo);
            return 1;
        }
        else if ((*a)->valor < x) 
             a = & ((*a)->dir);

        else a = & ((*a)->esq);
    }

    *a = novo;

    return 0;
}

// 45
int lookupAB (ABin a,int x) {
    while (a != NULL) {
        if (a->valor == x) return 1;
        else if (a->valor < x) 
            a = a->dir;
        else 
            a = a->esq;
    }

    return 0;
}

// 46
int depthOrd (ABin a, int x) {
    int nivel = 1;

    while (a != NULL) {
        if (a->valor == x) return nivel;
        else if (a->valor < x) 
            a = a->dir;
        else a = a->esq;

        nivel++;
    }

    return -1;
}

// 47
int maiorAB (ABin a) {
    while (a->dir != NULL) a = a->dir;

    return a->valor;
}

// 48
void removeMaiorA (ABin *a) {
    while ((*a)->dir != NULL) 
        a = & ((*a)->dir);

    ABin temp = *a;
    *a = (*a)->esq;
    free (temp);

}

// 49
int quantosMaiores (ABin a,int x) {
    int r;

    if (a == NULL) return 0;

    if (a->valor > x) {
        r = 1 + quantosMaiores (a->dir,x) + quantosMaiores (a->esq,x);
    } else {
        r = quantosMaiores (a->dir,x);
    }

    return r;
}

// 50
void listToBTree (LInt l,ABin *a) {
    if (l == NULL) {
        *a = NULL;
        return;
    }
    
    ABin novo = malloc (sizeof (struct nodo));
    novo->valor = l->valor;
    novo->esq = NULL;
    *a = novo;

    listToBTree (l->prox,& ((*a)->dir));
}

// 51
int deProcuraAux (ABin a,int menor,int maior) {
    if (a == NULL) return 1;
    else if (a->valor < menor || a->valor > maior) return 0;

    return (deProcuraAux (a->esq,menor,a->valor) && deProcuraAux (a->dir,a->valor,maior));
}

int deProcura (ABin a) {
    return deProcuraAux (a,INT_MIN,INT_MAX);
}




