#include "aeronave.h"
#include <glib.h>
#include <string.h>
#include <stdio.h>

struct aeronave {
    char *airplane_id;
    char *manufactor;
    char *model;
    //int year;
    //int capacity;
    //int range;
    int flight_count;
};

Aeronave* cria_aeronave(const gchar** dados) {
    Aeronave* aeronave = malloc(sizeof(struct aeronave));
    if (!aeronave) return NULL;

    aeronave->airplane_id = strdup(dados[0]);
    aeronave->manufactor = strdup(dados[1]);
    aeronave->model = strdup(dados[2]);

    //aeronave->year = atoi(dados[3]);
    //aeronave->capacity = atoi(dados[4]);
    //aeronave->range = atoi(dados[5]);
    aeronave->flight_count = 0;

    return aeronave;
}

/*
Aeronave* cria_aeronave(gchar** dados) {
    Aeronave* aeronave = malloc(sizeof(struct aeronave));
    if (!aeronave) return NULL;

    aeronave->airplane_id = dados[0]; dados[0] = NULL;
    aeronave->manufactor = dados[1]; dados[1] = NULL;
    aeronave->model = dados[2]; dados[2] = NULL;

    aeronave->flight_count = 0;

    return aeronave;
}
*/

const char *get_aircraft_identifier (const Aeronave *aircraft) {
    return aircraft->airplane_id;
}

const char *get_aircraft_manufactor (const Aeronave *aircraft) {
    return aircraft->manufactor;
}

int get_aircraft_flight_count (const Aeronave *aircraft) {
    return aircraft->flight_count;
}

const char *get_aircraft_model(const Aeronave *aircraft) {
    return aircraft->model;
}

void incrementa_flight_count(Aeronave *aircraft) {
    if (!aircraft) return;
    
    aircraft->flight_count++;
}

/*
Valores de retorno:
    -> -1 : fligth_count de a1 é maior do que o de a2;
    -> 1  : fligth_count de a1 é menor do que o de a2;
    -> 0  : os flight_counts de a1 e a2 são iguais;
*/
int aeronaves_compare_flight_count(const void *p1, const void *p2) {
    Aeronave *a1 = (Aeronave*)p1;
    Aeronave *a2 = (Aeronave*)p2;

    int fc1 = get_aircraft_flight_count (a1);
    int fc2 = get_aircraft_flight_count (a2);    

    if (fc1 > fc2) return -1;
    if (fc1 < fc2) return 1;
    return aeronaves_compare_id (a1,a2);
}

int aeronaves_compare_id(const void *p1, const void *p2) {
    Aeronave *a1 = (Aeronave*)p1;
    Aeronave *a2 = (Aeronave*)p2;

    return strcmp(get_aircraft_identifier (a1), get_aircraft_identifier (a2));
}

void free_aeronave (void* a) {
    if (!a) return;
    Aeronave *aeronave = a;
    free (aeronave->airplane_id);
    free (aeronave->manufactor);
    free (aeronave->model);
    free(aeronave);
}
