#include <stdio.h>
#include "ficha3.h"
#include <math.h>

int main () {
    int G,N,totalValores = 0;
    float totalMedia;

    if (scanf ("%d",&G) != 1 || G > 100 || G < 0) return -1;

    Numero valores[100*G];
    Grupo grupos[G];

    for (int i = 0; i < G; i++) {
        if (scanf ("%d",&N) != 1 ||N > 100) return -1;

        for (int j = 0; j < N ;j++) {
            if (scanf ("%d",&valores[totalValores].val) != 1) return -1;
        
            valores[totalValores].grupo = i + 1;            
            
            totalValores++;
        }
    }
    
    organizaValores(valores, totalValores);
    imprimeValores(valores, totalValores);

    mediaOrdem (grupos,G,valores,totalValores,&totalMedia);
    imprimeGrupos (grupos,G,&totalMedia);

    imprimeResultado (grupos,G,totalValores,&totalMedia);

    return 0;
}