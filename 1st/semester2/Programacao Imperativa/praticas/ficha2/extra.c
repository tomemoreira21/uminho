#include <stdio.h> 

int main () {
    int i,j,*a,*b;

    i = 3; a = &i;
    j = 5; b = &j;

    i++; // a = 4, i = 4
    j = i + *b; // j = 9

    b = a; // b = 4
    j = j + *b; // j = 13

    printf ("%d\n",j);

    return 0;
}