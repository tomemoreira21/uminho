#include "validacao_sintatica_dados.h"
#include <glib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


// Validação sintática da leitura aeronaves
int validacao_sintatica_aeronave (const gchar** dados) {
    return valida_ano(dados[3]) == 0 ? 0 : 1;
}

// Validação sintática da leitura aeroportos
int validacao_sintatica_aeroporto (const gchar** dados) {
    return valida_code_aeroporto(dados[0]) == 0 && valida_latitude(dados[4]) == 0 &&
            valida_longitude(dados[5]) == 0 && valida_type_aeroporto(dados[7]) == 0 ? 0 : 1;
}

// Validação sintática da leitura de passageiros
int validacao_sintatica_passageiro (const gchar** dados) {
    return valida_nr_documento(dados[0]) == 0 && valida_data(dados[3]) == 0 && 
           valida_genero(dados[5]) == 0 && valida_email(dados[6]) == 0 ? 0 : 1;
}

// Validação sintática da leitura de reservas
int validacao_sintatica_reserva (const gchar** dados) {
    return valida_id_reserva(dados[0]) == 0 && valida_listas_CSV(dados[1]) == 0 &&
           valida_lista_ids(dados[1]) == 0 && 
           valida_nr_documento(dados[2]) == 0 ? 0 : 1;                
}

// Validação sinstática da leitura de voos
int validacao_sintatica_voo (const gchar** dados) {
    return valida_id_voo(dados[0]) == 0 && 
           valida_data_hora(dados[1]) == 0 &&
           valida_data_hora(dados[2]) == 0 && valida_data_hora(dados[3]) == 0 &&
           valida_data_hora(dados[4]) == 0 && valida_code_aeroporto(dados[7]) == 0 &&
           valida_code_aeroporto(dados[8]) == 0 ? 0 : 1;
}

/*
Casos de Devolução:
    0 -> a data é válida
    1 -> formato inválido
    2 -> a data é posterior a 2025/09/30
    3 -> a data é inválida
*/
int valida_data (const char *data_str) {
    if (strlen (data_str) != 10 || data_str[4] != '-' || data_str[7] != '-')
        return 1;
        
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit((unsigned char)data_str[i]))
            return 1;
    }

    int ano = (data_str[0]-'0')*1000 + (data_str[1]-'0')*100 + (data_str[2]-'0')*10 + (data_str[3]-'0');
    int mes = (data_str[5]-'0')*10 + (data_str[6]-'0');
    int dia = (data_str[8]-'0')*10 + (data_str[9]-'0');

    if (!g_date_valid_dmy (dia,mes,ano)) 
        return 3; 
    
    int data_as_int = (ano * 10000) + (mes * 100) + dia;
    int reference_as_int = 20250930;                  

    if (data_as_int > reference_as_int) {
        return 2; 
    }

    return 0;
}

/*
int valida_data (const char *data_str) {
    if (strlen (data_str) != 10 || data_str[4] != '-' || data_str[7] != '-')
        return 1; 

    guint ano,mes,dia;
    int lidos = sscanf (data_str,"%4u-%2u-%2u",&ano,&mes,&dia);
    if (lidos != 3)
        return 1;

    if (!g_date_valid_dmy (dia,mes,ano)) 
        return 3; 
    
    GDate *data = g_date_new_dmy (dia,mes,ano);
    GDate *reference = g_date_new_dmy (30,9,2025);

    if (g_date_compare (data,reference) > 0) {
        g_date_free (reference);
        g_date_free (data);
        return 2; 
    }

    g_date_free (reference);
    g_date_free (data);
    return 0;
}
*/

