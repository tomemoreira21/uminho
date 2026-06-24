#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa {
    char nome[50];
    int idade;
} Pessoa;

Pessoa criaPessoa (const char *nome,int idade) {
    Pessoa p;
    strcpy(p.nome,nome);
    p.idade = idade;

    return p;
}

// int registo = pos / sizeof(struct pessoa) - 1, -1 porque o ponteiro já avançou após o read
long adiciona_pessoa (Pessoa p,const char *path_dest) {
    int fd = open(path_dest,O_WRONLY | O_CREAT | O_APPEND,0600);
    if (fd < 0) {
        perror ("Erro ao abrir o ficheiro de destino");
        return -1;
    }

    ssize_t bytes_written = write (fd,&p,sizeof(struct pessoa));
    off_t posAtual = lseek(fd,0,SEEK_CUR);

    long registo = posAtual /sizeof(struct pessoa) - 1;
    close(fd);
    return registo;
}

int ler_pessoa (const char *path_origin,const char *path_dest,int N) {
    int fd_origin = open(path_origin,O_RDONLY);
    if (fd_origin < 0) {
        perror ("Erro ao abrir o ficheiro de origem");
        return -1;
    }

    int fd_dest = open(path_dest,O_WRONLY | O_CREAT | O_TRUNC,0600);
    if (fd_dest < 0) {
        perror("Erro ao abrir o ficheiro de escrita");
        return -1;
    }

    int i = 0;
    Pessoa p;
    while (i < N && sizeof (struct pessoa) == read(fd_origin,&p,sizeof (struct pessoa))) {
        ssize_t bytes_written = write (fd_dest,&p,sizeof(struct pessoa));
        if (bytes_written != sizeof(struct pessoa)) return -1;

        printf ("Nome: %s,Idade: %d\n",p.nome,p.idade);
        i++;
    }

    close(fd_origin);
    close(fd_dest);
    return 0;
}

int atualiza_idade(Pessoa p,const char* pathname) {
    int fd = open (pathname,O_RDWR);    
    if (fd < 0) {
        perror("Erro ao abrir o ficheiro");
        return -1;
    }

    Pessoa p_lida;
    while ((sizeof (struct pessoa) == read(fd,&p_lida,sizeof(struct pessoa)))) {
        if (strcmp (p_lida.nome,p.nome) == 0) {
            p_lida.idade = p.idade;
            lseek(fd,-sizeof(struct pessoa),SEEK_CUR); // voltar ao inicio do registro que quero alterar
            ssize_t bytes_written = write(fd,&p_lida,sizeof(struct pessoa));
            close(fd);
            return 0;
        }
    }

    close(fd);
    return -1;
}


// int pos = sizeof(struct pessoa) * registo
int atualizaPorRegisto (int registo,int novaIdade,const char *pathname) {
    int fd = open (pathname,O_RDWR);
    if (fd < 0) {
        perror("Erro ao abrir o ficheiro");
        return -1;
    }
    
    off_t off_set = sizeof(struct pessoa) * registo;
    off_t pos = lseek (fd,off_set,SEEK_SET);

    Pessoa p;
    ssize_t bytes_read = read(fd,&p,sizeof(struct pessoa));
    p.idade = novaIdade;

    lseek(fd,-bytes_read,SEEK_CUR); // vai para o inicio da linha
    ssize_t bytes_written = write(fd,&p,sizeof(struct pessoa));
    return 0;
} 

int main (int argc,char* argv[]) {
    const char *path_todasPessoas = "pessoasTotal.bin";
    const char *path_NPessoas = "pessoasN.bin";

    if (argc == 1) {
        // usar o comando time ./people
        int N = 1000000;    
        char nome[32];
        printf ("Inserindo %d pessoas ...\n",N);

        for (int i = 0; i < N; i++) {
            snprintf(nome,sizeof(nome),"Pessoa_%d",i);
            Pessoa p = criaPessoa(nome,i % 100);
            adiciona_pessoa(p,path_todasPessoas);
        }
    } 

    if (argc > 2) {
        if (strcmp (argv[1],"-i") == 0) {
            Pessoa p = criaPessoa(argv[2],atoi(argv[3]));
            long registo = adiciona_pessoa(p,path_todasPessoas);
            printf ("registo %ld\n",registo);
        } else if (strcmp (argv[1],"-l") == 0) {
            ler_pessoa(path_todasPessoas,path_NPessoas,atoi(argv[2]));
        } else if (strcmp (argv[1],"-u") == 0) {
            Pessoa p = criaPessoa(argv[2],atoi(argv[3]));
            atualiza_idade(p,path_todasPessoas);
        } else if (strcmp(argv[1],"-o") == 0) {
            atualizaPorRegisto(atoi(argv[2]),atoi(argv[3]),path_todasPessoas);
        }
    }

    return 0;
}