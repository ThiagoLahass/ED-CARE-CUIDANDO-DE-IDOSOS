#ifndef LISTACUIDADOR_H
#define LISTACUIDADOR_H

#include <stdio.h>
#include <stdlib.h>
#include "cuidador.h"

typedef struct celula Celula;
typedef struct lista_cuidador Lista_cuidador;

Celula* Celula_cuidador_Inicializa ( Cuidador* cuidador );
Lista_cuidador* Lista_cuidador_Inicializa ();
void Lista_cuidador_add_final (Lista_cuidador* lista, Cuidador* cuidador );
void Lista_cuidador_remove ( Lista_cuidador* lista, char* nome );
void Lista_cuidador_destroi ( Lista_cuidador** lista_ref );
void Lista_cuidador_imprime ( const Lista_cuidador* lista );

#endif