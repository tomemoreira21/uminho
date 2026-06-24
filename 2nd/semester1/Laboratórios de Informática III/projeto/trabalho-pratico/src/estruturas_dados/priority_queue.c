#include "priority_queue.h"
#include <stdlib.h>

struct priority_queue {
    void **data;
    int size;
    int capacity;
    int (*compare)(const void *, const void *);
    void (*free_func)(void *);
};

// Módulo para definir uma heap pode ser usado para o que quisermos no futuro tanto para max-heap como min-heap
void pq_swap (void **a,void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

void pq_heapify_up(PriorityQueue *pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->compare(pq->data[index], pq->data[parent]) <= 0)
            break;
        pq_swap(&pq->data[index], &pq->data[parent]);
        index = parent;
    }
}

void pq_heapify_upMin(PriorityQueue *pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->compare(pq->data[index], pq->data[parent]) >= 0)
            break;
        pq_swap(&pq->data[index], &pq->data[parent]);
        index = parent;
    }
}

void pq_heapify_down(PriorityQueue *pq, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < pq->size && pq->compare(pq->data[left], pq->data[largest]) > 0) {
            largest = left;
        }

        if (right < pq->size && pq->compare(pq->data[right], pq->data[largest]) > 0) {
            largest = right;
        }

        if (largest == index)
            break;

        pq_swap(&pq->data[index], &pq->data[largest]);
        index = largest;  
    }
}

void pq_heapify_downMin(PriorityQueue *pq, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < pq->size && pq->compare(pq->data[left], pq->data[smallest]) < 0)
            smallest = left;

        if (right < pq->size && pq->compare(pq->data[right], pq->data[smallest]) < 0)
            smallest = right;

        if (smallest == index)
            break;

        pq_swap(&pq->data[index], &pq->data[smallest]);
        index = smallest; 
    }
}

PriorityQueue *pq_new(int (*compare)(const void *, const void *), void (*free_func)(void *)) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->size = 0;
    pq->capacity = 64;
    pq->compare = compare;
    pq->free_func = free_func;
    pq->data = malloc(sizeof(void *) * pq->capacity);
    return pq;
}

PriorityQueue *pq_newGasto(int (*compare)(const void *, const void *), void (*free_func)(void *)) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->size = 0;
    pq->capacity = 10;
    pq->compare = compare;
    pq->free_func = free_func;
    pq->data = malloc(sizeof(void *) * pq->capacity);
    return pq;
}

void pq_free(PriorityQueue *pq) {
    if (!pq) return;

    if (pq->data != NULL) {
        if (pq->free_func != NULL) {
            for (int i = 0; i < pq->size; i++)
                pq->free_func(pq->data[i]);
        }
        free(pq->data);
    }
    free(pq);
}

void pq_push(PriorityQueue *pq, void *element) {
    if (pq->size >= pq->capacity) {
        pq->capacity *= 2;
        pq->data = realloc(pq->data, sizeof(void *) * pq->capacity);
    }

    pq->data[pq->size] = element;
    pq->size++;
    pq_heapify_up(pq, pq->size - 1);
}

void pq_pushGasto(PriorityQueue *pq, void *element) {
   if (pq->size >= pq->capacity) { 
        if (pq->compare(element, pq->data[0]) > 0) {
            pq->free_func(pq->data[0]); 
            pq->data[0] = element;
            pq_heapify_downMin(pq, 0);
        }

        else pq->free_func(element);
    } 

    else {
        pq->data[pq->size] = element;
        pq->size++;
        pq_heapify_upMin(pq, pq->size - 1);
    }
}

void *pq_pop(PriorityQueue *pq) {
    if (pq->size == 0) return NULL;

    void *top = pq->data[0];
    pq->size--;
    if (pq->size > 0) {
        pq->data[0] = pq->data[pq->size];
        pq_heapify_down(pq, 0);
    }
    return top;
}

int pq_is_empty(const PriorityQueue *pq) {
    return pq->size == 0;
}

int get_pq_size (const PriorityQueue *pq) {
    return pq->size;
}

const void *get_pq_data (const PriorityQueue *pq, int i) {
    if (!pq->data || i<0 || pq->size <= i) return NULL;
    return pq->data[i];
}