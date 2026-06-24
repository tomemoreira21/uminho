#define _GNU_SOURCE
#include "testar.h"
#include "utils.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query5.h"
#include "query4.h"
#include "query6.h"
#include "output.h"
#include "interpretador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <sys/resource.h>

struct queryStats {
    int total;
    int corretos;
    int erros;
    double tempo;
    int *primeira_linha_erro;
    int *nr_query;
    char **arquivo_erro;
    int tam;
};

static QueryStats *stats = NULL;
#define NUM_QUERIES 6

// Calcula diferença entre tempos
double diff_time(struct timespec start, struct timespec end) {
    double tempo = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return tempo;
}

// Memória usada (KB)
long memoria_usada_kb() {
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    return r_usage.ru_maxrss;
}

/*
Casos de Devolução:
    0 -> os ficheiros forem iguais
    -1 -> um dos ficheiros estiver vazio no inicio
    nr -> nr da primeira incongruência
*/
int compara_ficheiros(const char *ficheiro1, const char *ficheiro2) {
    gchar *conteudo1 = NULL;
    gchar *conteudo2 = NULL;

    if (!g_file_get_contents(ficheiro1, &conteudo1, NULL, NULL) ||
        !g_file_get_contents(ficheiro2, &conteudo2, NULL, NULL)) {
        g_free(conteudo1); g_free(conteudo2);
        return -1; 
    }

    GStrv linhas1 = g_strsplit(conteudo1, "\n", 0);
    GStrv linhas2 = g_strsplit(conteudo2, "\n", 0);

    int linha = 0;
    while (linhas1[linha] && linhas2[linha]) {
        if (strcmp(linhas1[linha], linhas2[linha]) != 0) {
            g_strfreev(linhas1); g_strfreev(linhas2);
            g_free(conteudo1); g_free(conteudo2);
            return linha + 1;
        }
        linha++;
    }

    if ((linhas1[linha] == NULL && linhas2[linha] != NULL) || 
        (linhas1[linha] != NULL && linhas2[linha] == NULL)) {

        g_strfreev(linhas1); g_strfreev(linhas2);
        g_free(conteudo1); g_free(conteudo2);
        return linha + 1;
    }

    g_strfreev(linhas1); g_strfreev(linhas2);
    g_free(conteudo1); g_free(conteudo2);
    return 0; 
}

void inicializar_stats(int num_queries) {
    stats = malloc(sizeof(struct queryStats) * num_queries);

    for (int i = 0; i < num_queries; i++) {
        stats[i].total = 0;
        stats[i].corretos = 0;
        stats[i].erros = 0;
        stats[i].tempo = 0.0;
        stats[i].tam = 8;
        stats[i].primeira_linha_erro = malloc (stats[i].tam * sizeof (int));
        stats[i].nr_query = malloc (stats[i].tam * sizeof (int));
        stats[i].arquivo_erro = malloc(stats[i].tam * sizeof(char*));
    }
}

