/**
 * @file testar.h
 * @brief Declaração de funções para testes automáticos e estatísticas de execução.
 *
 * Este módulo fornece funções para:
 *  - Medir tempo de execução de queries
 *  - Comparar ficheiros de output gerado com esperado
 *  - Monitorizar uso de memória
 *  - Armazenar e apresentar estatísticas de testes
 *
 * Funciona com as queries 1 a 6, aeroportos, aeronaves, voos, passageiros e reservas.
 */
#ifndef TESTAR_H
#define TESTAR_H

#include <time.h>
#include "aeronaves.h"
#include "aeroportos.h"
#include "passageiros.h"
#include "voos.h"
#include "reservas.h"
#include "query5.h"
#include "query4.h"

/**
 * @struct queryStats
 * @brief Estrutura para armazenar estatísticas de execução de uma query.
 *
 * Campos:
 *  - total: total de testes executados
 *  - corretos: número de testes corretos
 *  - erros: número de erros encontrados
 *  - tempo: tempo total gasto na execução
 *  - primeira_linha_erro: linha onde ocorreu a primeira discrepância em cada erro
 *  - nr_query: número da query associada ao erro
 *  - arquivo_erro: nome do ficheiro que apresentou erro
 *  - tam: capacidade atual dos arrays
 */
typedef struct queryStats QueryStats;


/**
 * @brief Calcula a diferença em segundos entre dois tempos.
 *
 * @param start Tempo inicial.
 * @param end Tempo final.
 * @return Diferença em segundos (com precisão de nanossegundos).
 */
double diff_time(struct timespec start, struct timespec end);

/**
 * @brief Retorna a memória usada pelo processo em KB.
 *
 * @return Memória utilizada em kilobytes.
 */
long memoria_usada_kb();

/**
 * @brief Compara o conteúdo de dois ficheiros linha a linha.
 *
 * @param ficheiro1 Caminho para o primeiro ficheiro.
 * @param ficheiro2 Caminho para o segundo ficheiro.
 * @return 0 se forem iguais, -1 se algum ficheiro estiver vazio, ou número da primeira linha com discrepância.
 */
int compara_ficheiros(const char *ficheiro1, const char *ficheiro2);

/**
 * @brief Inicializa a estrutura de estatísticas para as queries.
 *
 * @param num_queries Número de queries a monitorizar.
 */
void inicializar_stats(int num_queries);

/**
 * @brief Executa os testes definidos num ficheiro de input e compara os outputs com os esperados.
 *
 * @param input_file Caminho para o ficheiro com comandos de teste.
 * @param pasta_output_esperado Pasta contendo os ficheiros de output esperados.
 * @param g Apontador para o GestorGlobal, para aceder a voos, aeroportos, passageiros e reservas.
 */
void executar_testes(const char *input_file, const char *pasta_output_esperado, GestorGlobal *g);

/**
 * @brief Executa e regista estatísticas para a query 1.
 *
 * @param rest String com o code IATA.
 * @param output_gerado Ficheiro com o output gerado pela execução.
 * @param output_esperado Ficheiro com o output esperado para comparação.
 * @param c Caracter separador usado na execução.
 * @param nr_query Número da query.
 * @param gestorAeroportos Apontador para a estrutura de gestão de aeroportos.
 */
void execution_stats_q1(const char *rest, const char *output_gerado, const gchar *output_esperado, char c, int nr_query, Aeroportos *gestorAeroportos);

/**
 * @brief Executa e regista estatísticas para a query 2.
 *
 * @param N Top N fornecido.
 * @param manufactor Nome do fabricante utilizado na query.
 * @param output_gerado Ficheiro com o output gerado pela execução.
 * @param output_esperado Ficheiro com o output esperado para comparação.
 * @param c Caracter separador usado na execução.
 * @param nr_query Número da query.
 * @param gestorAeronaves Apontador para a estrutura de gestão de aeronaves.
 */
void execution_stats_q2(int N, const char *manufactor, const char *output_gerado, const gchar *output_esperado, char c, int nr_query, Aeronaves *gestorAeronaves);

/**
 * @brief Executa e regista estatísticas para a query 3.
 *
 * @param data_inicio Data de início definida pela query.
 * @param data_fim Data de fim definida pela query.
 * @param output_gerado Ficheiro com o output gerado pela execução.
 * @param output_esperado Ficheiro com o output esperado para comparação.
 * @param c Caracter separador usado na execução.
 * @param nr_query Número da query.
 * @param gestorAeroportos Apontador para a estrutura de gestão de aeroportos.
 * @param btree_datas Árvore de datas (GTree) utilizada na query.
 */
void execution_stats_q3(GDate *data_inicio, GDate *data_fim, const char *output_gerado, const gchar *output_esperado, char c, int nr_query, Aeroportos *gestorAeroportos,GTree *btree_datas);

/**
 * @brief Executa e regista estatísticas para a query 4.
 *
 * @param data_inicio Data de início definida pela query.
 * @param data_fim Data de fim definida pela query.
 * @param output_gerado Ficheiro com o output gerado pela execução.
 * @param output_esperado Ficheiro com o output esperado para comparação.
 * @param c Caracter separador usado na execução.
 * @param nr_query Número da query.
 * @param gestorPassageiros Apontador para a estrutura de gestão de passageiros.
 * @param seamAno_table Hash table auxiliar de estatísticas sem ano.
 */
void execution_stats_q4(GDate *data_inicio, GDate *data_fim, const char *output_gerado, const gchar *output_esperado, char c, int nr_query, Passageiros *gestorPassageiros, TableSemAno *seamAno_table);

/**
 * @brief Executa e regista estatísticas para a query 5.
 *
 * @param output_gerado Ficheiro com o output gerado pela execução.
 * @param output_esperado Ficheiro com o output esperado para comparação.
 * @param topN Número de resultados a considerar.
 * @param c Caracter separador usado na execução.
 * @param nr_query Número da query.
 * @param r Apontador para o array de resultados de companhias aéreas.
 */
void execution_stats_q5(const char *output_gerado, const gchar *output_esperado,int topN, char c,int nr_query,AirlineResult *r);

/**
 * @brief Executa e regista estatísticas para a query 6.
 *
 * @param output_gerado Ficheiro com o output gerado pela execução.
 * @param output_esperado Ficheiro com o output esperado para comparação.
 * @param nationality Nacionalidade utilizada como filtro na query.
 * @param c Caracter separador usado na execução.
 * @param nr_query Número da query.
 * @param stats_nacionalidade Hash table com estatísticas por nacionalidade.
 */
void execution_stats_q6(const char *output_gerado, const gchar *output_esperado,const char *nationality, char c,int nr_query,GHashTable *stats_nacionalidade);

/**
 * @brief Liberta a memória alocada para as estatísticas das queries.
 *
 * @param num_queries Número de queries monitorizadas.
 */
void free_stats(int num_queries);

/**
 * @brief Mostra no terminal os resultados da execução dos testes.
 *
 * Inclui número de testes corretos, discrepâncias, memória utilizada, tempo médio por query e tempo total.
 *
 * @param num_queries Número de queries monitorizadas.
 * @param tempo_total_s Tempo total de execução em segundos.
 * @param mem_kb Memória utilizada em KB.
 */
void mostrar_resultados(int num_queries, double tempo_total_s, long mem_kb);

#endif