#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1
/*
int fizzbuzz(int n) {
    int fizzBuzz = 0,c = 0;

    for (int i = 0; i < n; i++) {
        if (fizz(i) && buzz(i)) {
            printf("FizzBuzz\n");
            if (fizzBuzz) c++;
            else fizzBuzz = 1;
        } else if (fizz(i)) {
            printf("Fizz\n");
            if (fizzBuzz) c++;
        } else if (buzz(i)) {
            printf("Buzz\n");
            if (fizzBuzz) return c;
        } else {
            printf("%d\n", i);
            if (fizzBuzz) c++;
        }
    }

    return -1;
}
*/
// 2
void reverse(int v[], int i, int j) {
    while (i < j) {
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
        i++;
        j--;
    }
}

void rodaEsq(int v[], int N, int r) {
    if (r <= 0 || r >= N) return; 

    reverse (v,0,r-1);
    
    reverse (v,r,N-1);

    reverse (v,0,N-1);
}

// 3
typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;

// 1 é código de erro
int delete(int n, LInt *l) {
    int i = 0;

    while (*l != NULL && i < n) {
        i++;
        l = & ((*l)->prox);
    }

    if (*l == NULL) return 1;
    else {
        LInt temp = *l;
        *l = (*l)->prox;
        free (temp);
        return 0;
    }
}

// 4
int maxCresc(LInt l) {
    if (l == NULL) return 0;

    int freq = 1,freqMax = 1;
    
    while (l->prox != NULL) {
        int valorAtual = l->valor;
        int valorProx = l->prox->valor;

        if (valorProx > valorAtual) {
            freq++;
        } else {
            if (freq > freqMax) {
                freqMax = freq;
            }

            freq = 1;
        }

        l = l->prox;
    }

    if (freq > freqMax) {
        freqMax = freq;
    }

    return freqMax;
}

// 5
typedef struct abin_nodo {
    int valor;
    struct abin_nodo *esq, *dir;
} *ABin;

ABin folhaEsq(ABin a) {
    if (a == NULL) return NULL;

    while (a->esq != NULL || a->dir != NULL) {
        if (a->esq == NULL) {
            a = a->dir;
        } else a = a->esq;
    }

    return a;
}

// 6
// devolve 0 se não for válido os parênteses
int parentesisOk(char exp[]) {
    char st[strlen (exp)];
    int sp = 0;

    for (int i = 0; exp[i] != '\0';i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
            st[sp++] = exp[i];
        } else {
            if ((exp[i] == ')' && st[sp-1] == '(') ||
                (exp[i] == '}' && st[sp-1] == '{') ||
                (exp[i] == ']' && st[sp-1] == '[')) {
                    if (sp == 0) return 0;
                    sp--;
            }
        }
    }

    return (sp == 0);
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
    LInt novo = malloc (sizeof (struct lint_nodo));
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
    printf ("Código de erro: %d\n",delete (0,&lista));
    imprimeLista (lista);

    printf ("Código de erro: %d\n",delete (1,&lista));
    imprimeLista (lista);

    printf ("Código de erro: %d\n",delete (2,&lista));

    // 4
    LInt lista1 = NULL;
    lista1 = newLInt (lista1, 4);
    lista1 = newLInt (lista1, 5);
    lista1 = newLInt (lista1, 12);
    lista1 = newLInt (lista1, 10);
    lista1 = newLInt (lista1, 4);
    lista1 = newLInt (lista1, 1);
    lista1 = newLInt (lista1, 2);
    lista1 = newLInt (lista1, 3);
    lista1 = newLInt (lista1, 2);
    lista1 = newLInt (lista1, 1);

    LInt lista2 = NULL;
    lista2 = newLInt (lista2, 3);
    lista2 = newLInt (lista2, 2);
    lista2 = newLInt (lista2, 1);

    printf ("MaxCresc: %d\n",maxCresc (lista1));
    printf ("MaxCresc: %d\n",maxCresc (lista2));

    // 6
    printf ("ParentisesOk: %d\n",parentesisOk ("3 + [2 - (3 - x)] + 4"));
    printf ("ParentisesOk: %d\n",parentesisOk ("3 + [2 - (3 - x]) + 4"));

    return 0;
}

