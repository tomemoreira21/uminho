#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <sys/wait.h>


/*
grep -v ^# /etc/passwd -> dá todos as linhas que não têm o caractere #
cut -f7 -d: -> seleciona a coluna 7 em que o delimitador é :
uniq -> pega em linhas consecutivas e reduz a uma (agrupa)
wc -l -> número de linhas finais

Serão necessários 3 pipes, 4 processos

processos = N
pipes = N - 1
*/
