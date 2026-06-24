/**
 * @file reservas.h
 * @brief Declarações das funções e estrutura de gestão de reservas.
 *
 * Contém a definição do tipo Reservas e funções para criar, adicionar, acessar e liberar reservas.
 * Integra a gestão com voos, passageiros e aeroportos.
 */
#ifndef RESERVAS_H
#define RESERVAS_H

#include "reserva.h" 
#include "voos.h"
#include "passageiros.h" 
#include "aeroportos.h"
#include "gestor_global.h"
#include <glib.h>


/**
 * @typedef Reservas
 * @brief Hash table que armazena reservas, indexadas pelo número de documento do passageiro.
 */
typedef GHashTable Reservas;

/**
 * @brief Cria a coleção de reservas.
 *
 * Inicializa uma GHashTable que armazena reservas.
 *
 * @return Apontador para a coleção de reservas.
 */
Reservas *reservas_create();

/**
 * @brief Liberta a memória ocupada pela coleção de reservas.
 *
 * @param gestor Apontador para a coleção de reservas.
 */
void reservas_free (Reservas *gestor);

/**
 * @brief Carrega reservas a partir de um diretório de dados.
 *
 * Lê o ficheiro de reservas, realiza validação sintática e lógica,
 * e adiciona cada reserva válida à coleção.
 *
 * @param dir Diretório onde se encontram os ficheiros de entrada.
 * @param gestor Apontador para o GestorGlobal, usado para integração com outras coleções.
 */
void reservas_load(const char *dir, GestorGlobal *gestor);

/**
 * @brief Adiciona uma reserva à coleção.
 *
 * Atualiza estatísticas, contadores de chegadas/partidas e regista nacionalidades.
 * Integrado com voos, passageiros e aeroportos.
 *
 * @param objeto Apontador para a reserva a adicionar.
 * @param colecao Apontador para o GestorGlobal.
 */
void reservas_add(void *objeto, void *colecao);

/**
 * @brief Obtém uma reserva a partir de um identificador.
 *
 * @param gestor Apontador para a coleção de reservas.
 * @param id Número do documento do passageiro associado à reserva.
 * @return Apontador para a reserva ou NULL se não encontrada.
 */
Reserva *reservas_get (Reservas *gestor, const char *id);

#endif