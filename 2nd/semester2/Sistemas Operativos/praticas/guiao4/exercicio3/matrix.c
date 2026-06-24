#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(123456); // fixed seed
    //srand(time(NULL)); // seed based on time - always changing

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

void lookupNumber(int** matrix, int value, int* vector){
    int fildes[2];
    pipe(fildes);

    for (int i = 0; i < ROWS; i++) {
        pid_t fork_res;
        fork_res = fork();

        if (fork_res == 0) {
            close(fildes[0]);

            Minfo f;
            f.line_nr = i;
            f.ocur_nr = 0;

            for (int j = 0; j < COLUMNS; j++) {
                if (matrix[i][j] == value) f.ocur_nr++;
            }

            write(fildes[1],&f,sizeof(Minfo));
            close(fildes[1]);
            _exit(0);
        } 
    }

    close(fildes[1]); // pai fecha o descritor de escrita

    for (int i = 0; i < ROWS; i++) {
        Minfo f_received;

        read(fildes[0],&f_received,sizeof(Minfo));
        printf("Line %d found value %d -> %d times\n",f_received.line_nr,value,f_received.ocur_nr);

        vector[f_received.line_nr] = f_received.ocur_nr;
    }

    close(fildes[0]);

    for (int i = 0; i < ROWS; i++) {
        int status;
        pid_t exit_pid = wait(&status);

        if (WIFEXITED(status)) 
            printf("[proc_%d] exited with status = %d\n",exit_pid,WEXITSTATUS(status));
    }
}
