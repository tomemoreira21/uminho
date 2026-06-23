#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct celula {
    char *palavra;
    int ocorr;
    struct celula * prox;
} * Palavras;

// 1 
void libertaLista (Palavras l) {
    Palavras temp;
    
    while (l != NULL) {
        temp = l->prox;
        free (l->palavra);
        free (l);
        l = temp;
    }
}

// 2 
int quantasP (Palavras l) {
    int p = 0;

    while (l != NULL) {
        if (l->ocorr > 0) p++;
        l = l->prox;
    }

    return p;
} 

// 3
void listaPal (Palavras l) {
    while (l != NULL) {
        printf ("%s -> %d ocorrências\n",l->palavra,l->ocorr);
        l = l->prox;
    }
}

// 4 
char * ultima (Palavras l) {
    if (l == NULL) return NULL;

    while (l->prox != NULL) {
        l = l->prox;
    }

    return l->palavra;
}

// 5
Palavras acrescentaInicio (Palavras l, char *p) {
    Palavras r = malloc (sizeof (struct celula));

    r->palavra = p;
    r->ocorr = 1;
    r->prox = l;

    return r;
}

// 6 
Palavras acrescentaFim (Palavras l,char *p) {
    Palavras temp = l,novaPalavra = malloc (sizeof (struct celula));

    novaPalavra->palavra = p;
    novaPalavra->ocorr = 1;
    novaPalavra->prox = NULL;

    if (l == NULL) {
        libertaLista (novaPalavra);
        return acrescentaInicio (NULL,p);
    }

    while (temp -> prox != NULL) {
        temp = temp->prox;
    }

    temp->prox = novaPalavra;

    return l;
}

// 7 
Palavras acrescenta (Palavras l,char *p) {
    int existe = 0;
    Palavras temp = l;

    while (l != NULL && !existe) {
        if (strcmp (l->palavra,p) == 0) {
            existe = 1;
            l->ocorr++;
        } 

        l = l->prox; 
    }

    return (!existe) ? acrescentaInicio (temp,p) : temp;
}

// 8
struct celula * maisFreq (Palavras l) {
    Palavras maisFreq = malloc (sizeof (struct celula));
    int ocorrMax = 0;  

    while (l != NULL) {
        if (l->ocorr > ocorrMax) {
            ocorrMax = l->ocorr;
            maisFreq->palavra = l->palavra;
            maisFreq->ocorr = l->ocorr;
            maisFreq->prox = NULL;
            
        } 
        
        l = l->prox;
    }

    return maisFreq;
}

int main() {
    Palavras l = NULL;

    l = acrescenta(l, strdup("gato"));
    l = acrescenta(l, strdup ("cão"));
    l = acrescenta(l, strdup ("pássaro"));
    l = acrescenta(l, strdup ("gato"));
    l = acrescenta(l, strdup ("gato"));
    l = acrescenta(l, strdup ("cão"));

    printf("Lista de palavras:\n");
    listaPal(l);

    Palavras freq = maisFreq(l);
    printf ("\nPalavra mais frequente é %s com %d ocorrências\n",freq->palavra,freq->ocorr);

    libertaLista(l);
    return 0;
}