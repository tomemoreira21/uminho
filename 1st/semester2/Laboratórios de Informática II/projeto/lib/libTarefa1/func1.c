#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../func.h"

int leLinha(char *coordenada){
    int tam=1,l=0,mult=1;
    
    while (coordenada[tam]!='\0') tam++;
    
    for (int i=tam-1;i>0; i--){
        l += (coordenada[i] - '0') * mult;
        mult *= 10;
    }

    return l;
}

int devolveJogada(Tabuleiro t,Jogada j,char *coordenada){
    int l,c;

    c = coordenada[0] - 'a';
    l = leLinha(coordenada);

    if ((l >= 0 && l < t->linhas) && (c >= 0 && c < t->colunas)) {
        j->l = l;
        j->c = c;
        j->letraAnterior = t->tabuleiro[j->l][j->c];
        return 1;

    } else return 0;
}

void inicializaStack (StackJogadas s) {
    s->size = 100;
    s->sp = 0;
    s->grupoAtual = 1;
    s->jogadas = malloc(s->size * sizeof(struct jogada));
}

void inicializaJogo (Jogo j) {
    j->venceu = 0;
    j->estadoJogo = 1;
    j->tabuleiro = malloc (sizeof (struct tabuleiro));
    j->tabuleiro->tabuleiro = NULL;
}

int comandoB(StackJogadas s, Tabuleiro t, char *coordenada, int m) {
    Jogada j = malloc(sizeof(struct jogada));

    if (devolveJogada(t,j,coordenada)) {
        if (!addMaiuscula(s, t, j, m)) {
            free (j);
            return 1;
       }
    } else {
        free(j);
        return 1;
    }

    return 0;
}

int comandoR (StackJogadas s,Tabuleiro t,char *coordenada, int m) {
    Jogada j = malloc(sizeof(struct jogada));

    if (devolveJogada (t,j,coordenada)) {
        if (!addRiscar (s,t,j,m)) {
            free (j);
            return 1;
        }
    } else {
        free (j);
        return 1;
    }

    return 0;
}

int comandoG (Tabuleiro t, char *str) {
    FILE *file = fopen(str, "r"); 

    if (file == NULL) return 1;
    else {
        fclose(file); 
        if (gravarJogo(t, str) != 0) return 1; 
    }

    return 0;
}

int comandoL(Tabuleiro t,char *str) {
    FILE *file = fopen(str, "r");
    if (file == NULL) return 1;

    if ((fscanf(file, "%d %d", &t->linhas, &t->colunas) != 2)  || t->linhas <= 0 || t->colunas <= 0) return fclose (file), 1;

    t->tabuleiro = malloc(t->linhas * sizeof(char *));
    for (int i = 0; i < t->linhas; i++)
        t->tabuleiro[i] = malloc(t->colunas * sizeof(char));

    char temp[t->colunas + 1]; 
    for (int i = 0; i < t->linhas; i++) {
        if (fscanf(file, "%s", temp) != 1) {
            for (int j = 0; j < i; j++) free(t->tabuleiro[j]);
            free(t->tabuleiro);
            return fclose (file), 1;
        } 
        for (int j = 0; j < t->colunas; j++) {
            if (temp[j] == '\0') return fclose (file),1;
            t->tabuleiro[i][j] = temp[j];
        }
    }

    fclose(file);
    return 0;
}

int gravarJogo (Tabuleiro t,char *nomeFicheiro) {
    FILE *file = fopen (nomeFicheiro,"w");

    if (file == NULL) {
        return 1;
    }

    fprintf (file,"%d %d\n",t->linhas,t->colunas);
    for (int j = 0; j < t->linhas; j++) {
        for (int i = 0; i < t->colunas;i++) {
            fprintf (file,"%c",t->tabuleiro [j] [i]);
        }
        fprintf (file, "\n");
    }

    fclose (file);
    return 0;
}

int clearFicheiro(char *nomeFicheiro) {
    FILE *file = fopen(nomeFicheiro, "w");
    
    if (file == NULL) {
        return 1;
    }
    fclose(file);
    return 0;
}

void pushJogada (StackJogadas s,Jogada j) {
    if (s->size == s->sp) {
        s->jogadas = realloc(s->jogadas, 2 * s->size * sizeof(Jogada));
        s->size *= 2;
    }

    s->jogadas [s->sp++] = j;
} 

int addMaiuscula (StackJogadas s,Tabuleiro t,Jogada j, int m) {
    if (comandoRBValido (t,j->l,j->c)) {
        j->marcador = m;
        pushJogada (s,j); 
        t->tabuleiro [j->l] [j->c] = toupper (t->tabuleiro [j->l] [j->c]);
        return 1;
    }

   return 0;
}

int addRiscar(StackJogadas s, Tabuleiro t, Jogada j, int m) {
    if (comandoRBValido (t,j->l,j->c)) {
        j->marcador = m;
        pushJogada (s,j);
        t->tabuleiro [j->l] [j->c] = '#';
        return 1;
    }

  return 0;
}

int coordValida(int linhas, int colunas,int l, int c){
    return ((l >= 0 && l < linhas) && (c >= 0 && c < colunas));
}

int comandoRBValido(Tabuleiro t, int l, int c){
    if (!coordValida(t->linhas,t->colunas,l,c)) return 0;
    else return (islower(t->tabuleiro[l][c]));
}

void liberaTabuleiro(Tabuleiro t) {
  if (t != NULL) {
     if (t->tabuleiro != NULL) {
        for (int i = 0; i < t->linhas; i++) {
            free(t->tabuleiro[i]);
        }
        free(t->tabuleiro);
    }
    free(t); 
    }
}

void liberaJogadas(StackJogadas s) {
    for (int i = 0; i < s->sp; i++) {
        free(s->jogadas[i]);
    }
    s->sp = 0;
}

void liberaStack (StackJogadas s) {
    for (int i = 0; i < s->sp; i++) {
        free(s->jogadas[i]);
    }
    free(s->jogadas);
    free(s);
}

