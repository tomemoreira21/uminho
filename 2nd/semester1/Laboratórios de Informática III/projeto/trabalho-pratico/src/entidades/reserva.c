#include "reserva.h"
#include "utils.h"
#include <glib.h>

struct reserva {
    char *reservation_id;
    GPtrArray *flight_ids; 
    char *document_number;
    //char *seat;
    float price;
    //gboolean extra_luggage;
    //gboolean priority_boarding;
    //char *qr_code;
};

Reserva* cria_reserva(const gchar** dados) {
    Reserva* reserva = malloc(sizeof(struct reserva));
    if (!reserva) return NULL;
    
    reserva->reservation_id = strdup (dados[0]);
    reserva->flight_ids = type_string_flight_ids (dados[1]);
    reserva->document_number = strdup(dados[2]);

    //reserva->seat = dados[3];
    reserva->price = atof(dados[4]);

    //if (strcmp(dados[5], "True") == 0) reserva->extra_luggage = TRUE;
    //else reserva->extra_luggage = FALSE;

    //if (strcmp(dados[6], "True") == 0) reserva->priority_boarding = TRUE;
    //else reserva->priority_boarding = FALSE;

    //reserva->qr_code = dados[7];

    return reserva;
}

/*
Reserva* cria_reserva(gchar** dados) {
    Reserva* reserva = malloc(sizeof(struct reserva));
    if (!reserva) return NULL;
    
    reserva->reservation_id = dados[0]; dados[0] = NULL;
    reserva->document_number = dados[2]; dados[2] = NULL;

    // a string original em dados[1] deve ser limpa depois.
    reserva->flight_ids = type_string_flight_ids(dados[1]);
    
    reserva->price = atof(dados[4]);
    
    return reserva;
}
*/

const char *get_reservation_id (const Reserva *reservation) {
    return reservation->reservation_id;
}

const char *get_reservation_document_number (const Reserva *reservation) {
    return reservation->document_number;
}

GPtrArray *get_flight_ids (const Reserva *reservation) {
    return reservation->flight_ids;
}

float get_reservation_price (const Reserva *reservation) {
    return reservation->price;
}

void free_reserva (void* r) {
    Reserva *reserva = r;
    if (!reserva) return;

    free (reserva->reservation_id);
    if (reserva->flight_ids) g_ptr_array_free(reserva->flight_ids, TRUE);
    free (reserva->document_number);
    //free (reserva->seat);
    //free (reserva->qr_code);
    free (reserva);
}
