#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define Max 100

typedef struct pQueue {
    int valores [Max];
    int tamanho;
} PriorityQueue;

// 1 Min-Heaps
/*
Invariante de ordem
O valor associado a cada nó é inferior ou igual a todos os seus valores descendentes

Invariante de forma 
A arvóre binária é completa (apenas o último nível pode não estar totalmente preenchido)

filho esq - 2*i + 1 
filho dir - 2*i + 2
pai - (i-1)/2
1ºfolha - N/2

*/

// 2
void swap (int h[],int x,int y) {
    int temp = h[x];
    h[x] = h[y];    
    h[y] = temp;
}

void bubbleUp (int i, int h[]) {
    int pai = (i-1)/2;
    
    while (i > 0 && h[pai] > h[i]) {
        swap (h,pai,i);
        i = pai;
        pai = (i-1)/2;
    }
}

// Pior caso: ocorre quando o elemento que se encontra na posição i é menor elemento do heap 
// Desta forma vai executar: O(log(i)) trocas/comparações

// 3
void bubbleDown (int i,int h[],int N) {
    int esq = 2*i+1;
    int dir = 2*i+1;
    int min = i;

    if (esq < N && h[esq] < h[i]) i = esq;
    if (dir < N && h[dir] < h[i]) i = dir;
    
    if (min != i) {
        swap (h,min,i);
        bubbleDown (i,h,N-1);
    }
}

// 4
void empty (PriorityQueue *q) {
    q->tamanho = 0;
}

int isEmpty (PriorityQueue *q) {
    return (q->tamanho == 0);
}

int addPQ (int x,PriorityQueue *q) {
    if (q->tamanho == Max) return 1;

    int i = q->tamanho; 
    q->valores[i] = x;
    bubbleUp (i,q->valores);
    q->tamanho++;
    return 0;
}

int removePQ (PriorityQueue *q,int *rem) {
    if (q->tamanho == 0) return 1;

    *rem = q->valores[0];
    swap (q->valores,0,q->tamanho-1);
    q->tamanho--;
    bubbleDown (0,q->valores,q->tamanho);
    return 0;
}

// 5
// top-down
void heapify_v1 (int v[],int N) {
    for (int i = 1; i < N; i++) {
        bubbleUp (i,v);
    }
}

// Ordem decrescente: sum {1 <= k <= N} i = O(N²)

// bottom-up
void heapify_v2 (int v[],int N) {
    for (int i = N/2 -1 ; i >= 0; i--) {
        bubbleDown (i,v,N);
    }
}

// Ordem decrescente: O(N) 

// 6
void ordenaHeap (int h[],int N) {
    for (int i = 0; i < N-1; i++) {
        // Move o menor elemento (raiz) para a última posição livre
        swap (h,0,N-i-1);

        // Restaura a min-heap na parte útil do array
        bubbleDown (0,h,N-i-1);
    }
}

// 7
/*
Uma solução possı́vel consiste em começar por ler os k primeiros elementos e organizá-
los numa min-heap. Para cada um dos N − k seguintes, caso seja maior do que o menor
dos números organizados, insere-se esse elemento na min-heap, removendo o menos dos
que lá estão.

1ºsolução

1º ler os k primeiros -> O(k)
2º fazer as trocas do N-k elementos -> (N-k)log(k)
pelo que no pior caso:
    -> Tpc(N) = O(k) + (N-k)log(k) = O(Nlog(k))

2ºsolução

A lista tem no máximo k elementos, então:

 -> Percorrer a lista: O(k)
 -> Inserir no ponto encontrado: O(1)

➡ Custo por inserção = O(k)

Cada um dos N números é processado com custo O(k). Pelo que:

Tpc(N) = O(Nk)
*/

// 2 Tabelas de Hash
unsigned hash(char *str){
    unsigned hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    
    return hash;
}
// 2.1 Chaining 
#define Size 10
typedef struct nodo {
    char *chave; 
    int ocorr;
    struct nodo *prox;
} Nodo, *THashC [Size];

// 1
void initEmptyC(THashC t) {
    for (int i = 0; i < Size; i++)
        t[i] = NULL;
}

// 2
void addC (char *s,THashC t) {
    int idx = hash(s) % Size;
    Nodo *node = t[idx];

    while (node != NULL) {
        if (strcmp (node->chave,s) == 0) {
            node->ocorr++;
            return;
        }

        node = node->prox;
    }

    Nodo *new = malloc (sizeof (struct nodo));
    if (new == NULL) return;
    new->chave = strdup (s);
    new->ocorr = 1;
    new->prox = t[idx];

    t[idx] = new;
}

