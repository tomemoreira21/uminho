#include "query2.h"
#include "output.h"
#include "interativo.h"
#include <aeronaves.h>
#include <utils.h>
#include <priority_queue.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

struct entradaheap {
    GList *nodo;
};

void incrementa_flight_count_da_aeronave(Aeronaves *gestorAeronaves, Voo* voo) {
    if (!voo) return;

    const char* aircraft_id = get_aircraft(voo);
    Aeronave* a = aeronaves_get_by_id(gestorAeronaves,aircraft_id);
    if (!a) return;

    const char* manufacturer = get_aircraft_manufactor(a);
    Fabricante *fab = g_hash_table_lookup(aeronaves_get_all_manufacturers(gestorAeronaves), manufacturer);
    if (!fab) return;

    Aeronave *aircraft = g_hash_table_lookup(aeronaves_get_airplane_id (fab), aircraft_id);
    if (!aircraft) return;

    incrementa_flight_count(aircraft);
}

int compare_heap_entry (const void *a,const void *b) {
    const EntradaHeap *ea = (const EntradaHeap*)a;
    const EntradaHeap *eb = (const EntradaHeap*)b;
    
    const Aeronave *a1 = (const Aeronave *)ea->nodo->data;
    const Aeronave *a2 = (const Aeronave *)eb->nodo->data;

    return -aeronaves_compare_flight_count (a1,a2); // Inverter sinal -> para ficar uma max-heap
}

void query2_com_filtro (int N, const char *manufacturer, char c,const char *output_file, Aeronaves *gestorAeronaves) {    
    if (!manufacturer || N <= 0 || !aeronaves_is_initialized(gestorAeronaves)) 
        return;

    int modo_interativo = (output_file == NULL);

    FILE *out = !modo_interativo ? fopen (output_file,"w") : NULL; // se não existir o ficheiro txt ele cria-o
    if (!modo_interativo && !out) return;

    GList *lista_interativa = NULL;
    GList *lista = aeronaves_get_by_manufacturer (gestorAeronaves,manufacturer);
    if (lista == NULL) {
        if (!modo_interativo) {
            fprintf (out,"\n");
            fclose (out);
        } else {
            output_interativo_query2(lista_interativa,N);
            g_list_free(lista_interativa);
        }
        return;
    }

    for (int i = 0; i < N && lista != NULL; i++) {
        Aeronave *a = (Aeronave *)lista->data;

        if (modo_interativo) {
            lista_interativa = g_list_append(lista_interativa, a);
        } else {
            char buffer_count[32];
            sprintf (buffer_count,"%d",get_aircraft_flight_count(a)); // necessário para converter para string

            output_fields (out,c,4,
                get_aircraft_identifier(a),
                get_aircraft_manufactor(a),
                get_aircraft_model(a),
                buffer_count    
            );
        }

        lista = lista->next;
    }

    if (!modo_interativo) 
        fclose (out);
    else {
        output_interativo_query2(lista_interativa,N);
        g_list_free(lista_interativa);
    }
}

void query2_sem_filtro (int N, char c,const char *output_file, Aeronaves *gestorAeronaves) {
    if (N <= 0 || !aeronaves_is_initialized(gestorAeronaves)) 
        return;

    int modo_interativo = (output_file == NULL);

    FILE *out = !modo_interativo ? fopen (output_file,"w") : NULL; // se não existir o ficheiro txt ele cria-o
    if (!modo_interativo && !out) return;

    GList *lista_interativa = NULL;
    PriorityQueue *pq = pq_new (compare_heap_entry,free);
    GHashTable *all = aeronaves_get_all_manufacturers(gestorAeronaves);

    if (!all) return;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, all);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Fabricante *fab = (Fabricante*)value;
        GList *lista = aeronaves_get_airplane_list(fab);

        if (lista != NULL) {
            EntradaHeap *entry = malloc(sizeof(EntradaHeap));
            entry->nodo = lista;
            pq_push(pq, entry);
        }
    }

    int printed = 0;
    while (!pq_is_empty (pq) && printed < N) {
        EntradaHeap *top = pq_pop (pq);
        Aeronave *a = (Aeronave *)top->nodo->data;

        if (modo_interativo) {
            lista_interativa = g_list_append(lista_interativa, a);
        } else {
            char buffer_count[32];
            sprintf (buffer_count,"%d",get_aircraft_flight_count(a)); // necessário para converter para string

            output_fields (out,c,4,
                get_aircraft_identifier(a),
                get_aircraft_manufactor(a),
                get_aircraft_model(a),
                buffer_count    
            );
        }

        printed++;

        // Avançar na lista do fabricante
        if (top->nodo->next != NULL) {
            top->nodo = top->nodo->next;
            pq_push (pq,top);
        } else {
            free (top);
        }
    }

    pq_free(pq);

    if (!modo_interativo)
        fclose (out);
    else {
        output_interativo_query2(lista_interativa,N);
        g_list_free(lista_interativa);
    }
}

void query2_listar_aeronaves_mais_voos (int N, const char *manufactor, char c, const char *output_file, Aeronaves *gestorAeronaves) {
    if (manufactor != NULL)
        query2_com_filtro (N,manufactor,c,output_file,gestorAeronaves);
    else 
        query2_sem_filtro (N,c,output_file,gestorAeronaves);
}

