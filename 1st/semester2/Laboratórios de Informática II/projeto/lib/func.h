#ifndef FUNC_H
#define FUNC_H

typedef struct tabuleiro {
    int linhas;
    int colunas;
    char **tabuleiro;
} *Tabuleiro;

typedef struct jogada{
    int marcador; // marcador (= 0 jogadas individuais) (>0 jogadas coletivas)
    int l;
    int c;
    char letraAnterior;
} *Jogada;

typedef struct stack{
    int sp;
    int size;
    int grupoAtual;
    Jogada *jogadas;
} *StackJogadas;

typedef struct coodenadas{
    int linha;
    int coluna;
}Coordenada;

typedef enum tipo_erro {
    ERRO_DUPLICADO_BRANCO_LINHA, // na mesma linha tem a mesma letra em branco  
    ERRO_DUPLICADO_BRANCO_COLUNA, // na mesma coluna tem a mesma letra em branco
    ERRO_DUPLICADO_BRANCO_LINHA_COLUNA, // // na mesma linha e na mesma coluna tem a mesma letra em branco
    ERRO_FALTA_RISCAR_LINHA, // na mesma linha falta riscar a letra minuscula
    ERRO_FALTA_RISCAR_COLUNA, // na mesma coluna falta riscar a letra minuscula
    ERRO_FALTA_RISCAR_LINHA_COLUNA, // na mesma linha e na mesma coluna falta riscar a letra minuscula
    ERRO_VIZINHO_NAO_BRANCO,  // está riscada mas os vizinhos não está todos a branco
    ERRO_VIZINHO_RISCADO, // está riscada e os dos vizinhos está riscado também
    ERRO_NENHUM
} TipoErro;

typedef struct lista {
    int l;
    int c;
    TipoErro erro;
    struct lista *prox;
} *ListaConflitos;

typedef struct jogo {
    int estadoJogo; // 0 se o jogo não tem minúsculas, e será 1 caso contrário 
    int venceu;
    Tabuleiro tabuleiro;
} *Jogo;

// Tarefa1 
int leLinha(char *coordenada);
int devolveJogada(Tabuleiro t,Jogada j,char *coordenada);
void inicializaStack (StackJogadas s);
void inicializaJogo (Jogo j);
int comandoB(StackJogadas s, Tabuleiro t, char *coordenada, int m);
int comandoR (StackJogadas s,Tabuleiro t,char *coordenada, int m);
int comandoG (Tabuleiro t, char *str);
int comandoL (Tabuleiro t, char *str);
int comandoL(Tabuleiro t,char *str);
int gravarJogo (Tabuleiro t,char *nomeFicheiro);
int clearFicheiro(char *nomeFicheiro);
void pushJogada (StackJogadas s,Jogada j);
int addMaiuscula (StackJogadas s,Tabuleiro t,Jogada j, int m);
int addRiscar(StackJogadas s, Tabuleiro t,Jogada j, int m);
int coordValida(int linhas, int colunas,int l, int c);
int comandoRBValido(Tabuleiro t, int l, int c);
void liberaTabuleiro (Tabuleiro t);
void liberaJogadas (StackJogadas s);
void liberaStack (StackJogadas s);

// Tarefa2
ListaConflitos insereOrdenado(ListaConflitos lista, int linha, int coluna, TipoErro erro);
ListaConflitos verificaConflitos (Tabuleiro t,ListaConflitos lista);
TipoErro verificarRiscadas (Tabuleiro t,int i,int j);
TipoErro verificarVizinhosBrancos (Tabuleiro t,int i,int j);
TipoErro verificarRepeticoes(Tabuleiro t, int i, int j, char atual);
TipoErro verificarFaltaRiscar(Tabuleiro t, int i, int j, char atual);
void liberaLista(ListaConflitos lista);
void undoStack (Tabuleiro t,StackJogadas s);
int comandoD (Tabuleiro t,StackJogadas s);

// Tarefa3
int existeCaminho (Tabuleiro t);

