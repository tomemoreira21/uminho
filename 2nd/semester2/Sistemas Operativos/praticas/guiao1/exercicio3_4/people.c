#include <stdio.h>
#include <string.h>
#include "person.h"


int main(int argc, char* argv[]){
    if (argc < 3) {
        printf("Usage:\n");
        printf("Add new person: ./people -i [name] [age]\n");
        printf("List N persons: ./people -l [N]\n");
        printf("Change person age: ./people -u [name] [age]\n");
        printf("Change person age (v2): ./people -o [position] [age]\n");
        return 1;
    }

    if (strcmp(argv[1],"-i") == 0) {
        int res = new_person (argv[2],atoi(argv[3]));
        printf ("registo %d\n",res);
    }

    if (strcmp(argv[1],"-l") == 0) {
        list_n_persons(atoi(argv[2]));
    }

    if (strcmp(argv[1],"-u") == 0){
        update_age_v1(argv[2],atoi(argv[3]));
    }

    if (strcmp(argv[1],"-o") == 0) {
        update_age_v2(atoi(argv[2]),atoi(argv[3]));
    }

    return 0;
}
