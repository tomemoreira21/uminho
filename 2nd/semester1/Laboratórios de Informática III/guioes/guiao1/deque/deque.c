#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Deque create () {
    Deque deque = malloc (sizeof (struct deque));
    deque->size = 0;
    deque->back = NULL;
    deque->front = NULL;

    return deque;
}

void push (Deque deque,void* data) {
    Node new = createNode (data);   

    if (deque->size == 0) {
        deque->front = deque->back = new;
    } else {
        Node back = deque->back;
        back->prox = new;
        new->ant = back;
        deque->back = new;
    }

    deque->size++;
}

void pushFront (Deque deque,void* data) {
    Node new = createNode (data);

    if (deque->size == 0) {
        deque->back = deque->front = new;
    } else {
        Node front = deque->front;
        front->ant = new;
        new->prox = front;
        deque->front = new;
    }

    deque->size++;
}

void* pop(Deque deque) {
    if (deque->size == 0) return NULL;

    Node back = deque->back;
    if (deque->size == 1) {
        deque->back = deque->front = NULL;
    } else {
        deque->back = back->ant;
        deque->back->prox = NULL;
    }
    
    void* v = back->data;
    free (back);
    deque->size--;

    return v;
}

void* popFront (Deque deque) {
    if (deque->size == 0) return NULL;

    Node front = deque->front;
    if (deque->size == 1) {
        deque->back = deque->front = NULL;
    } else {
        deque->front = front->prox;
        deque->front->ant = NULL;
    }

    void* v = front->data;
    free (front);
    deque->size--;

    return v;
}   

int size (Deque deque) {
    return deque->size;
}

bool isEmpty (Deque deque) {
    return deque->size == 0;
}

void reverse (Deque deque) {
    Node temp = NULL;
    Node atual = deque->front;

    while (atual != NULL) {
        temp = atual->ant;
        atual->ant = atual->prox;
        atual->prox = temp;
        atual = atual->ant;
    }

    temp = deque->front;
    deque->front = deque->back;
    deque->back = temp;
}

void printFunc (void *data) {
    int *i = data;
    printf ("%d",*i);
}

void printDeque (Deque deque,void(*printFunc)(void*)) {
    Node front = deque->front;
    deque->printfFunc = printFunc;

    printf ("[");
    while (front != NULL) {
        deque->printfFunc (front->data);
        if (front->prox != NULL) printf(" -> ");
        front = front->prox;
    }

    printf ("]\n");
}

void destroy (Deque deque) {
    Node front = deque->front;

    while (front != NULL) {
        Node temp = front;
        free (temp->data);
        free (temp);
        front = front->prox;
    }

}