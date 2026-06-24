/**
 * @file passageiro.h
 * @brief Definição da entidade Passageiro e funções associadas.
 *
 * Este módulo define a estrutura opaca ::Passageiro, que representa um
 * passageiro do sistema, bem como as funções responsáveis pela:
 *  - criação de passageiros a partir de dados parseados,
 *  - acesso aos seus campos principais,
 *  - libertação da memória associada.
 *
 * A estrutura interna do Passageiro é mantida oculta, promovendo
 * encapsulamento e modularidade.
 */
#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H


/**
 * @struct passageiro
 * @brief Estrutura opaca que representa um passageiro.
 */
typedef struct passageiro Passageiro;



/**
 * @enum Gender
 * @brief Enumeração representativa do género do passageiro.
 *
 */
typedef enum {
    M,
    F,
    O
} Gender; 

#include <glib.h>


/**
 * @brief Cria um novo passageiro a partir dos dados lidos do ficheiro.
 *
 * Recebe um array de strings resultante do parsing de uma linha de dados
 * e constrói um objeto ::Passageiro. As strings relevantes são transferidas
 * para a estrutura, ficando a responsabilidade da sua libertação associada
 * ao passageiro.
 *
 * @param dados Array de strings com os campos do passageiro.
 * @return Apontador para o Passageiro criado, ou NULL em caso de erro.
 */
Passageiro* cria_passageiro(const gchar** dados);

/**
 * @brief Obtém o número de documento do passageiro.
 *
 * @param passenger Apontador para o Passageiro.
 * @return String com o número do documento.
 */
const char *get_passenger_number (const Passageiro *passenger);

/**
 * @brief Obtém a nacionalidade do passageiro.
 *
 * @param passenger Apontador para o Passageiro.
 * @return String com a nacionalidade.
 */
const char *get_nationality (const Passageiro *passenger);

/**
 * @brief Obtém o primeiro nome do passageiro.
 *
 * @param passenger Apontador para o Passageiro.
 * @return String com o primeiro nome.
 */
const char *get_first_name (const Passageiro *passenger);

/**
 * @brief Obtém o último nome do passageiro.
 *
 * @param passenger Apontador para o Passageiro.
 * @return String com o último nome.
 */
const char *get_last_name (const Passageiro *passenger);

/**
 * @brief Obtém a data de nascimento do passageiro.
 *
 * @param passenger Apontador para o Passageiro.
 * @return String com a data de nascimento.
 */
const char *get_dob (const Passageiro *passenger);

/**
 * @brief Liberta toda a memória associada a um Passageiro.
 *
 * Liberta os campos internos e a própria estrutura.
 *
 * @param p Apontador para o Passageiro a libertar.
 */
void free_passageiro (void* p);

#endif