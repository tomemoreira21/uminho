#include "voo.h"
#include "utils.h"
#include <glib.h>
#include <string.h>

struct voo {
    char *flight_id;                      
    GDateTime *departure;
    GDateTime *actual_departure;
    GDateTime *arrival;
    GDateTime *actual_arrival;  
    //char *gate;
    VooStatus status;
    char *origin;    
    char *destination; 
    char *aircraft;
    char *airline;
    //char *tracking_url;
};

Voo* cria_voo(const gchar** dados) {
    Voo *voo = malloc(sizeof(struct voo));
    if (!voo) return NULL;

    voo->flight_id = strdup (dados[0]);
    voo->departure = type_string_to_datetime (dados[1]);
    voo->actual_departure = type_string_to_datetime (dados[2]);
    voo->arrival = type_string_to_datetime (dados[3]);
    voo->actual_arrival = type_string_to_datetime (dados[4]);
    //voo->gate = dados[5];
    
    if (strcmp(dados[6], "Delayed") == 0) voo->status = DELAYED;
    else if (strcmp(dados[6], "On Time") == 0) voo->status = ON_TIME;
    else voo->status = CANCELLED;

    voo->origin = strdup (dados[7]);
    voo->destination = strdup(dados[8]);
    voo->aircraft = strdup(dados[9]);
    voo->airline = strdup(dados[10]);
    //voo->tracking_url = dados[11];

    return voo;
}

/*
Voo* cria_voo(gchar** dados) {
    Voo *voo = malloc(sizeof(struct voo));
    if (!voo) return NULL;

    // Transfere posse (rouba o ponteiro e anula no array)
    voo->flight_id = dados[0]; dados[0] = NULL;
    voo->origin    = dados[7]; dados[7] = NULL;
    voo->destination = dados[8]; dados[8] = NULL;
    voo->aircraft  = dados[9]; dados[9] = NULL;
    voo->airline   = dados[10]; dados[10] = NULL;

    // Converte dados (o free será feito no final do loop)
    voo->departure = type_string_to_datetime(dados[1]);
    voo->actual_departure = type_string_to_datetime(dados[2]);
    voo->arrival = type_string_to_datetime(dados[3]);
    voo->actual_arrival = type_string_to_datetime(dados[4]);
    
    if (strcmp(dados[6], "Delayed") == 0) voo->status = DELAYED;
    else if (strcmp(dados[6], "On Time") == 0) voo->status = ON_TIME;
    else voo->status = CANCELLED;

    return voo;
}
}
*/

const char *get_flight_id(const Voo *v) {
    return v->flight_id;
}

const char *get_origin(const Voo *v) {
    return v->origin;
}

const char *get_destination(const Voo *v) {
    return v->destination;
}

const char *get_aircraft (const Voo *v) {
    return v->aircraft;
}

const char *get_airline(const Voo *v) {
    return v->airline;
}

GDateTime *get_departure(const Voo *v) { 
    return v->departure; 
}

GDateTime *get_actual_departure(const Voo *v) { 
    return v->actual_departure; 
}

GDateTime *get_arrival(const Voo *v) { 
    return v->arrival; 
}

GDateTime *get_actual_arrival(const Voo *v) { 
    return v->actual_arrival; 
}

VooStatus get_status(const Voo *v) {
    return v->status;
}

void free_voo (void* v) {
    Voo *voo = v;
    if (!voo) return;

    if (voo->departure) g_date_time_unref(voo->departure);
    if (voo->actual_departure) g_date_time_unref(voo->actual_departure);
    if (voo->arrival) g_date_time_unref(voo->arrival);
    if (voo->actual_arrival) g_date_time_unref(voo->actual_arrival);
    
    free(voo->flight_id);
    free(voo->origin);
    free(voo->destination);
    free(voo->aircraft);
    free(voo->airline);

    //free (voo->tracking_url);
    free (voo);
}

