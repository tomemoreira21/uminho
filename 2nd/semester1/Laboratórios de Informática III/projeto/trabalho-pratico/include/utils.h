
/**
 * @file utils.h
 * @brief Funções utilitárias de conversão e manipulação de datas, horas e listas.
 *
 * Este módulo fornece funções para:
 *  - Converter strings para GDateTime e GDate.
 *  - Extrair apenas a data de um GDateTime.
 *  - Transformar strings de IDs de voos em arrays dinâmicos (GPtrArray).
 * 
 * As funções são usadas em diversos módulos para normalizar formatos e facilitar o processamento de dados.
 */
#ifndef UTILS_H
#define UTILS_H

#include <glib.h>


/**
 * @brief Converte uma string de data e hora num GDateTime.
 *
 * A string deve estar no formato "YYYY-MM-DD HH:MM".
 * Se a string for "N/A" ou tiver formato inválido, devolve NULL.
 * O GDateTime criado utiliza o fuso horário UTC.
 *
 * @param str String com a data e hora.
 * @return Apontador para GDateTime ou NULL em caso de erro.
 */
GDateTime *type_string_to_datetime (const char *str);


/**
 * @brief Converte uma string de data num GDate.
 *
 * A string deve estar no formato "YYYY-MM-DD".
 *
 * @param str String com a data.
 * @return Apontador para GDate ou NULL se o formato for inválido.
 */
GDate *type_string_to_gdate(const char *str);


/**
 * @brief Converte uma string com IDs de voos num array dinâmico.
 *
 * A string deve estar no formato "[ID1,ID2,...]".
 * Cada identificador é copiado e armazenado num GPtrArray.
 *
 * @param str String com a lista de identificadores de voos.
 * @return Apontador para GPtrArray com os IDs ou NULL em caso de erro.
 */
GPtrArray *type_string_flight_ids(const char *str);


/**
 * @brief Extrai apenas a data de um GDateTime.
 *
 * Cria um novo GDate com o ano, mês e dia do GDateTime fornecido.
 *
 * @param dt Apontador para GDateTime.
 * @return Apontador para GDate ou NULL se dt for NULL.
 */
GDate *datetime_to_date(GDateTime *dt);


#endif