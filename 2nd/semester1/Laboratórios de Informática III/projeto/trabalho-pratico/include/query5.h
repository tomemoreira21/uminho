/**
 * @file query5.h
 * @brief Módulo que implementa a query 5: top N companhias aéreas com mais tempo de atraso médio por voo.
 *
 * Este módulo fornece estruturas e funções para:
 *  - Acumular dados de atrasos por companhia aérea durante o carregamento dos voos.
 *  - Calcular médias de atraso por voo.
 *  - Ordenar os resultados por atraso médio e nome da companhia.
 *  - Gerar ficheiros de output com as companhias mais afetadas por atrasos.
 */
#ifndef QUERY5_H
#define QUERY5_H

#include <glib.h> 

/**
 * @struct airlineDelay
 * @brief Estrutura interna usada para acumular informação de atrasos por companhia.
 *
 * Esta estrutura guarda o total de minutos de atraso e o número total de voos
 * associados a uma determinada companhia aérea. É utilizada como value na
 * GHashTable durante a fase de load dos dados.
 */
typedef struct airlineDelay AirlineDelay;

/**
 * @struct airlineResult
 * @brief Estrutura que representa o resultado final da Query 5.
 *
 * Após o load dos dados e cálculos respetivos, cada elemento da
 * estrutura contém o nome da companhia aérea, o número de voos registados e
 * a média de atraso desses voos. Esta estrutura é posteriormente ordenada
 * de acordo com os critérios da Query 5.
 */
typedef struct airlineResult AirlineResult;
typedef struct airlineStat AirlineStat;

/**
 * @brief Inicializa a estrutura de dados necessária para acumular os dados.
 *
 * Esta função deve ser chamada antes de qualquer outra função relacionada
 * com a Query 5. Inicializa a hash table sendo responsável por armazenar os 
 * dados relativamente às companhias aéreas (atrasos por companhia aérea).
 * 
 * @return Apontador para a hash table inicializada.
 */
GHashTable *airlines_create();

/**
 * @brief Cria e inicializa uma estrutura AirlineResult vazia.
 *
 * Esta função aloca memória para um objeto AirlineResult, inicializa o
 * array de resultados de companhias aéreas como NULL e define o tamanho como 0.
 * É utilizada para armazenar os resultados finais da query de atrasos por companhia aérea.
 *
 * @return Apontador para a estrutura AirlineResult criada.
 */
AirlineResult *airlines_result_create();

/**
 * @brief Obtém o nome de uma companhia aérea a partir de uma estrutura AirlineStat.
 *
 * Esta função devolve diretamente o apontador para uma string que representa o nome da companhia
 * aérea contida na estrutura AirlineStat.
 *
 * @param a Apontador para a estrutura AirlineStat.
 * @return Nome da companhia aérea.
 */
const char *get_airline_name (AirlineStat *a);

/**
 * @brief Obtém o número de voos registados para uma companhia aérea.
 *
 * Esta função retorna o valor de n_flights presente na estrutura AirlineStat,
 * representando quantos voos dessa companhia foram contabilizados.
 *
 * @param a Apontador para a estrutura AirlineStat.
 * @return Número de voos da companhia aérea.
 */
int get_airline_flights (AirlineStat *a);

/**
 * @brief Obtém o atraso médio por voo de uma companhia aérea.
 *
 * Esta função devolve o valor de avg_delay contido na estrutura AirlineStat,
 * correspondendo à média dos atrasos em minutos para todos os voos registados
 * dessa companhia aérea.
 *
 * @param a Apontador para a estrutura AirlineStat.
 * @return Atraso médio por voo em minutos.
 */
double get_airline_avg_delay (AirlineStat *a);

/**
 * @brief Regista um atraso associado a uma determinada companhia aérea.
 *
 * Atualiza a hash table somando o atraso passado como parâmetro e incrementando
 * o número de voos dessa companhia. Caso a companhia ainda não exista na tabela,
 * a função cria automaticamente uma nova entrada.
 *
 * @param airline_name Nome da companhia aérea.
 * @param delay_minutes Atraso (em minutos) que será adicionado à companhia respetiva.
 * @param airline_table Apontador para a hash table das companhias aéreas.
 */
void airlines_add_delay (const char *airline_name, long delay_minutes,GHashTable *airline_table);

/**
 * @brief Calcula a diferença em minutos entre duas datas.
 *
 * Esta função recebe dois objetos GDateTime e devolve o intervalo entre eles
 * expresso em minutos. É utilizada para determinar o atraso real de um voo.
 *
 * @param end Data/hora final.
 * @param start Data/hora inicial.
 * @return Diferença entre as datas em minutos.
 */
long diff_minutes(GDateTime *end, GDateTime *start);

/**
 * @brief Função de comparação usada pelo qsort para ordenar companhias.
 *
 * Ordena primeiro por média de atraso em ordem decrescente. Em caso de empate,
 * ordena alfabeticamente pelo nome da companhia.
 *
 * @param a Apontador para o primeiro elemento a comparar.
 * @param b Apontador para o segundo elemento a comparar.
 * @return Valor negativo, zero ou positivo conforme exigido pelo qsort.
 */
int cmp_airline(const void *a, const void *b);

/**
 * @brief Constrói o array final de resultados da Query 5.
 *
 * Converte os dados acumulados na hash table para um array de AirlineResult.
 * Calcula médias, copia dados e ordena os resultados com qsort. Esta função
 * deve ser chamada após todo o carregamento dos voos e antes de executar a query.
 * 
 * @param airline_table Apontador para a hash table das companhias aéreas.
 * @param r Apontador para o array de resultados das companhias aéreas.
 */
void build_airline_results(GHashTable *airline_table,AirlineResult *r);

/**
 * @brief Gera o ficheiro de output com as companhias mais afetadas por atrasos.
 *
 * A função escreve no ficheiro indicado as top N companhias aéreas com maior
 * média de atraso, apresentando nome da companhia, número de voos e o atraso médio calculado.
 *
 * @param topN Número de companhias a listar.
 * @param c Separador usado entre os campos.
 * @param output_file Caminho para o ficheiro de saída.
 * @param r Apontador para o array de resultados das companhias aéreas.
 */
void query5_listar_companhias_mais_atrasos (int topN, char c,const char *output_file,AirlineResult *r);

/**
 * @brief Liberta toda a memória alocada pela estrutura da Query 5.
 *
 * Remove e destrói a hash table e o array de resultados criado em build_airline_results().
 * Esta função deve ser chamada no final da execução do programa.
 * 
 * @param airline_table Apontador para a hash table das companhias aéreas a libertar.
 * @param r Apontador para o array de resultados das companhias aéreas a libertar.
 */
void free_airlines(GHashTable *airline_table,AirlineResult *r);

#endif