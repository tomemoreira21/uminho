#ifndef NODE_H
#define NODE_H

typedef struct node {
    void* data;
    struct node* ant;
    struct node* prox;
} *Node;

Node createNode (void* data);

#endif