#include <stdio.h> 

void triangulo (int n) {
    int x = 1; 

    for (int i = 1; i <= n; i++,x+=2) {
        for (int j = 1; j <= n - i; j++) {
            putchar (' ');
        }

        for (int j = 1; j <= x; j++) {
            putchar ('#');
        }
        putchar ('\n');
    }
}

int main () {
    triangulo (5);
    return 0;
}