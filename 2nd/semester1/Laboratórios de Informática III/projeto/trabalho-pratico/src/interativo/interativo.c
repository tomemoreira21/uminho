#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include "interativo.h"
#include "gestor_global.h"
#include "aeronaves.h"
#include "aeroportos.h"
#include "passageiros.h"
#include "voos.h"
#include "reservas.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"
#include "query6.h"
#include "utils.h"
#include <ncurses.h>
#include <sys/stat.h>
#include <unistd.h>
#include "limits.h"
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define NUM_QUERIES 6

const char *queries[NUM_QUERIES] = {
    "Query1. Resumo do aeroporto (por código IATA)",
    "Query2. Top N aeronaves com mais voos realizados",
    "Query3. Aeroporto com mais partidas entre duas datas",
    "Query4. Passageiro que mais gastou em viagens durante um período",
    "Query5. Top N companhias aéreas com maior atraso médio por voo",
    "Query6. Aeroporto de destino mais comum por nacionalidade"
};

void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); // permite setas
}

void desenha_init() {
    if (has_colors() == FALSE) {
        endwin();
        printf("Seu terminal não suporta cores.\n");
        return;
    }
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Verde sobre fundo preto

    clear();

    int center_linha = LINES / 2 - 2;
    int center_col = COLS / 2;

    const char *msg = "BEM-VINDO AO SISTEMA DE VOOS";

    // Ativa atributos de cor + negrito (aparência maior)
    attron(COLOR_PAIR(1) | A_BOLD);

    mvprintw(center_linha - 1, center_col - strlen(msg)/2, "%s", msg);

    attroff(COLOR_PAIR(1) | A_BOLD); // desliga atributos

    mvprintw(center_linha + 2, center_col - 20, "Pressione qualquer tecla para continuar...");
    refresh();

    getch();

}

int dataset_existe(const char *dir) {
    struct stat st;
    return (stat(dir, &st) == 0 && S_ISDIR(st.st_mode));
}

void muda_diretoria_raiz() {
    char path[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);

    if (len == -1) return;

    path[len] = '\0';

    // Remove o nome do executável
    char *last_slash = strrchr(path, '/');
    if (last_slash) {
        *last_slash = '\0';
        if (chdir(path) != 0) return;
    }
}

int get_dataset_path(char *path) {
    int dataset_valido = 0;
    char final_path[PATH_MAX];
    char resolved_path[PATH_MAX];

    while (!dataset_valido) {
        clear();
        mvprintw(1, 2, "Introduza o caminho do dataset:");
        mvprintw(2, 2, "Apenas são permitidos ficheiros em formato CSV, PIPE ou TSV");
        mvprintw(3, 2, "> ");
        refresh();

        echo();
        curs_set(1);
        getnstr(path,PATH_MAX - 1);
        noecho();
        curs_set(0);
        
        if (path[0] == '~') {
            const char *home = getenv("HOME");
            if (!home) home = ""; 
            snprintf(final_path, PATH_MAX, "%s%s", home, path + 1);
        } else {
            snprintf(final_path, PATH_MAX, "%s", path);
        }

        // Normalização do caminho: resolve os casos ../ e ./ 
        if (realpath(final_path,resolved_path) == NULL) {
            mvprintw(5, 2, "Diretoria '%s' não existe.", final_path);
            mvprintw(6, 2, "Pressione qualquer tecla para continuar ou ESC para sair.");

            int tecla = getch();
            if (tecla == 27)
                return -1;
            continue;
        }

        if (dataset_existe(final_path)) {
            snprintf(path, PATH_MAX, "%s", final_path);
            dataset_valido = 1;
        } else {
            mvprintw(5, 2, "Diretoria '%s' não existe.", final_path);
            mvprintw(6, 2, "Pressione qualquer tecla para continuar ou ESC para sair.");
            
            int tecla = getch();
            if (tecla == 27) 
                return -1;    
        }
    }

    return 0;
}

