#include "utils.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>

GDateTime *type_string_to_datetime (const char *str) {
    if (strcmp (str,"N/A") == 0) return NULL;
    
    int ano = (str[0]-'0')*1000 + (str[1]-'0')*100 + (str[2]-'0')*10 + (str[3]-'0');
    int mes = (str[5]-'0')*10 + (str[6]-'0');
    int dia = (str[8]-'0')*10 + (str[9]-'0');
    int hora = (str[11]-'0')*10 + (str[12]-'0');
    int min = (str[14]-'0')*10 + (str[15]-'0');

    static GTimeZone *utc = NULL;
    if (!utc) utc = g_time_zone_new_utc();

    return g_date_time_new(utc, ano, mes, dia, hora, min, 0.0);
}

GDate *type_string_to_gdate(const char *str) {
    if (strcmp (str,"N/A") == 0) return NULL;
    
    int ano = (str[0]-'0')*1000 + (str[1]-'0')*100 + (str[2]-'0')*10 + (str[3]-'0');
    int mes = (str[5]-'0')*10 + (str[6]-'0');
    int dia = (str[8]-'0')*10 + (str[9]-'0');

    return g_date_new_dmy(dia, mes, ano);
}

/*
GDateTime *type_string_to_datetime (const char *str) {
    if (strcmp (str,"N/A") == 0) return NULL;
    
    guint ano,mes,dia,hora,minuto;

    if (sscanf (str,"%4u-%2u-%2u %2u:%2u",&ano,&mes,&dia,&hora,&minuto) != 5)
        return NULL;

    static GTimeZone *utc = NULL;
    if (!utc) utc = g_time_zone_new_utc();

    return g_date_time_new(utc, ano, mes, dia, hora, minuto, 0.0);
    
}

GDate *type_string_to_gdate(const char *str) {
    guint ano, mes, dia;

    if (sscanf(str, "%4u-%2u-%2u", &ano, &mes, &dia) != 3)
        return NULL;

    return g_date_new_dmy(dia, mes, ano);
}
*/

GPtrArray *type_string_flight_ids(const char *str) {
    if (!str || str[0] == '\0') return NULL;

    GPtrArray *array = g_ptr_array_new_with_free_func(g_free);

    const char *s = str;

    if (*s == '[') s++;
    const char *end = str + strlen(str);
    if (end > s && end[-1] == ']') end--;

    const char *start = s;
    for (const char *p = s; p <= end; p++) {
        if (p == end || *p == ',') {
            while (*start == ' ' || *start == '\'') start++;

            const char *e = p;
            while (e > start && (e[-1] == ' ' || e[-1] == '\'')) e--;

            if (e > start) {
                g_ptr_array_add(array, g_strndup(start, e - start));
            }
            start = p + 1;
        }
    }

    return array;
}

/*
GPtrArray *type_string_flight_ids(const char *str) {
    if (!str) return NULL;
    GPtrArray *array = g_ptr_array_new_with_free_func(g_free);

    char *s_orig = strdup(str);
    if (!s_orig) {
        g_ptr_array_free(array, TRUE);
        return NULL;
    }

    size_t len = strlen(s_orig);
    char *s = s_orig;
    if (len >= 2 && s[0] == '[' && s[len-1] == ']') {
        s[len-1] = '\0';  
        s++;               
    }

    char *token;
    char *rest = s;

    while ((token = strsep(&rest, ",")) != NULL) {
        while (*token == ' ' || *token == '\'') token++;

        char *end = token + strlen(token) - 1;
        while (end > token && (*end == ' ' || *end == '\'')) {
            *end = '\0';
            end--;
        }

        if (*token) {
            g_ptr_array_add(array, g_strdup(token));
        }
    }

    free(s_orig);  
    return array;
}
*/

GDate *datetime_to_date(GDateTime *dt) {
    if (!dt) return NULL;

    gint y, m, d;
    g_date_time_get_ymd(dt, &y, &m, &d);

    GDate *data = g_date_new_dmy(d, m, y);
    return data;
}

/*
GDate *datetime_to_date(GDateTime *dt) {
    if (!dt) return NULL;

    GDate *data = g_date_new();
    g_date_set_dmy (
        data,
        g_date_time_get_day_of_month (dt),
        g_date_time_get_month (dt),
        g_date_time_get_year (dt)
    );

    return data;
}
*/
