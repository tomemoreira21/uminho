#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../func.h"

int existeCaminho (Tabuleiro t) {
    int visitadas[t->linhas][t->colunas],naoRiscadas = 0,nVisitadas = 0,l = -1,c = -1;
    Coordenada posicoes[t->linhas * t->colunas];
    memset(visitadas, 0, sizeof(visitadas));

    for (int i = 0; i < t->linhas; i++){
        for (int j = 0; j < t->colunas; j++) {
            if (t->tabuleiro[i][j] != '#') {
                naoRiscadas++;
                if (l == -1) l = i, c = j;
            }
        }
    }
    
    if (naoRiscadas == 0) return 0; // estão todas riscadas 
    if (naoRiscadas == (t->linhas * t->colunas)) return 1; // não tem casas riscadas
    
    posicoes[nVisitadas++] = (Coordenada){l, c};
    visitadas[l][c] = 1;

    int i = 0,dL[] = {0, 1, 0, -1},dC[] = {1, 0, -1, 0};
    
    while (i < nVisitadas) {
        Coordenada atual = posicoes[i++];
        for (int k = 0; k < 4; k++) {
            int vizinhoL = atual.linha + dL[k], vizinhoC = atual.coluna + dC[k];
            
            if (coordValida(t->linhas,t->colunas,vizinhoL,vizinhoC) &&
                t->tabuleiro[vizinhoL][vizinhoC] != '#' && visitadas[vizinhoL][vizinhoC] == 0) {
                        posicoes[nVisitadas++] = (Coordenada){vizinhoL, vizinhoC};
                        visitadas[vizinhoL][vizinhoC] = 1;
                }
            }
        }
    
    return (nVisitadas == naoRiscadas);
}
