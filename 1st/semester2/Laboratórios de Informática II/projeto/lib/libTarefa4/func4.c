#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../func.h"

int ajudaUtilizador(StackJogadas s, Tabuleiro t, ListaConflitos lista,int m) {
    int ajudou = 0,estaIsolado = 1;

    while (lista != NULL) {
        int i = lista->l,j = lista->c, r = 0;
        TipoErro erro = lista->erro;

        if (erro == ERRO_DUPLICADO_BRANCO_LINHA_COLUNA)
            r = ajudaRiscarDuplicadosLinhaColuna(s, t, i, j);

        else if (erro == ERRO_DUPLICADO_BRANCO_LINHA)
            r = ajudaRiscarDuplicadosLinha(s, t, i, j);

        else if (erro == ERRO_DUPLICADO_BRANCO_COLUNA)
            r = ajudaRiscarDuplicadosColuna(s, t, i, j);

        else if (erro == ERRO_FALTA_RISCAR_LINHA_COLUNA) 
            r = ajudaRiscarLinhaColuna (s,t,i,j);
        
        else if (erro == ERRO_FALTA_RISCAR_LINHA)
            r = ajudaRiscarLinha (s,t,i,j);
        
        else if (erro == ERRO_FALTA_RISCAR_COLUNA)
            r = ajudaRiscarColuna (s,t,i,j);

        else if (erro == ERRO_VIZINHO_NAO_BRANCO)
            r = ajudaPintarVizinhosNaoBranco(s, t, i, j);

        if (r == 1) ajudou = 1;

        lista = lista->prox;
    }

    while (estaIsolado == 1) {
        int r = ajudaIsolarNaoBranco(s, t);
        if (r == 1) ajudou = 1;
        else estaIsolado = 0;
    }
    
    if (m == 0) s->grupoAtual++;

    return ajudou;
}

Jogada devolveJogadaAjuda(Tabuleiro t, int l, int c){
    Jogada jog = malloc(sizeof (struct jogada));
    jog->c = c;
    jog->l = l;
    jog->letraAnterior = t->tabuleiro[l][c];

    return jog;
}

int permiteRiscar (Tabuleiro t, int i, int j) {
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    for (int k = 0; k < 4; k++) {
        int x = i + dx[k];
        int y = j + dy[k];

        if (coordValida(t->linhas, t->colunas, x, y)) {
            if (t->tabuleiro[x][y] == '#') {
                return 0; 
            }
        }
    }

    return 1;
}

/*
Se ela é branca e só tem uma minúscula ao seu redor então para existir caminho obrigatoriamente 
entre as brancas tem de ser maiuscula
*/
int ajudaIsolarNaoBranco (StackJogadas s, Tabuleiro t) {
    int dx[] = {0, 1, 0, -1},dy[] = {1, 0, -1, 0};

    for (int i = 0; i < t->linhas; i++) {
        for (int j = 0; j < t->colunas; j++) {
            char atual = t->tabuleiro[i][j];
            if (isupper(atual)) {  
                int countMinusc = 0, countMaiusc = 0,linhaAlvo = -1, colunaAlvo = -1;

                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k],y = j + dy[k];

                    if (coordValida(t->linhas, t->colunas, x, y)) {
                        char vizinho = t->tabuleiro[x][y];
                        if (islower(vizinho)) {
                            countMinusc++,linhaAlvo = x;colunaAlvo = y;
                        }

                        if (isupper (vizinho)) countMaiusc++;
                    }
                }

                if (countMinusc == 1 && countMaiusc == 0) {
                    Jogada jog = devolveJogadaAjuda(t, linhaAlvo, colunaAlvo);
                    if (!addMaiuscula(s, t, jog, s->grupoAtual)) return 0;

                    if (!existeCaminho (t)) {
                        undoStack (t,s);
                        return 0;
                    }

                    return 1;
                }
            }
        }
    }

    return 0;
}

int ajudaPintarVizinhosNaoBranco (StackJogadas s, Tabuleiro t,int i,int j) {
    int p = 0;

    if (i > 0 && t->tabuleiro[i-1][j] != '#' && !isupper(t->tabuleiro[i-1][j])) {
        Jogada jog = devolveJogadaAjuda(t,i-1,j);
        addMaiuscula(s,t,jog,s->grupoAtual);
        p++;
    }

    if (i < t->linhas - 1 && t->tabuleiro[i+1][j] != '#' && !isupper(t->tabuleiro[i+1][j])) {
        Jogada jog = devolveJogadaAjuda(t,i+1,j);
        addMaiuscula(s,t,jog,s->grupoAtual);
        p++;
    }

    if (j > 0 && t->tabuleiro[i][j-1] != '#' && !isupper(t->tabuleiro[i][j-1])) {
        Jogada jog = devolveJogadaAjuda(t,i,j-1);
        addMaiuscula(s,t,jog,s->grupoAtual);
        p++;
    }

    if (j < t->colunas - 1 && t->tabuleiro[i][j+1] != '#' && !isupper(t->tabuleiro[i][j+1])) {
        Jogada jog = devolveJogadaAjuda(t,i,j+1);
        addMaiuscula(s,t,jog,s->grupoAtual);
        p++;
    }

    if (p == 0) return 0;

    return 1;
}

