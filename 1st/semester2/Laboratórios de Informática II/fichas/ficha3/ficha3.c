#include <stdio.h> 
#include "ficha3.h"
#include <stdlib.h>
#include <math.h>

void imprimeValores(Numero valores[], int totalValores) {
    printf(" Pos  Ord  Grp     OrdRel  Val  Prm\n");

    for (int i = 0; i < totalValores; i++) {
        printf("%4d %4d %4d %10.1f %4d %4d\n",
               valores[i].pos,valores[i].ord, valores[i].grupo,
               valores[i].ordRel, valores[i].val, valores[i].prm);
    }
}

void imprimeGrupos (Grupo grupos [],int G, float *total) {
    int i;
    printf ("\n  Grp MediaOrdem\n");

    for (i = 0; i < G; i++) {
        printf (" %4d %10.1f\n",grupos[i].grupo,grupos[i].mediaOrdem);
    }

    printf ("Todos %10.1f\n",*total);
}

void imprimeResultado (Grupo grupos[],int G,int totalValores, float *total) {
    double ref,calc;

    ref = valor_referencia (G);
    calc = calculaX (grupos,G,totalValores,total);

    printf ("\nCalc: %.2f\n",calc);
    printf (" Ref: %.2f\n",ref);

    (calc < ref) ? printf ("Nao\n") : printf ("Sim\n");
}

/*
Esta função é responsável por várias tarefas: 
 - ordenar os valores todos, com base no próprio valor
 - calcula os indices da posição e do ord neste novo array ordenado
 - calcula os valores do OrdRel e do Prm
*/
void organizaValores (Numero valores[],int totalValores) {
    ordenaValores (valores,0,totalValores - 1);

    for (int i = 0; i < totalValores; i++) { 
        valores[i].pos = i; 
        valores[i].ord = i + 1;
    }

    valorOrdRelPrm (valores,totalValores);
}

void valorOrdRelPrm (Numero valores[],int totalValores) {
    int i = 0,c,j,pos;
    float mediaOrdRel,somaOrdens;

    while (i < totalValores) {
        pos = i;
        somaOrdens = valores[i].ord;
        c = 1;

        j = i + 1;
        while (j < totalValores && valores[j].val == valores[i].val) {
                somaOrdens += valores[j].ord;
                c++;j++;
        }

        mediaOrdRel = (c > 0) ? somaOrdens / c : 0;

        for (int k = i; k < j; k++) {
            valores[k].ordRel = mediaOrdRel;
            valores[k].prm = pos;
        }
        
        i = j;
        }
}


void mediaOrdem (Grupo grupos[],int G,Numero valores[],int totalValores, float *total) {
    int j = 0,c;
    float soma;

    while (j < G) {
        soma = 0;
        c = 0;

    grupos[j].grupo = j + 1;
    grupos[j].elementos = 0;

    for (int i = 0; i < totalValores;i++) {
        if (valores[i].grupo == grupos[j].grupo) {
            soma += valores[i].ordRel;
            grupos[j].elementos ++;
            c++;
        }
    }

    grupos[j].mediaOrdem = (c > 0) ? (soma / c) : 0;
    j++;
    
    }

    *total = (totalValores + 1)/ 2.0;

}

double calculaX (Grupo grupos[],int G,int totalValores, float *total) {
    double S = 0,X;

    for (int i = 0; i < G; i++) {
        S += grupos[i].elementos * pow ((grupos[i].mediaOrdem - *total),2);
    }

    X = (totalValores > 0) ? ((totalValores - 1.0) / totalValores) * ((12.0 * S) / (pow((double)totalValores, 2) - 1.0)) : 0;

    return X;
}

double valor_referencia(int num_grupos) {
    double p = 0.95;
    double df = num_grupos - 1;
    double a = (p < 0.5) ?  sqrt(-2.0 * log(p)) : sqrt(-2.0 * log(1.0 - p));
    double poly = 2.515517 + 0.802853 * a + 0.010328 * a * a;
    double q = 1.0 + 1.432788 * a + 0.189269 * a * a + 0.001308 * a * a * a;
    double z = (p < 0.5) ? -(a - poly / q) : (a - poly / q);
    double x = df * pow(1.0 - 2.0 / (9.0 * df) + z * sqrt(2.0 / (9.0 * df)), 3.0);
    return x;
}


void swap (Numero *x,Numero *y) {
    Numero temp;

    temp = *x;
    *x = *y;
    *y = temp;
}



int partition (Numero valores[], int m, int M) {
    int pivo = valores[M].val;  
    int i = m - 1;                

    for (int j = m; j < M; j++) {
        if (valores[j].val < pivo || (valores[j].val == pivo && valores[j].grupo < valores[M].grupo)) {
            i++;
            swap(&valores[i], &valores[j]);
        }
    }

    swap(&valores[i + 1], &valores[M]);  
    return i + 1;
}

    
void ordenaValores (Numero valores[],int m,int M) {
    int p;

    if (m < M) {
        p = partition (valores,m,M);
        
        ordenaValores (valores,m,p-1);
        ordenaValores (valores,p + 1,M);
    }
} 


