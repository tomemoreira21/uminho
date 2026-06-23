#include <stdio.h>
#include <stdlib.h>
#include "problemaD.h"

int main () {
    int C;
    if (scanf ("%d",&C) != 1) return 1;

    Tabuleiro *tabuleiros = malloc(C * sizeof(Tabuleiro));
    Caso *casos = malloc(C * sizeof(Caso));

    for (int j = 0; j < C; j++) {
        if (!processaCasos (tabuleiros,casos,j)) {
            libertaTabuleiros (tabuleiros,j+1);
            libertaCasos (casos,j+1);
            return 1;
        } 
    }

    imprimeCasos (casos,C);
    libertaTabuleiros (tabuleiros,C);
    libertaCasos (casos,C);

    return 0;
}