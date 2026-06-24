#include "passageiro.h"
#include "utils.h"
#include <glib.h>

struct passageiro {
    char *document_number;
    char* first_name;
    char* last_name;
    char* dob;
    char* nationality;
    //Gender gender;
    //char* email;
    //char* phone;
    //char* address;
    //char* foto;
};

Passageiro* cria_passageiro(const gchar** dados) {
    Passageiro* passageiro = malloc(sizeof(struct passageiro));
    if (!passageiro) return NULL;
    
    passageiro->document_number = strdup(dados[0]);
    passageiro->first_name = strdup(dados[1]);
    passageiro->last_name = strdup(dados[2]);
    passageiro->dob = strdup(dados[3]);
    passageiro->nationality = strdup(dados[4]);

    //if (strcmp(dados[5], "M") == 0) passageiro->gender = M;
    //else if (strcmp(dados[5], "F") == 0) passageiro->gender = F;
    //else passageiro->gender = O;

    //passageiro->email = strdup(dados[6]);
    //passageiro->phone = strdup(dados[7]);
    //passageiro->address = strdup(dados[8]);
    //passageiro->foto = strdup (dados[9]);

    return passageiro;
}

/*
Passageiro* cria_passageiro(gchar** dados) {
    Passageiro* passageiro = malloc(sizeof(struct passageiro));
    if (!passageiro) return NULL;
    
    passageiro->document_number = dados[0]; dados[0] = NULL;
    passageiro->first_name = dados[1]; dados[1] = NULL;
    passageiro->last_name = dados[2]; dados[2] = NULL;
    passageiro->dob = dados[3]; dados[3] = NULL;
    passageiro->nationality = dados[4]; dados[4] = NULL;

    // passageiro->email = (char*)dados[6]; dados[6] = NULL;

    return passageiro;
}
*/

const char *get_passenger_number (const Passageiro *passenger) {
    return passenger->document_number;
}

const char *get_nationality (const Passageiro *passenger) {
    return passenger->nationality;
}

const char *get_first_name (const Passageiro *passenger) {
    return passenger->first_name;
}

const char *get_last_name (const Passageiro *passenger) {
    return passenger->last_name;
}

const char *get_dob (const Passageiro *passenger){
    return passenger->dob;
}


void free_passageiro (void* p) {
    Passageiro* passageiro = p;
    if (!passageiro) return;

    free (passageiro->document_number);
    free (passageiro->first_name);
    free (passageiro->last_name);
    free(passageiro->dob);
    free (passageiro->nationality);
    //free (passageiro->email);
    //free (passageiro->phone);
    //free (passageiro->address);
    //free (passageiro->foto);

    free (passageiro);
}

