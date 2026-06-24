#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack stackCreate (void (*elemPrint) (void *)) {
    Stack s = malloc (sizeof (struct stack));
    s->elemPrint = elemPrint;
    s->size = 0;
    s->top = NULL;

    return s;
}

void stackPush (Stack s,void* data) {
    Node new = nodeCreate (data);
    new->prox = s->top;
    s->top = new;
    s->size++;
}

void* stackPop (Stack s) {
    // pre: s->top != NULL
    Node remove = s->top;
    void* v = remove->data;
    s->top = remove->prox;
    free (remove);
    s->size--;

    return v;
}

void stackPrint (Stack stack) {
    Node atual = stack->top;
    while (atual != NULL) {
        stack->elemPrint(atual->data);
        printf (" -> ");
        atual = atual->prox;
    }
    printf ("NULL\n");
}