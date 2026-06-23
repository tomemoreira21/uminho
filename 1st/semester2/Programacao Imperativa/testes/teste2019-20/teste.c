#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// PARTE A
// 1
int maiorPrefixo (char s1[],char s2[]) {
    int c = 0;

    for (int i = 0; s1[i] != '\0' && s1[i] == s2[i];i++)
        c++;     

    return c;
}

// 2
int remRep (char x[]) {
    int j = 1;

    for (int i = 1; x[i] != '\0';i++) {
        if (x[i-1] != x[i]) {
            x[j++] = x[i];
        }
    }

    x[j] = '\0';

    return j;
}

// 3
typedef struct lligada {
    int valor;
    struct lligada *prox;
} *LInt;

void splitQS (LInt l,int x,LInt *mx,LInt *Mx) {
    *mx = NULL;
    *Mx = NULL;

    LInt *pmx = mx,*pMx = Mx;

    while (l != NULL) {
        if (l->valor < x) {
            *pmx = l; pmx = & ((*pmx)->prox);
        } else {
            *pMx = l; pMx = & ((*pMx)->prox);
        }

        l = l->prox;
    }

    *pmx = NULL;
    *pMx = NULL;
}

// 4
int removeDups (LInt *l) {
    int r = 0;
    LInt atual = *l;

    while (atual != NULL) {
        LInt *proxima = & (atual->prox);
        int valor = atual->valor;
        while (*proxima != NULL) {
            if (valor == (*proxima)->valor) {
                LInt temp = *proxima;
                *proxima = (*proxima)->prox;
                free (temp);
                r++;
            } else {
                proxima = & ((*proxima)->prox);
            } 
        }

        atual = atual->prox;
    }

    return r;
}

// PARTE B
typedef struct dict {
    char *palavra;
    int ocorr;
    struct dict *esq,*dir;
} *Dict;

Dict rodaDireita (Dict d) {
    Dict r = d->esq;
    d->esq = r->dir;
    r->dir = d;
    return r;
}

// 1
/*
- Caso quando a árvore é vazia (NULL)
- Caso quando a árvore da esquerda é vazia (NULL)

       c                  b                  
      / \                / \ 
     b   d       ->     a   c
    /                        \
   a                          d  
*/

// 2
Dict rodaEsquerda (Dict d) {
    Dict r = d->dir;
    d->dir = r->esq;
    r->esq = d;
    return r;
}

/*
- Caso quando a árvore é vazia (NULL)
- Caso quando a árvore da direita é vazia (NULL)
*/

// 3
Dict promoveMenor(Dict d) {
    if (d == NULL || d->esq == NULL)
        return d;

    d->esq = promoveMenor(d->esq);
    return rodaDireita(d);
}

/*
       c                      a             
      / \                      \
     b   d       ->             c
    /                          /  \
   a                          b    d
*/

// 4
Dict acrescenta(Dict d, char *pal) {
    if (d == NULL) {
        Dict novo = malloc(sizeof(struct dict));
        strcpy (d->palavra,pal);
        novo->ocorr = 1;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    int cmp = strcmp(pal,d->palavra);

    if (cmp == 0) {
        d->ocorr++;  
        return d;
    }
    else if (cmp < 0) {
        d->esq = acrescenta(d->esq, pal);
        return rodaDireita(d);  
    }
    else {
        d->dir = acrescenta(d->dir, pal);
        return rodaEsquerda(d);  
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
    LInt novo = malloc (sizeof (struct lligada));
    novo->valor = x;
    novo->prox = l;

    return novo;
}

LInt criaLista() {
    LInt l = NULL;
    l = newLInt(l, 1);
    l = newLInt(l, 2);
    l = newLInt(l, 3);
    l = newLInt(l, 10);
    return l; // Resultado: 10 -> 3 -> 2 -> 1 -> NULL
}

LInt criaListaRep () {
    LInt l = NULL;
    l = newLInt(l, 10);
    l = newLInt(l, 10);
    l = newLInt(l, 1);
    l = newLInt(l, 2);
    l = newLInt(l, 1);
    l = newLInt(l, 10);
    return l; // Resultado: 10 -> 1 -> 2 -> 1 -> 10 -> 10 -> NULL
}

int main () {
    // 1
    printf ("Maior prefixo: %d\n",maiorPrefixo ("banana","banco"));
    printf ("Maior prefixo: %d\n",maiorPrefixo ("carro","calo"));

    // 2
    char s1[] = "aaabaabbbaaa";
    printf ("%d\n",remRep (s1));
    printf ("%s\n",s1);

    // 3
    LInt lista = criaLista (),menores = NULL,maiores = NULL;
    splitQS (lista,3,&menores,&maiores);
    printf ("Menores: ");
    imprimeLista (menores);
    printf ("Maiores: ");
    imprimeLista (maiores);

    // 4
    LInt listaR = criaListaRep ();
    printf ("Removidos: %d\n",removeDups (&listaR));
    imprimeLista (listaR);


    return 0;

}