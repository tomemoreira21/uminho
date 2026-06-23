#include <stdio.h>
#include <stdlib.h>
#include "problemaE.h"

int main () {
    Tabuleiro t = malloc (sizeof (struct tabuleiro));

    if (t == NULL || !leTabuleiro (t)) {
        liberaTabuleiro (t);
        return 1;
    }

    int N;
    if ((scanf ("%d",&N) != 1) || N <= 0) {
        liberaTabuleiro (t);
        return 1;
    }

    Casos casos = inicializaCasos(N);
    if (casos == NULL) {
        liberaTabuleiro(t);
        liberaCasos(casos);
        return 1;
    }
    casos->numCasos = N;

    if (!processaCasos(casos)) {
        liberaTabuleiro(t);
        liberaCasos(casos);
        return 1;
    }


    imprimeResultado (t,casos);
    liberaTabuleiro(t);
    liberaCasos(casos);
    return 0;
}   