#include "deque.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main () {
    srand(time(NULL));
    Deque deque = create ();  

    for (int i = 0; i < 10; i++) {
        int *v = malloc (sizeof (int));
        *v = rand() % 100;
        if (i % 2 == 0) {
            printf ("Após a inserção do %d no ínicio da fila...\n",*v);
            pushFront (deque,v);
        } else {
            printf ("Após a inserção do %d no fim da fila...\n",*v);
            push (deque,v);
        }

        printDeque (deque,printFunc);
        printf ("size: %d\n",size (deque));
        printf ("isEmpty: %s\n\n",(isEmpty (deque)) ? "SIM" : "NÃO");
    }   

    printf("\033[35mApós o reverse da fila...\033[0m\n");
    reverse (deque);
    printDeque (deque,printFunc);
    printf ("size: %d\n",size (deque));
    printf ("isEmpty: %s\n\n",(isEmpty (deque)) ? "SIM" : "NÃO");
    
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            int *v = popFront (deque);            
            printf ("Após a remoção do %d no ínicio da fila...\n",*v);
        } else {
            int *v = pop (deque);
            printf ("Após a remoção do %d no fim da fila...\n",*v);
        }

        printDeque (deque,printFunc);
        printf ("size: %d\n",size(deque));
        printf ("isEmpty: %s\n\n",(isEmpty (deque)) ? "SIM" : "NÃO");
    }

    destroy (deque);
    free (deque);

    return 0;
}