/*
Casos de Devolução:
    0 -> a data e hora é válida
    1 -> formato inválido
    2 -> a data ou hora é inválida
*/
int valida_data_hora (const char *datetime_str) {
    if (strcmp (datetime_str,"N/A") == 0) return 0;

    if (strlen (datetime_str) != 16 || datetime_str [10] != ' ' || datetime_str[13] != ':')
        return 1;

    char data_part[11];
    strncpy (data_part,datetime_str,10);
    data_part[10] = '\0';

    int res = valida_data (data_part);
    if (res != 0) return res;

    if (!isdigit((unsigned char)datetime_str[11]) || !isdigit((unsigned char)datetime_str[12]) ||
        !isdigit((unsigned char)datetime_str[14]) || !isdigit((unsigned char)datetime_str[15]))
        return 1;

    int hora = (datetime_str[11]-'0')*10 + (datetime_str[12]-'0');
    int minuto = (datetime_str[14]-'0')*10 + (datetime_str[15]-'0');

    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) 
        return 2;

    return 0;
}

/*
int valida_data_hora (const char *datetime_str) {
    if (strcmp (datetime_str,"N/A") == 0) return 0;

    char data_part[11];
    strncpy (data_part,datetime_str,10);
    data_part[10] = '\0';

    int res = valida_data (data_part);
    if (res != 0) return res;

    if (strlen (datetime_str) != 16 || datetime_str [10] != ' ' || datetime_str[13] != ':')
        return 1;

    int hora, minuto;
    int lidos = sscanf (datetime_str + 11,"%2u:%2u",&hora,&minuto);
    if (lidos != 2)
        return 1;

    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) 
        return 2;

    return 0;
}
*/

/*
Casos de Devolução:
    0 -> ano válido
    1 -> formato inválido
    2 -> ano inválido
*/
int valida_ano (const char *ano_str) {
    if (strlen (ano_str) != 4)
        return 1;

    for (int i = 0; i < 4; i++) {
        if (!isdigit((unsigned char)ano_str[i]))
            return 1;
    }

    int ano = atoi (ano_str);
    if (ano > 2025) 
        return 2;

    return 0;
}

// Validação de Email
/*
Casos de Devolução:
    0 -> email válido
    1 → formato inválido
    2 → username inválido
    3 → lstring inválida
    4 → rstring inválida
*/
int valida_email (const char *email_str) {
    if (!email_str || strlen (email_str) == 0)
        return 1;
    
    const char *rest = strchr(email_str,'@');
    if (!rest || rest == email_str)
        return 1;
    
    // Valida o username
    for (const char *p = email_str; p < rest; p++) {
        if (!(islower ((unsigned char)*p) || isdigit ((unsigned char)*p) || *p == '.'))
            return 2;
    }

    // Valida o domínio
    const char *dominio = rest + 1;
    if (strlen (dominio) < 4) 
        return 1;
    
    const char *dot = strrchr(dominio, '.');
    if (!dot || dot == dominio || *(dot + 1) == '\0')
        return 1;

    // Valida lstring
    for (const char *p = dominio; p < dot; p++) {
        if (!islower ((unsigned char)*p))
            return 3;
    }

    int rlen = strlen (dot + 1);
    if (rlen < 2 || rlen > 3) 
        return 1;
    
    // Valida rstring
    for (const char *p = dot + 1; *p != '\0'; p++) {
        if (!islower ((unsigned char)*p))
            return 4;
    }

    return 0;
}

// Validação do tipo Aeroporto
/*
Casos de Devolução:
    0 -> type válido
    1 -> type inválido
*/
int valida_type_aeroporto (const char *type) {
    if (strcmp (type,"small_airport") == 0 || 
        strcmp (type,"medium_airport") == 0 ||
        strcmp (type,"large_airport") == 0 || 
        strcmp (type,"heliport") == 0 || 
        strcmp (type,"seaplane_base") == 0)
        return 0;

    return 1;
}

// Validação Latitude/Longitude
int valida_latitude (const char *latitude_str) {
    return valida_formato (latitude_str,-90,90);
}

int valida_longitude (const char *longitude_str) {
    return valida_formato (longitude_str,-180,180);
}

