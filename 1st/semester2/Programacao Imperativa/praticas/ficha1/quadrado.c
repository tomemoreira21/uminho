#include <stdio.h>

void quadrado (int n) {
    int i,j; 

    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            putchar ('#');
        }
    putchar ('\n');
    }   
}


int main () {
    quadrado (5);
    return 0;
}

