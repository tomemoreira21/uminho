#include "interpretador.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"
#include "query6.h"
#include "output.h"
#include "utils.h"
#include <stdlib.h>
#include <glib.h>
#include <stdio.h>
#include <ctype.h>

char* parse_query_token(char *line, int *query_num, int *has_suffix, char *suffix_char) {
    if (!line) return NULL;

    char *rest = line;
    char *token = strsep(&rest, " ");  // pega primeiro token
    
    *has_suffix = 0;
    *suffix_char = '\0';

    int len = strlen(token);
    int i = 0;
    while (i < len && isdigit(token[i]))
        i++;

    // se terminou exatamente no fim, ou seja, não tem sufixo
    if (i == len) {
        *query_num = atoi(token);
        return rest;
    }

    // se tem exatamente um caractere depois do número então considera como sufixo
    if (i == len - 1) {
        *has_suffix = 1;
        *suffix_char = token[i];
        token[i] = '\0';
        *query_num = atoi(token);
        return rest;
    }

    return NULL; // mais de um caratere depois do número
}

void processa_queries (const char *input_file, GestorGlobal *g) {
    FILE *file = fopen(input_file, "r");
    if (!file) return;

    char *linha = NULL;
    size_t len = 0;
    ssize_t read;
    int query_output_counter = 1;

    while ((read = getline(&linha, &len, file)) != -1) {
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

        char output_file[256];
        snprintf(output_file, sizeof(output_file), "resultados/command%d_output.txt", query_output_counter++);

        char sep_char = has_suffix ? output_get_separador(suffix_char,get_gestor_Output(g)) : ';'; // default será ';'

        switch (query_num) {
            case 1:
                query1_listar_aeroporto(rest,sep_char,output_file,get_gestor_Aeroportos(g));
                break;

            case 2:
                if (!rest) break;
                char *n_str = strsep(&rest, " ");
                if (!n_str) break;
                int N = atoi(n_str);
                char *manufacturer = (rest && strlen(rest) > 0) ? rest : NULL;
                query2_listar_aeronaves_mais_voos(N, manufacturer, sep_char, output_file,get_gestor_Aeronaves(g));
                break;

            case 3:
                if (!rest) break;
                char *data_inicio_str = strsep(&rest, " ");
                char *data_fim_str = (rest && strlen(rest) > 0) ? rest : NULL;
                if (!data_inicio_str || !data_fim_str) break;

                GDate *data_inicio = type_string_to_gdate (data_inicio_str);
                GDate *data_fim = type_string_to_gdate (data_fim_str);
                
                query3_aeroporto_mais_partidas (data_inicio,data_fim, sep_char,output_file,get_gestor_Aeroportos(g),get_btree_query3(get_gestor_Queries(g)));
              
                g_date_free (data_inicio);
                g_date_free (data_fim);
                break;

            case 4:
                if (!rest) 
                    query4_passageiro_mais_vezes_top10(NULL,NULL,sep_char,output_file,get_gestor_Passageiros(g),get_hashtable_query4(get_gestor_Queries(g)));

                else {
                    char *data_inicio_str = strsep(&rest, " ");
                    char *data_fim_str = (rest && strlen(rest) > 0) ? rest : NULL;

                    if (!data_inicio_str || !data_fim_str) break;
                    GDate *data_inicio = type_string_to_gdate (data_inicio_str);
                    GDate *data_fim = type_string_to_gdate (data_fim_str);

                    query4_passageiro_mais_vezes_top10(data_inicio,data_fim,sep_char,output_file,get_gestor_Passageiros(g),get_hashtable_query4(get_gestor_Queries(g)));

                    g_date_free (data_inicio);
                    g_date_free (data_fim);
                }

                break;

            case 5:
                if (!rest) break;
                char *topN_str = strsep(&rest, " ");
                if (!topN_str) break;
                int topN = atoi(topN_str);
                query5_listar_companhias_mais_atrasos (topN,sep_char,output_file,get_array_query5(get_gestor_Queries(g)));
                break;

            case 6:
                if (!rest) break;
                while (*rest == ' ') rest++;
                char *nationality = rest;
                if (!nationality) break;
                query6_aeroporto_destino (nationality,sep_char,output_file,get_hashtable_query6(get_gestor_Queries(g)));
                break;

            default:
                break;

        }

        free (linha_init);
    }

    free (linha);
    fclose (file);
}