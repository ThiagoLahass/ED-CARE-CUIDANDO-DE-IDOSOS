#ifndef LISTAIDOSO_H
#define LISTAIDOSO_H

#include <stdio.h>
#include <stdlib.h>
#include "idoso.h"

typedef struct celula Celula;
typedef struct lista_idoso Lista_idoso;

Celula* Celula_idoso_Inicializa ( Idoso* idoso );
Lista_idoso* Lista_idoso_Inicializa ();
Idoso* Retorna_idoso_pelo_nome( Lista_idoso* lista, char* nome );
void Lista_idoso_add_final (Lista_idoso* lista, Idoso* idoso );
void Lista_idoso_remove ( Lista_idoso* lista, char* nome );
void Lista_idoso_destroi ( Lista_idoso** lista_ref );
void Lista_idoso_imprime ( const Lista_idoso* lista );

#endif