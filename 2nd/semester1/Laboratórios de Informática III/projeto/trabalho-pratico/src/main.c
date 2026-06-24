#include "interpretador.h"
#include "testar.h"
#include "interativo.h"
#include "gestor_global.h"
#include <stdio.h>

int main (int argc, char **argv) {
    struct timespec start_total, end_total;
    clock_gettime(CLOCK_REALTIME, &start_total);

    GestorGlobal *gestor = gestor_create();

    if (argc == 1) 
        processa_interativo (gestor);
    else {
        const char *dir = argv[1];
        const char *queries_fich = argv[2];
        const char *expected_results = (argc == 4) ? argv[3] : NULL;

        gestor_load(dir,gestor);

        if (expected_results != NULL) 
            executar_testes (queries_fich,expected_results,gestor);
        else 
            processa_queries (queries_fich,gestor);
    }

    gestor_free(gestor);
    clock_gettime(CLOCK_REALTIME, &end_total);
    double tempo = diff_time(start_total, end_total);
    printf("TEMPO TOTAL: %.3fs\n", tempo);

    return 0;
}