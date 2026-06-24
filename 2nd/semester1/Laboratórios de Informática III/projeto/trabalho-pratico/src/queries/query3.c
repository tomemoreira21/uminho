#include "query3.h"
#include "utils.h"
#include "output.h"
#include "interativo.h"
#include <aeroportos.h>
#include <stdio.h>

struct info_data {
    GHashTable *voos_por_aeroporto; // key: code aeroporto (char*), value: int* (count)
};

struct hash_counter {
    GHashTable *hash_global;
    char *melhor_aeroporto;
    int melhor_count;
    GDate *data_inicio;
    GDate *data_fim;
};

GTree *btree_datas_create() {
    GTree *btree_datas = g_tree_new_full ((GCompareDataFunc) compare_dates,NULL,(GDestroyNotify) g_date_free,(GDestroyNotify)info_data_free);
    
    return btree_datas;
}

InfoData *info_data_new () {
    InfoData *info = malloc (sizeof (struct info_data));
    info->voos_por_aeroporto = g_hash_table_new_full (g_str_hash,g_str_equal,g_free,free);

    return info;
}

HashCounter *hash_counter_init(GDate *inicio,GDate *fim) {
    HashCounter *hash = malloc (sizeof (struct hash_counter));
    hash->hash_global = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);
    hash->melhor_aeroporto = NULL;
    hash->melhor_count = 0;

    hash->data_inicio = inicio ? g_date_copy (inicio) : NULL;
    hash->data_fim = fim ? g_date_copy (fim) : NULL;

    return hash;
}

/*
A árvore está na seguinte ordem:
    Esquerda -> datas mais antigas
    Direita -> datas mais recentes
*/
int compare_dates(const void *a, const void *b, void *user_data) {
    (void)user_data;

    const GDate *date1 = (const GDate *)a;
    const GDate *date2 = (const GDate *)b;

    if (g_date_get_year(date1) != g_date_get_year(date2))
        return g_date_get_year(date1) - g_date_get_year(date2);

    if (g_date_get_month(date1) != g_date_get_month(date2))
        return g_date_get_month(date1) - g_date_get_month(date2);

    return g_date_get_day(date1) - g_date_get_day(date2);
}

void adicionar_voo_btree (Voo *voo,GTree *btree_datas) {
    if (!btree_datas || !voo) return;

    GDateTime *dt = get_actual_departure (voo);
    if (!dt) return;

    GDate *data_voo = datetime_to_date (dt);
    InfoData *info = g_tree_lookup (btree_datas,data_voo);

    if (info == NULL) {
        info = info_data_new();
        g_tree_insert (btree_datas,g_date_copy(data_voo),info);
    }

    const char *origem = get_origin (voo);
    int *count = g_hash_table_lookup(info->voos_por_aeroporto,origem);

    if (!count) {
        count = malloc (sizeof(int));
        *count = 1;
        g_hash_table_insert(info->voos_por_aeroporto,g_strdup(origem),count);
    } else {
        (*count)++;
    }

    g_date_free (data_voo);
}

void acumula_voos_por_data (void *key,void *value,void *user_data) {
    (void)key;
    
    InfoData *info = (InfoData*)value;
    HashCounter *h = (HashCounter*)user_data;

    GHashTableIter iter;
    char *airport_code;
    int *count_ptr;
    g_hash_table_iter_init (&iter,info->voos_por_aeroporto);

    while (g_hash_table_iter_next (&iter,(void**)&airport_code,(void**)&count_ptr)) {
        const char *code = airport_code;
        int count = *count_ptr;

        int *count_global = g_hash_table_lookup(h->hash_global,code);
        if (count_global == NULL) {
            count_global = malloc (sizeof(int));
            *count_global = count;
            g_hash_table_insert(h->hash_global,g_strdup (code),count_global);
        } else {
            *count_global += count;
        }

        if (h->melhor_aeroporto == NULL || *count_global > h->melhor_count || 
            (*count_global == h->melhor_count && strcmp (code,h->melhor_aeroporto) < 0)) {
                free (h->melhor_aeroporto);
                h->melhor_aeroporto = strdup (code);
                h->melhor_count = *count_global;
        }   
    }
}

gboolean percorre_datas_intervalo(HashCounter *h,GTree *btree_datas) {
    if (!btree_datas || !h || !h->data_inicio || !h->data_fim) 
        return FALSE;

    // Começa no primeiro nó >= data_inicio
    GTreeNode *it = g_tree_lower_bound (btree_datas,h->data_inicio);
    while (it != NULL) {
        GDate *data_voo = g_tree_node_key(it);
        InfoData *info = g_tree_node_value(it);

        if (g_date_compare(data_voo,h->data_fim) > 0)
            break;
        
        acumula_voos_por_data(data_voo,info,h);

        it = g_tree_node_next(it);
    }

    return TRUE;
}

const char *hash_counter_get_melhor_aeroporto(const HashCounter *h) {
    return h ? h->melhor_aeroporto : NULL;
}

int hash_counter_get_melhor_count(const HashCounter *h) {
    return h ? h->melhor_count : 0;
}

void free_btree_datas(GTree *btree_datas) {
    if (btree_datas != NULL) {
        g_tree_destroy(btree_datas);
        btree_datas = NULL;
    }
}

void info_data_free(InfoData *info) {
    if (!info) return;
    g_hash_table_destroy (info->voos_por_aeroporto);    
    free (info);
}

void hash_free (HashCounter *h) {
    if (!h) return;
    g_hash_table_destroy (h->hash_global);
    free (h->melhor_aeroporto);
    if (h->data_inicio) g_date_free (h->data_inicio);
    if (h->data_fim) g_date_free (h->data_fim);
    free (h);
}

void query3_aeroporto_mais_partidas(GDate *data_inicio, GDate *data_fim, char c, const char *output_file, Aeroportos *gestorAeroportos,GTree *btree_datas) {
    int modo_interativo = (output_file == NULL);

    FILE *out = !modo_interativo ? fopen(output_file, "w") : NULL;
    if (!out && !modo_interativo)
        return;

    HashCounter *h = hash_counter_init(data_inicio, data_fim);
    percorre_datas_intervalo(h,btree_datas);

    const char *melhor = hash_counter_get_melhor_aeroporto(h);
    if (!melhor) {
        if (!modo_interativo)
            fprintf(out, "\n");
        else 
            output_interativo_aeroporto(NULL);
    } else {
        Aeroporto *airport = aeroportos_get(gestorAeroportos,melhor);

        if (modo_interativo) {
           output_interativo_aeroporto(airport);
        } else {
            char buffer_count[32];
            sprintf (buffer_count,"%d",hash_counter_get_melhor_count(h)); // necessário para converter para string

            output_fields (out,c,5,
                get_airport_code(airport),
                get_airport_name(airport),
                get_airport_city(airport),
                get_airport_country(airport),
                buffer_count
            );
        }
    }

    if (!modo_interativo) fclose(out);
    hash_free(h);
}
