#ifndef CUIDADOR_H
#define CUIDADOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct cuidador Cuidador;

Cuidador* Aloca_cuidador ( char* nome );
char*  Retorna_nome_cuidador (Cuidador* cuidador);
void   Imprime_cuidador (Cuidador* cuidador);
void   Desaloca_cuidador (Cuidador* cuidador);

void Cuidador_atualiza_informacoes ( Cuidador* cuidador, int lat, int lon );

int Cuidador_latitude_atual ( Cuidador* cuidador );

int Cuidador_longitude_atual ( Cuidador* cuidador );

#endif