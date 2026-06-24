#include "gestor_global.h"
#include "aeronaves.h"
#include "aeroportos.h"
#include "passageiros.h"
#include "reservas.h"
#include "voos.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"
#include "query6.h"
#include "output.h"

struct global {
    Aeronaves *gestorAeronaves;
    Aeroportos *gestorAeroportos;
    Passageiros *gestorPassageiros;
    Voos *gestorVoos;
    Reservas *gestorReservas;
    Queries *gestorQueries; // contém as estruturas auxiliares às queries
    GHashTable *gestorOutput; // contém a hash table do modulo do output
};

struct queries {
    GTree *btree_datas; // estrutura utilizada na query 3 (key: GDate*, value: InfoData*)

    // estruturas auxiliares usadas na query 5 (hash table e o array)
    GHashTable *airline_table;
    AirlineResult *airline_results;

    GHashTable *stats_nacionalidade; // estrutura utilizada na query 6 (key: char* nacionalidade, value: NacionalidadeInfo*)

    TableSemAno *semAno_table;
};

GestorGlobal *gestor_create() {
    GestorGlobal *g = malloc(sizeof(struct global));
    if (!g) return NULL;

    g->gestorAeronaves = aeronaves_create();
    g->gestorAeroportos = aeroportos_create();
    g->gestorPassageiros = passageiros_create();
    g->gestorVoos = voos_create();
    g->gestorReservas = reservas_create();
    g->gestorQueries = queries_create();
    g->gestorOutput = output_create();

    return g;
}

Queries *queries_create() {
    Queries *q = malloc (sizeof(struct queries));
    if (!q) return NULL;

    q->btree_datas = btree_datas_create();
    q->airline_table = airlines_create();
    q->airline_results = airlines_result_create();
    q->stats_nacionalidade = stats_nacionalidade_create();
    q->semAno_table = criaHashTableAnoSemanas();

    return q;
}  

void queries_prepare(GestorGlobal *g) {
    if (!g) return;

    aeronaves_ordena_listas (g->gestorAeronaves); // ordena todas as listas das aeronaves em função do flight count no fim de carregar todos os dados
    build_airline_results(g->gestorQueries->airline_table,g->gestorQueries->airline_results); // converte a hash table para array ficando ordenado
    criaTop10(g->gestorQueries->semAno_table);

}



void gestor_load(const char *dir, GestorGlobal *gestor) {
    aeronaves_load (dir,gestor->gestorAeronaves);
    aeroportos_load (dir,gestor->gestorAeroportos);
    passageiros_load (dir,gestor->gestorPassageiros);
    voos_load (dir,gestor);
    reservas_load (dir,gestor);

    queries_prepare(gestor);
}

void *get_gestor_Aeronaves(GestorGlobal *g) {
    return g->gestorAeronaves;
}

void *get_gestor_Aeroportos(GestorGlobal *g) {
    return g->gestorAeroportos;
}

void *get_gestor_Passageiros(GestorGlobal *g) {
    return g->gestorPassageiros;
}

void *get_gestor_Voos(GestorGlobal *g) {
    return g->gestorVoos;
}

void *get_gestor_Reservas(GestorGlobal *g) {
    return g->gestorReservas;
}

void *get_gestor_Queries(GestorGlobal *g) {
    return g->gestorQueries;
}

void *get_gestor_Output(GestorGlobal *g) {
    return g->gestorOutput;
}

void *get_btree_query3(Queries *q) {
    return q->btree_datas;
}

void *get_hashtable_query4(Queries *q) {
    return q->semAno_table;
}

void *get_array_query5(Queries *q) {
    return q->airline_results;
}

void *get_hashtable_query5(Queries *q) {
    return q->airline_table;
}

void *get_hashtable_query6(Queries *q) {
    return q->stats_nacionalidade;
}


void gestor_free(GestorGlobal *g) {
    aeronaves_free(g->gestorAeronaves);
    aeroportos_free(g->gestorAeroportos);
    passageiros_free(g->gestorPassageiros);
    voos_free(g->gestorVoos);
    reservas_free(g->gestorReservas);
    queries_free(g->gestorQueries);
    output_free(g->gestorOutput);

    free(g);
}

void queries_free(Queries *q) {
    free_btree_datas(q->btree_datas);
    free_airlines(q->airline_table,q->airline_results);
    free_stats_nacionalidade(q->stats_nacionalidade);
    g_hash_table_destroy(q->semAno_table);

    free(q);
}