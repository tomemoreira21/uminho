#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct slist {
    int valor;
    struct slist *prox;
} *LInt;    

typedef struct nodo {
    int valor;
    struct nodo *esq,*dir;
} *ABin;

ABin newABin(int v, ABin e, ABin d) {
    ABin nova = malloc (sizeof (struct nodo));
    nova->valor = v;
    nova->esq = e;
    nova->dir = d;

    return nova;
}

ABin exemploABP() {
    ABin n1 = newABin(1, NULL, NULL);
    ABin n4 = newABin(4, NULL, NULL);
    ABin n3 = newABin(3, n1, n4);
    ABin n10 = newABin(10, NULL, NULL);
    ABin n8 = newABin(8, NULL, n10);
    ABin raiz = newABin(5, n3, n8);

    return raiz;
}

// PARTE A
// 1
int length (char s[]) {
    int c = 0;

    for (int i = 0; s[i] != '\0';i++) 
        c++;

    return c;
}

void strrev (char s[]) {
    int i = 0, j = length (s) - 1;

    while (i < j) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;

        i++;j--;
    }   
}

// 2
int remRep (char x[]) {
    int j = 1;

    for (int i = 1; x[i] != '\0';i++) {
        if (x[i] != x[i-1]) x[j++] = x[i];
    }

    x[j] = '\0';
    return j;
}

// 3
void merge (int r[],int a[],int b[],int na,int nb) {
    int i = 0,j = 0,k = 0;

    while (i < na && j < nb) {
        if (a[i] <= b[j]) {
            r[k++] = a[i++];
        } else {
            r[k++] = b[j++];
        }
    }

    while (i < na) {
        r[k++] = a[i++];
    }

    while (j < nb) {
        r[k++] = b[j++];
    }

}

// 4
int deProcuraAux (ABin a,int min,int max) {
    if (a == NULL) return 1;
    if (a->valor < min || a->valor > max) return 0;

    return (deProcuraAux (a->esq,min,a->valor) && deProcuraAux (a->dir,a->valor,max));
}

int deProcura (ABin a) {
    return deProcuraAux (a,INT_MIN,INT_MAX);  
}

// 5
int freeAB (ABin a) {
    if (a == NULL) return 0;

    ABin esq = a->esq,dir = a->dir;
    free (a);

    return (1 + freeAB (esq) + freeAB (dir));
}

int pruneAB (ABin *a,int l) {
    if (*a == NULL) return 0;

    if (l == 1) {
        int r = freeAB (*a);
        *a = NULL;
        return r;
    } else {
        int pruneEsq = pruneAB (& ((*a)->esq),l - 1);
        int pruneDir = pruneAB (& ((*a)->dir),l - 1);
        return (pruneEsq + pruneDir);
    }

}

// PARTE B
// 1
typedef struct digito {
    unsigned char val;
    struct digito *prox;
} *Num;

// 1
// a)
void appendNum (Num *l,unsigned int i) {
    Num novo = malloc (sizeof (struct digito));
    novo->val = i;
    novo->prox = NULL;

    while (*l != NULL) l = & ((*l)->prox);
    
    *l = novo;    
}

Num fromInt (unsigned int i) {
    Num list = NULL;

    while (i != 0) {
        int digito = i % 10;
        appendNum (&list,digito);        
        i /= 10;
    }

    return list;
}

// b)
unsigned int toInt (Num n) {
    int soma = 0,mult = 1;

    while (n != NULL) {
        soma += n->val * mult;
        mult *= 10;
        n = n->prox;
    }

    return soma;
}

// 2
Num addNum (Num a,Num b) {
    unsigned int numA = toInt (a);
    unsigned int numB = toInt (b);

    return (fromInt (numA + numB));
}

// 3
Num mulDig (unsigned char dig,Num a) {
    unsigned int numA = toInt (a);
    int resultado = dig * numA;

    return (fromInt (resultado));
}


void imprimeList (Num l) {

    putchar ('[');
    while (l != NULL) {
        printf ("%d%c",l->val,(l->prox == NULL) ? ']' : ',');
        l = l->prox;
    }

    putchar ('\n');

}

Num numero987 () {
    Num l987 = malloc(sizeof(struct digito));
    l987->val = 7;
    l987->prox = malloc(sizeof(struct digito));
    l987->prox->val = 8;
    l987->prox->prox = malloc(sizeof(struct digito));
    l987->prox->prox->val = 9;
    l987->prox->prox->prox = NULL;

    return l987;
}

Num numero9876 () {
    Num l9876 = malloc(sizeof(struct digito));
    l9876->val = 6;
    l9876->prox = malloc(sizeof(struct digito));
    l9876->prox->val = 7;
    l9876->prox->prox = malloc(sizeof(struct digito));
    l9876->prox->prox->val = 8;
    l9876->prox->prox->prox = malloc(sizeof(struct digito));
    l9876->prox->prox->prox->val = 9;
    l9876->prox->prox->prox->prox = NULL;

    return l9876;
}

int main () {
    // PARTE A
    // 1
    char s[] = "palavra";
    strrev (s);
    printf ("%s\n",s);

    // 2
    char s1[] = "aaabaabbbaac";
    printf ("Comprimento: %d\n",remRep (s1));  
    printf ("%s\n",s1); 

    // 3
    int v1[] = {1,5,6},v2[] = {2,8,10},r[6];
    merge (r,v1,v2,3,3);
    for (int i = 0; i < 6; i++) printf ("%d ",r[i]);
    putchar ('\n');

    // 4
    ABin arvore = exemploABP ();
    printf ("DeProcura: %d\n",deProcura (arvore));

    // PARTE B
    Num l987 = numero987 (), l9876 = numero9876 ();
    // 1 a)
    Num list = fromInt (123);
    imprimeList (list);

    // 1 b)
    printf ("%d\n",toInt (list));

    // 2
    Num lista = addNum (l987,l9876);
    imprimeList (lista);

    // 3
    Num result = mulDig (8,l987);
    imprimeList (result);

    return 0;
}