int carrega_dataset(GestorGlobal *gestor, char *dir) {
    const char *tipos[] = {
        "Aeronaves",
        "Aeroportos",
        "Passageiros",
        "Voos",
        "Reservas"
    };

    int barra_tamanho = 30;
    int barra_coluna = 25;
    float tempo_total = 0;

    clear();
    mvprintw(1, 2, "A carregar dataset...");
    refresh();
    
    for (int t = 0; t < 5; t++) {
        struct timespec inicio, fim;
        clock_gettime(CLOCK_REALTIME, &inicio);

        int linha = 3 + t;
        
        switch(t) {
            case 0:
                aeronaves_load(dir, get_gestor_Aeronaves(gestor));
                break;
            case 1:
                aeroportos_load(dir, get_gestor_Aeroportos(gestor));
                break;
            case 2:
                passageiros_load(dir, get_gestor_Passageiros(gestor));
                break;
            case 3:
                voos_load(dir, gestor);
                break;
            case 4:
                reservas_load(dir, gestor);
                break;
        }
        
        clock_gettime(CLOCK_REALTIME, &fim);
        double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;
        tempo_total += tempo;

        // Preenche a barra de acordo com o tempo real
        move(linha, barra_coluna);
        mvprintw(linha, 2, "Loading %-15s ", tipos[t]);
        addch('[');

        int steps = barra_tamanho;
        double delay = (tempo * 1000000) / steps;

         for (int i = 0; i < steps; i++) {
            addch('#');
            refresh();
            usleep((int)delay);
        }
        
        addch(']');
        printw(" %.3fs", tempo);
        refresh();
    }

    mvprintw(9, 2, "Dataset carregado com sucesso! Tempo total: %.2fs", tempo_total);
    mvprintw(10, 2, "Pressione qualquer tecla para continuar ou ESC para sair.");
    refresh();

    int tecla = getch();
    if (tecla == 27) 
        return -1;  
    
    return 0;  
}

int menu_queries() {
    int escolha = 0;
    int tecla;

    keypad(stdscr, TRUE); 
    curs_set(0);           

    while (1) {
        clear();
        mvprintw(1, 2, "Selecione a query que deseja executar:");
        mvprintw(2, 2, "(Pressione ESC para sair)");

        for (int i = 0; i < NUM_QUERIES; i++) {
            if (i == escolha)
                attron(A_REVERSE);  // destaca a opção selecionada
            mvprintw(4 + i, 2, "%s", queries[i]);
            if (i == escolha)
                attroff(A_REVERSE);
        }

        refresh();

        tecla = getch();
        switch (tecla) {
            case KEY_UP:
                if (escolha > 0) escolha--;
                break;
            case KEY_DOWN:
                if (escolha < NUM_QUERIES - 1) escolha++;
                break;
            case '\n':
            case KEY_ENTER:
                return escolha + 1; // retorna a query escolhida
            case 27: // ESC
                return -1; // sair
        }
    }
}

void solicita_code(char *code) {
    int valido = 0;

    while (!valido) {
        clear();
        mvprintw(2, 2, "Introduza o código IATA do aeroporto (3 caracteres):");
        mvprintw(3, 2, "> ");
        refresh();

        echo();
        curs_set(1);
        getnstr(code, 3);  // lê no máximo 3 caracteres
        noecho();
        curs_set(0);

        if (strlen(code) == 3) {
            valido = 1; // código válido
        } else {
            mvprintw(5, 2, "Código inválido! Deve ter exatamente 3 caracteres.");
            mvprintw(6, 2, "Pressione qualquer tecla para tentar novamente.");
            refresh();
            getch();
        }
    }
}

void output_interativo_aeroporto(Aeroporto *airport) {
    if (airport == NULL) {
        clear();
        mvprintw(3, 2, "Aeroporto não encontrado!");
        mvprintw(4, 2, "Pressione qualquer tecla para voltar ao menu.");
        refresh();
        getch();
        return;
    }
    
    clear();
    mvprintw(1, 2, "=== Resumo do Aeroporto ===");
    mvprintw(3, 2, "Código: %s", get_airport_code(airport));
    mvprintw(4, 2, "Nome: %s", get_airport_name(airport));
    mvprintw(5, 2, "Cidade: %s", get_airport_city(airport));
    mvprintw(6, 2, "País: %s", get_airport_country(airport));
    mvprintw(7, 2, "Tipo: %s", get_airport_type_string(airport));
    mvprintw(8, 2, "Número de Chegadas: %d", get_airport_arrival_count(airport));
    mvprintw(9, 2, "Número de Partidas: %d", get_airport_departure_count(airport));
    mvprintw(11, 2, "Pressione qualquer tecla para voltar ao menu.");
    refresh();
    getch();
}

