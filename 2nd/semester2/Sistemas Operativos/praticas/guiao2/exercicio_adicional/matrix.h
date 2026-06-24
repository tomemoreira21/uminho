#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

#define MAX_RAND 100
#define ROWS 10
#define COLUMNS 10

#define FILENAME "matrix"

int **createMatrix();
void printMatrix(int **matrix);
void writeMatrix(int **matrix);
int linesWithValue(int value);