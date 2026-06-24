/**
 * @file aeroportos.h
 * @brief Interface do gestor de aeroportos.
 *
 * Define a estrutura e as funções responsáveis pela gestão da coleção
 * de aeroportos do sistema, incluindo:
 *  - criação e destruição da coleção,
 *  - inserção e acesso a aeroportos por código IATA,
 *  - atualização de contadores de partidas e chegadas,
 *  - carregamento dos dados a partir de ficheiros.
 */
#ifndef AEROPORTOS_H
#define AEROPORTOS_H

#include "aeroporto.h"
#include "gestor_global.h"
#include <glib.h>


/**
 * @typedef Aeroportos
 * @brief Tabela de hash que representa a coleção de aeroportos.
 *
 * Esta coleção é implementada como uma GHashTable onde:
 *  - A *key* é o código IATA (string);
 *  - O *value* é um objeto ::Aeroporto.
 *
 * A tabela é configurada com funções de destruição adequadas para que a memória
 * seja libertada corretamente quando ocorre a sua destruição.
 */
typedef GHashTable Aeroportos;

/**
 * @brief Cria a estrutura que armazena todos os aeroportos.
 *
 * Inicializa uma hash table configurada para:
 *  - usar as funções da glib, g_str_hash e g_str_equal, como hash/igualdade das keys,
 *  - libertar automaticamente as keys (g_free),
 *  - libertar os aeroportos com free_airport().
 *
 * @return Apontador para a nova coleção Aeroportos.
 */
Aeroportos* aeroportos_create();

/**
 * @brief Insere um aeroporto na coleção.
 *
 * Insere o Aeroporto na hash table usando o seu código IATA
 * como chave.
 *
 * @param objeto Apontador para o Aeroporto a inserir.
 * @param colecao Apontador para a coleção Aeroportos onde será inserido.
 */
void aeroportos_add (void *objeto, void *colecao);

/**
 * @brief Obtém um aeroporto pelo respetivo código IATA.
 *
 * @param gestor Coleção de aeroportos onde procurar.
 * @param code Código IATA do aeroporto.
 * @return Apontador para o Aeroporto, ou NULL caso não exista.
 */

Aeroporto *aeroportos_get(Aeroportos *gestor, const char *code);
/**
 * @brief Liberta toda a coleção de aeroportos.
 *
 * Esta função destrói a hash table após libertar automaticamente todas as keys e
 * todos os aeroportos através de free_airport().
 *
 * @param gestor Coleção de aeroportos a destruir.
 */
void aeroportos_free(Aeroportos *gestor);
/**
 * @brief Incrementa o contador de partidas de um aeroporto.
 *
 * Procura o aeroporto pelo código IATA e incrementa o respetivo contador.
 *
 * @param gestor Coleção de aeroportos.
 * @param code Código IATA do aeroporto em questão.
 */
void incrementa_departure_count_na_coleção (Aeroportos *gestor, const char *code);
/**
 * @brief Incrementa o contador de chegadas de um aeroporto.
 *
 * Procura o aeroporto pelo código IATA e incrementa o respetivo contador.
 *
 * @param gestor Coleção de aeroportos.
 * @param code Código IATA do aeroporto em questão.
 */
void incrementa_arrival_count_na_coleção (Aeroportos *gestor, const char *code);
/**
 * @brief Carrega a coleção de aeroportos a partir do ficheiro de entrada.
 *
 * Constrói o caminho para o ficheiro airports e para o ficheiro de erros,
 * e invoca cria_colecao_do_csv() com as validações sintáticas dos aeroportos
 * e as funções de criação e adição de aeroportos, direcionadas a esta estrutura.
 * 
 * @param dir Diretório da base dos ficheiros de dados.
 * @param gestor Coleção onde os aeroportos serão inseridos.
 */
void aeroportos_load(const char *dir, Aeroportos *gestor);

#endif