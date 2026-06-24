#include "stack.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void printInt (void* data) {
    int *i = data;
    printf ("%d",*i);
}

int main () {
    srand(time(NULL));
    
    Stack s = stackCreate (&printInt);
    for (int i = 0; i < 5; i++) {
        int *valor = malloc (sizeof (int)); 
        *valor = rand() % 100;
        stackPush (s,valor);
        printf ("Após a inserção do %d...\n",*valor);
        stackPrint (s);
        printf ("size: %d\n\n",s->size);
    }

    for (int i = 0; i < 5; i++) {
        int *valor = stackPop (s);
        printf ("Após a remoção do %d...\n",*valor);
        stackPrint (s);
        printf ("size: %d\n\n",s->size);
        free (valor);
    }


    free (s);
    return 0;
}