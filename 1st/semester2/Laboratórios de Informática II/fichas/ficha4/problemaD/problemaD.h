#ifndef PROBLEMAD_H
#define PROBLEMAD_H

typedef struct {
    int L;  
    int C;  
    int R;  
} Triplo;

typedef struct {
    int linhas;
    int colunas;
    int xInicial;
    int yInicial;
    int numTriplos;
    Triplo *triplos;
} Tabuleiro;

typedef struct {
    int x;  
    int y; 
} Posicao;

typedef struct {
    int caso;               
    int numElementos;  
    int size;     
    Posicao* posicoes;      
} Caso;

int processaCasos(Tabuleiro *tabuleiros, Caso *casos,int j);
void imprimeCasos (Caso c[],int N);
void swap (Posicao p[],int x,int y);
int partition (Posicao p[],int N,Posicao *pnova);
void ordenaPosicoes (Posicao p[],int N);
void ordenaCaso (Caso *c);
void inicializaCaso (Caso *c,int indice);
int posicaoJaAdicionada (Caso *c,int x,int y);
int dentroTabuleiro (Tabuleiro *t,int x,int y);
int adicionaPosicao (Caso *c,int x,int y);
int geraPosicoes (Tabuleiro *t,Caso *c, Triplo triplo);
void geraCaso (Tabuleiro *t,Caso *c);
void libertaTabuleiros(Tabuleiro *t, int N);
void libertaCasos(Caso *c, int N);



#endif