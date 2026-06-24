#include "validacao_logica_dados.h"
#include "voo.h"
#include "aeronave.h"
#include <string.h>
#include <stdio.h>
#include <glib.h>
#include "reserva.h"
#include "gestor_global.h"

// Validação lógica dos voos
int valida_logica_voo (void *voo, void *colecao) {
    const Voo *v = voo;
    GestorGlobal *g = colecao;
    return (voo_origem_destino_validos (v) == 0 &&
            voo_datas_validas_logic (v) == 0 && 
            voo_aircraft_valida (v,get_gestor_Aeronaves(g)) == 0) ? 0 : 1;
}

// Validação lógica das reservas
int valida_logica_reserva (void *res, void *colecao) {
    const Reserva *r = res;
    GestorGlobal *g = colecao;
    return (reserva_flight_id_valid (r,get_gestor_Voos(g)) == 0 &&
            reserva_document_number (r,get_gestor_Passageiros(g)) == 0 &&
            reserva_same_fightId (r,get_gestor_Voos(g)) == 0) ? 0 : 1;
}

/*
Casos de Devolução:
    0 -> se o campo destination do voo for diferente do campo origin
    1 -> caso contrário
*/
int voo_origem_destino_validos(const void *voo) {
    const Voo *v= voo;
    const char *origin = get_origin(v);
    const char *destination = get_destination(v);

    if (!origin || !destination)
        return 1;

    return strcmp(origin, destination) != 0 ? 0 : 1; 
}

/*
Casos de Devolução:
    0 -> se os campos são válidos
    1 -> caso contrário
*/
int voo_datas_validas_logic(const void *voo) {
    const Voo *v= voo;
    GDateTime *departure = get_departure(v);
    GDateTime *actualDeparture = get_actual_departure(v);
    GDateTime *arrival = get_arrival(v);
    GDateTime *actualArrival = get_actual_arrival(v);
    VooStatus status = get_status(v);
    
    if (!departure || !arrival) 
        return 1;
    
    if (g_date_time_compare (arrival,departure) <= 0)
        return 1;

    switch (status) {
        case ON_TIME:
            if (!actualDeparture || !actualArrival)
                return 1; 
            if (g_date_time_compare(actualArrival, actualDeparture) <= 0)
                return 1; 
            break;

        case CANCELLED:
            if (actualDeparture != NULL || actualArrival != NULL)
                return 1;
            break;

        case DELAYED:
            if (!actualDeparture || !actualArrival)
                return 1; 
            if (g_date_time_compare(actualDeparture, departure) < 0 ||
                g_date_time_compare(actualArrival, arrival) < 0 ||
                g_date_time_compare(actualArrival, actualDeparture) <= 0)
                return 1;
            break;

        default:
            return 1;
    }
    
    return 0;
}

/*
Casos de Devolução:
    0 -> o campo aircraft corresponde a uma aeronave existente
    1 -> caso contrário
*/
int voo_aircraft_valida (const void *voo, Aeronaves *gestorAeronaves) {
    const Voo *v= voo;
    if (!v) return 1;

    const char *aircraft = get_aircraft (v);
    if (!aircraft) return 1;
      
    Aeronave *a = aeronaves_get_by_id (gestorAeronaves,aircraft);
    return (a == NULL) ? 1 : 0;
}

/*
Casos de Devolução:
    0 -> possui um ou dois voos e todos eles existentes
    1 -> caso contrário
*/
int reserva_flight_id_valid (const void *res, Voos *gestorVoos) {
    const Reserva *r=res;
    GPtrArray *flightId = get_flight_ids(r);
    if(!flightId) return 1;

    int len = flightId->len;
    if (len <1 || len>2) return 1;

    for (int i = 0; i < len; i++) {
        char *flight_id = (char*) g_ptr_array_index(flightId, i);
        if (!flight_id || voos_get (gestorVoos,flight_id) == NULL) 
            return 1;
    }

    return 0;
}

int reserva_document_number (const void *res, Passageiros *gestorPassageiros) {
    const Reserva *r=res;
    const char *document_nr = get_reservation_document_number (r);
    if (!document_nr) return 1;

    Passageiro *passenger = passageiros_get (gestorPassageiros,document_nr);

    return (passenger == NULL) ? 1 : 0;
}

int reserva_same_fightId (const void *res, Voos *gestorVoos) {
    const Reserva *r=res;
    GPtrArray *flightIDs = get_flight_ids(r);

    if (flightIDs->len == 2) {
        const char *flightId1 = g_ptr_array_index(flightIDs, 0);
        const char *flightId2 = g_ptr_array_index(flightIDs, 1);

        Voo *v1 = voos_get (gestorVoos,flightId1);
        Voo *v2 = voos_get (gestorVoos,flightId2);

        const char *destination = get_destination (v1);
        const char *origin = get_origin (v2);

        if (!destination || !origin)
            return 1;

        if (strcmp (destination,origin) != 0)
            return 1;
    }

    return 0;
}