void solicita_dados_query2(int *topN, char *manufacturer,size_t max_len) {
    int valido = 0;

    while (!valido) {
        clear();
        mvprintw(2, 2, "Introduza o valor de Top N (número positivo):");
        mvprintw(3, 2, "> ");
        refresh();

        echo();
        curs_set(1);
        char buffer[16];
        getnstr(buffer, 15);
        noecho();
        curs_set(0);

        *topN = atoi(buffer);
        if (*topN > 0)
            valido = 1;
        else {
            mvprintw(5, 2, "Valor inválido! Deve ser um número positivo.");
            mvprintw(6, 2, "Pressione qualquer tecla para tentar novamente.");
            refresh();
            getch();
        }
    }

    valido = 0;
    while (!valido) {
        clear();
        mvprintw(2, 2, "Deseja inserir um fabricante? (S/N):");
        mvprintw(3, 2, "> ");
        refresh();

        echo();
        curs_set(1);
        char resposta[2];
        getnstr(resposta, 1);
        noecho();
        curs_set(0);

        char ch = toupper(resposta[0]);
        if (ch == 'S') {
            valido = 1;

            clear();
            mvprintw(2, 2, "Introduza o nome do fabricante:");
            mvprintw(3, 2, "> ");
            refresh();

            echo();
            curs_set(1);
            getnstr(manufacturer, (int)max_len - 1);
            manufacturer[max_len - 1] = '\0';
            noecho();
            curs_set(0);

        } else if (ch == 'N') {
            valido = 1;
            manufacturer[0] = '\0'; 
        } else {
            mvprintw(5, 2, "Resposta inválida! Digite 'S' ou 'N'.");
            mvprintw(6, 2, "Pressione qualquer tecla para tentar novamente.");
            refresh();
            getch();
        }
    }
}

void output_interativo_query2(GList *lista, int topN) {
    clear();
    keypad(stdscr, TRUE);

    if (lista == NULL) {
        mvprintw(3, 2, "Nenhuma aeronave encontrada.");
        mvprintw(4, 2, "Prima qualquer tecla para voltar.");
        refresh();
        getch();
        return;
    }
    
    int pad_height = 1000;  
    int pad_width  = COLS;

    WINDOW *pad = newpad(pad_height, pad_width);

    int line = 0;
    int i = 1;

    mvwprintw(pad, line++, 2, "=== Top %d Aeronaves com Mais Voos ===", topN);
    line++;

    for (GList *l = lista; l != NULL; l = l->next, i++) {
        Aeronave *a = l->data;

        mvwprintw(pad, line++, 2, "Top %d", i);
        mvwprintw(pad, line++, 4, "Identificador: %s", get_aircraft_identifier(a));
        mvwprintw(pad, line++, 4, "Fabricante:   %s", get_aircraft_manufactor(a));
        mvwprintw(pad, line++, 4, "Modelo:       %s", get_aircraft_model(a));
        mvwprintw(pad, line++, 4, "Nº de Voos:   %d", get_aircraft_flight_count(a));
        line++;
    }

    mvwprintw(pad, line++, 2, "Prima 'q' para voltar");

    int offset = 0;
    int ch;
    
    refresh();
    doupdate();

    prefresh(
        pad,
        offset, 0,
        0, 0,
        LINES - 1, COLS - 1
    );

    while ((ch = getch()) != 'q') {
        if (ch == KEY_DOWN && offset < line - LINES)
            offset++;
        else if (ch == KEY_UP && offset > 0)
            offset--;

        prefresh(
            pad,
            offset, 0,          
            0, 0,               
            LINES - 1, COLS - 1
        );
    }

    delwin(pad);
}

