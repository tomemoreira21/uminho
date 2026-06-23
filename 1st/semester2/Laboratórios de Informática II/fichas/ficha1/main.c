#include <stdio.h> 
#include "ficha1.h"

int main () {
    int N;
    long long int I,F;
    
    if (scanf ("%d",&N) != 1 || (N < 1 || N > 26)) {
        return -1;
    }

    letraValor v[N];
    
    for (int i = 0; i < N; i++) {
        if (scanf (" %c %lld",&v[i].letra,&v[i].valor) != 2 || (v[i].valor < 0 || v[i].valor > 1000000000)) return -1;
    }
    

    if (scanf ("%lld %lld",&I,&F) != 2 || (I < 0 || I > 1000000000) || (F < 0 || F > 1000000000)) {
        return -1;
    } 

    ordenarAlfabetico (v,N);
    contaMultiplos (v,N,I,F);

    for (int i = 0; i < N; i++) {
        printf ("%c %lld\n",v[i].letra,v[i].valor);
    }

    return 0;
}