/*
Casos de Devolução:
    0 -> formato válido
    1 -> formato inválido
    2 -> fora do intervalo permitido
*/
int valida_formato (const char *coord_str,int min,int max) {
    if (!coord_str || strlen (coord_str) == 0)
        return 1;

    const char *p = coord_str;
    if (*p == '-') p++;

    if (!isdigit ((unsigned char)*p))
        return 1;

    while (*p != '\0' && *p != '.') {
        if (!isdigit ((unsigned char)*p)) 
            return 1;
        p++;
    }

    if (*p != '.') 
        return 1;

    p++;

    int dec_count = 0;
    while (*p != '\0') {
        if (!isdigit((unsigned char)*p))
            return 1; 
        dec_count++;
        p++;
    }

    if (dec_count == 0 || dec_count > 8)
        return 1; 

    double val = atof (coord_str);
    if (val < min || val > max) 
        return 2;

    return 0; 
}

// Validação código aeroporto
/*
Casos de Devolução:
    0 -> código válido
    1 -> código inválido
*/
int valida_code_aeroporto (const char *code_str) {
    if (!code_str || strlen (code_str) != 3) 
        return 1;

    for (int i = 0; i < 3; i++) {
        if (!isupper ((unsigned char)code_str[i])) 
            return 1;
    }

    return 0;
}

// Validação interna de cada id voo pertence à lista
/*
Casos de Devolução:
    0 -> se todos os id são válidos
    1 -> caso contrário
*/
int valida_lista_ids(const char *str) {
    if (!str) return 1;

    char *s = strdup(str);
    if (!s) return 1;

    size_t len = strlen(s);
    if (len < 2) {
        free(s);
        return 1;
    }

    char *start = strchr(s, '[');
    char *end = strrchr(s, ']');

    if (!start || !end || end <= start) {
        free(s);
        return 1;
    }

    *end = '\0';  
    start++;     

    char *rest = start;
    char *token;

    while ((token = strsep(&rest, ",")) != NULL) {
        
        while (*token == ' ' || *token == '\'')
            token++;

        char *t_end = token + strlen(token) - 1;
        while (t_end > token && (*t_end == ' ' || *t_end == '\'')) {
            *t_end = '\0';
            t_end--;
        }

        if (*token != '\0' && valida_id_voo(token) != 0) {
            free (s);
            return 1;
        }
    }

    free(s);
    return 0;
}

// Validação identificador voo
/*
Casos de Devolução:
    0 -> id válido
    1 -> id inválido
*/
int valida_id_voo (const char *id_str) {
    if (!id_str)
        return 1;
    
    size_t len = strlen (id_str);
    if (len != 7 && len != 8)   
        return 1;
    
    for (int i = 0; i < 2; i++) {
        if (!isupper ((unsigned char)id_str[i])) 
            return 1;
    
    }

    for (size_t i = 2; i < len; i++) {
        if (!isdigit ((unsigned char)id_str[i])) 
            return 1;
        
    }

    return 0;
}

// Validação identificador reserva
/*
Casos de Devolução:
    0 -> id válido
    1 -> id inválido
*/
int valida_id_reserva (const char *id_str) {
    if (!id_str || strlen (id_str) != 10)
        return 1;

    if (id_str[0] != 'R')
        return 1;

    for (int i = 1; i < 10; i++) {
        if (!isdigit((unsigned char)id_str[i]))
            return 1;
    }

    return 0;
}

// Validação do número de documento
/*
Casos de Devolução:
    0 -> número de documento válido
    1 -> número de documento inválido
*/
int valida_nr_documento (const char *nr_documento_str) {
    if (!nr_documento_str || strlen (nr_documento_str) != 9)
        return 1;

    for (int i = 0; i < 9; i++) {
        if (!isdigit ((unsigned char)nr_documento_str[i]))
            return 1;
    }

    return 0;
}

// Validação género passageiro
/*
Casos de Devolução:
    0 -> género válido
    1 -> género inválido
*/
int valida_genero (const char *genero_str) {
    if (strcmp (genero_str,"M") == 0 ||
        strcmp (genero_str,"F") == 0 || 
        strcmp (genero_str,"O") == 0)
        return 0;

    return 1;
}

// Validacao Listas CSVs
/*
Casos de Devolução:
    0 -> lista válida
    1 -> lista inválida
*/
int valida_listas_CSV (const char *list_str) {
    if (!list_str)
        return 1;

    size_t len = strlen (list_str);
    if (len < 2 || list_str[0] != '[' || list_str[len - 1] != ']')
        return 1;

    return 0;
}


