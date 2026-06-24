#include <stdio.h>
#include <stdlib.h>

/*
static -> restringe o uso da função somente para aquele módulo
extern -> é o inverso do mesmo
*/

int main () {
    char *p = malloc (sizeof (*p));

    *p = 'a';
    printf ("Valor char: %c\n",*p);

    free (p);
    return 0;
}