void solicita_dados_query3(GDate *data_inicio, GDate *data_fim) {
    int valido = 0;
    char buffer[16];

    while (!valido) {
        // Ler data de início
        while (1) {
            clear();
            mvprintw(2, 2, "Introduza a data de início (AAAA-MM-DD):");
            mvprintw(3, 2, "> ");
            refresh();

            echo();
            curs_set(1);
            getnstr(buffer, sizeof(buffer) - 1);
            noecho();
            curs_set(0);

            GDate *d = type_string_to_gdate(buffer);
            if (d) {
                g_date_set_day(data_inicio, g_date_get_day(d));
                g_date_set_month(data_inicio, g_date_get_month(d));
                g_date_set_year(data_inicio, g_date_get_year(d));
                g_date_free(d);
                break;
            } else {
                mvprintw(5, 2, "Data inválida! Formato correto: AAAA-MM-DD");
                mvprintw(6, 2, "Prima qualquer tecla para tentar novamente.");
                refresh();
                getch();
            }
        }

        // Ler data de fim
        while (1) {
            clear();
            mvprintw(2, 2, "Introduza a data de fim (AAAA-MM-DD):");
            mvprintw(3, 2, "> ");
            refresh();

            echo();
            curs_set(1);
            getnstr(buffer, sizeof(buffer) - 1);
            noecho();
            curs_set(0);

            GDate *d = type_string_to_gdate(buffer);
            if (d) {
                g_date_set_day(data_fim, g_date_get_day(d));
                g_date_set_month(data_fim, g_date_get_month(d));
                g_date_set_year(data_fim, g_date_get_year(d));
                g_date_free(d);

                if (g_date_compare(data_fim, data_inicio) > 0) {
                    valido = 1; // datas válidas
                    break;
                } else {
                    mvprintw(5, 2, "Erro: a data de fim deve ser posterior à data de início.");
                    mvprintw(6, 2, "Prima qualquer tecla para tentar novamente.");
                    refresh();
                    getch();
                }
            } else {
                mvprintw(5, 2, "Data inválida! Formato correto: AAAA-MM-DD");
                mvprintw(6, 2, "Prima qualquer tecla para tentar novamente.");
                refresh();
                getch();
            }
        }
    }
}

void solicita_dados_query4(GDate **data_inicio, GDate **data_fim) {
    char buffer[16];

    while (1) {
        clear();
        mvprintw(2, 2, "Deseja inserir uma restrição de datas? (S/N):");
        mvprintw(3, 2, "> ");
        refresh();

        echo();
        curs_set(1);
        char resposta[2] = {0};
        getnstr(resposta, 1);
        noecho();
        curs_set(0);

        char ch = toupper(resposta[0]);

        if (ch == 'N') {
            *data_inicio = NULL;
            *data_fim = NULL;
            return;
        }

        if (ch == 'S') {
            if (!*data_inicio) *data_inicio = g_date_new();
            if (!*data_fim) *data_fim = g_date_new();
            break;
        }

        mvprintw(5, 2, "Resposta inválida! Use S ou N.");
        mvprintw(6, 2, "Prima qualquer tecla para tentar novamente.");
        getch();
    }

    // recebe a data inicio
    while (1) {
        clear();
        mvprintw(2, 2, "Introduza a data de início (AAAA-MM-DD):");
        mvprintw(3, 2, "> ");
        refresh();

        echo();
        curs_set(1);
        getnstr(buffer, sizeof(buffer) - 1);
        noecho();
        curs_set(0);

        GDate *d = type_string_to_gdate(buffer);
        if (d) {
            g_date_set_day(*data_inicio, g_date_get_day(d));
            g_date_set_month(*data_inicio, g_date_get_month(d));
            g_date_set_year(*data_inicio, g_date_get_year(d));
            g_date_free(d);
            break;
        }

        mvprintw(5, 2, "Data inválida! Formato correto: AAAA-MM-DD");
        mvprintw(6, 2, "Prima qualquer tecla para tentar novamente.");
        getch();
    }

    // recebe a data final
    while (1) {
        clear();
        mvprintw(2, 2, "Introduza a data de fim (AAAA-MM-DD):");
        mvprintw(3, 2, "> ");
        refresh();

        echo();
        curs_set(1);
        getnstr(buffer, sizeof(buffer) - 1);
        noecho();
        curs_set(0);

        GDate *d = type_string_to_gdate(buffer);
        if (d) {
            g_date_set_day(*data_fim, g_date_get_day(d));
            g_date_set_month(*data_fim, g_date_get_month(d));
            g_date_set_year(*data_fim, g_date_get_year(d));
            g_date_free(d);

            if (g_date_compare(*data_fim, *data_inicio) > 0)
                break;

            mvprintw(5, 2, "Erro: a data de fim deve ser posterior à data de início.");
            mvprintw(6, 2, "Prima qualquer tecla para tentar novamente.");
            getch();
        } else {
            mvprintw(5, 2, "Data inválida! Formato correto: AAAA-MM-DD");
            mvprintw(6, 2, "Prima qualquer tecla para tentar novamente.");
            getch();
        }
    }
}

