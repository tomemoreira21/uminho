#include <stdio.h>
#include <stdlib.h>
#define Max 100 

typedef struct staticQueue {
    int front;
    int length;
    int values [Max];
    } QUEUE, *SQueue;

// 2 
// a)
void SinitQueue (SQueue q) {
    q->front = 0;
    q->length = 0;
}

// b) 
int SisEmptyQ (SQueue q) {
    return (q->length == 0);
}

// c) 
int Senqueue (SQueue q,int x) {
    int r = 1;

    if (q->length < Max) {
        q->values [(q->front + q->length) % Max] = x;
        q->length++;
        r = 0;
    }

    return r;
}

// d) 
int Sdequeue (SQueue q,int *x) {
    int r = 1;

    if (!SisEmptyQ (q)) {
        *x = q->values[q->front];
        q->front = (q->front + 1) % Max;
        q->length --;
        r = 0;
    }

    return r;
}

// e) 
int Sfront (SQueue q,int *x) {
    int r = 1;

    if (!SisEmptyQ (q)) {
        *x = q->values[q->front];
        r = 0;
    }

    return r;
}

void printfQueue (SQueue q) {
    printf ("Queue: ");
    for (int i = q->front; i < q->front + q->length; i++) {
        printf ("%d ",q->values[i]);
    }
    putchar ('\n');
}

// Usando o Malloc
typedef struct dinQueue {
    int size; // guarda o tamanho do array values (é como se fosse a constante Max)
    int front;
    int length;
    int *values;
} *DQueue;

// a) 
void SinitDinQueue (DQueue q) {
    q->size = 1;
    q->length = 0;
    q->front = 0;
    q->values = malloc (q->size * sizeof (int));
}

// b) 
int SisEmptyDinQueue (DQueue q) {
    return (q->length == 0);
}

// c) 
int resize (DQueue q) {
    int *t;

    t = q->values;
    q->values = malloc (2*q->size*sizeof (int));

    if (q->values == NULL) return 1;

    for (int i = 0; i < q->size; i++)
        q->values[i] = t[(q->front + i) % q->size];
    
    free (t);
    q->size *= 2;
    q->front = 0;

    return 0;
}

int SdeDinQueue (DQueue q,int x) {
    if (q->length == q->size) resize (q);

    q->values[(q->front + q->length) % q->size] = x;
    q->length ++;

    return 0;
}

void printfDinQueue (DQueue q) {
    printf ("DQueue: ");
    for (int i = q->front; i < q->front + q->length;i++) {
        printf ("%d ",q->values[i]);
    }

    putchar ('\n');
}

int main () {
    DQueue Q = malloc(sizeof(struct dinQueue));
    int x;
    
    SinitDinQueue (Q);

    SdeDinQueue (Q,10);
    SdeDinQueue (Q,20);
    SdeDinQueue (Q,30);

    printfDinQueue (Q);

    return 0;

}


