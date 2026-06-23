#include <stdio.h>

void addTo (int *b,int a) {
    *b = *b + a;
}

int main () {
    int x = 4, y = 10;
    int *a;

    a = &x;
    addTo (a,5); // *b = 9,ou seja, x = 9;
    addTo (&y,y); // *b = 20, ou seja, y = 20;
    x += y;  // x = 29;
    addTo (a,x); // *b = 58, ou seja, x = 58;
    printf ("%d",x); 

    return 0;
}