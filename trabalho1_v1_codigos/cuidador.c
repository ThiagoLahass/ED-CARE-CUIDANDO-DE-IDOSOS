#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cuidador.h"
#include "lista_cuidador.h"

struct cuidador{
	char* nome;
    float latitude;
    float longitude;
};

Cuidador* Aloca_cuidador ( char* nome ) {
    Cuidador* cuidador = (Cuidador*) calloc (1, sizeof(Cuidador) );
    cuidador->nome = strdup(nome);

    return cuidador;
}

char*  Retorna_nome_cuidador (Cuidador* cuidador) {
    return cuidador->nome;
}

void   Imprime_cuidador (Cuidador* cuidador) {
    printf("Nome: %s\n", cuidador->nome );
}

void   Desaloca_cuidador (Cuidador* cuidador) {
    free(cuidador->nome);
    free(cuidador);
}

void Cuidador_atualiza_informacoes ( Cuidador* cuidador, int lat, int lon ) {
    cuidador->latitude = lat;
    cuidador->longitude = lon;
}

int Cuidador_latitude_atual ( Cuidador* cuidador ){
    return cuidador->latitude;
}

int Cuidador_longitude_atual ( Cuidador* cuidador ){
    return cuidador->longitude;
}