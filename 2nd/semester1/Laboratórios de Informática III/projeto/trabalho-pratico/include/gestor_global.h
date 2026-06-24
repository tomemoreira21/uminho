/**
 * @file gestor_global.h
 * @brief Interface do Gestor Global do sistema.
 *
 * Este módulo define o GestorGlobal, uma estrutura central que agrega
 * todos os gestores do sistema (aeronaves, aeroportos, passageiros,
 * voos, reservas, queries e output).
 *
 * Fornece funções para:
 *  - Criar e destruir o gestor global
 *  - Carregar os dados a partir de ficheiros
 *  - Aceder aos diferentes gestores internos
 *  - Gerir estruturas auxiliares usadas pelas queries
 */
#ifndef GESTORGLOBAL_H
#define GESTORGLOBAL_H
/**
 * @struct global
 * @brief Estrutura opaca que agrega todos os gestores do sistema.
 *
 * Contém apontadores para os gestores de:
 *  - Aeronaves
 *  - Aeroportos
 *  - Passageiros
 *  - Voos
 *  - Reservas
 *  - Queries
 *  - Output
 */
typedef struct global GestorGlobal;
/**
 * @struct queries
 * @brief Estrutura que armazena dados auxiliares para as queries.
 *
 * Contém:
 *  - btree_datas: GTree utilizada na Query 3 (key: GDate*, value: InfoData*)
 *  - airline_table: hash table auxiliar para Query 5
 *  - airline_results: array de resultados ordenado para Query 5
 *  - stats_nacionalidade: hash table utilizada na Query 6
 *  - semAno_table: hash table utilizada na Query 4
 */
typedef struct queries Queries;

/**
 * @brief Cria e inicializa um novo GestorGlobal.
 *
 * Aloca memória e inicializa cada um dos gestores internos.
 *
 * @return Apontador para um GestorGlobal inicializado, ou NULL em caso de erro.
 */
GestorGlobal *gestor_create();

/**
 * @brief Cria e inicializa a estrutura auxiliar Queries.
 *
 * Inicializa todas as estruturas auxiliares usadas pelas queries:
 *  - btree_datas
 *  - airline_table
 *  - airline_results
 *  - stats_nacionalidade
 *  - semAno_table
 *
 * @return Apontador para uma Queries inicializada, ou NULL em caso de erro.
 */
Queries *queries_create();

/**
 * @brief Carrega todos os dados a partir dos ficheiros de entrada.
 *
 * Esta função invoca as funções de leitura de cada gestor específico.
 *
 * @param dir Diretório onde se encontram os ficheiros de dados.
 * @param gestor  Apontador para o GestorGlobal a ser preenchido.
 */
void gestor_load(const char *dir, GestorGlobal *gestor);

/**
 * @brief Obtém o gestor de Aeronaves.
 * @param g Apontador para o GestorGlobal.
 * @return Apontador para o gestor Aeronaves.
 */
void *get_gestor_Aeronaves(GestorGlobal *g);

/**
 * @brief Obtém o gestor de Aeroportos.
 * @param g Apontador para o GestorGlobal.
 * @return Apontador para o gestor Aeroportos.
 */
void *get_gestor_Aeroportos(GestorGlobal *g);

/**
 * @brief Obtém o gestor de Passageiros.
 * @param g Apontador para o GestorGlobal.
 * @return Apontador para o gestor Passageiros.
 */
void *get_gestor_Passageiros(GestorGlobal *g);

/**
 * @brief Obtém o gestor de Voos.
 * @param g Apontador para o GestorGlobal.
 * @return Apontador para o gestor Voos.
 */
void *get_gestor_Voos(GestorGlobal *g);

/**
 * @brief Obtém o gestor de Reservas.
 * @param g Apontador para o GestorGlobal.
 * @return Apontador para o gestor Reservas.
 */
void *get_gestor_Reservas(GestorGlobal *g);

/**
 * @brief Liberta toda a memória associada ao GestorGlobal.
 *
 * Esta função liberta cada gestor específico e, por fim, a 
 * própria estrutura GestorGlobal.
 *
 * @param g Apontador para o GestorGlobal a destruir.
 */
void gestor_free(GestorGlobal *g);

/**
 * @brief Obtém o gestor de Queries.
 * @param g Apontador para o GestorGlobal.
 * @return Apontador para a estrutura Queries.
 */
void *get_gestor_Queries(GestorGlobal *g);

/**
 * @brief Devolve a árvore de datas utilizada na Query 3.
 * @param q Apontador para a estrutura Queries.
 * @return Apontador para a GTree de datas.
 */
void *get_btree_query3(Queries *q);

/**
 * @brief Devolve a hash table utilizada na Query 4.
 * @param q Apontador para a estrutura Queries.
 * @return Apontador para a hash table.
 */
void *get_hashtable_query4(Queries *q);

/**
 * @brief Devolve o array de resultados ordenado utilizado na Query 5.
 * @param q Apontador para a estrutura Queries.
 * @return Apontador para o array de resultados.
 */
void *get_array_query5(Queries *q);

/**
 * @brief Devolve a hash table auxiliar utilizada na Query 5.
 * @param q Apontador para a estrutura Queries.
 * @return Apontador para a hash table.
 */
void *get_hashtable_query5(Queries *q);

/**
 * @brief Devolve a hash table utilizada na Query 6.
 * @param q Apontador para a estrutura Queries.
 * @return Apontador para a hash table.
 */
void *get_hashtable_query6(Queries *q);

/**
 * @brief Liberta toda a memória associada à estrutura Queries.
 * @param q Apontador para a estrutura Queries a destruir.
 */
void queries_free(Queries *q);

/**
 * @brief Prepara as estruturas das Queries após o carregamento dos dados.
 *        Ordena listas e constrói arrays auxiliares.
 * @param g Apontador para o GestorGlobal.
 */
void queries_prepare(GestorGlobal *g);

/**
 * @brief Obtém o gestor de Output.
 * @param g Apontador para o GestorGlobal.
 * @return Apontador para a hash table de Output.
 */
void *get_gestor_Output(GestorGlobal *g);


#endif