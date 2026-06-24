/**
 * @file output.h
 * @brief Funções auxiliares para formatação e escrita de resultados das queries.
 *
 * Este módulo gere os separadores utilizados no output, por exemplo,
 * separadores especiais definidos por sufixos das queries(; com sufixo S), e fornece
 * funções genéricas para escrever campos formatados em ficheiros.
 */
#ifndef OUTPUT_H
#define OUTPUT_H

#include <glib.h>
#include <stdio.h>

/**
 * @brief Inicializa a tabela de separadores usada pelas queries.
 *
 * Esta função deve ser chamada antes de qualquer operação de escrita
 * que dependa de identificadores de separador (ex.: 'S' → '=').
 * 
 * @return Apontador para a tabela de separadores inicializada.
 */
GHashTable *output_create();

/**
 * @brief Obtém o separador associado a um identificador.
 *
 * - Caso o identificador exista na tabela, retorna o separador registado.
 * - Caso não exista, retorna ';' como separador por defeito.
 *
 * @param id Caractere identificador do separador (ex.: 'S').
 * @return Caractere separador correspondente.
 */
char output_get_separador(char id,GHashTable *separadores);

/**
 * @brief Escreve vários campos no ficheiro, separados por um delimitador.
 *
 * Esta função aceita um número variável de strings e escreve-as no ficheiro
 * na mesma linha, separadas por `sep`. Termina sempre com '\n'.
 *
 * @param out Ficheiro onde escrever.
 * @param sep Separador a usar entre campos.
 * @param n Número de campos a escrever.
 * @param ... Lista de strings (char*) a serem escritas.
 */
void output_fields(FILE *out, char sep, int n, ...);

/**
 * @brief Liberta os recursos associados ao módulo de output.
 *
 * Destrói a hash table de separadores. Deve ser chamada no fim do programa.
 */
void output_free(GHashTable *separadores);

#endif