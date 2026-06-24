#include "stdio.h"
#include "stdlib.h"

#define NV 10

typedef struct aresta {
    int dest; int custo;
    struct aresta *prox; 
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];

// REPRESENTAÇÕES
// 1
void addEdge (GrafoL g,int or,int dest,int custo) {
    LAdj new = malloc (sizeof (struct aresta));
    new->custo = custo;
    new->dest = dest;
    new->prox = g[or];
    g[or] = new;
}


void fromMat (GrafoM in,GrafoL out) {
    for (int i = 0; i < NV; i++)
        out[i] = NULL;

    for (int or = 0; or < NV; or++) {
        for (int dest = 0; dest < NV; dest++) {
            if (in[or][dest] == 1) 
                addEdge (out,or,dest,0);
        }
    }
}

// 2
void inverteL (GrafoL in,GrafoL out) {
    for (int i = 0; i < NV; i++)
        out[i] = NULL;
    
    for (int or = 0; or < NV; or++) {
        for (LAdj l = in[or]; l != NULL; l = l->prox) {
            addEdge (out,l->dest,or,l->custo);
        }
    }
}

void inverteM (GrafoM in, GrafoM out) {
    for (int or = 0; or < NV; or++) {
        for (int dest = 0; dest < NV; dest++) {
            out[or][dest] = in[dest][or];
        }
    }
}

// 3
int inDegree (GrafoL g) {
    int entrada[NV], maxDegree = 0;

    for (int i = 0; i < NV; i++) entrada[i] = 0;

    for (int or = 0; or < NV; or++) {
        for (LAdj l = g[or]; l != NULL; l = l->prox) {
            int v = l->dest;
            entrada[v] = entrada[v] + 1;
            if (entrada[v] > maxDegree) maxDegree = entrada[v];
        }
    }

    return maxDegree;
}

// 4
// devolve 0 se está tudo ok, caso contrário devolve 1
int colorOK (GrafoL g,int cor[]) {

    for (int or = 0; or < NV; or++) {
        int cor_u = cor[or];
        for (LAdj l = g[or]; l != NULL; l = l->prox) {
            int cor_v = cor[l->dest];

            if (cor_u == cor_v) return 1;
        }
    }

    return 0;
}

// 5
// devolve 1 se há a aresta or -> dest, senão devolve 0
int lookupEdge (GrafoL g,int or,int dest) {
    for (LAdj l = g[or]; l != NULL; l = l->prox) 
        if (l->dest == dest) return 1;

    return 0;
}

// devolve 0 se é homomorfismo, caso contrário devolve 1
int homomorfOK (GrafoL g,GrafoL h,int f[]) {
    
    for (int or = 0; or < NV; or++) {
        for (LAdj l = g[or]; l != NULL; l = l->prox) {
            int dest = l->dest;
            if (!lookupEdge (h,f[or],f[dest])) return 1;
        }
    }

    return 0;
}

// TRAVESSIAS
/*
p[] -> array que guarda os seus pais
l[] -> guarda a distância ao or
v[] -> array de visitados 
    - -1 -> equivale ao cinzento ou seja está a ser visitado
    - 0 -> ainda não foi visitado
    - 1 -> signifca que já foi visitado ele e os filhos 
*/

// Algoritmo de DFS
int DFRec (GrafoL g, int or,int v[],int p[],int l[]){
    int i; LAdj a;
    i = 1;
    v[or] = -1;
    for (a=g[or];a!=NULL;a=a->prox) {
        if (!v[a->dest]){
            p[a->dest] = or;
            l[a->dest] = 1+l[or];
            i+=DFRec(g,a->dest,v,p,l);
        }
    }

    v[or] = 1;
    return i;
}

int DF (GrafoL g, int or,int v[],int p[],int l[]){
    int i;
    for (i=0; i<NV; i++) {
        v[i]= 0 ;
        p[i] = -1;
        l[i] = -1;
    }

    p[or] = -1; l[or] = 0;
    return DFRec (g,or,v,p,l);
}

