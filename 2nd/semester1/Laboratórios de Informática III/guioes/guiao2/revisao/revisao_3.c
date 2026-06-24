#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// contar o número de palavras que tem o ficheiro
int countWords (char *str) {
    int count = 0; 
    char* token = strsep (&str," "); // o único limitador é espaço 

    while (token != NULL) {
        if (strlen (token) > 0) count++;
        token = strsep (&str," ");
    }

    return count;
}

int main (int argc,char **argv) {
    if (argc < 2) {
        fprintf (stderr,"Missing Filename\n");
        return 1;
    }

    FILE* fr = fopen (argv[1],"r");
    char* line = NULL;
    size_t len;
    ssize_t read;
    int count = 0,l = 1,num = 0;
    while ((read = getline (&line,&len,fr)) != -1) {
        line[read-1] = '\0';
        num = countWords (line);
        count += num;
        printf ("Linha %d: %d words\n",l++,num);
    }

    printf ("Total: %d words\n",count);
    return 0;
}
