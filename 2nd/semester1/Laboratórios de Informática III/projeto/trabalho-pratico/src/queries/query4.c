#include "query4.h"
#include "priority_queue.h"
#include "passageiro.h"
#include "utils.h"
#include "output.h"
#include "interativo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct semanaAno {
    int semana;
    int ano;
};

struct node {
    char *document_number;
    float gasto;
};

/*
A ideia passa por ter uma hash table em que:

    key: (Nº Semana, Ano)
    Value: countETop10

    countETop10 por usa vez tem:
    
        hash table count:
            key: document_number
            value: valor gasto naquela semana

        uma minheap que constitui um top 10 semanal que so é construída depois de todas as reservas do dataset serem lidas

    Para cada query criar uma hash table de counts para o intervalo dado, guardando apenas o melhor, algo do género do que fazemos na q3
*/
struct countETop10 {
    GHashTable *count; 
    PriorityQueue *top10;
};

struct hash_counter {
    GHashTable *hash_global;
    char *mais_vezes_top10;
    int melhor_count;
};

// Criação de estruturas auxiliares
CountEmTop10 *criaCountEmTop10() {
    CountEmTop10 *ctGlobal = malloc (sizeof (struct hash_counter));
    if (!ctGlobal) return NULL;

    ctGlobal->hash_global = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,g_free);
    ctGlobal->mais_vezes_top10 = NULL;
    ctGlobal->melhor_count = 0;

    return ctGlobal;
}

TableSemAno *criaHashTableAnoSemanas() {
    GHashTable *sa = g_hash_table_new_full(hashSemanaAno,compareSemAno,free,freeCountETop10);

    return sa;
}

CTop10 *criaCountETop10() {
    CTop10 *ct = malloc(sizeof (struct countETop10));
    if (!ct) return NULL;

    GHashTable *count = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,g_free);

    ct->count = count;
    ct->top10 = NULL;
    
    return ct;
}

gboolean compareSemAno(const void *sa1,const void *sa2) {
    const SemAno *SA1 = sa1;
    const SemAno *SA2 = sa2;

    return SA1->ano == SA2->ano && SA1->semana == SA2->semana;
}

int compareNodos(const void *novo,const void *topo) {
    const Nodo *Nnovo = novo;
    const Nodo *Ntopo = topo;

    if (Nnovo->gasto < Ntopo->gasto) return -1;
    else if (Nnovo->gasto > Ntopo->gasto) return 1;

    return -strcmp(Nnovo->document_number, Ntopo->document_number);
}

unsigned int hashSemanaAno(const void *sa) {
    const SemAno *SA = sa;
    return (unsigned int)(SA->ano * 53 + SA->semana);
}

const char *get_ctGlobal_melhor (CountEmTop10 *h) {
    return h->mais_vezes_top10;
}

int get_ctGlobal_count (CountEmTop10 *h) {
    return h->melhor_count;
}

// Query
SemAno *semanaAno (GDate *departure) {
    SemAno *sa = malloc(sizeof (struct semanaAno));
    if (!sa) return NULL;

    sa->ano = g_date_get_year(departure);
    sa->semana = g_date_get_sunday_week_of_year(departure);

    return sa;
}

void adicionaGasto(float gasto, char *document_number, const Voo *v, TableSemAno *semAno_table) {
    if (!v || !semAno_table || !document_number) return;

    GDateTime *dp = get_departure(v);
    if (!dp) {
        free(document_number);
        return;
    }

    GDate *departure = datetime_to_date(dp);
    if (!departure) {
        free(document_number);
        return;
    }

    SemAno *sa = semanaAno(departure);
    if (!sa) {
        free(document_number);
        return;
    }
    g_date_free(departure);

    CTop10 *ct = g_hash_table_lookup(semAno_table, sa);
    if (!ct) {
        ct = criaCountETop10();
        g_hash_table_insert(semAno_table, sa, ct);
    }

    else free(sa);

    float *prev = g_hash_table_lookup(ct->count, document_number);

    if (prev) {
        *prev += gasto;
        free(document_number);
    }
        
    else {
        float *novoGasto = malloc(sizeof (float));
        *novoGasto = gasto;
        g_hash_table_insert(ct->count, document_number, novoGasto);
    }
}

