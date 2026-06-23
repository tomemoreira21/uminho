#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "func.h"

void imprimeTabuleiro (Tabuleiro t) {
    printf("    ");
    for (int i = 0; i < t->colunas; i++) {
        printf("%c ", 'a' + i);
    }
    putchar ('\n');

    printf("    ");
    for (int i = 0; i < t->colunas; i++) {
        printf("- ");
    }
    putchar('\n');

    for (int j = 0; j < t->linhas; j++) {
        printf("%2d  ", j); 
        for (int i = 0; i < t->colunas; i++) {
            printf("%c ", t->tabuleiro[j][i]);
        }
        putchar('\n');
    }
    putchar('\n');
}

void imprimirConflitos(ListaConflitos lista, Tabuleiro t) {
    int letrasRepetidasLinha[t->linhas][26];
    int letrasRepetidasColuna[t->colunas][26];
    memset (letrasRepetidasLinha,0,sizeof (letrasRepetidasLinha));
    memset (letrasRepetidasColuna,0,sizeof (letrasRepetidasColuna));
    
    ListaConflitos atual = lista;
    while (atual != NULL) {
        int i = atual->l;
        int j = atual->c;
        TipoErro erro = atual->erro;
        char letra = t->tabuleiro[i][j];

        if (isupper(letra)) {
            imprimeErroDuplicadoBranco(i, j, letra, erro, letrasRepetidasLinha, letrasRepetidasColuna);
            imprimeErroFaltaRiscar(i, j, letra, erro, letrasRepetidasLinha, letrasRepetidasColuna);
        } else imprimeErroVizinhanca(i, j, erro);  

    atual = atual->prox;
    }                
}

void imprimeErroDuplicadoBranco(int i, int j, char letra, TipoErro erro, int letrasRepetidasLinha[][26], int letrasRepetidasColuna[][26]) {
    int indice = letra - 'A';

    if (erro == ERRO_DUPLICADO_BRANCO_LINHA_COLUNA && !letrasRepetidasLinha[i][indice] && !letrasRepetidasColuna[j][indice]) {
        printf("\033[1;31m[ERRO]\033[0m Na linha %d e na coluna %c: Letra branca %c repetida na mesma linha e coluna.\n", i, 'A' + j, letra);
        letrasRepetidasLinha[i][indice] = 1;
        letrasRepetidasColuna[j][indice] = 1;
    } else if (erro == ERRO_DUPLICADO_BRANCO_LINHA && !letrasRepetidasLinha[i][indice]) {
        printf("\033[1;31m[ERRO]\033[0m Na linha %d: Letra branca %c repetida na mesma linha.\n", i, letra);
        letrasRepetidasLinha[i][indice] = 1;
    } else if (erro == ERRO_DUPLICADO_BRANCO_COLUNA && !letrasRepetidasColuna[j][indice]) {
        printf("\033[1;31m[ERRO]\033[0m Na coluna %c: Letra branca %c repetida na mesma coluna.\n", 'A' + j, letra);
        letrasRepetidasColuna[j][indice] = 1;
    }
}

void imprimeErroFaltaRiscar(int i, int j, char letra, TipoErro erro,int letrasRepetidasLinha[][26], int letrasRepetidasColuna[][26]) {
    int indice = letra - 'A';

    if (erro == ERRO_FALTA_RISCAR_LINHA_COLUNA && !letrasRepetidasLinha[i][indice] && !letrasRepetidasColuna[j][indice]) {
        printf("\033[1;31m[ERRO]\033[0m Na linha %d e na coluna %c: Letra %c por riscar.\n", i, 'A' + j, tolower(letra));
        letrasRepetidasLinha[i][indice] = 1;
        letrasRepetidasColuna[j][indice] = 1;
    } else if (erro == ERRO_FALTA_RISCAR_LINHA && !letrasRepetidasLinha[i][indice]) {
        printf("\033[1;31m[ERRO]\033[0m Na linha %d: Letra %c por riscar.\n", i, tolower(letra));
        letrasRepetidasLinha[i][indice] = 1;
    } else if (erro == ERRO_FALTA_RISCAR_COLUNA && !letrasRepetidasColuna[j][indice]) {
        printf("\033[1;31m[ERRO]\033[0m Na coluna %c: Letra %c por riscar.\n", 'A' + j, tolower(letra));
        letrasRepetidasColuna[j][indice] = 1;
    }
}

