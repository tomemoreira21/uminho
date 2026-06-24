/**
 * @file interpretador.h
 * @brief Interface do módulo de interpretação e execução de queries.
 *
 * Este módulo é responsável por:
 *  - Ler e interpretar linhas do ficheiro de queries;
 *  - Extrair o número da query e um eventual sufixo de formatação;
 *  - Encaminhar a execução para a query correspondente;
 *  - Utilizar o GestorGlobal para aceder aos dados carregados.
 *
 */

#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "aeronaves.h"
#include "aeroportos.h"
#include "passageiros.h"
#include "voos.h"
#include "reservas.h"
#include "gestor_global.h"



/**
 * @brief Extrai o número da query e um eventual sufixo (ex.: "2S", "5", "3S").
 *
 * O token inicial da linha será sempre do formato:
 *    - "<num>"
 *    - "<num><char>"
 *
 * Exemplos:
 *   "2S aaa bbb" → query_num = 2, has_suffix = 1, suffix_char = 'S'
 *   "3 aaa"      → query_num = 3, has_suffix = 0
 *
 * @param line Linha completa (modificada internamente).
 * @param query_num Apontador onde fica guardado o número da query.
 * @param has_suffix Apontador que indica se existe sufixo (0 ou 1).
 * @param suffix_char Apontador que recebe o sufixo, caso exista.
 * @return Apontador para o resto da linha (argumentos da query), ou NULL em erro.
 */
char* parse_query_token(char *line, int *query_num, int *has_suffix, char *suffix_char);
/**
 * @brief Lê o ficheiro de queries, interpreta cada linha e executa a respetiva query.
 *
 * Para cada linha é criado um ficheiro de output
 *
 * @param input_file Caminho para o ficheiro de entrada.
 * @param g Apontador para o Gestor Global com toda a informação.
 */
void processa_queries (const char *input_file, GestorGlobal *g);

#endif