void solicita_dados_query6(char *nationality,size_t max_len) {
    clear();
    mvprintw(2, 2, "Introduza a nacionalidade:");
    mvprintw(3, 2, "> ");
    refresh();

    echo();
    curs_set(1);
    getnstr(nationality, (int)max_len - 1);
    nationality[max_len - 1] = '\0';
    noecho();
    curs_set(0);
}

void output_interativo_nacionalidade(NacionalidadeInfo *info,const char *nationality) {
    if (info == NULL) {
        clear();
        mvprintw(3, 2, "Não existem dados disponíveis para a nacionalidade inserida.");
        mvprintw(4, 2, "Pressione qualquer tecla para voltar ao menu.");
        refresh();
        getch();
        return;
    }
    
    int best_count = get_nacionalidade_best_count(info);
    const char *code = get_nacionalidade_best_iata(info);;

    clear();
    mvprintw(1, 2, "=== Aeroporto mais comum para passageiros de nacionalidade %s ===",nationality);
    mvprintw(3, 2, "Código do Aeroporto: %s", code);
    mvprintw(4, 2, "Número de Partidas: %d", best_count);
    mvprintw(6, 2, "Pressione qualquer tecla para voltar ao menu.");
    refresh();
    getch();
}

void solicita_dados_query5(int *topN) {
    int valido = 0;

    while (!valido) {
        clear();
        mvprintw(2, 2, "Introduza o valor de Top N (número positivo):");
        mvprintw(3, 2, "> ");
        refresh();

        echo();
        curs_set(1);
        char buffer[16];
        getnstr(buffer, 15);
        noecho();
        curs_set(0);

        *topN = atoi(buffer);
        if (*topN > 0)
            valido = 1;
        else {
            mvprintw(5, 2, "Valor inválido! Deve ser um número positivo.");
            mvprintw(6, 2, "Pressione qualquer tecla para tentar novamente.");
            refresh();
            getch();
        }
    }
}

void output_interativo_query4 (CountEmTop10 *h,Passageiros *gestorPassageiros,GDate *data_inicio,GDate *data_fim) {
    if (h == NULL) {
        clear();
        mvprintw(3, 2, "Não existe nenhum aeroporto que ficou no top10.");
        mvprintw(4, 2, "Pressione qualquer tecla para voltar ao menu.");
        refresh();
        getch();
        return;
    }
    
    const char *melhor = get_ctGlobal_melhor(h);
    Passageiro *p = passageiros_get(gestorPassageiros,melhor);
    int count = get_ctGlobal_count(h);

    clear();
    if (!data_inicio && !data_fim) {
        mvprintw(1, 2, "=== Passageiro que este mais tempo no top10 dos passageiros que mais gastaram em viagens ===");
        mvprintw(3, 2, "ID do Passageiro: %s", melhor);
        mvprintw(4, 2, "Nome: %s %s",get_first_name(p),get_last_name(p));
        mvprintw(5, 2, "Data de Nascimento: %s",get_dob(p));
        mvprintw(6, 2, "Nacionalidade: %s",get_nationality(p));
        mvprintw(7, 2, "Número de vezes no Top10: %d", count);
        mvprintw(9, 2, "Pressione qualquer tecla para voltar ao menu.");
    } else { 
        char buffer_inicio[11];
        char buffer_fim[11];

        g_date_strftime(buffer_inicio,sizeof(buffer_inicio),"%Y-%m-%d",data_inicio);
        g_date_strftime(buffer_fim,sizeof(buffer_fim),"%Y-%m-%d",data_fim);

        mvprintw(1, 2, "=== Passageiro que esteve mais tempo no top10 dos passageiros que mais gastaram em viagens ===");
        mvprintw(2, 2, "No intervalo de datas: [%s,%s]",buffer_inicio,buffer_fim);
        mvprintw(4, 2, "ID do Passageiro: %s", melhor);
        mvprintw(5, 2, "Nome: %s %s",get_first_name(p),get_last_name(p));
        mvprintw(6, 2, "Data de Nascimento: %s",get_dob(p));
        mvprintw(7, 2, "Nacionalidade: %s",get_nationality(p));
        mvprintw(8, 2, "Número de vezes no Top10: %d", count);
        mvprintw(10, 2, "Pressione qualquer tecla para voltar ao menu.");
    }
    
    refresh();
    getch();
}