int addBrancoRiscar(StackJogadas s, Tabuleiro t, Jogada j, int m) {
    if (isupper(t->tabuleiro[j->l][j->c])) {
        j->marcador = m;
        pushJogada(s, j);  
        t->tabuleiro[j->l][j->c] = '#'; 
        return 1;
    } 
        
    free (j);
    return 0;  
}

int ajudaRiscarDuplicadosLinhaColuna (StackJogadas s, Tabuleiro t, int i, int j) {
    int topoStackAntes = s->sp;
    
    if (!ajudaRiscarDuplicadosLinha(s, t, i, j)) {
        backTrack (t,s,topoStackAntes);
        return 0;
    }
    
    topoStackAntes = s->sp;

    if (!ajudaRiscarDuplicadosColuna(s, t, i, j)) {
        backTrack (t,s,topoStackAntes);
        return 0;
    }
    
    return 1;
}

int ajudaRiscarDuplicadosColuna (StackJogadas s,Tabuleiro t,int i,int j) {
    int r = 0;
    char letra = t->tabuleiro[i][j];

    for (int k = 0; k < t->linhas;k++) {
        if (k != i && t->tabuleiro[k][j] == letra && permiteRiscar (t,k,j)) {
            Jogada jog = devolveJogadaAjuda (t,k,j);
            int topoStackAntes = s->sp;

            if (!addBrancoRiscar (s,t,jog,s->grupoAtual)) return 0;

            if (!existeCaminho (t)) {
                backTrack (t,s,topoStackAntes);
                return 0;
            }
            r = 1;
        }
    }

    return r;
}

int ajudaRiscarDuplicadosLinha (StackJogadas s,Tabuleiro t,int i,int j) {
    int r = 0;
    char letra = t->tabuleiro[i][j];

    for (int k = 0; k < t->colunas;k++) {
        if (k != j && t->tabuleiro[i][k] == letra && permiteRiscar (t,i,k)) {
            Jogada jog = devolveJogadaAjuda (t,i,k);

            int topoStackAntes = s->sp;
            
            if (!addBrancoRiscar (s,t,jog,s->grupoAtual)) return 0;

            if (!existeCaminho (t)) {
                backTrack (t,s,topoStackAntes);
                return 0;
            }
            r = 1;
        }
    }
    
    return r;
}

int ajudaRiscarLinha (StackJogadas s,Tabuleiro t,int i,int j) {
    int r = 0;
    char letra = tolower (t->tabuleiro[i][j]);

    for (int k = 0; k < t->colunas;k++) {
        if (k != j && t->tabuleiro[i][k] == letra && permiteRiscar (t,i,k)) {
            Jogada jog = devolveJogadaAjuda (t,i,k);
            int topoStackAntes = s->sp;
            
            if (!addRiscar (s,t,jog,s->grupoAtual)) return 0;

            if (!existeCaminho (t)) {
                backTrack (t,s,topoStackAntes);
                return 0;
            }
            r = 1;
        }
    }
    
    return r;
}

int ajudaRiscarColuna (StackJogadas s,Tabuleiro t,int i,int j) {
    int r = 0;
    char letra = tolower (t->tabuleiro[i][j]);

    for (int k = 0; k < t->linhas;k++) {
        if (k != i && t->tabuleiro[k][j] == letra && permiteRiscar (t,k,j)) {
            Jogada jog = devolveJogadaAjuda (t,k,j);
            int topoStackAntes = s->sp;

            if (!addRiscar (s,t,jog,s->grupoAtual)) return 0;

            if (!existeCaminho (t)) {
                backTrack (t,s,topoStackAntes);
                return 0;
            }
            r = 1;
        }
    }

    return r;
}

int ajudaRiscarLinhaColuna (StackJogadas s, Tabuleiro t, int i, int j) {
    int topoStackAntes = s->sp;
    
    if (!ajudaRiscarLinha(s, t, i, j)) {
        backTrack (t,s,topoStackAntes);
        return 0;
    }
    
    topoStackAntes = s->sp;

    if (!ajudaRiscarColuna(s, t, i, j)) {
        backTrack (t,s,topoStackAntes);
        return 0;
    }
    
    return 1;
}

int comandoA(StackJogadas s, Tabuleiro t,int m) {
    int alteracao = 0;
    int ajuda = 1;
    ListaConflitos lista = NULL;
    int topoStackAntes = s->sp;

    while (ajuda == 1) {
        lista = verificaConflitos(t, lista);
        ajuda = ajudaUtilizador(s, t, lista,1);
        
        if (ajuda == 0 && lista != NULL) {
            backTrack (t,s,topoStackAntes);
            alteracao = -1;
        }
        
        if (ajuda == 1) alteracao = 1;

        liberaLista(lista);
        lista = NULL;
    }

    if (m == 0) s->grupoAtual ++;

    return alteracao;
}
