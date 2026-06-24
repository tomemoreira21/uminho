/**
 * @file validacao_sintatica_dados.h
 * @brief Declarações das funções de validação sintática de dados do sistema.
 * 
 * Contém funções auxiliares para validação de:
 *  - Datas e horas
 *  - Anos
 *  - E-mails
 *  - Códigos de aeroporto (IATA)
 *  - Coordenadas geográficas
 *  - Listas de IDs e formatos específicos de voos e reservas
 *
 * Todas as funções recebem strings ou arrays de strings e retornam códigos de 
 * erro indicando se o campo é válido ou inválido.
 */
#ifndef VALIDACAO_SINTATICA_H
#define VALIDACAO_SINTATICA_H

#include <glib.h>


/**
 * @brief Valida sintaticamente os campos de uma aeronave.
 *
 * Verifica se o ano de fabrico possui um formato válido.
 *
 * @param dados Array de strings contendo os campos lidos do ficheiro de entrada.
 * @return 0 se for válido, 1 caso contrário.
 */

int validacao_sintatica_aeronave (const gchar** ano);

/**
 * @brief Valida sintaticamente os campos de um aeroporto.
 *
 * Verifica código IATA, latitude, longitude e tipo.
 *
 * @param dados Array de strings contendo os campos lidos do ficheiro de entrada.
 * @return 0 se for válido, 1 caso contrário.
 */

int validacao_sintatica_aeroporto (const gchar** dados);

/**
 * @brief Valida sintaticamente os campos de um passageiro.
 *
 * Verifica número de documento, data, género e e-mail.
 *
 * @param dados Array de strings contendo os campos lidos do CSV.
 * @return 0 se for válido, 1 caso contrário.
 */
int validacao_sintatica_passageiro (const gchar** dados);

/**
 * @brief Valida sintaticamente os campos de uma reserva.
 *
 * Verifica id da reserva, lista de flight IDs e número de documento.
 *
 * @param dados Array de strings contendo os campos lidos do ficheiro de entrada.
 * @return 0 se for válido, 1 caso contrário.
 */
int validacao_sintatica_reserva (const gchar** dados);

/**
 * @brief Valida sintaticamente os campos de um voo.
 *
 * Verifica id, datas/horas e códigos dos aeroportos.
 *
 * @param dados Array de strings contendo os campos lidos do ficheiro de entrada.
 * @return 0 se for válido, 1 caso contrário.
 */
int validacao_sintatica_voo (const gchar** dados);

/**
 * @brief Valida uma data no formato YYYY-MM-DD.
 *
 * @param data_str String com a data.
 * @return Código de erro (0 a 3).
 */
int valida_data (const char *data_str);

/**
 * @brief Valida uma data e hora no formato YYYY-MM-DD HH:MM.
 *
 * @param datetime_str String com data e hora.
 * @return Código de erro (0 a 2).
 */
int valida_data_hora (const char *datetime_str);

/**
 * @brief Valida um ano no formato YYYY.
 *
 * @param ano_str String do ano.
 * @return Devolve 0 caso seja válido e devolve 1 ou 2 caso ou o formato ou o ano seja inválido, respetivamente.
 */
int valida_ano (const char *ano_str);

/**
 * @brief Valida um endereço de e-mail segundo as regras definidas pelo projeto.
 *
 * Esta função verifica a estrutura geral do e-mail, a validade do username,
 * do domínio e da TLD, retornando códigos de erro específicos para cada tipo
 * de falha.
 * 
 * @param email_str String do e-mail.
 * @return Devolve 0 caso seja válido ou retorna um código de erro (1 a 4).
 */
int valida_email (const char *email_str);

/**
 * @brief Valida o tipo textual de aeroporto.
 *
 * Verifica se a string recebida é uma das opções para o tipo do aeroporto apresentado no enunciado.
 * Ex:("small_airport","heliport",...)
 * 
 * @param type String com o tipo.
 * @return 0 se for válido, 1 caso contrário.
 */
int valida_type_aeroporto (const char *type);

/**
 * @brief Valida latitude no formato correto e dentro do intervalo permitido.
 *
 * @param latitude_str String da latitude.
 * @return Devolve 0 caso seja válido ou retorna um código de erro (1 a 2).
 */
int valida_latitude (const char *latitude_str);

/**
 * @brief Valida longitude no formato correto e dentro do intervalo permitido.
 *
 * @param longitude_str String da longitude.
 * @return Devolve 0 caso seja válido ou retorna um código de erro (1 a 2).
 */
int valida_longitude (const char *longitude_str);

/**
 * @brief Valida o formato numérico de uma coordenada.
 *
 * @param coord_str String da coordenada.
 * @param min Valor mínimo permitido.
 * @param max Valor máximo permitido.
 * @return Devolve 0 caso seja válido ou retorna um código de erro (1 a 2).
 */
int valida_formato (const char *coord_str,int min,int max);

/**
 * @brief Valida um código IATA de aeroporto (3 letras maiúsculas).
 *
 * @param code_str String do código.
 * @return 0 se válido, 1 caso contrário.
 */
int valida_code_aeroporto (const char *code_str);

/**
 * @brief Valida lista textual de flight IDs (conteúdo interno).
 *
 * @param str String da lista.
 * @return 0 se válido, 1 caso contrário.
 */
int valida_lista_ids(const char *str);

/**
 * @brief Valida um identificador de voo no formato AA00000.
 *
 * O ID deve começar com 2 letras maísculas, seguido de 5 ou 6 digitos.
 * 
 * @param id_str String do ID.
 * @return 0 se válido, 1 caso contrário.
 */
int valida_id_voo (const char *id_str);

/**
 * @brief Valida o identificador de reserva no formato R#########.
 *
 * O ID deve começar com 'R' seguido de 9 dígitos (R000000000).
 * 
 * @param id_str String do ID.
 * @return 0 se válido, 1 caso contrário.
 */
int valida_id_reserva (const char *id_str);

/**
 * @brief Valida o número de documento (9 dígitos).
 *
 * @param nr_documento_str String do número.
 * @return 0 se válido, 1 caso contrário.
 */
int valida_nr_documento (const char *nr_documento_str);

/**
 * @brief Valida o género (M, F ou O).
 *
 * @param genero_str String do género.
 * @return 0 se válido, 1 caso contrário.
 */
int valida_genero (const char *genero_str);

/**
 * @brief Valida o formato exterior de listas CSV.
 *
 * @param list_str String da lista.
 * @return 0 se válido, 1 caso contrário.
 */
int valida_listas_CSV (const char *list_str);

#endif