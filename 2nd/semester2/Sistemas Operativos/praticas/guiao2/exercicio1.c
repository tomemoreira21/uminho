#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc,char *argv[]) {
    // pid do pai, é o pid da bash (do terminal)
    printf ("PID ATUAL -> %d,PID PAI -> %d\n",getpid(),getppid());
    return 0;
}