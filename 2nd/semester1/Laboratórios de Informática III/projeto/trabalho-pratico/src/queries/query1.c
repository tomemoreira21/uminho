#include "query1.h"
#include "aeroportos.h"
#include "output.h" 
#include "interativo.h"
#include <stdio.h> 
#include <string.h>

void incrementa_arrival_e_departure_count_na_coleção(Aeroportos *gestor, const Voo *voo) {
    incrementa_departure_count_na_coleção(gestor,get_origin(voo));
    incrementa_arrival_count_na_coleção(gestor,get_destination(voo));
}

void query1_listar_aeroporto (const char *code, char c, const char *output_file, Aeroportos *gestorAeroportos) {
    FILE *out = (output_file != NULL) ? fopen (output_file,"w") : NULL;
    Aeroporto *airport = aeroportos_get (gestorAeroportos,code);

    if (output_file == NULL) {
        output_interativo_aeroporto(airport);
        return;
    }

    if (airport == NULL) {
        fprintf (out,"\n");
        fclose(out);
        return;
    }

    char buffer_count_arrival[32], buffer_count_departure[32];
    sprintf (buffer_count_arrival,"%d",get_airport_arrival_count(airport)); // necessário para converter para string
    sprintf (buffer_count_departure,"%d",get_airport_departure_count(airport)); // necessário para converter para string
    
    output_fields (out,c,7,
        get_airport_code(airport),
        get_airport_name(airport),
        get_airport_city(airport),
        get_airport_country(airport),
        get_airport_type_string(airport),
        buffer_count_arrival,
        buffer_count_departure
    );
    
    fclose(out);
}

