#include "aeroporto.h"
#include <stdlib.h>
#include <glib.h>
#include <string.h>

struct aeroporto {
    char *code;
    char *name;
    char *city;
    char *country;
    //double latitude;
    //double longitude;
    //char* icao;
    TypeAeroporto type;
    int arrival_count;
    int departure_count;
};

static const char *TypeAeroporto_str[] = {
    "small_airport",
    "medium_airport",
    "large_airport",
    "heliport",
    "seaplane_base"
};

Aeroporto* cria_aeroporto(const gchar** dados) {
    Aeroporto* aeroporto = malloc(sizeof(struct aeroporto));
    if (!aeroporto) return NULL;

    aeroporto->code = strdup (dados[0]);
    aeroporto->name = strdup(dados[1]);
    aeroporto->city = strdup (dados[2]);
    aeroporto->country = strdup(dados[3]);
    //aeroporto->latitude = atof (dados[4]);
    //aeroporto->longitude = atof (dados[5]);
    //aeroporto->icao = dados[6];
    
    if (strcmp(dados[7], "small_airport") == 0) aeroporto->type = SMALL_AIRPORT;
    else if (strcmp(dados[7], "medium_airport") == 0) aeroporto->type = MEDIUM_AIRPORT;
    else if (strcmp(dados[7], "large_airport") == 0) aeroporto->type = LARGE_AIRPORT;
    else if (strcmp(dados[7], "heliport") == 0) aeroporto->type = HELIPORT;
    else aeroporto->type = SEAPLANE_BASE;

    aeroporto->arrival_count = 0;
    aeroporto->departure_count = 0;
    
    return aeroporto;
}

/*
Aeroporto* cria_aeroporto(gchar** dados) {
    Aeroporto* aeroporto = malloc(sizeof(struct aeroporto));
    if (!aeroporto) return NULL;

    aeroporto->code = dados[0]; dados[0] = NULL;
    aeroporto->name = dados[1]; dados[1] = NULL;
    aeroporto->city = dados[2]; dados[2] = NULL;
    aeroporto->country = dados[3]; dados[3] = NULL;
    
    if (strcmp(dados[7], "small_airport") == 0) aeroporto->type = SMALL_AIRPORT;
    else if (strcmp(dados[7], "medium_airport") == 0) aeroporto->type = MEDIUM_AIRPORT;
    else if (strcmp(dados[7], "large_airport") == 0) aeroporto->type = LARGE_AIRPORT;
    else if (strcmp(dados[7], "heliport") == 0) aeroporto->type = HELIPORT;
    else aeroporto->type = SEAPLANE_BASE;

    aeroporto->arrival_count = 0;
    aeroporto->departure_count = 0;
    
    return aeroporto;
}
*/

const char *get_airport_code (const Aeroporto *airport) {
    return airport->code;
}

const char *get_airport_name (const Aeroporto *airport) {
    return airport->name;
}

const char *get_airport_city (const Aeroporto *airport) {
    return airport->city;
}

const char *get_airport_country (const Aeroporto *airport) {
    return airport->country;
}


TypeAeroporto get_airport_type (const Aeroporto *airport) {
    return airport->type;
}

const char *get_airport_type_string(const Aeroporto *airport) {
    return TypeAeroporto_str[airport->type];
}

int get_airport_arrival_count(const Aeroporto *airport) {
    return airport->arrival_count;
}

int get_airport_departure_count(const Aeroporto *airport) {
    return airport->departure_count;
}

void incrementa_departure_count(Aeroporto *airport) {
    airport->departure_count++;
}

void incrementa_arrival_count(Aeroporto *airport) {
    airport->arrival_count++;
}

void free_airport(void* a) {
    Aeroporto *airport = a;
    if (!airport) return; 

    free (airport->code);
    free (airport->city);
    free (airport->country);
    free (airport->name);
    //free(airport->icao);
    free (airport);
}

