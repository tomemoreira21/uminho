#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void sayEntry (char *str) {
    int idade;
    char g;
    char *nome = malloc(strlen(str) + 1); // +1 para o '\0'

    sscanf(str, "%s - %d - %c", nome, &idade, &g);
    printf ("Nome: %s\n",nome);
    printf ("Idade: %d\n",idade);
    printf ("Género: %s\n",(g == 'M') ? "Masculino" : "Feminino");
    putchar ('\n');

    free (nome);
}

int main (int argc,char **argv) {
    if (argc < 2) {
        fprintf (stderr,"Missing filename\n");
        return 1;
    }

    FILE* fr = fopen (argv[1],"r");
    ssize_t read;
    size_t len;
    char *line = NULL;

    while ((read = getline (&line,&len,fr)) != -1) {
        sayEntry (line);
    }
    free (line);
    
    fclose (fr);
    return 0;
}