#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>

void toUpperStr (char* str) {
    for (int i = 0; str[i] != '\0'; i++) 
        str[i] = toupper (str[i]);
}

int main (int argc,char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Missing file.\n");
        return 1;
    }

    char* filename = argv[1];
    FILE* fp = fopen (filename,"r"); // abre o ficheiro com o intuito de leitura
    if (fp == NULL) {
        perror("Error");
        return 1;
    }

    char* lineptr = NULL;
    size_t len;
    ssize_t read;
    while ((read = getline (&lineptr,&len,fp)) != -1) {
        toUpperStr (lineptr);
        printf ("%s",lineptr);
    }
    free (lineptr); // necessário dar o free

    /* limita o comprimento que lê por linha
    char str[100];
    while (fgets (str,100,fp)) {
        toUpperStr (str);
        printf ("%s",str);
    }
    */
    putchar ('\n');

    fclose(fp);
    return 0;
}