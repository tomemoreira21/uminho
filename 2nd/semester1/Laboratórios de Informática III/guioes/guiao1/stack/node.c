#include "node.h"
#include <stdlib.h>

Node nodeCreate (void* data) {
    Node new = malloc (sizeof (struct node));
    new->data = data;
    new->prox = NULL;

    return new;
}