#include <stdio.h>

/*
x = 28 
y = 2
d = 's' 
v = 1
*/

// Pergunta 1
int determinaPos (long x, long y, int v,char d) {
    int t = 1;

    while (t <= 10000) {
        if (t % 3 == 0 && t % 5 == 0) {

            if (d == 'n')
            d = 'e';   
            else if (d == 'e')
            d = 's';
            else if (d == 's')
            d = 'w';
            else
            d = 'n';
        
        } else if (t % 3 == 0)
        
            v += 2;
        
        else if (t % 5 == 0)
        
            v -= 1;
        
        else {
            if (d == 'n')
            y += v;
            else if (d == 'e')
            x += v;
            else if (d == 's')
            y -= v;
            else
            x -= v;
        }
        t++;

    }

    return x;
}

// Pergunta 2
int determinaDist (long x, long y, int v,char d) {
    int t = 1;
    int distanciaAtual = 0;
    int maiorDistancia = 0;

    while (t <= 10000) {
        if (t % 3 == 0 && t % 5 == 0) {

            if (distanciaAtual > maiorDistancia) {
                maiorDistancia = distanciaAtual;
            }

            distanciaAtual = 0;
            if (d == 'n')
            d = 'e';   
            else if (d == 'e')
            d = 's';
            else if (d == 's')
            d = 'w';
            else
            d = 'n';
        
        } else if (t % 3 == 0)
        
            v += 2;
        
        else if (t % 5 == 0)
        
            v -= 1;
        
        else {
            distanciaAtual += v;
        }
        t++;
    }

    return maiorDistancia;
}


int main () {
    printf ("Posição x final: %d\n",determinaPos (28,2,1,'s'));
    printf ("Máxima distância : %d\n",determinaDist (28,2,1,'s'));
    return 0;
}

// Pergunta 1 -> -15988
// Pergunta 2 -> 31952