void criaTop10(TableSemAno *semAno_table) {
    if (!semAno_table) return;

    GHashTableIter iter1;
    gpointer key1, value1;
    g_hash_table_iter_init(&iter1, semAno_table);

    while (g_hash_table_iter_next(&iter1, &key1, &value1)) {
        CTop10 *ct = (CTop10*)value1;
        GHashTableIter iter2;
        gpointer key2, value2;
        g_hash_table_iter_init(&iter2, ct->count);

        while (g_hash_table_iter_next(&iter2, &key2, &value2)) {
            Nodo *n = malloc(sizeof (struct node));
            n->document_number = strdup((char *)key2);
            n->gasto = *(float*)value2;

            if (!ct->top10) {
                ct->top10 = pq_newGasto(compareNodos,freeNodos);
            }

            pq_pushGasto(ct->top10,n);
        }
    }
}

void query4_com_filtro(GDate *data_inicio, GDate *data_fim, char c, const char *output_file, Passageiros *gestorPassageiros, TableSemAno *semAno_table) {
    int modo_interativo = (output_file == NULL);

    FILE *out = !modo_interativo ? fopen(output_file, "w") : NULL;
    if (!out && !modo_interativo)
        return;

    CountEmTop10 *ctGlobal = criaCountEmTop10();
    if (!ctGlobal) return;

    GDate *d = g_date_new_dmy(
        g_date_get_day(data_inicio),
        g_date_get_month(data_inicio),
        g_date_get_year(data_inicio)
    );

    while (g_date_get_weekday(d) != G_DATE_SUNDAY) {
        g_date_subtract_days(d, 1);
    }

    while (g_date_compare(d, data_fim) <= 0) {
        SemAno *sa = semanaAno(d);

        CTop10 *ct = g_hash_table_lookup(semAno_table, sa);
        if (!ct || !ct->top10) {
            free(sa);
            g_date_add_days(d, 7);
            continue;
        }

        PriorityQueue *pq = ct->top10;
        if (!pq) continue;

        int size = get_pq_size(pq);
        for (int i = 0; i<size; i++) {
            const Nodo *n = get_pq_data(pq,i);
            if (!n) continue;
            const char *doc = n->document_number;
            
            int *count = g_hash_table_lookup(ctGlobal->hash_global,doc);
            if (count == NULL) {
                count = malloc (sizeof(int));
                *count = 1;
                g_hash_table_insert(ctGlobal->hash_global,strdup(doc),count);
            } else {
                *count += 1;
            }

            if (ctGlobal->mais_vezes_top10 == NULL || *count > ctGlobal->melhor_count || 
                (*count == ctGlobal->melhor_count && strcmp(doc,ctGlobal->mais_vezes_top10) < 0 )) {
                    free (ctGlobal->mais_vezes_top10);
                    ctGlobal->mais_vezes_top10 = strdup (doc);
                    ctGlobal->melhor_count = *count;
            }  

        }

        free(sa);
        g_date_add_days(d, 7);      // avançar uma semana
    }


    const char *melhor = ctGlobal->mais_vezes_top10;
    if (!melhor) {
        if (!modo_interativo)
            fprintf(out, "\n");
        else 
            output_interativo_query4(NULL,gestorPassageiros,data_inicio,data_fim);
    } else {
        Passageiro *p= passageiros_get(gestorPassageiros,melhor);

        if (modo_interativo) {
           output_interativo_query4(ctGlobal,gestorPassageiros,data_inicio,data_fim);
        } else {
            char buffer_count[32];
            sprintf (buffer_count,"%d",ctGlobal->melhor_count); // necessário para converter para string

            output_fields (out,c,6,                  
                ctGlobal->mais_vezes_top10,
                get_first_name(p),
                get_last_name(p),
                get_dob(p),
                get_nationality(p),
                buffer_count
            );
        }
    }

    if (!modo_interativo) fclose(out);
    g_date_free(d);
    freeCountEmTop10(ctGlobal);
}

