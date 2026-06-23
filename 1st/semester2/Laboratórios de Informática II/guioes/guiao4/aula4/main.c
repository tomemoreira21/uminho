#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 12


void bufferO() {
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        printf("Error\n");
        return;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    printf(buffer);
}

void pointersAri() {
    int n[] = {10, 20, 30, 40, 50};
    int *ptr = n, r = 0;

    for (size_t i = 0; i < sizeof(n) / sizeof(n[0]); i++) {
        r += * (ptr + i);
        printf("Element %zu: %d, Address: %p\n", i, r ,ptr + i);
    }
}

char* addressSt() {
    static char local[16] = "Stack";
    return local;
}


int arrayR() {
    int array[5];
    int i;

    printf("Initial array:\n");
    for (i = 0; i < 5; i++) {
        array[i] = i * i;
        printf("array[%d] = %d\n", i, array[i]);
    }
}

int main() {
    arrayR ();

    return 0;
}