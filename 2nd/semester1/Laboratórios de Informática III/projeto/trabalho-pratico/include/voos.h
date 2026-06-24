/**
 * @file voos.h
 * @brief Definição do gestor de voos e funções auxiliares.
 *
 * Este módulo define a coleção de voos (Voos) e fornece funções para
 * criar, adicionar, aceder, carregar de ficheiros e libertar voos.
 */
#ifndef VOOS_H
#define VOOS_H

#include "voo.h"
#include "aeronaves.h"
#include "gestor_global.h"
#include <glib.h>


/**
 * @typedef Voos
 * @brief Hash table que mapeia ID do voo para Voo*.
 */
typedef GHashTable Voos;



/**
 * @brief Cria uma nova coleção de voos.
 *
 * Inicializa uma hash table para armazenar voos por ID.
 *
 * @return Apontador para Voos criado, ou NULL em caso de erro.
 */
Voos *voos_create();

/**
 * @brief Liberta toda a memória associada à coleção de voos.
 *
 * Liberta cada voo individual e a própria hash table.
 *
 * @param gestor Apontador para Voos a ser libertado.
 */
void voos_free (Voos *gestor);

/**
 * @brief Carrega voos a partir dos ficheiros de entrada.
 *
 * Invoca funções de validação sintática e lógica, cria Voo* e adiciona à coleção.
 *
 * @param dir Diretório onde se encontram os ficheiros de voos.
 * @param gestor Apontador para GestorGlobal que contém a coleção de voos.
 */
void voos_load(const char *dir, GestorGlobal *gestor);

/**
 * @brief Adiciona um voo à coleção.
 *
 * Insere o voo na hash table e atualiza contadores de aeronaves, btree de datas
 * e tabela de atrasos por companhia aérea.
 *
 * @param objeto Apontador para Voo a ser adicionado.
 * @param colecao Apontador para GestorGlobal que contém a coleção de voos.
 */
void voos_add(void *objeto,void *colecao);

/**
 * @brief Obtém um voo pelo seu ID.
 *
 * @param gestor Apontador para Voos.
 * @param id ID do voo a procurar.
 * @return Apontador para Voo correspondente, ou NULL se não encontrado.
 */
Voo *voos_get (Voos *gestor, const char *id);

#endif