#include "ficha1.h"

void swap (letraValor *x,letraValor *y) {
    letraValor temp;

    temp = *x;
    *x = * y;
    *y = temp;
}

void ordenarAlfabetico (letraValor v[],int N) {

    for (int j = 0; j < N - 1; j++) {
        for (int i = 0; i < N - j - 1; i++) {
            if (v[i].letra > v[i+1].letra) 
                swap (&v[i],&v[i+1]); 
        }
        
    }
}

void contaMultiplos (letraValor v[],int N,long long int I,long long int F) {
    
    for (int j = 0; j < N; j++) {
        if (I > F) {
            v[j].valor = 0;
        } else {
            v[j].valor = (F / v[j].valor) - ((I - 1) / v[j].valor);
        }
}


