#include <stdio.h> 
#include <string.h>
#include "ficha2.h"

int main () {
    int C;

    if (scanf ("%d",&C) != 1 || C < 1 || C > 100) {
        return -1;
    }

    numero valores[C];

    for (int i = 0; i < C; i++) {
        if (scanf ("%1000s %d",valores[i].N,&valores[i].S) != 2 || strlen (valores[i].N) > 1000 || valores[i].S < 0 || valores[i].S > (int)strlen (valores[i].N)) {
            return -1; 
        }
    }

    maiorProduto (valores,C);

    for (int i = 0; i < C; i++) {
        imprimeMaiorProduto (valores[i].maxProduto);
    }

    return 0;
}