// Tarefa4
int ajudaUtilizador (StackJogadas s, Tabuleiro t,ListaConflitos lista,int m);
Jogada devolveJogadaAjuda (Tabuleiro t, int l, int c);
int ajudaPintarVizinhosNaoBranco (StackJogadas s,Tabuleiro t,int i,int j);
int ajudaRiscarDuplicadosColuna (StackJogadas s,Tabuleiro t,int i,int j);
int ajudaRiscarDuplicadosLinha (StackJogadas s,Tabuleiro t,int i,int j);
int ajudaRiscarDuplicadosLinhaColuna (StackJogadas s, Tabuleiro t, int i, int j);
int ajudaRiscarLinha (StackJogadas s,Tabuleiro t,int i,int j);
int ajudaRiscarColuna (StackJogadas s,Tabuleiro t,int i,int j);
int ajudaRiscarLinhaColuna (StackJogadas s, Tabuleiro t, int i, int j);
int addBrancoRiscar(StackJogadas s, Tabuleiro t, Jogada j, int m);
int ajudaIsolarNaoBranco (StackJogadas s,Tabuleiro t);
int permiteRiscar (Tabuleiro t, int i, int j);
int comandoA(StackJogadas s, Tabuleiro t,int m);

// Tarefa5
int jogoResolvido (Tabuleiro t,ListaConflitos lista);
int letraRepeteNaLinhaOuColuna(Tabuleiro t, int i, int j);
Jogada copiaJogada(Jogada j);
void desfazStack(StackJogadas s, Tabuleiro t);
int resolveJogo(Tabuleiro t, StackJogadas s);
void recuperaTabuleiroInicial(Tabuleiro t, StackJogadas s);
Tabuleiro copiaTabuleiro (Tabuleiro t);
int resolveJogoEstadoInvalido (Tabuleiro t, StackJogadas s);
int possuiConflitos (Tabuleiro t, ListaConflitos* lista);
void pintarMaisPropagacao (Tabuleiro t,StackJogadas s,Jogada jog,int *alteracoes);
void riscarMaisPropagacao (Tabuleiro t,StackJogadas s,Jogada jog,int *alteracoes,int *jogadaFoiRiscada,int topoStackAntes);
void backTrack (Tabuleiro t,StackJogadas s,int topoStackAntes);
int contaMin (Tabuleiro t);
void verificaEstadoJogo (Jogo jogo);
void verificaVitoria (Jogo j,ListaConflitos lista);

// Interface
void imprimeTabuleiro (Tabuleiro t);
void imprimirConflitos(ListaConflitos lista, Tabuleiro t);
void imprimeErroDuplicadoBranco(int i, int j, char letra, TipoErro erro, int letrasRepetidasLinha[][26], int letrasRepetidasColuna[][26]);
void imprimeErroFaltaRiscar(int i, int j, char letra, TipoErro erro,int letrasRepetidasLinha[][26], int letrasRepetidasColuna[][26]);
void imprimeErroVizinhanca(int i, int j, TipoErro erro);
void imprimeResultado(Jogo j);
void imprimeAjuda (StackJogadas s,Tabuleiro t,int topoStackAntes,int topoStackApos);
void printMenu();
void printComandos();
void printRegras();
void jogo (Jogo j,StackJogadas s, ListaConflitos lista);

// Extra
int gravaStack (StackJogadas s, char *nomeFicheiro, char *nomeTabuleiro);
int restauraStack(StackJogadas s, char *nomeFicheiro, char *nomeTabuleiro);

// Repl
int tentarRestaurarJogo(Jogo j, StackJogadas s, char *nomeFicheiroSave,char *nomeTabuleiro);
void processaComando(char comando, Jogo j, StackJogadas s, char *nomeTabuleiro, ListaConflitos *lista);
void leituraInicialJogo(Jogo j,int *leJogo, int *jogoAtivo, char *nomeTabuleiro);
void encerraJogo(Jogo j,StackJogadas s,ListaConflitos *lista, char *nomeTabuleiro,int *jogoAtivo);
void trataComandoB(StackJogadas s, Tabuleiro t);
void trataComandoR(StackJogadas s, Tabuleiro t);
void trataComandoG(Jogo j, StackJogadas s);
void trataComandoD(Jogo j, StackJogadas s);
void trataComandoV(Jogo j, ListaConflitos *lista);
void trataComandoAjuda(Jogo j, StackJogadas s, ListaConflitos *lista);
void trataComandoA(StackJogadas s, Tabuleiro t);
void trataComandoResolve(Jogo j, StackJogadas s, ListaConflitos *lista);
void trataComandoNovoJogo(Jogo j, StackJogadas s,char *nomeTabuleiro);
void comandosJogo (Jogo j, StackJogadas s); 

#endif