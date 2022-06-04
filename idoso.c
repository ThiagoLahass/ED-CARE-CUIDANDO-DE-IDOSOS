#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "idoso.h"
#include "lista_idoso.h"
#include "cuidador.h"
#include "lista_cuidador.h"

struct idoso{
	char*           nome; 
    Lista_idoso*    lista_amigos;
    Lista_cuidador* lista_cuidadores;
};


Idoso* Aloca_idoso ( char* nome ) {
    Idoso* idoso = (Idoso*) calloc (1, sizeof(Idoso) );
    idoso->nome = strdup(nome);

    return idoso;
}

char*  Retorna_nome_idoso (Idoso* idoso) {
    return idoso->nome;
}

void   Imprime_idoso (Idoso* idoso){
    printf("Nome: %s\n", idoso->nome );
}

void   Desaloca_idoso (Idoso* idoso) {
    free(idoso->nome);

    free(idoso);
}

void Adiciona_amigo ( Idoso* idoso, Idoso* novo_amigo) {
    Lista_idoso_add_final(idoso->lista_amigos, novo_amigo);
    Lista_idoso_add_final(novo_amigo->lista_amigos, idoso);
}

void Remove_amigo ( Idoso* idoso1, Idoso* idoso2 ) {
    Lista_idoso_remove( idoso1->lista_amigos, Retorna_nome_idoso( idoso2 ));
    Lista_idoso_remove( idoso2->lista_amigos, Retorna_nome_idoso( idoso1 ));
}

void Adiciona_cuidador( Idoso* idoso, Cuidador* cuidador ) {
    Lista_cuidador_add_final( idoso->lista_cuidadores, cuidador );
}

//Remove cuidador nao eh necessario pois nao
//existe a possiblidade de um cuidador morrer no contexto dado