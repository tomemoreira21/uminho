/**
 * @file aeronaves.h
 * @brief Módulo que gere a coleção de aeronaves.
 *
 * Este módulo fornece funções para:
 *  - Criar e inicializar a coleção de aeronaves.
 *  - Adicionar aeronaves à coleção.
 *  - Obter listas de aeronaves por fabricante ou por identificador.
 *  - Ordenar aeronaves por número de voos.
 *  - Carregar aeronaves a partir de ficheiros.
 *  - Libertar memória associada a fabricantes e à coleção.
 */
#ifndef AERONAVES_H
#define AERONAVES_H

#include "aeronave.h"
#include "gestor_global.h"
#include <glib.h>


/**
 * @struct aeronaves
 * @brief Estrutura que representa a coleção de todas as aeronaves.
 *
 * Contém duas hash tables:
 *  - by_manufacturer: mapeia o nome do fabricante para a estrutura Fabricante.
 *  - by_identifier: mapeia o identificador da aeronave para a própria Aeronave.
 */
typedef struct aeronaves Aeronaves;
/**
 * @struct fabricante
 * @brief Estrutura que representa um fabricante e as suas aeronaves.
 *
 * Contém os dados de um fabricante:
 *  - lista_aeronaves: lista ligada (GList) de todos os ponteiros para Aeronave pertencentes ao fabricante.
 *  - by_airplane_id: GHashTable que associa cada identificador de aeronave (char*) ao respetivo Aeronave*.
*/
typedef struct fabricante Fabricante;


/**
 * @brief Cria e inicializa a coleção de aeronaves.
 *
 * @return Apontador para Aeronaves inicializado, ou NULL em caso de erro.
 */
Aeronaves *aeronaves_create();

/**
 * @brief Adiciona uma aeronave à coleção.
 *
 * Se o fabricante não existir, cria uma nova entrada para ele.
 *
 * @param objeto Apontador para Aeronave a adicionar.
 * @param colecao Apontador para a coleção ::Aeronaves.
 */
void aeronaves_add(void *objeto, void *colecao);
/**
 * @brief Verifica se a coleção de aeronaves está inicializada.
 *
 * @param gestor Apontador para Aeronaves.
 * @return 1 se inicializado, 0 caso contrário.
 */
int aeronaves_is_initialized(Aeronaves *gestor);
/**
 * @brief Retorna a tabela de todos os fabricantes registados na coleção de aeronaves.
 *
 * Cada entrada da hash table mapeia o nome do fabricante (string) para a estrutura Fabricante correspondente.
 *
 * @param gestor Apontador para a coleção Aeronaves.
 * @return GHashTable* onde cada chave é o nome do fabricante (char*) e cada valor é um apontador para Fabricante.
 */
GHashTable *aeronaves_get_all_manufacturers(Aeronaves *gestor);

/**
 * @brief Obtém a lista de aeronaves de um fabricante específico.
 *
 * @param gestor Apontador para Aeronaves.
 * @param manufacturer Nome do fabricante.
 * @return GList* de Aeronave* ou NULL se não existir.
 */
GList *aeronaves_get_by_manufacturer(Aeronaves *gestor, const char *manufacturer);
/**
 * @brief Obtém a hash table que mapeia ID da aeronave → Aeronave* de um fabricante.
 *
 * @param fab Apontador para Fabricante.
 * @return GHashTable* ou NULL se não existir.
 */
GHashTable *aeronaves_get_airplane_id(Fabricante *fab);

/**
 * @brief Obtém a lista de aeronaves de um fabricante.
 *
 * @param fab Apontador para Fabricante.
 * @return GList* de Aeronave* ou NULL se não existir.
 */
GList *aeronaves_get_airplane_list(Fabricante *fab);
/**
 * @brief Liberta a memória associada a um fabricante.
 *
 * Liberta a lista de aeronaves (invocando free_aeronave) e a hash table interna.
 *
 * @param fab_ptr Apontador para Fabricante.
 */
void free_fabricante(void *fab_ptr);
/**
 * @brief Obtém uma aeronave pelo seu identificador.
 *
 * @param gestor Apontador para Aeronaves.
 * @param id Identificador da aeronave.
 * @return Apontador para Aeronave ou NULL se não existir.
 */
Aeronave *aeronaves_get_by_id(Aeronaves *gestor, const char *id);
/**
 * @brief Ordena todas as listas de aeronaves dos fabricantes pelo número de voos.
 *
 * Aeronaves com mais voos aparecem primeiro.
 *
 * @param gestor Apontador para Aeronaves.
 */
void aeronaves_ordena_listas(Aeronaves *gestor);
/**
 * @brief Liberta toda a memória da coleção de aeronaves.
 *
 * Inclui fabricantes, listas de aeronaves e hash tables.
 *
 * @param gestor Apontador para Aeronaves.
 */
void aeronaves_free(Aeronaves *gestor);
/**
 * @brief Carrega aeronaves a partir de ficheiro.
 *
 * Cria a coleção de aeronaves, adiciona cada aeronave e regista erros em ficheiro próprio.
 *
 * @param dir Diretório onde se encontra o ficheiro "aircrafts".
 * @param gestor Apontador para Aeronaves a preencher.
 */
void aeronaves_load(const char *dir,Aeronaves *gestor);

#endif