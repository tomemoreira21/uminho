#ifndef PROBLEMAE_H
#define PROBLEMAE_H

typedef struct {
    int L;  
    int C;  
    int R;  
} Triplo;

typedef struct tabuleiro {
    int linhas;
    int colunas;
    char **tabuleiro;
} *Tabuleiro;

typedef struct caso {
    int xInicial;
    int yInicial;
    int xFinal;
    int yFinal;
    int numTriplos;
    char *caminho;
    Triplo *triplos;
} *Caso;

typedef struct posicao {
    int x;
    int y;
    int indiceLetra; 
    int visitadosLocais[40][40];  
} *Posicao;

typedef struct queue {
    Posicao *valores;
    int frente;
    int atras;
    int size;
} *Queue;


typedef struct casos {              
    int numCasos;
    int size;     
    Caso *caso;      
} *Casos;


void imprimeResultado (Tabuleiro t,Casos casos);
Queue inicializaQueue ();
int ***inicializaVisitados(int linhas, int colunas, int lenCaminho);
char *leCaminho();
int queueVazia (Queue q);
void pushQueue (Queue q,Posicao p);
Posicao popQueue (Queue q);
void repoeVisitados(int ***v, int linhas, int colunas, int lenCaminho);
int dentroTabuleiro (Tabuleiro t,int l,int c);
int geraMovimentosTriplo (Triplo triplo,int movimentos[8][2]);
int adicionaValido(Queue q, int nx, int ny, int proxIndice, Posicao p);
int verificaPosicao (Tabuleiro t, Caso c, Queue q, int ***visitados, Posicao p);
int verificaTrajeto(Tabuleiro t, Caso c);

// Leitura na Main
int leTabuleiro (Tabuleiro t);
int processaCaso (Caso c);
int processaCasos (Casos c);
Casos inicializaCasos(int N);
void liberaQueue (Queue q);
void liberaValoresQueue (Queue q);
void liberaVisitados(int ***visitados, int linhas,int colunas);
void liberaTabuleiro(Tabuleiro t);
void liberaCasos (Casos c);


#endif