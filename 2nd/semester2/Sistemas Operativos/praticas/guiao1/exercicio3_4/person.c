#include "person.h"

// devolve o registo onde insere
int new_person (char *nome,int idade) {
    int fd_dest = open (FILENAME,O_CREAT | O_APPEND | O_WRONLY,0600);
    if (fd_dest < 0) {
        perror ("Erro no ficheiro de destino");
        return 1;
    }

    Person p;
    strcpy(p.nome,nome);
    p.idade = idade;

    ssize_t bytes_written = write (fd_dest,&p,sizeof(struct person));
    off_t posAtual = lseek (fd_dest,-bytes_written,SEEK_CUR);
    if (posAtual == -1) {
        perror("lseek");
        return 1;      
    }

    close(fd_dest);   
    return posAtual/sizeof(struct person);
}

int list_n_persons (int N) {
    int fd = open (FILENAME, O_RDONLY);
    if (fd < 0) {
        perror ("Erro no ficheiro de origem");
        return 1;
    }

    long i = 0;
    ssize_t bytes_read;
    Person p;
    char buffer[1024];

    while (i < N && (sizeof (struct person) == (bytes_read = read (fd,&p,sizeof (struct person))))) {
        int len = snprintf(buffer,sizeof(buffer),"Nome: %s,Idade = %d\n",p.nome,p.idade);
        ssize_t bytes_written = write (1,buffer,len);    
        
        if (len != bytes_written) {
            perror ("Bytes written and length are different");
            return 1;
        }
    
        i++;
    }

    close(fd);
    return 0;
}

int update_age_v1 (char *nome,int idade) {
    int fd = open (FILENAME,O_RDWR);
    if (fd < 0) {
        perror ("Erro ao abrir o ficheiro de origem");
        return 1;
    }

    ssize_t bytes_read;
    Person p;

    while ((sizeof (struct person) == (bytes_read = read(fd,&p,sizeof (struct person))))) {
        if (strcmp (p.nome,nome) == 0) {
            p.idade = idade;
            lseek(fd,-sizeof(struct person),SEEK_CUR);
            ssize_t bytes_written = write (fd,&p,sizeof (struct person));
            
            if (bytes_written != sizeof (struct person)) {
                perror("Bytes written and bytes read are different");
                return 1;
            }

            break;
        }
    }

    close(fd);
    return 0;
}

int update_age_v2 (int reg,int idade) {
    int fd = open (FILENAME,O_RDWR);
    if (fd < 0) {
        perror ("Erro ao abrir o ficheiro de origem");
        return 1;
    }

    off_t offset = reg * sizeof(struct person);
    off_t pos = lseek(fd,offset,SEEK_SET);
    if (pos == -1) {
        perror("lseek");
        return 1;   
    }

    Person p;
    ssize_t bytes_read = read(fd,&p,sizeof (struct person));
    p.idade = idade;

    off_t pos_init = lseek (fd,-sizeof(struct person),SEEK_CUR);
    if (pos_init == -1) {
        perror("lseek");
        return 1;   
    }

    ssize_t bytes_written = write(fd,&p,sizeof(struct person)); 

    close(fd);
    return 0;
}

