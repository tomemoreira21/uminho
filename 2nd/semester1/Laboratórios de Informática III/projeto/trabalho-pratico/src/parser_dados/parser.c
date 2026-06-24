#include "parser_dados.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <glib.h>
#include <string.h>

enum filetype {
    FILE_CSV,
    FILE_TSV,
    FILE_PIPE,
    FILE_UNKNOWN
};

void cria_colecao_do_csv(const char *nome_ficheiro_dados, 
                        const char *nome_ficheiro_erros, 
                        int (*valida_sintaxe)(const gchar **), 
                        int (*valida_logica)(void *, void *), 
                        void* (*cria_objeto)(const gchar **), 
                        void (*adiciona_a_colecao)(void *objeto, void *colecao), 
                        void (*free_objeto)(void *objeto), 
                        void *colecao) {

    FileType tipo = deteta_tipo_ficheiro(nome_ficheiro_dados);
    parser_fn parser = get_parser(tipo);

    FILE *file = fopen(nome_ficheiro_dados, "r");
    FILE *error_file = NULL;

    if (!file) return;

    char *header = NULL;
    size_t len_header = 0;
    ssize_t read_header;

    if ((read_header = getline (&header, &len_header,file)) == -1) {
        free (header);
        fclose (file);
        return;
    }

    char *linha = NULL;
    size_t len_linha = 0;
    ssize_t read_linha; 

    while ((read_linha = getline (&linha,&len_linha,file)) != -1) {                 // linha_init pode-se tirar
        char *linha_init = strdup (linha);
        if (!linha_init) continue; 

        if (read_linha > 0 && linha[read_linha - 1] == '\n')
                    linha[read_linha - 1] = '\0'; 
        
        gchar **dados = parser(linha);

        //int n_campos = 0;
        //while (dados[n_campos] != NULL) n_campos++;
        
        int erro_sintaxe = valida_sintaxe ((const gchar **)dados) == 1;
        if (erro_sintaxe) {
            if (!error_file) {
                error_file = fopen (nome_ficheiro_erros,"w");              // só abre se houver erro
                fputs(header,error_file);          
            }     

            fputs(linha_init,error_file);
            g_strfreev(dados);
            free (linha_init);
            continue;
        }

        void *objeto = cria_objeto ((const gchar **)dados);
        if (objeto != NULL) {
            int erro_logica = valida_logica != NULL && valida_logica (objeto,colecao) == 1;
            if (!erro_logica) 
                adiciona_a_colecao (objeto,colecao);
            else {
                 if (!error_file) {
                    error_file = fopen (nome_ficheiro_erros,"w");              // só abre se houver erro
                    fputs(header,error_file);          
                }     

                fputs(linha_init, error_file);
                free_objeto (objeto);
            }
        }

        /*
        for (int i = 0; i<n_campos; i++) {                  
            if (dados[i])
                g_free(dados[i]); 
        }
        // Liberta o array de ponteiros 
        g_free(dados);
        */
        g_strfreev(dados);
        free (linha_init);
    }

    free (header);
    free (linha);
    if (error_file != NULL) fclose(error_file);
    fclose (file);
}

gchar** parse_delimited_line(const char* linha, char sep_char) {
    int capacidade = 16;
    gchar **campos = g_malloc0(sizeof(gchar*) * capacidade);
    if (!campos) return NULL;

    int idx = 0;
    const char *start = linha;
    gboolean dentro_aspas = FALSE;

    for (const char *p = linha;; p++) {
        if (*p == '"') {
            dentro_aspas = !dentro_aspas;
        } else if ((*p == sep_char && !dentro_aspas) || *p == '\0') {
            
            const char *campo_start = start;
            size_t campo_tam = p - start;

            // remove aspas do início e fim se houver
            if (campo_tam >= 2 && *campo_start == '"' && *(p - 1) == '"') {
                campo_start++;
                campo_tam -= 2;
            }

            // aloca memória para o campo + '\0'
            gchar *campo = g_malloc(campo_tam + 1);
            if (!campo) {
                g_strfreev(campos);
                return NULL;
            }

            // copia os dados
            memcpy(campo, campo_start, campo_tam);
            campo[campo_tam] = '\0';

            // adiciona ao array de campos
            campos[idx++] = campo;

            // realloc se necessário
            if (idx >= capacidade) {
                capacidade *= 2;
                gchar **temp = g_realloc(campos, sizeof(gchar*) * capacidade);
                if (!temp) {
                    g_strfreev(campos);
                    return NULL;
                }
                campos = temp;
            }

            // se chegou ao fim da linha, sai do loop
            if (*p == '\0') break;

            // próximo campo começa depois da vírgula
            start = p + 1;
        }
    }

    // adiciona terminador NULL
    campos[idx] = NULL;

    return campos;
}

gchar** parse_csv_line(const char* linha) {
    return parse_delimited_line (linha,',');
}

gchar** parse_tsv_line(const char* linha) {
    return parse_delimited_line (linha,'\t');
}

gchar** parse_pipe_line(const char* linha) {
    return parse_delimited_line (linha,'|');
}

FileType deteta_tipo_ficheiro(const char *path) {
    const char *ext = strrchr(path, '.');
    if (!ext) return FILE_UNKNOWN;

    ext++; // avançar depois do ponto

    if (strcasecmp(ext, "csv") == 0) return FILE_CSV;
    if (strcasecmp(ext, "tsv") == 0) return FILE_TSV;
    if (strcasecmp(ext, "psv") == 0 || strcasecmp(ext, "pipe") == 0) return FILE_PIPE;

    return FILE_UNKNOWN;
}

parser_fn get_parser(FileType tipo) {
    switch (tipo) {
        case FILE_CSV: return parse_csv_line;
        case FILE_TSV: return parse_tsv_line;
        case FILE_PIPE: return parse_pipe_line;
        default: return parse_csv_line; 
    }
}

char *get_ficheiro_dados(const char *dir,const char *basename) {
    static char path[256];
    const char *exts[] = {"csv", "tsv", "psv"};

    for (int i = 0; i < 3; i++) {
        snprintf(path, sizeof(path), "%s/%s.%s", dir, basename, exts[i]);
        FILE *file = fopen(path, "r");
        if (file != NULL) {
            fclose(file);
            return path; 
        }
    }
        
    return NULL; // nenhum encontrado
}