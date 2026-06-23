#include <stdio.h>

void circulo (int r) {
    int c = 0;
    for (int i = -r; i <= r; i++) {
        for (int j = -r; j <= r; j++) {
            if (i*i + j*j <= r*r) putchar ('#');
            else putchar (' ');
    }
    putchar ('\n');
  }
}

int main () {
    circulo (4);
    return 0;
}