#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../func.h"

int gravaStack (StackJogadas s, char *nomeFicheiro, char *nomeTabuleiro) {    
    FILE *file = fopen (nomeFicheiro,"w");
    if (file == NULL) {
        return 1;
    }

    fprintf(file, "%d %d\n", s->sp, s->grupoAtual);

    for (int i = 0; i < s->sp;i++) 
        fprintf (file,"%d %d %d %c\n",s->jogadas[i]->marcador,s->jogadas[i]->l,s->jogadas[i]->c,s->jogadas[i]->letraAnterior);
    
    fprintf (file,"%s\n",nomeTabuleiro);
    fprintf (file, "\n");
    fclose (file);

    return 0;
}

int restauraStack(StackJogadas s, char *nomeFicheiro, char *nomeTabuleiro) {
    FILE *file = fopen(nomeFicheiro, "r");
    if (file == NULL) return 1;

    int spNovo, grupoAtualNovo;
    if (fscanf(file, "%d %d", &spNovo, &grupoAtualNovo) != 2) {
        fclose(file);
        return 1;
    }

    liberaJogadas(s), s->sp = 0, s->grupoAtual = grupoAtualNovo;

    for (int i = 0; i < spNovo; i++) {
        int marcador, l, c;
        char letraAnterior;
        
        if (fscanf(file, "%d %d %d %c", &marcador, &l, &c, &letraAnterior) != 4) {
            fclose(file);
            return 1;
        }

        Jogada nova = malloc(sizeof(struct jogada));
        nova->marcador = marcador;
        nova->l = l;
        nova->c = c;
        nova->letraAnterior = letraAnterior;

        s->jogadas[s->sp++] = nova;
    }

    if (fscanf(file,"%1023s",nomeTabuleiro) != 1) {
        fclose(file);
        return 1;
    }


    fclose(file);
    return 0;
}

