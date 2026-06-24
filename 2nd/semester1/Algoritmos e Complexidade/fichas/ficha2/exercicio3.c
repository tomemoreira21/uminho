#include <stdio.h>

int soma (int v[], int a, int b) {
    int r = 0, i;
    for (i= a; i <= b; i++)
        r = r + v[i];

    return r;
}

int maxSoma (int v[],int N) {
    int c[N],m;

    c[0] = v[0];
    m = c[0];

    for (int i = 1; i < N; i++) {
        c[i] = (c[i-1] > 0) ? v[i] + c[i-1] : v[i];

        if (c[i] > m) m = c[i];
    }

    return m;
}