// 3
// retorna 0 se o elemento não ocorre
int lookupC (char *s,THashC t) {
    int idx = hash(s) % Size;
    Nodo *node = t[idx];

    while (node != NULL) {
        if (strcmp (node->chave,s) == 0)
            return node->ocorr;

        node = node->prox;
    }

    return 0;
}

// 4
// devolve 0 se consegue remover, e devolve 1 se não existir o elem
int removeC (char *s,THashC t) {
    int idx = hash(s) % Size;
    Nodo **node = &t[idx];

    while (*node != NULL) {
        if (strcmp ((*node)->chave,s) == 0) {
            (*node)->ocorr--;
            if ((*node)->ocorr == 0) {
                Nodo *temp = *node;
                *node = (*node)->prox;
                free(temp);
            }

            return 0;
        }

        node = &((*node)->prox);
    }

    return 1;
}


// 2.2 Open Addressing
#define Free 0
#define Used 1
#define Del 2
typedef struct bucket {
    int status; // Free | Used | Del
    char *chave; int ocorr;
} THashO [Size];

// 1
int where (char *s,THashO t) {
    return (hash (s) % Size);
}

// 2 
// a)
void initEmptyO (THashO t) {
    for (int i = 0; i < Size; i++) {
        t[i].chave = NULL;
        t[i].status = Free;
        t[i].ocorr = 0;
    }
}

// b)
void addO (char *s,THashO t) {
    int idx = where(s,t);
    int del = -1,k;

    for (int i = 0; i < Size; i++) {
        k = (idx + i) % Size;
        if (t[k].status == Used) {
            if (strcmp (t[k].chave,s) == 0) {
                t[k].ocorr++;
                return;
            }
        } 

        if (t[k].status == Free) break;

        if (t[k].status == Del && del == -1)
            del = k;
    }

    if (del == -1) {
        t[k].chave = strdup (s);
        t[k].ocorr = 1;
        t[k].status = Used;
    } else {
        t[del].chave = strdup (s);
        t[del].ocorr = 1;
        t[del].status = Used;
    }
}

// c)
// devolve 0 se não encontrar o elemento
int lookupO (char *s,THashO t) {
    int idx = where(s,t);

    for (int i = 0; i < Size; i++) {
        int k = (idx + i) % Size;

        if (t[k].status == Free) return 0;

        if (t[k].status == Used && strcmp (t[k].chave,s) == 0) 
            return t[k].ocorr;
    }
    
    return 0;
}

// d)
// devolve 0 se conseguiu remover, 1 em caso contrário
int removeO (char *s,THashO t) {
    int idx = where(s,t);
    
    for (int i = 0; i < Size; i++) {
        int k = (idx + i) % Size;

        if (t[k].status == Free) return 1;

        if (t[k].status == Used && strcmp (t[k].chave,s) == 0) {
            t[k].ocorr--;
            if (t[k].ocorr == 0) 
                t[k].status = Del;
                    
            return 0;
        }
        
    }

    return 1;
}

// Função auxiliar de dar print da tabela de hash de chaining
void imprime_THashC (THashC t) {
    for (int i = 0; i < Size; i++) {
        printf("%d\t", i);

        Nodo *list = t[i];
        if (list == NULL) {
            printf("---");
        } else {
            while (list != NULL) {
                printf ("%s (%d) -> ",list->chave,list->ocorr);
                list = list->prox;
            };

            printf ("NULL");
        }
        putchar('\n');
    }
}

// Função auxiliar de dar print da tabela de hash de open addressing
char *int_to_string (int v) {
    switch (v) {
        case Free: return "Free";
        case Used: return "Used";
        case Del:  return "Del";
        default:   return "???";
    }
}

void imprime_THashO (THashO t) {
    for (int i = 0; i < Size; i++) {
        printf ("%d\t",i);

        if (t[i].status == Used) 
            printf ("%s (%d) - %s\n",t[i].chave,t[i].ocorr,int_to_string(t[i].status));
        else  
            printf ("%s\n",int_to_string(t[i].status));
    }
}

// 3
//  devolve quantos elementos ficaram na hash table final
int garb_collection (THashO t) {
    THashO temp;
    initEmptyO (temp);
    int count = 0;

    for (int i = 0; i < Size; i++) {
        if (t[i].status == Used) {
            addO (t[i].chave,temp);
            count ++;
        }
    }

    for (int k = 0; k < Size; k++) {
        t[k] = temp[k];
    }

    return count;
}

/*
Como função de inserção tende para ser constante temos TaddO(N) = O(1)
Pelo que como percorremos a hash table toda então:

T(N) = O(1 * N) = O(N)
*/

