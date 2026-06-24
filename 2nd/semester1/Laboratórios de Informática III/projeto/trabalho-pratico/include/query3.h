/**
 * @file query3.h
 * @brief Módulo que implementa a query 3: aeroporto com mais partidas num intervalo de datas.
 *
 * Este módulo fornece estruturas e funções para:
 * - Armazenar voos por data e aeroporto com GTree e GHashTable;
 * - Acumular contagens globais de voos por aeroporto;
 * - Determinar o aeroporto com mais partidas num dado intervalo;
 * - Escrever resultados em ficheiro ou no modo interativo.
 */
#ifndef QUERY3_H
#define QUERY3_H

#include "voo.h"
#include "aeroportos.h"
#include <glib.h>

/**
 * @struct info_data
 * @brief Estrutura que armazena contagem de voos por aeroporto para uma data.
 *
 * Cada chave da hash table é o code IATA do aeroporto (string),
 * e cada valor é um inteiro indicando o número de voos registados.
 */
typedef struct info_data InfoData;

/**
 * @struct hash_counter
 * @brief Estrutura usada para acumular contagem global de voos num intervalo.
 *
 * Contém uma hash table global com contagem de voos por aeroporto,
 * o code IATA do aeroporto com maior número de partidas e o respetivo número, e o intervalo de datas solicitadas pela query em questão.
 */
typedef struct hash_counter HashCounter;

/**
 * @brief Inicializa a árvore de datas (GTree) para armazenar InfoData.
 *
 * Cria a GTree se ainda não existir, usando compare_dates para ordenar
 * as datas. Cada nó da árvore contém um apontador para InfoData.
 * 
 * @return Apontador para a árvore de datas inicializada.
 */
GTree *btree_datas_create();

/**
 * @brief Cria uma nova estrutura InfoData.
 *
 * Inicializa a hash table interna que conta voos por aeroporto.
 *
 * @return Apontador para a nova InfoData alocada.
 */
InfoData *info_data_new();

/**
 * @brief Inicializa uma estrutura HashCounter para um intervalo de datas.
 *
 * @param inicio Data inicial do intervalo (pode ser NULL).
 * @param fim Data final do intervalo (pode ser NULL).
 * @return Apontador para a nova estrutura HashCounter.
 */
HashCounter *hash_counter_init(GDate *inicio,GDate *fim);

/**
 * @brief Função de comparação usada pela GTree para ordenar datas.
 *
 * Ordena primeiro pelo ano, depois mês, depois dia.
 *
 * @param a Apontador para a primeira data (GDate*).
 * @param b Apontador para a segunda data (GDate*).
 * @param user_data Dados adicionais (não utilizados).
 * @return Valor negativo, zero ou positivo conforme exigido pela GTree.
 */
int compare_dates(const void *a, const void *b, void *user_data);

/**
 * @brief Adiciona um voo à árvore de datas, atualizando contagens.
 *
 * Converte a data do voo para o tipo GDate e atualiza a hash table
 * do aeroporto correspondente. Cria InfoData se necessário.
 *
 * @param voo Apontador para o voo a adicionar.
 * @param btree_datas Apontador para a árvore de datas.
 */
void adicionar_voo_btree (Voo *voo,GTree *btree_datas);

/**
 * @brief Acumula voos de um InfoData para um HashCounter global.
 *
 * Atualiza contagens globais e mantém o aeroporto com maior número de partidas.
 *
 * @param key Chave do nó da árvore (GDate*).
 * @param value Valor associado (InfoData*).
 * @param user_data Apontador para HashCounter.
 */
void acumula_voos_por_data (void *key,void *value,void *user_data);

/**
 * @brief Percorre a árvore de datas no intervalo definido.
 *
 * Para cada data no intervalo, acumula os voos no HashCounter.
 *
 * @param h Apontador para a estrutura HashCounter.
 * @param btree_datas Apontador para a árvore de datas.
 * @return TRUE se o percurso foi bem sucedido, FALSE caso contrário.
 */
gboolean percorre_datas_intervalo(HashCounter *h,GTree *btree_datas);

/**
 * @brief Devolve o code IATA do aeroporto com mais partidas acumuladas.
 *
 * @param h Apontador para a estrutura HashCounter.
 * @return Code IATA do aeroporto com mais partidas, ou NULL se nenhum.
 */
const char *hash_counter_get_melhor_aeroporto(const HashCounter *h);

/**
 * @brief Devolve o número de voos do aeroporto com mais partidas.
 *
 * @param h Apontador para a estrutura HashCounter.
 * @return Número de voos do melhor aeroporto.
 */
int hash_counter_get_melhor_count(const HashCounter *h);

/**
 * @brief Liberta a memória da árvore de datas (btree_datas).
 * @param btree_datas Apontador para a árvore de datas a libertar.
 */
void free_btree_datas(GTree *btree_datas);

/**
 * @brief Liberta a memória de uma estrutura InfoData.
 *
 * Liberta também a hash table interna de voos por aeroporto.
 *
 * @param info Apontador para a InfoData a libertar.
 */
void info_data_free(InfoData *info);

/**
 * @brief Liberta a memória de um HashCounter.
 *
 * Inclui hash table global, strings e datas copiadas.
 *
 * @param h Apontador para o HashCounter a libertar.
 */
void hash_free (HashCounter *h);

/**
 * @brief Determina o aeroporto com mais partidas num intervalo de datas
 *        e escreve o resultado no ficheiro de output.
 *
 * @param data_inicio Data inicial do intervalo.
 * @param data_fim Data final do intervalo.
 * @param c Separador usado entre os campos.
 * @param output_file Caminho do ficheiro de output (NULL para modo interativo).
 * @param gestorAeroportos Apontador para o gestor de aeroportos.
 * @param btree_datas Apontador para a árvore de datas contendo os voos.
 */
void query3_aeroporto_mais_partidas(GDate *data_inicio, GDate *data_fim, char c, const char *output_file, Aeroportos *gestorAeroportos,GTree *btree_datas);

#endif