void output_interativo_query5 (GList *lista,int topN) {
    clear();
    keypad(stdscr, TRUE);
    
    int pad_height = 1000;  
    int pad_width  = COLS;

    WINDOW *pad = newpad(pad_height, pad_width);

    int line = 0;
    int i = 1;

    mvwprintw(pad, line++, 2, "=== Top %d Companhias Aéreas com Mais Tempo de Atraso por Voo ===", topN);
    line++;

    for (GList *l = lista; l != NULL; l = l->next, i++) {
        AirlineStat *a = l->data;

        mvwprintw(pad, line++, 2, "Top %d", i);
        mvwprintw(pad, line++, 4, "Aeronave: %s", get_airline_name (a));
        mvwprintw(pad, line++, 4, "Nº de Voos: %d", get_airline_flights(a));
        mvwprintw(pad, line++, 4, "Tempo Médio de Atraso Por Voo: %.3f min", get_airline_avg_delay(a));
        line++;
    }

    mvwprintw(pad, line++, 2, "Prima 'q' para voltar");

    int offset = 0;
    int ch;
    
    refresh();
    doupdate();

    prefresh(
        pad,
        offset, 0,
        0, 0,
        LINES - 1, COLS - 1
    );

    while ((ch = getch()) != 'q') {
        if (ch == KEY_DOWN && offset < line - LINES)
            offset++;
        else if (ch == KEY_UP && offset > 0)
            offset--;

        prefresh(
            pad,
            offset, 0,          
            0, 0,               
            LINES - 1, COLS - 1
        );
    }

    delwin(pad);
}

void processa_interativo (GestorGlobal *gestor) {
    init_ncurses();
    desenha_init();
    muda_diretoria_raiz();

    char dir[PATH_MAX];
    if (get_dataset_path(dir) == -1) {
        end_ncurses();
        return;
    }

    if (carrega_dataset(gestor,dir) == -1) {
        end_ncurses();
        return;
    }
    
    queries_prepare(gestor);
    int terminou = 0;

    while (!terminou) {
        int query_escolhida = menu_queries();
        switch (query_escolhida) {
            case 1:
                char code[4] = {0};
                solicita_code(code);
                query1_listar_aeroporto(code,'\0',NULL,get_gestor_Aeroportos(gestor));
                break;
            case 2:
                int topN = 0;
                char manufacturer[64];
                solicita_dados_query2(&topN, manufacturer,sizeof (manufacturer));
                query2_listar_aeronaves_mais_voos(topN,(manufacturer[0] != '\0') ? manufacturer : NULL,'\0',NULL, get_gestor_Aeronaves(gestor));
                break;
            case 3:
                GDate data_inicio;
                GDate data_fim;
                g_date_clear(&data_inicio,1);
                g_date_clear(&data_fim,1);

                solicita_dados_query3(&data_inicio,&data_fim);
                query3_aeroporto_mais_partidas(&data_inicio,&data_fim,'\0',NULL,get_gestor_Aeroportos(gestor),get_btree_query3(get_gestor_Queries(gestor)));
                break;
            case 4:
                GDate *data_inicio_1 = NULL;
                GDate *data_fim_1 = NULL;

                solicita_dados_query4(&data_inicio_1,&data_fim_1);
                query4_passageiro_mais_vezes_top10(data_inicio_1,data_fim_1,'\0',NULL,get_gestor_Passageiros(gestor),get_hashtable_query4(get_gestor_Queries(gestor)));                
                break;
            case 5:
                int N = 0;
                solicita_dados_query5(&N);
                query5_listar_companhias_mais_atrasos(N,'\0',NULL,get_array_query5(get_gestor_Queries(gestor)));
                break;
            case 6:
                char nationality[128];
                solicita_dados_query6(nationality,sizeof(nationality));
                query6_aeroporto_destino(nationality,'\0',NULL,get_hashtable_query6(get_gestor_Queries(gestor)));
                break;
            case -1: // ESC
                terminou = 1;
                break;
            default:
                break;
        }
    }


    end_ncurses();



}

void end_ncurses() {
    endwin();
    curs_set(1);
};