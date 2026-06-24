/**
 * @file query1.h
 * @brief Módulo que implementa a query 1: informação de aeroportos de acordo com o identificador.
 *
 * Este módulo fornece funções para:
 * - Atualizar contadores de chegadas e partidas de voos em aeroportos;
 * - Listar informações detalhadas de um aeroporto, incluindo contagens de voos;
 * - Escrever os resultados em ficheiro ou apresentar no modo interativo.
 */
#ifndef QUERY1_H
#define QUERY1_H

#include "voos.h"
#include "aeroportos.h"

/**
 * @brief Incrementa os contadores de chegadas e partidas de um voo na coleção.
 *
 * Para o voo fornecido, incrementa o contador de partidas no aeroporto de origem
 * e o contador de chegadas no aeroporto de destino. 
 *
 * @param gestor Apontador para o gestor de aeroportos onde os contadores devem ser atualizados.
 * @param voo Apontador para o voo cujos contadores devem ser atualizados.
 */
void incrementa_arrival_e_departure_count_na_coleção(Aeroportos *gestor, const Voo *voo);

/**
 * @brief Escreve no ficheiro de output a informação de um aeroporto.
 *
 * Caso o aeroporto não exista, escreve uma linha vazia. Caso exista,
 * escreve os campos: code IATA, nome, cidade, país, tipo, número de chegadas
 * e número de partidas. Caso o output_file seja null, é ecrita a informação no modo interativo.
 *
 * @param code Code IATA do aeroporto a consultar.
 * @param c Separador usado entre os campos.
 * @param output_file Caminho do ficheiro de output ou NULL para modo interativo.
 * @param gestorAeroportos Apontador para o gestor de aeroportos onde será feita a pesquisa.
 */
void query1_listar_aeroporto (const char *code, char c, const char *output_file, Aeroportos *gestorAeroportos);

#endif