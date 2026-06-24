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

// A ideia passa por ter um processo por linha

// ex.5
int valueExists(int **matrix, int value) {
    for (int i = 0; i < ROWS; i++) {
        pid_t fork_res;
        
        fork_res = fork();

        if (fork_res == 0) {
            // child process
            for (int j = 0; j < COLUMNS; j++) {
                if (matrix[i][j] == value) 
                    _exit(0); 
            }

            _exit(1); // indica que não ocorre naquela linha
        }
    }

    for (int i = 0; i < ROWS; i++) {
        int status;
        pid_t exit_pid = wait(&status);

        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) 
                printf ("[proc-%d] (filho) PPID = %d found the value %d\n",exit_pid,getpid(),value);
            else 
                printf ("[proc-%d] (filho) PPID = %d exited. nothing found\n",exit_pid,getpid());
        }
    }

    return 0;

}
    
// ex.6
void linesWithValue(int **matrix, int value) {
    pid_t pids_values[ROWS] = {0};

    for (int i = 0; i < ROWS; i++) {
        pid_t fork_res;
        
        fork_res = fork();

        if (fork_res == 0) {
            // child process
            for (int j = 0; j < COLUMNS; j++) {
                if (matrix[i][j] == value) 
                    _exit(0);
            }
            _exit(1);

        } else {
            // parent process
            pids_values[i] = fork_res;
        }
    }

    for (int i = 0; i < ROWS; i++) {
        int status;
        pid_t exit_pid = waitpid(pids_values[i],&status,0);

        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0)
                printf ("[proc-%d] (filho) PPID = %d found the value %d on row %d\n",exit_pid,getpid(),value,i);
            else 
                printf ("[proc-%d] (filho) PPID = %d exited. nothing found on row %d\n",exit_pid,getpid(),i);
        } 
            
    }
}