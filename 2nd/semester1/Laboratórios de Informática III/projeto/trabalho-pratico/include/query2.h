/**
 * @file query2.h
 * @brief Módulo que implementa a query 2: lista das aeronaves com mais voos.
 *
 * Este módulo fornece estruturas e funções para:
 * - Contabilizar o número de voos por aeronave;
 * - Utilizar uma heap (max-heap) para ordenar aeronaves por número de voos;
 * - Listar as N aeronaves com mais voos, com ou sem filtro por fabricante;
 * - Escrever os resultados em ficheiro ou apresentar no modo interativo.
 */
#ifndef QUERY2_H
#define QUERY2_H

/**
 * @struct entradaheap
 * @brief Estrutura usada para gerir entradas na heap de aeronaves.
 *
 * Contém uma lista (GList) de aeronaves de um determinado fabricante,
 * utilizada para implementar uma max-heap com base no número de voos.
 */
typedef struct entradaheap EntradaHeap;

#include "voo.h"
#include "aeronaves.h"

/**
 * @brief Incrementa o contador de voos de uma aeronave associada a um voo.
 *
 * Procura a aeronave pelo identificador do voo, acede ao fabricante
 * correspondente e incrementa o contador de voos da aeronave.
 *
 * @param gestorAeronaves Apontador para o gestor de aeronaves, onde é efetuada a pesquisa da aeronave associada ao voo.
 * @param voo Apontador para o voo que será usado para identificar a aeronave.
 */
void incrementa_flight_count_da_aeronave(Aeronaves *gestorAeronaves, Voo* voo);

/**
 * @brief Compara duas entradas da heap para ordenar aeronaves.
 *
 * Ordena em ordem decrescente de número de voos, transformando a heap
 * numa max-heap.
 *
 * @param a Apontador para a primeira entrada da heap.
 * @param b Apontador para a segunda entrada da heap.
 * @return Valor negativo, zero ou positivo conforme exigido pelo algoritmo de heap.
 */
int compare_heap_entry (const void *a,const void *b);

/**
 * @brief Lista as N aeronaves com mais voos de um fabricante específico.
 *
 * Escreve no ficheiro de output o seu identificador, fabricante, modelo e número de voos.
 *
 * @param N Número máximo de aeronaves a listar.
 * @param manufacturer Nome do fabricante a filtrar.
 * @param c Separador usado entre os campos.
 * @param output_file Caminho do ficheiro de output ou NULL para modo interativo.
 * @param gestorAeronaves Apontador para o gestor de aeronaves, utilizado para obter as aeronaves pertencentes a um determinado fabricante.
 */
void query2_com_filtro (int N, const char *manufacturer, char c,const char *output_file, Aeronaves *gestorAeronaves);

/**
 * @brief Lista as N aeronaves com mais voos, sem filtrar por fabricante.
 *
 * Utiliza uma heap (max-heap) para percorrer todas as aeronaves de todos os fabricantes.
 *
 * @param N Número máximo de aeronaves a listar.
 * @param c Separador usado entre os campos.
 * @param output_file Caminho do ficheiro de output ou NULL para modo interativo.
 * @param gestorAeronaves Apontador para o gestor de aeronaves.
 */
void query2_sem_filtro (int N, char c,const char *output_file, Aeronaves *gestorAeronaves);

/**
 * @brief Lista as N aeronaves com mais voos.
 *
 * Se for fornecido o parâmetro "manufactor", filtra apenas esse fabricante.
 * Caso contrário, considera todas as aeronaves.
 *
 * @param N Número máximo de aeronaves a listar.
 * @param manufactor Nome do fabricante a filtrar (pode ser NULL caso não tenha o filtro).
 * @param c Separador usado entre os campos.
 * @param output_file Caminho do ficheiro de output ou NULL para modo interativo.
 * @param gestorAeronaves Apontador para o gestor de aeronaves.
 */
void query2_listar_aeronaves_mais_voos (int N, const char *manufactor, char c, const char *output_file, Aeronaves *gestorAeronaves);

#endif