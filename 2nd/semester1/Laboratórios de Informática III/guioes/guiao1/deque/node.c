#include "node.h"
#include <stdlib.h>

Node createNode (void* data) {
    Node new = malloc (sizeof (struct node));
    new->data = data;
    new->ant = NULL;
    new->prox = NULL;

    return new;
}