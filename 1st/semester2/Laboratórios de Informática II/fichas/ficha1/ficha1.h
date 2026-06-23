#ifndef FICHA1_H
#define FICHA1_H

typedef struct {
    char letra;
    long long int valor;
} letraValor;

void swap(letraValor *x, letraValor *y);
void ordenarAlfabetico(letraValor v[], int N);
void contaMultiplos(letraValor v[], int N, long long int I,long long int F);

#endif