// 4. Está no caderno

// 5
// Informação extra
typedef struct bucketE {
    int idxHash; // onde mapeiou a hash table
    int probC;
    int status; // Free | Used | Del
    char *chave; int ocorr;
} THashE [Size];

void initEmptyE (THashE t) {
    for (int i = 0; i < Size; i++) {
        t[i].chave = NULL;
        t[i].ocorr = 0;
        t[i].probC = 0;
        t[i].status = Free;
    }
}

void addE (char *s, THashE t) {
    int idx = hash(s) % Size;
    int del = -1,k,col = 0;

    for (int i = 0; i < Size; i++) {
        k = (idx + i) % Size;

        if (t[k].status == Used) {
            if (strcmp(t[k].chave,s) == 0) {
                t[k].ocorr++;
                return;
            }
        }

        if (t[k].status == Free) break;

        if (t[k].status == Del && del == -1) del = k;

        col++;        
    }

    if (del == -1) {
        t[k].chave = strdup(s);
        t[k].ocorr = 1;
        t[k].idxHash = idx;
        t[k].probC = col;
        t[k].status = Used;
    } else {
        t[del].chave = strdup(s);
        t[del].ocorr = 1;
        t[del].idxHash = idx;
        t[del].probC = col;
        t[del].status = Used;
    }
}

// Função auxiliar de dar print da tabela de hash de open adressing com informação das colisões
void imprime_THashE (THashE t) {
    for (int i = 0; i < Size; i++) {
        printf ("%d\t",i);

        if (t[i].status == Used) 
            printf ("%s (%d) - %s - %d colisões - idx_inicial = %d\n",t[i].chave,t[i].ocorr,int_to_string(t[i].status),t[i].probC,t[i].idxHash);
        else  
            printf ("%s\n",int_to_string(t[i].status));
    }
}

int main() {
    printf("==== TESTE HASH TABLE — CHAINING ====\n\n");

    THashC tc;
    initEmptyC(tc);

    addC("ana", tc);
    addC("rui", tc);
    addC("maria", tc);
    addC("ana", tc);   // ocorrência extra
    addC("ze", tc);
    addC("rui", tc);   // ocorrência extra

    printf("Tabela após inserts:\n");
    imprime_THashC(tc);

    printf("\nlookupC(\"ana\") = %d\n", lookupC("ana", tc));
    printf("lookupC(\"ze\") = %d\n", lookupC("ze", tc));
    printf("lookupC(\"x\") = %d\n", lookupC("x", tc));

    printf("\nRemover 'rui'\n");
    removeC("rui", tc);
    imprime_THashC(tc);

    printf("\nRemover 'rui' novamente\n");
    removeC("rui", tc);
    imprime_THashC(tc);

    printf("\nRemover 'rui' mais uma vez (já não existe)\n");
    printf("removeC = %d\n\n", removeC("rui", tc));


    printf("\n\n==== TESTE HASH TABLE — OPEN ADDRESSING ====\n\n");

    THashO to;
    initEmptyO(to);

    addO("ana", to);
    addO("rui", to);
    addO("maria", to);
    addO("ana", to);    // ocorrência extra
    addO("ze", to);
    addO("rui", to);    // ocorrência extra

    printf("Tabela após inserts:\n");
    imprime_THashO(to);

    printf("\nlookupO(\"ana\") = %d\n", lookupO("ana", to));
    printf("lookupO(\"ze\") = %d\n", lookupO("ze", to));
    printf("lookupO(\"x\") = %d\n", lookupO("x", to));

    printf("\nRemover 'rui'\n");
    removeO("rui", to);
    imprime_THashO(to);

    printf("\nRemover 'rui' novamente\n");
    removeO("rui", to);
    imprime_THashO(to);

    printf("\nRemover 'rui' mais uma vez (já não existe)\n");
    printf("removeO = %d\n\n", removeO("rui", to));

    printf("\n\n==== TESTE HASH TABLE — OPEN ADDRESSING COM CONTAGEM DE COLISÕES ====\n\n");

    THashE te;
    initEmptyE(te);

    addE("ana", te);
    addE("rui", te);
    addE("maria", te);
    addE("ana", te);   // ocorrência extra
    addE("ze", te);
    addE("rui", te);   // ocorrência extra
    addE("julio", te);
    addE("luis", te);
    addE("vitor", te);
    addE("julio", te);   // ocorrência extra
    addE("carlos", te);
    addE("joana", te);   

    printf("Tabela após inserts (com probC e idxHash):\n");
    imprime_THashE(te);

    return 0;
}
