#ifndef FICHA3_H
#define FICHA3_H

typedef struct {
    int val;
    int pos;
    int ord;
    int grupo;
    float ordRel;
    int prm;
} Numero;

typedef struct {
    int grupo;
    int elementos;
    float mediaOrdem;
} Grupo;

void mediaOrdem (Grupo grupos[],int G,Numero valores[],int totalValores, float *total);
void imprimeGrupos (Grupo grupos [],int G, float *total);
void imprimeValores(Numero valores[], int totalValores);
void imprimeResultado (Grupo grupos[],int G,int totalValores, float *total);
double calculaX (Grupo grupos[],int G,int totalValores, float *total);
double valor_referencia(int num_grupos);
void swap (Numero *x,Numero *y);
int partition (Numero valores[], int m, int M);
void ordenaValores (Numero valores[],int m,int M);
void organizaValores (Numero valores[],int totalValores);
void valorOrdRelPrm (Numero valores[],int totalValores);

#endif