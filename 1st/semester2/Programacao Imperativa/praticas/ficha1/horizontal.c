#include <stdio.h> 

void triangulo (int dim) {
    int i,j; 

    // Desenha a Parte Crescente
    for (j = 1; j < dim; j++) {
        for (i = 0; i < j; i++) {
            putchar ('#');
        }
        putchar ('\n');
    }

    // Desenha a Parte Descrescente 
    for (j = dim; j > 0; j--) {
        for (i = 0; i < j; i++) {
            putchar ('#');
        }
        putchar ('\n');
    }

}

int main () {
    triangulo (5);
    return 0;
}