#include "output.h"
#include <stdarg.h>

GHashTable *output_create() {
    GHashTable *separadores = g_hash_table_new(g_direct_hash,g_direct_equal);

    // se houvesse mais poderia se adicionar
    g_hash_table_insert (separadores, GINT_TO_POINTER('S'), GINT_TO_POINTER('='));
    
    return separadores;
}

char output_get_separador(char id,GHashTable *separadores) {
    gpointer val = g_hash_table_lookup(separadores,GINT_TO_POINTER(id));
    if (val == NULL) return ';'; // default vai ser ';'

    return GPOINTER_TO_INT(val);
}

void output_fields(FILE *out, char sep, int n, ...) {
    if (!out) return;

    va_list args;
    va_start(args, n); // cria uma lista de argumentos variavéis

    for (int i = 0; i < n; i++) {
        char *s = va_arg(args, char *); // extrai o elemento e converte para char *
        fprintf(out, "%s", s);
        if (i < n-1) fprintf(out, "%c", sep);
    }

    fprintf(out, "\n");

    va_end(args);
}

void output_free(GHashTable *separadores) {
    if (separadores != NULL)
        g_hash_table_destroy (separadores);
}
