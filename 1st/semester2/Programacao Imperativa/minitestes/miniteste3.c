#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {  
    char nome[100];  
    int nr;  
    int nota;  
   } Aluno;

typedef struct cel {
    Aluno *aluno;
    struct cel *prox;
} *Turma;

int adicionaAluno(Turma *t, char *nome, int nr, int nota) {
    Aluno *novo_aluno = malloc(sizeof (struct aluno));

    if (novo_aluno == NULL) return 1;
    strcpy(novo_aluno->nome, nome);
    novo_aluno->nr = nr;
    novo_aluno->nota = nota;
    struct cel *nova_cel = malloc(sizeof(struct cel));

    if (nova_cel == NULL) {
     free(novo_aluno);
     return 1;
    }

    nova_cel->aluno = novo_aluno;

    while (*t != NULL && (*t)->aluno->nota < nota) { 
     t = &((*t)->prox);
    }

    nova_cel->prox = *t;
    *t = nova_cel;
    return 0;
}
