#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// 1
int perfeito (int x) {
    int soma = 0;

    for (int i = 1; i < x; i++) {
        if (x % i == 0) soma += i;
    }
    
    return (x == 1 || soma == x);
}

// 2
typedef struct {
    int x,y;
} Ponto;

void swap (Ponto pos[],int x,int y) {
    Ponto temp = pos[x];
    pos[x] = pos[y];
    pos[y] = temp;
}

int partition (Ponto pos[],int N,int d) {
    int i = 0;

    for (int j = 0; j < N; j++) {
        int dist = pos[j].x * pos[j].x + pos[j].y * pos[j].y;
        if (dist <= d) {
            swap (pos,i,j);
            i++;
        } 
    }
    
    return i;
}

void ordena(Ponto pos[], int N) {
    if (N > 1) {
        int p = partition (pos,N-1,pos[N-1].x * pos[N-1].x + pos[N-1].y * pos[N-1].y);
        swap (pos,p,N-1);
        ordena (pos,p);
        ordena (pos + p + 1, N - p - 1);
    }
}

// 3
typedef struct abin_nodo {
    int valor;
    struct abin_nodo *esq, *dir;
} *ABin;

int depth(ABin a, int x) {
    if (a == NULL) return -1;
    if (a->valor == x) return 0;

    int rE = depth (a->esq,x);
    int rD = depth (a->dir,x);

    if (rE == -1 && rD == -1) return -1;
    else if (rE != -1) return 1 + rD;
    else if (rD != -1) return 1 + rE;
    else return (1 + (rE < rD) ? rE : rD);
}

// 4
int wordle(char secreta[], char tentativa[]) {
    int p,i,j;
    int c = 0;

    for (j = 0; tentativa[j] != '\0';j++) {
        p = 0;
        for (i = 0; secreta[i] != '\0';i++) {
            if (tentativa[j] == secreta[i]) {
                if (i == j) {
                    tentativa[j] = toupper (tentativa[j]);
                    c++;
                } 
                p++;
            }
        }

        if (p == 0) tentativa[j] = '*';
    }

    return c;
}

// 5
typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;

LInt periodica(char s[]) {
    LInt r = NULL,*ptr = &r;
    int i = 0;

    while (s[i] != '\0' && s[i] != '(') {
        LInt novo = malloc (sizeof (struct lint_nodo));
        novo->valor = s[i] - '0';
        novo->prox = NULL;
        *ptr = novo;

        ptr = & ((*ptr)->prox);
        
        i++;
    }

    LInt cicloInicio = NULL;

    if (s[i] == '(') {
        i++; 
        cicloInicio = *ptr;

        while (s[i] != '\0' && s[i] != ')') {
            LInt novo = malloc(sizeof(struct lint_nodo));
            novo->valor = s[i] - '0';
            novo->prox = NULL;

            *ptr = novo;
            ptr = &((*ptr)->prox);
            i++;
        }

        *ptr = cicloInicio; 
    }

    return r;
}
 
// Função para descobrir se os elementos de um mesmo nivel são todos iguais
void aBinToArray(ABin a, int n, int v[], int *e) {
    if (a == NULL) return;

    if (n == 0) {
        v[*e] = a->valor;
        (*e)++;
    } else {
        aBinToArray(a->esq, n - 1, v, e);
        aBinToArray(a->dir, n - 1, v, e);
    }
}

int comparaElemIguais (int v[],int N) {
    if (N == 0) return 1;
    
    int elem = v[0];

    for (int i = 1; i < N; i++) {
        if (v[i] != elem) return 0;
    }

    return 1;
}

int todosIguais (ABin a,int n) {
    int v[1024];
    
    int e = 0;
    aBinToArray (a,n,v,&e);

    return (comparaElemIguais (v,e));
}




// Funções auxiliares
void imprimePos (Ponto pos[],int N) {

    putchar ('{');
    for (int i = 0; i < N; i++) {
        printf ("(%d,%d)%c",pos[i].x,pos[i].y,(i == N - 1) ? '}' : ',');
    }
    putchar ('\n');
}


int main () {
    // 1
    printf ("Número 28: %d\n",perfeito (28));
    printf ("Número 14: %d\n",perfeito (14));

    // 2
    Ponto v[3] = {{3,3}, {2,1}, {-1,0}};
    ordena (v,3);
    imprimePos (v,3);

    // 4
    char v1[] = "cerejas",v2[] = "bananas";
    printf ("laranja -> cerejas: %d\n",wordle ("laranja",v1));
    printf ("Resultado: %s\n",v1);
    printf ("laranja -> bananas: %d\n",wordle ("laranja",v2));
    printf ("Resultado: %s\n",v2);


    return 0;
}