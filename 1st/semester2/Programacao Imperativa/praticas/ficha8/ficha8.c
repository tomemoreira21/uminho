#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct slist {
    int valor;
    struct slist * prox;
} * LInt;

LInt newLInt (int x, LInt xs) {
    LInt r = malloc (sizeof(struct slist));
    if (r != NULL) {
        r->valor = x; r->prox = xs;
    }

    return r;
}

typedef LInt Stack;

typedef struct {
    LInt inicio,fim;
} Queue;

// 1
// a)
void initStack (Stack *s) {
    *s = NULL;
}

// b)
int SisEmpty (Stack s) {
    return (s == NULL);
}

// c)
int push (Stack *s,int x) {
    *s = newLInt (x,*s);
    return 1;
}

// d)
int pop (Stack *s,int *x) {
    int r = 1;

    if (!SisEmpty (*s)) {
        *x = (*s)->valor;
        Stack temp = *s;
        *s = (*s)->prox;
        free (temp);
        r = 0;
    }

    return r;
}

// e)
int top (Stack s,int *x) {
    int r = 1;

    if (!SisEmpty (s)) {
        *x = s->valor;
        r = 0;
    }

    return r;
}

// Função auxiliar
void imprimeLStack (Stack s) {
    
    printf ("[");
    while (s != NULL) {
        printf ("%d%c",s->valor,(s->prox == NULL) ? ']' : ',');
        s = s->prox;
    }
    putchar ('\n');

}

// 2
// a)
void initQueue (Queue *q) {
    q->inicio = NULL;
    q->fim = NULL;
}

// b)
int QisEmpty (Queue q) {
    return (q.inicio == NULL && q.fim == NULL);
}

// c)
int enqueue (Queue *q,int x) {
    LInt novo = malloc (sizeof (struct slist));
    novo->valor = x;
    novo->prox = NULL;

    if (q->inicio == NULL) {
        q->inicio = novo;
        q->fim = novo;
    } else {
        q->fim->prox = novo;
        q->fim = novo;
    }

    return 1;
}

// d)


 


int main () {
    Stack s;
    int x;
    initStack(&s);

    push(&s, 10); 
    push(&s, 20); 
    push(&s, 30); 

    imprimeLStack (s);
    pop (&s,&x);
    imprimeLStack (s);

    push (&s,50);
    imprimeLStack (s);

    top (s,&x);
    printf ("Elemento do topo: %d\n",x);

    return 0;

}