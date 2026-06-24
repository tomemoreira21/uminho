/**
 * @file validacao_logica_dados.h
 * @brief Declarações das funções de validação lógica de dados do sistema.
 * 
 * Contém funções para validar a consistência lógica entre os diferentes dados do sistema:
 *  - Coerência de datas e estado dos voos
 *  - Correspondência de voos com aeronaves existentes
 *  - Validação de reservas (passageiro, flight IDs, sequência de voos)
 *  - Verificação de campos específicos como origem/destino, aeronave, e flight IDs
 *
 * Todas as funções recebem apontadores genéricos para estruturas de dados e coleções
 * globais e retornam 0 se os dados forem válidos ou 1 caso contrário.
 */
#ifndef VALIDACAO_LOGICA_H
#define VALIDACAO_LOGICA_H

#include "voos.h"
#include "aeronaves.h"
#include "passageiro.h"
#include "passageiros.h"
#include "reservas.h"

/**
 * @brief Valida a lógica de um voo.
 *
 * Verifica se:
 *  - origem e destino são diferentes,
 *  - datas são coerentes com o estado do voo,
 *  - a aeronave associada existe.
 *
 * Usado no carregamento do ficheiro de entrada dos voos.
 *
 * @param voo Apontador genérico para o voo a validar.
 * @param colecao Apontador para o GestorGlobal, usado para consultar aeronaves.
 * @return 0 se for válido, 1 caso contrário.
 */

int valida_logica_voo (void *voo, void *colecao) ;

/**
 * @brief Valida a lógica de uma reserva.
 *
 * Verifica se:
 *  - os flight_ids existem,
 *  - o passageiro existe,
 *  - se existirem dois voos, estes encaixam logicamente (destino de um é a origem de outro).
 *
 * @param r Apontador genérico para a reserva.
 * @param colecao Apontador para o GestorGlobal.
 * @return 0 se a reserva for válida, 1 caso contrário.
 */
int valida_logica_reserva (void *r, void *colecao);

/**
 * @brief Verifica se origem e destino são diferentes.
 *
 * @param v Apontador para o voo.
 * @return 0 se forem diferentes, 1 se forem iguais ou inválidos.
 */
int voo_origem_destino_validos(const void *v);

/**
 * @brief Verifica coerência lógica entre as datas e o estado do voo.
 *
 * Função utilizada nos campos Departure, actualDeparture, Arrival e actualArrival do voo.
 * Verifica as coerências lógiacas entre as datas, dependendo do estado do voo (ex:Cancelado).
 * 
 * @param v Apontador para o voo.
 * @return 0 se as datas forem válidas, 1 caso contrário.
 */
int voo_datas_validas_logic(const void* v);

/**
 * @brief Verifica se o campo aircraft corresponde a uma aeronave existente.
 *
 * @param voo Apontador para o voo.
 * @param gestorAeronaves Coleção de aeronaves para validação.
 * @return 0 se existir, 1 caso contrário.
 */
int voo_aircraft_valida (const void *voo, Aeronaves *gestorAeronaves);

/**
 * @brief Verifica se os flight_ids numa reserva existem.
 *
 * Aceita 1 ou 2 ids.
 *
 * @param res Apontador para a reserva.
 * @param gestorVoos Coleção de voos usada na verificação.
 * @return 0 se todos existirem, 1 caso contrário.
 */
int reserva_flight_id_valid (const void *res, Voos *gestorVoos);

/**
 * @brief Verifica se o passageiro associado ao número de documento existe.
 *
 * @param res Apontador para a reserva.
 * @param gestorPassageiros Coleção de passageiros usada na verificação.
 * @return 0 se o passageiro existir, 1 caso contrário.
 */
int reserva_document_number (const void *res, Passageiros *gestorPassageiros);

/**
 * @brief Verifica a coerência entre dois flight_id de uma mesma reserva.
 *
 * Assegura que o destino do primeiro voo coincide com a origem do segundo.
 *
 * @param res Apontador para a reserva.
 * @param gestorVoos Coleção de voos usada na verificação.
 * @return 0 se forem coerentes, 1 caso contrário.
 */
int reserva_same_fightId (const void *res, Voos *gestorVoos);

#endif