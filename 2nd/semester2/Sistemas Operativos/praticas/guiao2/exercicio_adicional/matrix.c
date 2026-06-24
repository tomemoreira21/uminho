#include "matrix.h"


int **createMatrix() {

    srand(time(NULL)); // seed based on time - always changing

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void writeMatrix(int **matrix) {
    int fd = open (FILENAME,O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (fd < 0) {
        perror("Error open the filename");
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        ssize_t bytes_written = write (fd,matrix[i],COLUMNS * sizeof(int));

        if (bytes_written != COLUMNS * sizeof(int)) {
            perror("Error writing one row");
            close(fd);
            return;
        }
    }

    close(fd);
}

// A ideia passa por cada processo ler uma linha da matriz, uma vez que eles partilham o offset

int linesWithValue(int value) {
    pid_t pids[ROWS] = {0};
    for (int i = 0; i < ROWS; i++) {
        pid_t fork_res;

        fork_res = fork();

        if (fork_res == 0) {    
            int fd = open (FILENAME, O_RDONLY); // de forma a não partilhar o file descriptor
            if (fd < 0) {   
                perror ("Error open the filename");
                _exit(1);
            }

            off_t offset = i * COLUMNS * sizeof(int);
            lseek (fd,offset,SEEK_SET);

            int valuesLine[COLUMNS];   
            ssize_t bytes_read = read (fd,valuesLine,COLUMNS * sizeof(int));

            if (bytes_read != COLUMNS * sizeof(int)) {
                perror ("Error reading one row");
                close(fd);
                _exit(1);
            }

            for (int j = 0; j < COLUMNS; j++) {
                if (valuesLine[j] == value) {
                    close(fd);
                    _exit(0);
                }
            }

            close(fd);
            _exit(1); // não encontrou o value naquela linha
        } else {
            pids[i] = fork_res;
        }
    }   


    for (int i = 0; i < ROWS; i++) {
        int status;
        pid_t exit_pid = waitpid (pids[i],&status,0);

        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0)
                printf ("[proc-%d] (filho) PPID = %d found the value %d on row %d\n",exit_pid,getpid(),value,i);
            else 
                printf ("[proc-%d] (filho) PPID = %d exited. nothing found on row %d\n",exit_pid,getpid(),i);
        }
    }

    return 0;
}