void executar_testes(const char *input_file, const char *pasta_output_esperado, GestorGlobal *g) {
    FILE *file = fopen(input_file, "r");
    if (!file) return;

    char *linha = NULL;
    size_t len = 0;
    ssize_t read;
    int query_output_counter = 1;
    int nr_query = 0;

    inicializar_stats(NUM_QUERIES);

    struct timespec start_total, end_total;
    clock_gettime(CLOCK_REALTIME, &start_total);

    while ((read = getline(&linha, &len, file)) != -1) {
        nr_query ++;

        if (read > 0 && linha[read - 1] == '\n')
            linha[read - 1] = '\0';

        char *linha_init = strdup(linha);
        if (!linha_init) continue;

        int query_num = 0;
        int has_suffix = 0;
        char suffix_char = '\0';

        char *rest = parse_query_token(linha_init, &query_num, &has_suffix,&suffix_char);
        if (!rest && query_num == 0) {
            free(linha_init);
            continue;
        }

        char sep_char = has_suffix ? output_get_separador(suffix_char,get_gestor_Output(g)) : ';'; // default será ';'

        gchar *output_esperado = g_strdup_printf("%s/command%d_output.txt", pasta_output_esperado, nr_query);

        char output_gerado[256];
        snprintf(output_gerado, sizeof(output_gerado), "resultados/command%d_output.txt", query_output_counter++);

        switch (query_num) {
            case 1:
                execution_stats_q1(rest,output_gerado, output_esperado, sep_char,nr_query, get_gestor_Aeroportos(g));
                break;

            case 2:
                if (!rest) break;
                char *n_str = strsep(&rest, " ");
                if (!n_str) break;
                int N = atoi(n_str);
                char *manufacturer = (rest && strlen(rest) > 0) ? rest : NULL;
                execution_stats_q2(N, manufacturer, output_gerado, output_esperado, sep_char, nr_query,get_gestor_Aeronaves(g));
                break;

            case 3:
                if (!rest) break;
                char *data_inicio_str = strsep(&rest, " ");
                char *data_fim_str = (rest && strlen(rest) > 0) ? rest : NULL;
                if (!data_inicio_str || !data_fim_str) break;

                GDate *data_inicio = type_string_to_gdate (data_inicio_str);
                GDate *data_fim = type_string_to_gdate (data_fim_str);

                execution_stats_q3(data_inicio,data_fim,output_gerado, output_esperado, sep_char, nr_query,get_gestor_Aeroportos(g),get_btree_query3(get_gestor_Queries(g)));
                
                g_date_free (data_inicio);
                g_date_free (data_fim);
                break;

            case 4:
                if (!rest) 
                    execution_stats_q4(NULL,NULL,output_gerado,output_esperado,sep_char,nr_query,get_gestor_Passageiros(g),get_hashtable_query4(get_gestor_Queries(g)));

                else {
                    char *data_inicio_str = strsep(&rest, " ");
                    char *data_fim_str = (rest && strlen(rest) > 0) ? rest : NULL;

                    if (!data_inicio_str || !data_fim_str) break;
                    GDate *data_inicio = type_string_to_gdate (data_inicio_str);
                    GDate *data_fim = type_string_to_gdate (data_fim_str);

                    execution_stats_q4(data_inicio,data_fim,output_gerado,output_esperado,sep_char,nr_query,get_gestor_Passageiros(g),get_hashtable_query4(get_gestor_Queries(g)));

                    g_date_free (data_inicio);
                    g_date_free (data_fim);
                }
                
                break;

            case 5:
                if (!rest) break;
                char *topN_str = strsep(&rest, " ");
                if (!topN_str) break;
                int topN = atoi(topN_str);
                execution_stats_q5(output_gerado,output_esperado,topN,sep_char,nr_query,get_array_query5(get_gestor_Queries(g)));
                break;

            case 6:
                if (!rest) break;
                while (*rest == ' ') rest++;
                char *nationality = rest;
                if (!nationality) break;
                execution_stats_q6(output_gerado,output_esperado,nationality,sep_char,nr_query,get_hashtable_query6(get_gestor_Queries(g)));
                break;

            default:
                break;

        }

        free (linha_init);
        g_free(output_esperado);
    }

    clock_gettime(CLOCK_REALTIME, &end_total);
    double tempo_total_s = diff_time(start_total, end_total);
    long mem_kb = memoria_usada_kb();

    mostrar_resultados(NUM_QUERIES,tempo_total_s, mem_kb);
    free (linha);
    fclose (file);
    free_stats(NUM_QUERIES);
}

void execution_stats_q1(const char *rest, const char *output_gerado, const gchar *output_esperado, char c, int nr_query, Aeroportos *gestorAeroportos) {
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    query1_listar_aeroporto(rest, c,output_gerado,gestorAeroportos);

    clock_gettime(CLOCK_REALTIME, &end);
    double tempo_s = diff_time(start, end);

    int linha_diff = compara_ficheiros(output_gerado, output_esperado);
    stats[0].total++;
    stats[0].tempo += tempo_s;

    if (linha_diff == 0) {                          
        stats[0].corretos++;
    } 
    else if (linha_diff == -1) {
        stats[0].erros++;
    }
    else {  
        if (stats[0].erros >= stats[0].tam) {
            stats[0].tam *= 2;
            stats[0].primeira_linha_erro = realloc(stats[0].primeira_linha_erro, sizeof(int) * stats[0].tam);
            stats[0].nr_query = realloc(stats[0].nr_query, sizeof(int) * stats[0].tam);
            stats[0].arquivo_erro = realloc(stats[0].arquivo_erro, sizeof(char*) * stats[0].tam);
        }

        int idx = stats[0].erros;
        stats[0].primeira_linha_erro[idx] = linha_diff;
        stats[0].nr_query[idx] = nr_query;
        stats[0].arquivo_erro[idx] = g_strdup(output_gerado);
        stats[0].erros++;
    }
}

