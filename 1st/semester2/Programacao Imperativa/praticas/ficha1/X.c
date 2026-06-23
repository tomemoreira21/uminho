#include <stdio.h>

int desenharX (int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == n - i - 1 || i == j) {
                putchar ('#');
            } else {
                putchar (' ');
            }
        }
        putchar ('\n');
    }
}

int main () {
    desenharX (5);
    return 0;
}