// Algortimo de BFS
int BF (GrafoL g, int or,int v[],int p[],int l[]){
    int i, x; LAdj a;
    int q[NV], front, end;
    for (i=0; i<NV; i++) {
        v[i]= 0;
        p[i] = -1;
        l[i] = -1;
    }

    front = end = 0;
    q[end++] = or; //enqueue
    v[or] = 1; l[or]=0; p[or]=-1; //redundante
    i=1;

    while (front != end){
        x = q[front++]; //dequeue
        for (a=g[x]; a!=NULL; a=a->prox)
            if (!v[a->dest]){
                i++;
                v[a->dest]=1;
                p[a->dest]=x;
                l[a->dest]=1+l[x];
                q[end++]=a->dest; //enqueue
        }
    }

    return i;
}

// 1
int maisLonga (GrafoL g,int or,int p[]) {
    int q[NV], v[NV],l[NV], prev[NV],front, end,u;
    for (int i=0; i<NV; i++) {
        v[i]= 0;
        prev[i] = -1;
        l[i] = -1;
    }

    front = end = 0;
    q[end++] = or; //enqueue
    v[or] = 1; l[or] = 0; prev[or]=-1; //redundante

    int maxDist = 0;
    int maisLonge = or;

    while (front != end) {
        u = q[front++]; // dequeue

        for (LAdj a = g[u]; a != NULL; a = a->prox) {
            int d = a->dest;

            if (v[d] == 0) {
                v[d] = 1;
                l[d] = l[u] + 1;
                prev[d] = u;
                q[end++] = d;
                
                if (l[d] > maxDist) {
                    maxDist = l[d];
                    maisLonge = d;
                }
            }
        }
    }

    int lenMax = maxDist;
    int cur = maisLonge;

    for (int r = lenMax; r >= 0; r--) {
        p[r] = cur;
        cur = prev[cur];
    }

    return maxDist;
}

// 2
// undirected graph
// DFS -> usado para perceber estrutura dos grafos
void dfs_visit(GrafoL g,int or, int v[],int c[],int e) {
    v[or] = 1;
    c[or] = e;

    for (LAdj l = g[or]; l != NULL; l = l->prox) {
        int d = l->dest;
        if (v[d] == 0) 
            dfs_visit (g,d,v,c,e);
    }
}

int componentes (GrafoL g,int c[]) {
    int comp = 0;
    int v[NV];

    for (int i = 0; i < NV; i++) {
        c[i] = -1;
        v[i] = 0;
    }

    for (int or = 0; or < NV; or++) {
        if (v[or] == 0) {
            comp++;
            dfs_visit(g,or,v,c,comp);
        }
    }

    return comp;
}

// 3
void dfsTop (GrafoL g,int or,int v[],int ord[],int *pos) {
    v[or] = -1;

    for (LAdj l = g[or]; l != NULL; l = l->prox) {
        int d = l->dest;
        if (v[d] == 0)
            dfsTop (g,d,v,ord,pos);
    }

    v[or] = 1;
    ord[--(*pos)] = or;
}

int ordTop (GrafoL g,int ord[]) {
    int v[NV];
    int pos = NV;
    
    for (int i = 0; i < NV; i++) {
        v[i] = 0;
        ord[i] = -1;
    }

    for (int or = 0; or < NV; or++) {
        if (v[or] == 0)
            dfsTop (g,or,v,ord,&pos);
    }

    return 0;
}

// 4.
// devolve d onde foi detatado o ciclo, -1 se não tem ciclo
int cicloDfs (GrafoL g,int or,int v[],int p[]) {
    v[or] = -1;

    for (LAdj l = g[or]; l != NULL; l = l->prox) {
        int d = l->dest;
        p[d] = or;

        if (v[d] == -1) return d;

        if (v[d] == 0) 
            if (!cicloDfs (g,d,v,p)) return d;
    }

    v[or] = 1;

    return -1;
}

int ciclo (GrafoL g,int c[]) {
    int v[NV],p[NV];

    for (int i = 0; i < NV; i++) {
        v[i] = 0;
        p[i] = -1;
    }

    for (int or = 0; or < NV; or++) {
        if (v[or] == 0) {
            int d = cicloDfs(g,or,v,p);
            if (d != -1) { // há ciclo 

                int k = 0;
                int start = d;
                c[k++] = start;

                int u = p[start];
                while (u != start) {
                    c[k++] = u;
                    u = p[u];
                }
            
                return k; // retorna o número de vértices no ciclo
            }
        }
    }

    return 0;
}

