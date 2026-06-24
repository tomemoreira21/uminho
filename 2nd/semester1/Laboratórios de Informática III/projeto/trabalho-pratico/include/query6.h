/**
 * @file query6.h
 * @brief Módulo que implementa a query 6: listar o aeroporto de destino mais comum para passageiros de uma
 * determinada nacionalidade.
 *
 * Este módulo permite:
 *  - Armazenar e atualizar o número de voos por destino para cada nacionalidade.
 *  - Consultar o aeroporto mais visitado por uma nacionalidade.
 *  - Gerar output com o destino mais frequente e respetivo número de ocorrências.
 */

#ifndef QUERY6_H
#define QUERY6_H

#include "glib.h"

/**
 * @struct nacionalidadeInfo
 * @brief Estrutura interna usada para acumular destinos por nacionalidade.
 *
 * Esta estrutura guarda uma hash table de destinos (IATA → número de ocorrências)
 * e mantém adicionalmente o destino mais frequente (best_iata) e o respetivo
 * número de ocorrências (best_count), permitindo que a Query 6 seja respondida
 * sem necessidade de percorrer novamente toda a tabela interna.
 *
 * É utilizada como value na GHashTable global onde a key é a nacionalidade.
 */
typedef struct nacionalidadeInfo NacionalidadeInfo;


/**
 * @brief Inicializa a estrutura global usada para acumular estatísticas por nacionalidade.
 *
 * Cria a hash table principal onde cada nacionalidade será associada à respetiva
 * estrutura NacionalidadeInfo. Esta função deve ser chamada antes de qualquer
 * registo de voos ou execução da Query 6.
 * 
 * @return Apontador para a hash table inicializada.
 */
GHashTable *stats_nacionalidade_create();

/**
 * @brief Retorna o número de ocorrências do aeroporto mais visitado por uma nacionalidade.
 *
 * Esta função consulta a estrutura NacionalidadeInfo e devolve a contagem de voos
 * associados ao aeroporto mais frequente visitado pelos passageiros dessa nacionalidade.
 *
 * @param info Apontador para a estrutura NacionalidadeInfo de uma nacionalidade específica.
 * @return Inteiro representando o número de voos para o aeroporto mais frequente.
 */
int get_nacionalidade_best_count (NacionalidadeInfo *info);

/**
 * @brief Retorna o código IATA do aeroporto mais visitado por uma nacionalidade.
 *
 * Consulta a estrutura NacionalidadeInfo e devolve o código IATA do aeroporto
 * que recebeu mais voos de passageiros da nacionalidade associada.
 *
 * @param info Apontador para a estrutura NacionalidadeInfo de uma nacionalidade específica.
 * @return String constante com o código IATA do aeroporto mais frequente.
 */
const char *get_nacionalidade_best_iata (NacionalidadeInfo *info);

/**
 * @brief Cria e inicializa uma nova estrutura NacionalidadeInfo.
 *
 * Responsável por alocar memória, criar a hash table interna dos destinos
 * e definir os valores iniciais do destino mais frequente.
 *
 * @return Apontador para uma nova estrutura NacionalidadeInfo inicializada.
 */
NacionalidadeInfo *nacionalidade_info_new();

/**
 * @brief Incrementa o contador de um destino para uma determinada nacionalidade.
 *
 * Atualiza a hash table interna incrementando o contador associado ao código IATA.
 * Sempre que necessário, atualiza também o par (best_iata, best_count).
 *
 * @param info Estrutura associada à nacionalidade.
 * @param code Código IATA do aeroporto de destino.
 */
void incrementa_destino(NacionalidadeInfo *info,const char *code);

/**
 * @brief Regista a ocorrência de um voo associando nacionalidade ao destino.
 *
 * Caso a nacionalidade ainda não exista na hash table global, é criada uma nova
 * entrada. Em seguida, o destino é contabilizado através de incrementa_destino().
 *
 * @param nat Nacionalidade do passageiro.
 * @param dest Código IATA do aeroporto de destino.
 * @param stats_nacionalidade Apontador para a hash table de nacionalidades.
 */
void regista_nacionalidade(const char *nat,const char *dest,GHashTable *stats_nacionalidade);

/**
 * @brief Gera o output da Query 6 para uma dada nacionalidade.
 *
 * Dado uma nacionalidade, escreve no ficheiro indicado o destino mais frequente
 * (best_iata) e o respetivo número de ocorrências. Caso a nacionalidade não exista
 * ou não tenha registos, é escrita uma linha vazia.
 *
 * @param nationality Nacionalidade a consultar.
 * @param c Separador utilizado entre os campos.
 * @param output_file Caminho para o ficheiro de saída.
 * @param stats_nacionalidade Apontador para a hash table de nacionalidades.
 */
void query6_aeroporto_destino(const char *nationality, char c, const char *output_file,GHashTable *stats_nacionalidade);

/**
 * @brief Liberta a memória associada a uma estrutura NacionalidadeInfo.
 *
 * Destrói a hash table interna e liberta as strings e memória alocada.
 *
 * @param info Apontador para a estrutura a libertar.
 */
void free_nacionalidade_info(NacionalidadeInfo *info);

/**
 * @brief Liberta toda a memória alocada pela estrutura global da Query 6.
 *
 * Remove e destrói a hash table global contendo todas as nacionalidades.
 * Devendo ser chamada no final da execução do programa.
 * 
 * @param stats_nacionalidade Apontador para a hash table de nacionalidades a libertar.
 */
void free_stats_nacionalidade(GHashTable *stats_nacionalidade);

#endif