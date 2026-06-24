/**
 * @file aeroporto.h
 * @brief Definição da estrutura Aeroporto e funções associadas.
 *
 * Permite criar, consultar e gerir aeroportos, incluindo contadores
 * de chegadas e partidas, tipos de aeroportos e libertação de memória.
 */
#ifndef AEROPORTO_H
#define AEROPORTO_H



/**
 * @enum TypeAeroporto
 * @brief Enum que representa o tipo de aeroporto.
 *
 * Os valores correspondem diretamente às strings presentes no ficheiro de entrada.
 */
typedef enum {
    SMALL_AIRPORT,
    MEDIUM_AIRPORT,
    LARGE_AIRPORT,
    HELIPORT,
    SEAPLANE_BASE
} TypeAeroporto; 

/**
 * @struct aeroporto
 * @brief Estrutura que representa um aeroporto individual.
 *
 * Contém código IATA, nome, cidade, país, tipo e contadores de partidas e chegadas.
 */
typedef struct aeroporto Aeroporto;

#include <glib.h>
/**
 * @brief Cria um novo objeto Aeroporto a partir dos campos do ficheiro de entrada.
 *
 * Recebe um array de strings já dividido por colunas e aloca 
 * espaço para um novo aeroporto.
 * 
 * @param dados Array de strings contendo os campos da linha do ficheiro de entrada.
 * @return Apontador para o novo Aeroporto, ou NULL em caso de erro.
 */
Aeroporto* cria_aeroporto(const gchar** dados);

/**
 * @brief Obtém o código IATA do aeroporto.
 *
 * @param airport Apontador para o aeroporto.
 * @return String com o código IATA.
 */
const char *get_airport_code (const Aeroporto *airport);

/**
 * @brief Obtém o nome do aeroporto.
 *
 * @param airport Apontador para o aeroporto.
 * @return String com o nome.
 */
const char *get_airport_name (const Aeroporto *airport);

/**
 * @brief Obtém a cidade do aeroporto.
 *
 * @param airport Apontador para o aeroporto.
 * @return String com a cidade.
 */
const char *get_airport_city (const Aeroporto *airport);

/**
 * @brief Obtém o país onde o aeroporto se encontra.
 *
 * @param airport Apontador para o aeroporto.
 * @return String com o país.
 */
const char *get_airport_country (const Aeroporto *airport);

/**
 * @brief Obtém o tipo do aeroporto.
 *
 * @param airport Apontador para o aeroporto.
 * @return Tipo do aeroporto.
 */
TypeAeroporto get_airport_type (const Aeroporto *airport);

/**
 * @brief Obtém o tipo do aeroporto em formato string.
 *
 * @param airport Apontador para o aeroporto.
 * @return String correspondente ao tipo (ex.:"small_airport").
 */
const char *get_airport_type_string(const Aeroporto *airport);

/**
 * @brief Obtém o número de chegadas registadas no aeroporto.
 *
 * @param airport Apontador para o aeroporto.
 * @return Número de chegadas.
 */
int get_airport_arrival_count(const Aeroporto *airport);

/**
 * @brief Obtém o número de partidas registadas no aeroporto.
 *
 * @param airport Apontador para o aeroporto.
 * @return Número de partidas.
 */
int get_airport_departure_count(const Aeroporto *airport);

/**
 * @brief Incrementa o contador de partidas do aeroporto.
 *
 * Usado durante o carregamento dos voos ou em queries.
 *
 * @param airport Apontador para o aeroporto.
 */
void incrementa_departure_count(Aeroporto *airport);

/**
 * @brief Incrementa o contador de chegadas do aeroporto.
 *
 * Usado durante o carregamento dos voos ou em queries.
 *
 * @param airport Apontador para o aeroporto.
 */
void incrementa_arrival_count(Aeroporto *airport);

/**
 * @brief Liberta toda a memória associada a um aeroporto.
 *
 * Liberta todas as strings internas e a própria estrutura de seguida.
 *
 * @param a Apontador do tipo void para o aeroporto.
 */
void free_airport(void* a);


#endif