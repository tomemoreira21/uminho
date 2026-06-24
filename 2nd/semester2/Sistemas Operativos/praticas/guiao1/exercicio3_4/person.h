#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FILENAME "file_people"

typedef struct person {
    char nome[200];
    int idade;
} Person;


int new_person (char *nome,int age);
int list_n_persons (int N);
int update_age_v1 (char *nome,int idade);
int update_age_v2 (int reg,int idade);


#endif