void execution_stats_q2(int N, const char *manufactor, const char *output_gerado, const gchar *output_esperado, char c, int nr_query, Aeronaves *gestorAeronaves) {
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    query2_listar_aeronaves_mais_voos(N, manufactor, c, output_gerado,gestorAeronaves);

    clock_gettime(CLOCK_REALTIME, &end);
    double tempo_s = diff_time(start, end);

    int linha_diff = compara_ficheiros(output_gerado, output_esperado);
    stats[1].total++;
    stats[1].tempo += tempo_s;

    if (linha_diff == 0) {                          
        stats[1].corretos++;
    } 
    else if (linha_diff == -1) {
        stats[1].erros++;
    }
    else {  
        if (stats[1].erros >= stats[1].tam) {
            stats[1].tam *= 2;
            stats[1].primeira_linha_erro = realloc(stats[1].primeira_linha_erro, sizeof(int) * stats[1].tam);
            stats[1].nr_query = realloc(stats[1].nr_query, sizeof(int) * stats[1].tam);
            stats[1].arquivo_erro = realloc(stats[1].arquivo_erro, sizeof(char*) * stats[1].tam);
        }

        int idx = stats[1].erros;
        stats[1].primeira_linha_erro[idx] = linha_diff;
        stats[1].nr_query[idx] = nr_query;
        stats[1].arquivo_erro[idx] = g_strdup(output_gerado);
        stats[1].erros++;
    }
}

void execution_stats_q3(GDate *data_inicio, GDate *data_fim, const char *output_gerado, const gchar *output_esperado, char c, int nr_query, Aeroportos *gestorAeroportos,GTree *btree_datas) {
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    query3_aeroporto_mais_partidas (data_inicio,data_fim,c,output_gerado,gestorAeroportos,btree_datas);

    clock_gettime(CLOCK_REALTIME, &end);
    double tempo_s = diff_time(start, end);

    int linha_diff = compara_ficheiros(output_gerado, output_esperado);
    stats[2].total++;
    stats[2].tempo += tempo_s;

    if (linha_diff == 0) {                          
        stats[2].corretos++;
    } 
    else if (linha_diff == -1) {
        stats[2].erros++;
    }
    else {  
        if (stats[2].erros >= stats[2].tam) {
            stats[2].tam *= 2;
            stats[2].primeira_linha_erro = realloc(stats[2].primeira_linha_erro, sizeof(int) * stats[2].tam);
            stats[2].nr_query = realloc(stats[2].nr_query, sizeof(int) * stats[2].tam);
            stats[2].arquivo_erro = realloc(stats[2].arquivo_erro, sizeof(char*) * stats[2].tam);
        }

        int idx = stats[2].erros;
        stats[2].primeira_linha_erro[idx] = linha_diff;
        stats[2].nr_query[idx] = nr_query;
        stats[2].arquivo_erro[idx] = g_strdup(output_gerado);
        stats[2].erros++;
    }
}

void execution_stats_q4(GDate *data_inicio, GDate *data_fim, const char *output_gerado, const gchar *output_esperado, char c, int nr_query, Passageiros *gestorPassageiros, TableSemAno *seamAno_table) {
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    query4_passageiro_mais_vezes_top10(data_inicio,data_fim,c,output_gerado,gestorPassageiros,seamAno_table);

    clock_gettime(CLOCK_REALTIME, &end);
    double tempo_s = diff_time(start, end);

    int linha_diff = compara_ficheiros(output_gerado, output_esperado);
    stats[3].total++;
    stats[3].tempo += tempo_s;

    if (linha_diff == 0) {                          
        stats[3].corretos++;
    } 
    else if (linha_diff == -1) {
        stats[3].erros++;
    }
    else {  
        if (stats[3].erros >= stats[3].tam) {
            stats[3].tam *= 2;
            stats[3].primeira_linha_erro = realloc(stats[3].primeira_linha_erro, sizeof(int) * stats[3].tam);
            stats[3].nr_query = realloc(stats[3].nr_query, sizeof(int) * stats[3].tam);
            stats[3].arquivo_erro = realloc(stats[3].arquivo_erro, sizeof(char*) * stats[3].tam);
        }

        int idx = stats[3].erros;
        stats[3].primeira_linha_erro[idx] = linha_diff;
        stats[3].nr_query[idx] = nr_query;
        stats[3].arquivo_erro[idx] = g_strdup(output_gerado);
        stats[3].erros++;
    }
}

