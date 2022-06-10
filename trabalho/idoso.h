#ifndef IDOSO_H
#define IDOSO_H

#include <stdio.h>
#include <stdlib.h>
#include "cuidador.h"

typedef struct idoso Idoso;

Idoso* Aloca_idoso ( char* nome );
char*  Retorna_nome_idoso (Idoso* idoso);
void   Imprime_idoso (Idoso* idoso);
void   Desaloca_idoso (Idoso* idoso);

void Adiciona_amigo ( Idoso* idoso, Idoso* novo_amigo);
void Remove_amigo ( Idoso* idoso1, Idoso* idoso2 );

void Adiciona_cuidador( Idoso* idoso, Cuidador* cuidador );

void Imprime_lista_amigos( Idoso* idoso );

#endif