// 5
// usando BFS
int caminhoDFS (int L,int C,char *mapa[L],int v[L][C],int ls,int cs,int lf,int cf) {
    v[ls][cs] = -1;
    printf ("(%d,%d) -> ",ls,cs);

    int mov[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    
    for (int i = 0; i < 4; i++) {
        int x = ls + mov[i][0];
        int y = cs + mov[i][1];

        if (x == lf && y == cf) return 1;

        if (!v[x][y]) {
            if (mapa[x][y] != '#') 
                return 1 + caminhoDFS(L,C,mapa,v,x,y,lf,cf);
        }

    }

    v[ls][cs] = 1;
}

typedef struct {
    int x,y,dist;
} Node;

int caminho (int L,int C,char *mapa[L],int ls,int cs,int lf,int cf) {
    int v[L][C];

    for (int j = 0; j < L; j++) {
        for (int i = 0; i < C; i++) {
            v[j][i] = 0;
        }
    }

    int mov[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    Node queue[L*C];
    int front = 0, end = 0;
    queue[end++] = (Node){ls,cs}; //enqueue
    v[ls][cs] = 1;

    while (front != end) {
        Node u = queue[front++];

        if (u.x == lf && u.y == cf)
            return u.dist;

        for (int i = 0; i < 4; i++) {
           int x = u.x + mov[i][0];
           int y = u.y + mov[i][1];

           if (x >= 0 && x < L && y >= 0 && y < C) {
             if (!v[x][y]) {
                if (mapa[x][y] != '#') {
                    v[x][y] = 1;
                    queue[end++] = (Node){x,y,u.dist + 1};
                }
             }
          }
        }
    }
    
    return -1; // se não existir caminho
}

// Grafo da imagem
void buildGraph(GrafoL g) {
    // Inicializar listas
    for (int i = 0; i < NV; i++)
        g[i] = NULL;

    // Arestas segundo a imagem:

    // 0 -> 1 (5)
    addEdge(g, 0, 1, 5);
    // 0 -> 3 (2)
    addEdge(g, 0, 3, 2);

    // 1 -> 4 (8)
    addEdge(g, 1, 4, 8);

    // 2 -> 5 (2)
    addEdge(g, 2, 5, 2);
    // 2 -> 9 (2)
    addEdge(g, 2, 9, 2);

    // 3 -> 6 (2)
    addEdge(g, 3, 6, 2);

    // 5 -> 8 (8)
    addEdge(g, 5, 8, 8);

    // 6 → 7 (1)
    addEdge(g, 6, 7, 1);

    // 7 -> 3 (2)
    addEdge(g,7,3,2);

    // 7 -> 4 (7)
    addEdge(g,7,4,7);

    // 8 -> 4 (3)
    addEdge(g,8,4,3);

    // 8 → 9 (4)
    addEdge(g, 8, 9, 4);
}

// Função de print de um grafo
void dumpG (GrafoL g){
    int i; LAdj p;
    for (i=0; i<NV; i++){
        printf ("%d -> ", i);
        for (p=g[i]; p; p=p->prox)
            printf ("%d (%d) ", p->dest, p->custo);
        putchar('\n');
    }
}

int main () {
    GrafoL g,g1;
    buildGraph(g);

    char *mapa [10] = {"##########"
                        ,"# #   #  #"
                        ,"# # # #  #"
                        ,"#   # #  #"
                        ,"##### #  #"
                        ,"#     #  #"
                        ,"## ####  #"
                        ,"#  #     #"
                        ,"#     #  #"
                        ,"##########"};

    // 1.   
    inverteL(g,g1);
    dumpG(g1);

    // 2.
    printf ("\ninDegree: %d\n",inDegree(g));

    // TRAVESSIAS
    // 1.
    int p[NV];
    int max = maisLonga (g,0,p);
    printf ("\nmaisLonga: %d\n",max);
    for (int i = 0; i < max; i++) {
        printf("%d ",p[i]);
    }
    putchar('\n');

    // 2.
    int c[NV];
    int comp = componentes(g,c);
    printf ("\nnºcomponentes: %d\n",comp);
    for (int i = 0; i < NV; i++) {
        printf (" %d",c[i]);
    }
    putchar('\n');

    // 3.
    int ord[NV];
    ordTop (g,ord);

    printf ("\nOrdem Topológica: ");
    for (int i = 0; i < NV; i++) {
        printf ("%d ",ord[i]);
    }
    putchar('\n');

    // 5.
    int v[10][10];
    int passos = caminho(10,10,mapa,1,1,1,8);
    printf ("\nCaminho: %d\n",passos);


    return 0;
}