void execution_stats_q5(const char *output_gerado, const gchar *output_esperado,int topN, char c,int nr_query,AirlineResult *r) {
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    query5_listar_companhias_mais_atrasos(topN,c,output_gerado,r);

    clock_gettime(CLOCK_REALTIME, &end);
    double tempo_s = diff_time(start, end);

    int linha_diff = compara_ficheiros(output_gerado, output_esperado);
    stats[4].total++;
    stats[4].tempo += tempo_s;

    if (linha_diff == 0) {                          
        stats[4].corretos++;
    } 
    else if (linha_diff == -1) {
        stats[4].erros++;
    }
    else {  
        if (stats[4].erros >= stats[4].tam) {
            stats[4].tam *= 2;
            stats[4].primeira_linha_erro = realloc(stats[4].primeira_linha_erro, sizeof(int) * stats[4].tam);
            stats[4].nr_query = realloc(stats[4].nr_query, sizeof(int) * stats[4].tam);
            stats[4].arquivo_erro = realloc(stats[4].arquivo_erro, sizeof(char*) * stats[4].tam);
        }

        int idx = stats[4].erros;
        stats[4].primeira_linha_erro[idx] = linha_diff;
        stats[4].nr_query[idx] = nr_query;
        stats[4].arquivo_erro[idx] = g_strdup(output_gerado);
        stats[4].erros++;
    }
}

void execution_stats_q6(const char *output_gerado, const gchar *output_esperado,const char *nationality, char c,int nr_query,GHashTable *stats_nacionalidade) {
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    query6_aeroporto_destino(nationality,c,output_gerado,stats_nacionalidade);

    clock_gettime(CLOCK_REALTIME, &end);
    double tempo_s = diff_time(start, end);

    int linha_diff = compara_ficheiros(output_gerado, output_esperado);
    stats[5].total++;
    stats[5].tempo += tempo_s;

    if (linha_diff == 0) {                          
        stats[5].corretos++;
    } 
    else if (linha_diff == -1) {
        stats[5].erros++;
    }
    else {  
        if (stats[5].erros >= stats[5].tam) {
            stats[5].tam *= 2;
            stats[5].primeira_linha_erro = realloc(stats[5].primeira_linha_erro, sizeof(int) * stats[5].tam);
            stats[5].nr_query = realloc(stats[5].nr_query, sizeof(int) * stats[5].tam);
            stats[5].arquivo_erro = realloc(stats[5].arquivo_erro, sizeof(char*) * stats[5].tam);
        }

        int idx = stats[5].erros;
        stats[5].primeira_linha_erro[idx] = linha_diff;
        stats[5].nr_query[idx] = nr_query;
        stats[5].arquivo_erro[idx] = g_strdup(output_gerado);
        stats[5].erros++;
    }
}

void free_stats(int num_queries) {
    for (int i = 0; i < num_queries; i++) {
        free(stats[i].primeira_linha_erro);
        free(stats[i].nr_query);
        if (stats[i].arquivo_erro != NULL) {
            for (int j = 0; j < stats[i].erros; j++) {
                g_free(stats[i].arquivo_erro[j]);
            }
            free(stats[i].arquivo_erro);
        }
    }
    free (stats);
}

void mostrar_resultados(int num_queries, double tempo_total_s, long mem_kb) {
    printf("\n");

    for (int i = 0; i < num_queries; i++) {
        if (stats[i].total == 0) continue;

        printf("Q%d: %d de %d testes ok", i + 1, stats[i].corretos, stats[i].total);
        if (stats[i].corretos == stats[i].total) 
            printf("!\n");
        else
            printf("\n");

        for (int j = 0; j < stats[i].erros; j++)
            printf("\tDiscrepância na query %d: linha %d de \"%s\"\n",
                    stats[i].nr_query[j],
                    stats[i].primeira_linha_erro[j],
                    stats[i].arquivo_erro[j]);
    }

    printf("\nMemória utilizada: %.0f MB\n", mem_kb / 1024.0);

    printf("Tempos de execução:\n");
    for (int i = 0; i < num_queries; i++) {
        if (stats[i].total == 0) continue;
        double media = (stats[i].tempo / stats[i].total) * 1000.0;
        printf("Q%d: %.3f ms\n", i + 1, media);
    }

    printf("Tempo total: %.3f s\n\n", tempo_total_s);   
}