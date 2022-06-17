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
    float temperatura;
    int latitude;
    int longitude;
    int queda;
    int falecimento;
};


Idoso* Aloca_idoso ( char* nome ) {
    Idoso* idoso = (Idoso*) calloc (1, sizeof(Idoso) );
    idoso->nome = strdup(nome);
    idoso->lista_amigos = Lista_idoso_Inicializa();
    idoso->lista_cuidadores = Lista_cuidador_Inicializa();
    idoso->temperatura = 0;
    idoso->latitude = 0;
    idoso->longitude = 0;
    idoso->queda = 0;
    idoso->falecimento = 0;

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
    Lista_idoso_destroi( &idoso->lista_amigos );
    Lista_cuidador_destroi( &idoso->lista_cuidadores );

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

Lista_idoso* Retorna_lista_amigos( Idoso* idoso ) {
    return idoso->lista_amigos;
}
Lista_cuidador* Retorna_lista_cuidadores( Idoso* idoso ) {
    return idoso->lista_cuidadores;
}

void Imprime_lista_amigos( Idoso* idoso ) {
    Lista_idoso_imprime(idoso->lista_amigos);
}

void Imprime_lista_cuidadores( Idoso* idoso ) {
    Lista_cuidador_imprime( idoso->lista_cuidadores );
}
//Remove cuidador nao eh necessario pois nao
//existe a possiblidade de um cuidador morrer no contexto dado