void query4_sem_filtro(char c, const char *output_file, Passageiros *gestorPassageiros, TableSemAno *semAno_table) {
    CountEmTop10 *ctGlobal = criaCountEmTop10();
    if (!ctGlobal) return;

    int modo_interativo = (output_file == NULL);

    FILE *out = !modo_interativo ? fopen(output_file, "w") : NULL;
    if (!out && !modo_interativo)
        return;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, semAno_table);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        CTop10 *ct = (CTop10*)value;
        if (!ct->top10) continue;

        PriorityQueue *pq = ct->top10;
        if (!pq) continue;

        int size = get_pq_size(pq);
        for (int i = 0; i<size; i++) {
            const Nodo *n = get_pq_data(pq,i);
            if (!n) continue;
            const char *doc = n->document_number;
            
            int *count = g_hash_table_lookup(ctGlobal->hash_global,doc);
            if (count == NULL) {
                count = malloc (sizeof(int));
                *count = 1;
                g_hash_table_insert(ctGlobal->hash_global,strdup(doc),count);
            } else {
                *count += 1;
            }

            if (ctGlobal->mais_vezes_top10 == NULL || *count > ctGlobal->melhor_count || 
                (*count == ctGlobal->melhor_count && strcmp(doc,ctGlobal->mais_vezes_top10) < 0)) { 
                    free (ctGlobal->mais_vezes_top10);
                    ctGlobal->mais_vezes_top10 = strdup (doc);
                    ctGlobal->melhor_count = *count;
            }  

        }
    }

    const char *melhor = ctGlobal->mais_vezes_top10;
    if (!melhor) {
        if (!modo_interativo)
            fprintf(out, "\n");
        else 
            output_interativo_query4(NULL,gestorPassageiros,NULL,NULL);
    } else {
        Passageiro *p = passageiros_get(gestorPassageiros,melhor);

        if (modo_interativo) {
           output_interativo_query4(ctGlobal,gestorPassageiros,NULL,NULL);
        } else {
            char buffer_count[32];
            sprintf (buffer_count,"%d",ctGlobal->melhor_count); // necessário para converter para string

            output_fields (out,c,6,                  
                ctGlobal->mais_vezes_top10,
                get_first_name(p),
                get_last_name(p),
                get_dob(p),
                get_nationality(p),
                buffer_count
            );
        }
    }

    if (!modo_interativo) fclose(out);
    freeCountEmTop10(ctGlobal);
}

void query4_passageiro_mais_vezes_top10(GDate *data_inicio, GDate *data_fim, char c, const char *output_file, Passageiros *gestorPassageiros, TableSemAno *semAno_table) {
    if (!data_inicio && !data_fim) 
        query4_sem_filtro(c,output_file,gestorPassageiros,semAno_table);
    else 
        query4_com_filtro(data_inicio,data_fim,c,output_file,gestorPassageiros,semAno_table);
}

// Frees
void freeCountEmTop10(void *ct) {
    if (!ct) return;
    
    CountEmTop10 *c = ct;
    g_hash_table_destroy(c->hash_global);
    free(c->mais_vezes_top10);
    free(c);
}

void freeCountETop10 (void *ct) {
    if (!ct) return;
    CTop10 *c = ct;
    g_hash_table_destroy(c->count);
    pq_free(c->top10);
    free(c);
}

void freeNodos (void *n) {
    if (!n) return;
    Nodo *nodo = n;
    free(nodo->document_number);
    free(nodo);
}



