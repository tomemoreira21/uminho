#include <stdio.h>  

void rep (int n,char c) {
    for (int i = 0; i < n; i++) {
        putchar (c);
    }
}

void triangulo (int n) {
    int e = n - 1, c = 1;

    for (int i = 1; i <= n; i++) {
        rep (e,' ');
        rep (c,'#');
        putchar ('\n');

        c += 2;
        e --;
    }

}



int main () {
    triangulo (30);
    return 0;
}


