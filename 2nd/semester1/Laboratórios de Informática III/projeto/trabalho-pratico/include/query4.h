/**
 * @file query4.h
 * @brief Módulo que implementa a query 4: passageiro que aparece mais vezes no top 10 semanal de gastos
 *
 * Este módulo implementa a Query 4 do projeto, cujo objetivo é determinar
 * o passageiro que aparece mais vezes no top 10 semanal de gastos,
 * considerando opcionalmente um intervalo de datas.
 *
 * A abordagem baseia-se numa tabela de dispersão indexada por (ano, semana),
 * onde cada entrada contém:
 *  - uma tabela de contagem de gastos por passageiro nessa semana;
 *  - uma heap (priority queue) com o top 10 de passageiros dessa semana,
 *    ordenados pelo valor gasto.
 *
 * Após o processamento completo dos dados, as heaps semanais são usadas
 * para calcular, globalmente, qual o passageiro que surge mais vezes no
 * top 10, resolvendo empates por ordem lexicográfica do identificador.
 */
#ifndef QUERY4_H
#define QUERY4_H

#include <glib.h>
#include "voo.h"
#include "passageiros.h"
#include "reserva.h"

/**
 * @brief Estrutura que representa uma semana de um determinado ano.
 */
typedef struct semanaAno SemAno;

/**
 * @brief Estrutura que guarda os gastos por passageiro e o top 10 semanal.
 */
typedef struct countETop10 CTop10;

/**
 * @brief Nodo usado na heap para o top 10.
 */
typedef struct node Nodo;

/**
 * @brief Hash table indexada por (ano, semana).
 */
typedef GHashTable TableSemAno;

/**
 * @brief Estrutura auxiliar global para contar quantas vezes
 *        um passageiro aparece em top10.
 */
typedef struct hash_counter CountEmTop10;

/**
 * @brief Cria a estrutura global que conta aparições em top 10.
 * 
 * @return Apontador para CountEmTop10.
 */
CountEmTop10 *criaCountEmTop10();

/**
 * Cria a hash table que associa (semana, ano)
 * a uma estrutura de contagem e top 10.
 *
 * @return Apontador para TableSemAno
 */
TableSemAno *criaHashTableAnoSemanas();

/**
 * Cria a estrutura que contém a contagem e
 * a heap de top 10 para uma semana.
 *
 * @return Apontador para CTop10
 */
CTop10 *criaCountETop10();

/**
 * Compara duas estruturas semana/ano.
 *
 * @param sa1 Apontador para a primeira estrutura
 * @param sa2 Apontador para a segunda estrutura
 * @return TRUE se forem iguais, FALSE caso contrário
 */
gboolean compareSemAno(const void *sa1,const void *sa2);

/**
 * Função de comparação usada na heap do top 10.
 * Ordena por gasto e, em caso de empate, por ordem
 * lexicográfica inversa do documento.
 *
 * @param novo Apontador para o novo nodo
 * @param topo Apontador para o nodo do topo
 * @return Valor de comparação
 */
int compareNodos(const void *novo,const void *topo);

/**
 * Função de hash para a estrutura semana/ano.
 *
 * @param sa Apontador para SemAno
 * @return Valor hash
 */
unsigned int hashSemanaAno(const void *sa);

/**
 * Obtém o documento do passageiro que aparece
 * mais vezes em top 10.
 *
 * @param h Apontador para CountEmTop10
 * @return String com o documento
 */
const char *get_ctGlobal_melhor (CountEmTop10 *h);

/**
 * Obtém o número de vezes que o passageiro
 * aparece em top 10.
 *
 * @param h Apontador para CountEmTop10
 * @return Contagem
 */
int get_ctGlobal_count (CountEmTop10 *h);

/**
 * Cria uma estrutura semana/ano a partir da data
 * de partida de um voo.
 *
 * @param departure Apontador para GDate
 * @return Apontador para SemAno
 */
SemAno *semanaAno (GDate *departure);

/**
 * Adiciona o gasto de um passageiro à semana correspondente.
 *
 * @param gasto Valor gasto
 * @param document_number Documento do passageiro
 * @param v Apontador para Voo
 * @param semAno_table Hash table de semanas
 */
void adicionaGasto(float gasto, char *document_number, const Voo *v, TableSemAno *semAno_table);

/**
 * Constrói o top 10 semanal para todas as semanas
 * presentes na hash table.
 *
 * @param semAno_table Hash table de semanas
 */
void criaTop10(TableSemAno *semAno_table);

/**
 * Executa a query 4 com filtro de datas.
 *
 * @param data_inicio Data inicial
 * @param data_fim Data final
 * @param c Separador de campos
 * @param output_file Ficheiro de saída (ou NULL para modo interativo)
 * @param gestorPassageiros Apontador para gestor de passageiros
 * @param semAno_table Hash table de semanas
 */
void query4_com_filtro(GDate *data_inicio, GDate *data_fim, char c, const char *output_file, Passageiros *gestorPassageiros, TableSemAno *semAno_table);

/**
 * Executa a query 4 sem filtro de datas.
 *
 * @param c Separador de campos
 * @param output_file Ficheiro de saída (ou NULL para modo interativo)
 * @param gestorPassageiros Apontador para gestor de passageiros
 * @param semAno_table Hash table de semanas
 */
void query4_sem_filtro(char c, const char *output_file, Passageiros *gestorPassageiros, TableSemAno *semAno_table);

/**
 * Função principal da query 4.
 * Decide automaticamente se usa filtro ou não.
 *
 * @param data_inicio Data inicial
 * @param data_fim Data final
 * @param c Separador de campos
 * @param output_file Ficheiro de saída
 * @param gestorPassageiros Apontador para gestor de passageiros
 * @param semAno_table Hash table de semanas
 */
void query4_passageiro_mais_vezes_top10(GDate *data_inicio, GDate *data_fim, char c, const char *output_file, Passageiros *gestorPassageiros, TableSemAno *semAno_table);

/**
 * Liberta a estrutura CountEmTop10.
 *
 * @param ct Apontador para CountEmTop10
 */
void freeCountEmTop10(void *ct);

/**
 * Liberta a estrutura CTop10.
 *
 * @param ct Apontador para CTop10
 */
void freeCountETop10 (void *ct);

/**
 * Liberta um nodo da heap.
 *
 * @param n Apontador para Nodo
 */
void freeNodos (void *n);

#endif