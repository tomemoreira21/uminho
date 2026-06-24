/**
 * @file reserva.h
 * @brief Declarações das funções e estrutura de uma reserva.
 * 
 * Contém a definição da estrutura Reserva e funções para criação, acesso aos campos e libertação de memória.
 */
#ifndef RESERVA_H
#define RESERVA_H

/**
 * @brief Cria uma nova reserva a partir de dados lidos.
 * 
 * @param dados Array de strings contendo os campos da reserva: 
 *        [reservation_id, flight_ids (CSV), ...]
 * @return Apontador para a Reserva criada ou NULL se falhar.
 */
typedef struct reserva Reserva;

#include <glib.h>


/**
 * @brief Cria uma nova reserva a partir dos campos fornecidos.
 *
 * A função recebe um conjunto de strings já divididas pelas colunas do ficheiro de entrada.
 * Os índices utilizados são:
 *  - dados[0] → identificador da reserva
 *  - dados[1] → identificadores dos voos associados à reserva
 *  - dados[2] → número de documento do passageiro
 *  - dados[4] → preço da reserva
 *
 * @param dados Conjunto de strings correspondentes às colunas do registo.
 * @return Apontador para a nova reserva, ou NULL em caso de falha.
 */
Reserva* cria_reserva(const gchar** dados);

/**
 * @brief Retorna o ID da reserva.
 * 
 * @param reservation Apontador para a reserva.
 * @return String com o ID da reserva.
 */
const char *get_reservation_id (const Reserva *reservation);

/**
 * @brief Retorna o número do documento do passageiro associado à reserva.
 * 
 * @param reservation Apontador para a reserva.
 * @return String com o número do documento.
 */
const char *get_reservation_document_number (const Reserva *reservation);

/**
 * @brief Retorna o preço pago pela reserva.
 * 
 * @param reservation Apontador para a reserva.
 * @return Valor do preço da reserva.
 */
float get_reservation_price (const Reserva *reservation);

/**
 * @brief Retorna o array de IDs de voos associados à reserva.
 * 
 * @param reservation Apontador para a reserva.
 * @return GPtrArray* contendo os IDs dos voos.
 */
GPtrArray *get_flight_ids(const Reserva *reservation);

/**
 * @brief Liberta a memória ocupada por uma reserva.
 * 
 * @param r Apontador para a reserva a ser liberada.
 */
void free_reserva (void* r);

#endif