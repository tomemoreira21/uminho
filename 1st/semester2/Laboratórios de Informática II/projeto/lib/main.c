#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main () {
    Jogo j = malloc(sizeof(struct jogo));
    StackJogadas s = malloc(sizeof(struct stack));
    ListaConflitos lista = NULL;
            
    jogo(j,s,lista);    

    free (j);
    return 0;
}
