/**
 * @file aeronave.h
 * @brief Definição da estrutura Aeronave e funções associadas.
 *
 * Permite criar, consultar e gerir aeronaves, incluindo contagem de voos,
 * comparação de aeronaves e libertação de memória.
 */
#ifndef AERONAVE_H
#define AERONAVE_H

/**
 * @brief Estrutura opaca que representa uma aeronave.
 */
typedef struct aeronave Aeronave;

#include <glib.h>
/**
 * @brief Cria uma nova aeronave a partir dos campos fornecidos.
 *
 * A função recebe um conjunto de strings já divididas pelas colunas do ficheiro de entrada.
 * Os índices utilizados são:
 *  - dados[0] → identificador da aeronave
 *  - dados[1] → fabricante
 *  - dados[2] → modelo
 *
 * @param dados Conjunto de strings correspondentes às colunas do registo.
 * @return Apontador para a nova aeronave, ou NULL em caso de falha.
 */

Aeronave* cria_aeronave(const gchar** dados);
/**
 * @brief Obtém o identificador da aeronave.
 *
 * @param aircraft Apontador para a aeronave.
 * @return String com o ID (memória interna, não deve ser libertada).
 */
const char *get_aircraft_identifier (const Aeronave *aircraft);

/**
 * @brief Obtém o nome do fabricante da aeronave.
 *
 * @param aircraft Apontador para a aeronave.
 * @return String com o fabricante.
 */
const char *get_aircraft_manufactor (const Aeronave *aircraft);
/**
 * @brief Obtém o número de voos associados à aeronave.
 *
 * @param aircraft Apontador para a aeronave.
 * @return Contador de voos.
 */
int get_aircraft_flight_count (const Aeronave *aircraft);
/**
 * @brief Obtém o modelo da aeronave.
 *
 * @param aircraft Apontador para a aeronave.
 * @return String com o modelo.
 */
const char *get_aircraft_model(const Aeronave *aircraft);
/**
 * @brief Incrementa o contador de voos da aeronave.
 *
 * @param aircraft Apontador para a aeronave.
 */
void incrementa_flight_count(Aeronave *aircraft);
/**
 * @brief Compara duas aeronaves pelo número de voos realizados.
 *
 * A comparação é usada para ordenação: aeronaves com mais voos devem
 * aparecer primeiro. Em caso de empate, o critério secundário é a
 * ordenação lexicográfica do identificador da aeronave.
 *
 * @param p1 Apontador para a primeira aeronave.
 * @param p2 Apontador para a segunda aeronave.
 * @return -1 se a1 deve vir antes de a2,
 *          1 se a1 deve vir depois de a2,
 *          0 se ambas são equivalentes.
 */
int aeronaves_compare_flight_count(const void *p1, const void *p2);
/**
 * @brief Compara duas aeronaves pelo seu identificador.
 *
 * A comparação é puramente lexicográfica e é utilizada como critério
 * secundário em funções de ordenação.
 *
 * @param p1 Apontador para a primeira aeronave.
 * @param p2 Apontador para a segunda aeronave.
 * @return Resultado de strcmp entre os dois IDs.
 */
int aeronaves_compare_id(const void *p1, const void *p2);
/**
 * @brief Liberta toda a memória associada a uma aeronave.
 *
 * Liberta as strings internas e a própria estrutura.
 *
 * @param a Apontador genérico para uma aeronave (void* para compatibilidade
 *          com funções de destruição de GLib).
 */
void free_aeronave (void* a);

#endif