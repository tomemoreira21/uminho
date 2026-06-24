/**
 * @file interativo.h
 * @brief Interface para o módulo interativo do sistema.
 *
 * Este módulo implementa a interação com o utilizador via terminal,
 * utilizando a biblioteca ncurses. Permite navegar pelo menu, 
 * solicitar dados e apresentar os resultados das queries.
 */
#ifndef INTERATIVO_H
#define INTERATIVO_H

#include <ncurses.h>
#include "gestor_global.h"
#include "query4.h"
#include "aeroporto.h"
#include "query6.h"

/**
 * @brief Inicializa o modo ncurses.
 *
 * Configura o terminal para modo cbreak, sem eco e ativa teclado.
 */
void init_ncurses();

/**
 * @brief Desenha a tela inicial do sistema.
 *
 * Mostra mensagem de boas-vindas e verifica suporte a cores.
 */
void desenha_init();

/**
 * @brief Verifica se a diretoria do dataset existe.
 *
 * @param dir Caminho para o dataset.
 * @return 1 se existir, 0 caso contrário.
 */
int dataset_existe(const char *dir);

/**
 * @brief Solicita ao utilizador o caminho para o dataset.
 *
 * Normaliza o caminho e verifica existência.
 *
 * @param path Buffer para armazenar o caminho.
 * @return 0 se válido, -1 se ESC pressionado.
 */
int get_dataset_path(char *path);

/**
 * @brief Muda a diretoria de trabalho para a raiz do executável.
 */
void muda_diretoria_raiz();

/**
 * @brief Solicita ao utilizador um código IATA de aeroporto.
 *
 * O código deve ter exatamente 3 caracteres.
 *
 * @param code Buffer de 4 caracteres para armazenar o código.
 */
void solicita_code(char *code);

/**
 * @brief Solicita os dados para a query 2 (Top N aeronaves).
 *
 * @param topN Apontador para armazenar valor de Top N.
 * @param manufacturer Apontador para buffer que vai armazenar o fabricante (opcional).
 * @param max_len Tamanho máximo do buffer do fabricante.
 */
void solicita_dados_query2(int *topN, char *manufacturer,size_t max_len);

/**
 * @brief Solicita os dados para a query 3 (datas de início e fim).
 *
 * @param data_inicio Apontador para GDate de início.
 * @param data_fim Apontador para GDate de fim.
 */
void solicita_dados_query3(GDate *data_inicio, GDate *data_fim);

/**
 * @brief Solicita os dados para a query 4 (restrição de datas).
 *
 * @param data_inicio Apontador para apontador de GDate de início.
 * @param data_fim Apontador para apontador de GDate de fim.
 */
void solicita_dados_query4(GDate **data_inicio, GDate **data_fim);

/**
 * @brief Solicita os dados para a query 5 (Top N companhias aéreas).
 *
 * @param topN Apontador para armazenar o valor de Top N.
 */
void solicita_dados_query5(int *topN);

/**
 * @brief Solicita os dados para a query 6 (nacionalidade).
 *
 * @param nationality Apontador para buffer que vai armazenar a nacionalidade.
 * @param max_len Tamanho máximo do buffer.
 */
void solicita_dados_query6(char *nationality,size_t max_len);

/**
 * @brief Mostra resultados da query 2 no modo interativo.
 *
 * @param lista Apontador para lista de aeronaves (GList*).
 * @param topN Valor de Top N.
 */
void output_interativo_query2(GList *lista,int topN);

/**
 * @brief Mostra resultados da query 4 no modo interativo.
 *
 * @param h Apontador para estrutura CountEmTop10.
 * @param gestorPassageiros Apontador para Gestor de passageiros.
 * @param data_inicio Apontador para GDate de início (pode ser NULL).
 * @param data_fim Apontador para GDate de fim (pode ser NULL).
 */
void output_interativo_query4 (CountEmTop10 *h,Passageiros *gestorPassageiros,GDate *data_inicio,GDate *data_fim);

/**
 * @brief Mostra resultados da query 5 no modo interativo.
 *
 * @param lista Apontador para lista de companhias aéreas (GList*).
 * @param topN Valor de Top N.
 */
void output_interativo_query5 (GList *lista,int topN);

/**
 * @brief Mostra os detalhes de um aeroporto no modo interativo.
 *
 * @param airport Apontador para Aeroporto.
 */
void output_interativo_aeroporto(Aeroporto *airport);

/**
 * @brief Mostra o aeroporto mais comum para uma nacionalidade.
 *
 * @param info Apontador para NacionalidadeInfo.
 * @param nationality Apontador para nacionalidade do passageiro.
 */
void output_interativo_nacionalidade(NacionalidadeInfo *info,const char *nationality);

/**
 * @brief Carrega o dataset completo para o GestorGlobal.
 *
 * Mostra barra de progresso no terminal.
 *
 * @param gestor Apontador para o GestorGlobal.
 * @param dir Apontador para diretório do dataset.
 * @return 0 se sucesso, -1 se ESC pressionado.
 */
int carrega_dataset (GestorGlobal *gestor,char *dir);

/**
 * @brief Executa o menu interativo principal.
 *
 * Permite selecionar queries e mostrar resultados.
 *
 * @param gestor Apontador para o GestorGlobal.
 */
void processa_interativo (GestorGlobal *gestor);

/**
 * @brief Termina o modo ncurses e restaura terminal.
 */
void end_ncurses();

/**
 * @brief Mostra menu de queries e permite seleção.
 *
 * @return Número da query selecionada (1-6), -1 se ESC pressionado.
 */
int menu_queries();

#endif