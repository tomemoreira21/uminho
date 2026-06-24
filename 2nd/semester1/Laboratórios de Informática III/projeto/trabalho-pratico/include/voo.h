/**
 * @file voo.h
 * @brief Definição da estrutura Voo e funções auxiliares.
 *
 * Este módulo define a estrutura Voo, que representa um voo individual,
 * incluindo horários, origem, destino, aeronave, companhia aérea e status.
 * Fornece funções para criar, aceder aos campos e libertar a memória.
 */
#ifndef VOO_H
#define VOO_H


/**
 * @enum VooStatus
 * @brief Representa o estado de um voo.
 */
typedef enum {
    ON_TIME,
    DELAYED,
    CANCELLED
} VooStatus; 

/**
 * @struct voo
 * @brief Estrutura que representa um voo individual.
 *
 * Contém informações sobre horários, origem, destino, aeronave, companhia e status.
 */
typedef struct voo Voo;

#include <glib.h>


/**
 * @brief Cria um novo voo a partir de uma lista de strings.
 *
 * Converte datas/hora em GDateTime e copia strings para campos internos.
 *
 * @param dados Apontador para array de strings com os dados do voo.
 * @return Apontador para Voo criado, ou NULL em caso de erro.
 */
Voo* cria_voo(const gchar** dados);

/**
 * @brief Obtém o ID do voo.
 *
 * @param v Apontador para Voo.
 * @return Apontador para string com o identificador do voo.
 */
const char *get_flight_id(const Voo *v);

/**
 * @brief Obtém o aeroporto de origem do voo.
 *
 * @param v Apontador para Voo.
 * @return Apontador para string com o código do aeroporto de origem.
 */
const char *get_origin(const Voo *v);

/**
 * @brief Obtém o aeroporto de destino do voo.
 *
 * @param v Apontador para Voo.
 * @return Apontador para string com o código do aeroporto de destino.
 */
const char *get_destination(const Voo *v);

/**
 * @brief Obtém a aeronave associada ao voo.
 *
 * @param v Apontador para Voo.
 * @return Apontador para string com o identificador da aeronave.
 */
const char *get_aircraft (const Voo *v);

/**
 * @brief Obtém a companhia aérea do voo.
 *
 * @param v Apontador para Voo.
 * @return Apontador para string com o nome da companhia aérea.
 */
const char *get_airline(const Voo *v);

/**
 * @brief Obtém a hora prevista de partida.
 *
 * @param v Apontador para Voo.
 * @return Apontador para GDateTime com a hora prevista de partida.
 */
GDateTime *get_departure(const Voo *v);

/**
 * @brief Obtém a hora real de partida.
 *
 * @param v Apontador para Voo.
 * @return Apontador para GDateTime com a hora real de partida.
 */
GDateTime *get_actual_departure(const Voo *v);

/**
 * @brief Obtém a hora prevista de chegada.
 *
 * @param v Apontador para Voo.
 * @return Apontador para GDateTime com a hora prevista de chegada.
 */
GDateTime *get_arrival(const Voo *v);

/**
 * @brief Obtém a hora real de chegada.
 *
 * @param v Apontador para Voo.
 * @return Apontador para GDateTime com a hora real de chegada.
 */
GDateTime *get_actual_arrival(const Voo *v);

/**
 * @brief Obtém o status do voo.
 *
 * @param v Apontador para Voo.
 * @return VooStatus do voo.
 */
VooStatus get_status(const Voo *v);

/**
 * @brief Liberta toda a memória associada a um voo.
 *
 * Liberta strings e GDateTime internas, depois a própria estrutura.
 *
 * @param v Apontador para Voo a ser libertado.
 */
void free_voo (void* v);

#endif