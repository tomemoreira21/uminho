/**
 * @file passageiros.h
 * @brief Gestão da coleção de passageiros.
 *
 * Define a estrutura e as funções responsáveis por criar, carregar,
 * aceder e libertar passageiros do sistema.
 */
#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H

#include "passageiro.h"
#include "gestor_global.h" 
#include <glib.h>

/**
 * @typedef Passageiros
 * @brief Coleção de passageiros.
 *
 * Implementada como uma GHashTable onde a chave é o número de documento
 * e o valor é um Passageiro.
 */
typedef GHashTable Passageiros;


/**
 * @brief Cria e inicializa a coleção de passageiros.
 *
 * Inicializa uma GHashTable com funções de hash e comparação
 * de strings da GLib e destrutores adequados.
 *
 * @return Apontador para a coleção Passageiros inicializada.
 */
Passageiros *passageiros_create();

/**
 * @brief Cria e inicializa a coleção de passageiros.
 *
 * Inicializa uma GHashTable com funções de hash e comparação
 * de strings da GLib e destrutores adequados.
 *
 * @return Apontador para a coleção Passageiros inicializada.
 */
void passageiros_free(Passageiros *gestor);

/**
 * @brief Carrega os passageiros a partir do ficheiro de dados.
 *
 * Procura o ficheiro passengers (CSV/TSV/PSV), valida os dados,
 * cria os objetos Passageiro e insere-os na coleção.
 * Linhas inválidas são registadas num ficheiro de erros.
 *
 * @param dir Diretório base onde se encontram os ficheiros de dados.
 * @param gestor Coleção Passageiros a preencher.
 */
void passageiros_load(const char *dir, Passageiros *gestor);

/**
 * @brief Insere um passageiro na coleção.
 *
 * O passageiro é inserido usando o número de documento
 * como chave da hash table.
 *
 * @param objeto Apontador para o Passageiro a inserir.
 * @param colecao Apontador para a coleção Passageiros.
 */
void passageiros_add(void *objeto, void *colecao);

/**
 * @brief Obtém um passageiro pelo número de documento.
 *
 * @param gestor Coleção de passageiros.
 * @param document_number Número de documento do passageiro.
 * @return Apontador para o Passageiro ou NULL se não existir.
 */
Passageiro *passageiros_get(Passageiros *gestor, const char *document_number);

#endif