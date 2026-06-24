/**
 * @file parser_dados.h
 * @brief Funções genéricas de parsing e carregamento de ficheiros de dados.
 *
 * Este módulo fornece:
 *  - Parsing de linhas em diferentes formatos (CSV, TSV e PSV);
 *  - Deteção automática do tipo de ficheiro com base na extensão;
 *  - Funções auxiliares para criação genérica de coleções a partir de ficheiros;
 *  - Infraestrutura comum para validação sintática e lógica dos dados.
 *
 * É utilizado por todos os gestores do sistema durante o carregamento
 * inicial dos ficheiros de dados.
 */

#ifndef PARSER_DADOS_H
#define PARSER_DADOS_H

#include <glib.h>




/**
 * @brief Tipo enumerado que representa o formato do ficheiro de dados.
 */
typedef enum filetype FileType;

/**
 * @brief Tipo de função parser para uma linha de texto.
 *
 * Recebe uma linha e devolve um array de strings (campos).
 */
typedef gchar** (*parser_fn)(const char*);


/**
 * @brief Cria uma coleção a partir de um ficheiro CSV/TSV/PSV.
 *
 * Esta função lê um ficheiro de dados linha a linha, aplica validação
 * sintática e lógica, cria objetos válidos e adiciona-os à coleção.
 * Linhas inválidas são escritas num ficheiro de erros.
 *
 * @param nome_ficheiro_dados Caminho para o ficheiro de dados.
 * @param nome_ficheiro_erros Caminho para o ficheiro onde são escritos os erros.
 * @param valida_sintaxe Função de validação sintática.
 * @param valida_logica Função de validação lógica.
 * @param cria_objeto Função que cria o objeto a partir dos dados.
 * @param adiciona_a_colecao Função que insere o objeto na coleção.
 * @param free_objeto Função que liberta o objeto em caso de erro.
 * @param colecao Apontador para a coleção destino.
 */
void cria_colecao_do_csv(const char *nome_ficheiro_dados, 
                        const char *nome_ficheiro_erros, 
                        int (*valida_sintaxe)(const gchar **), 
                        int (*valida_logica)(void *, void *), 
                        void* (*cria_objeto)(const gchar **), 
                        void (*adiciona_a_colecao)(void *objeto, void *colecao), 
                        void (*free_objeto)(void *objeto), 
                        void *colecao);

/**
 * @brief Faz o parser genérico de uma linha com um separador definido.
 *
 * @param linha Linha a processar.
 * @param sep_char Caractere separador.
 * @return Array de strings.
 */
gchar** parse_delimited_line(const char* linha, char sep_char);

/**
 * @brief Faz o parse de uma linha no formato TSV.
 *
 * @param linha Linha a processar.
 * @return Array de strings.
 */
gchar** parse_tsv_line(const char* linha);
/**
 * @brief Faz o parse de uma linha no formato CSV.
 *
 * @param linha Linha a processar.
 * @return Array de strings.
 */
gchar** parse_csv_line(const char* linha);

/**
 * @brief Faz o parse de uma linha no formato PSV.
 *
 * @param linha Linha a processar.
 * @return Array de strings.
 */
gchar** parse_pipe_line(const char* linha);
/**
 * @brief Determina o tipo de ficheiro com base na extensão.
 *
 * @param path Caminho do ficheiro.
 * @return Tipo de ficheiro detetado.
 */
FileType deteta_tipo_ficheiro(const char *path);

/**
 * @brief Obtém a função parser adequada ao tipo de ficheiro.
 *
 * @param tipo Tipo de ficheiro.
 * @return Apontador para a função de parsing correspondente.
 */
parser_fn get_parser(FileType tipo);

/**
 * @brief Procura um ficheiro de dados com diferentes extensões.
 *
 * Testa extensões CSV, TSV e PSV dentro do diretório indicado.
 *
 * @param dir Diretório base.
 * @param basename Nome base do ficheiro (sem extensão).
 * @return Apontador para o caminho do ficheiro encontrado ou NULL.
 */
char *get_ficheiro_dados(const char *dir,const char *basename);

#endif