void imprimeErroVizinhanca(int i, int j, TipoErro erro) {
    if (erro == ERRO_VIZINHO_RISCADO) {
        printf("\033[1;31m[ERRO]\033[0m Na posição %c%d: Casa riscada com vizinho riscado.\n", 'a' + j, i);
    } else if (erro == ERRO_VIZINHO_NAO_BRANCO) {
        printf("\033[1;31m[ERRO]\033[0m Na posição %c%d: Casa riscada com vizinho(s) por pintar.\n", 'a' + j, i);
    }
}

void imprimeResultado(Jogo j) {
    if (j->venceu == 1) 
        printf("\033[32mParabéns! Venceste o jogo!\033[0m\n");
    else if (j->venceu == 0)
        printf("\033[1;31mPerdeste! Apesar de teres terminado o tabuleiro o mesmo apresenta conflitos.\033[0m\n");
}

void imprimeAjuda (StackJogadas s,Tabuleiro t,int topoStackAntes,int topoStackApos) {
    printf("\033[1;36m[Efeito da Ajuda]\n\033[0m");
    
    while (topoStackAntes < topoStackApos) {
        int l = s->jogadas[topoStackAntes]->l;
        int c = s->jogadas[topoStackAntes]->c;    
        char letraAnterior = s->jogadas[topoStackAntes]->letraAnterior;
        char novaLetra = t->tabuleiro[l][c];

        if (novaLetra == '#') {
            printf ("- Na coordenada %c%d a letra %c foi riscada\n",'a' + c,l,letraAnterior);
        } else {
            printf ("- Na coordenada %c%d a letra %c foi pintada\n",'a' + c,l,letraAnterior);
        }
        topoStackAntes ++;
    }
    putchar ('\n');
}

void printMenu() {
     printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
     printf("            \033[1;35m           Bem-Vindo ao Nosso Jogo!\033[0m           \n\n");
     printf("    [A] Iniciar o Jogo              [B] Comandos do Jogo\n");
     printf("    [C] Regras do Jogo              [D] Sair do Jogo\n");
     printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
 
}

void printComandos() {
    printf("\033[1;31m\n[Comandos disponíveis]\n\n\033[0m");
    printf("g <nome do tabuleiro> - Gravar o tabuleiro desejado\n");
    printf("l <nome do tabuleiro> - Ler o tabuleiro a jogar\n");
    printf("b <coordenada> - Colocar a letra em maiúsculas\n");
    printf("r <coordenada> - Colocar um '#' no local da letra\n");
    printf("v - Mostra as violações das regras do jogo cometidas\n");
    printf("d - Desfazer o último comando executado\n");
    printf("a - Ajuda o utilizador\n");
    printf("A - Ajuda o máximo que puder o utilizadaor\n");
    printf("R - Resolver o jogo\n");
    printf("s - Sair do jogo\n\n");
}

void printRegras() {
    printf("\033[1;31m\n[Regras do Jogo]\n\n\033[0m");
    printf("1. Cada casa contém um símbolo (uma letra inicialmente minúscula);\n");
    printf("2. Em cada linha e coluna só pode existir uma única réplica de cada símbolo que é pintada a branco (coloca-se a letra em maiúsculas);\n");
    printf("3. Todas as outras réplicas desse símbolo têm que ser riscadas (substituídas por um cardinal '#');\n");
    printf("4. Se uma casa está riscada, todas as casas vizinhas ortogonais  (acima, abaixo, à esquerda, à direita) têm que estar pintadas a branco;\n");
    printf("5. É necessário existir um caminho ortogonal entre todas as casas brancas do tabuleiro (ou seja, elas devem estar todas conectadas).\n\n");
}

void jogo (Jogo j,StackJogadas s, ListaConflitos lista) {
    int jogoEmAndamento = 1;
    char opcao;

    while (jogoEmAndamento) {
     printMenu();     
     if (scanf(" %c",&opcao) != 1) while (getchar() != '\n');

     if (opcao == 'a' || opcao =='A') {
            inicializaJogo (j);
            inicializaStack(s);
                
            comandosJogo (j,s);

            liberaTabuleiro(j->tabuleiro);
            liberaStack(s);
            liberaLista (lista);

        jogoEmAndamento = 0;
     }
     
     else if (opcao == 'b' || opcao == 'B') printComandos();
     else if (opcao == 'c' || opcao == 'C') printRegras();
     else if (opcao == 'd' || opcao == 'D') {
        free (s);  
        jogoEmAndamento = 0;
    } else printf("Opção inválida\n\n");

    }
}

