#include <stdio.h> 

// 2 
void quadrado (int dim) {
    int j,i,n = 1;

    for (j = 0; j < dim; j++) {
        for (i = 0; i < dim; i++,n++) {
            if (n % 2 == 0) putchar ('_');
            else putchar ('#');
        }
    putchar ('\n');
    }
}


/*
ou 
void quadradoEsp (int n) {
    int j,i; 

    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            if (j % 2 == 0) {
                if (i % 2 == 0) putchar ('#');
                else putchar ('_');
            }
            else {
                if (i % 2 == 0) putchar ('_');
                else putchar ('#');
            }
        }
        putchar ('\n');
    }

}
*/

int main () {
    quadrado (5);
    return 0;
}