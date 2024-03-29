#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_cuidador.h"
#include "cuidador.h"

struct celula{
    Cuidador* cuidador;
    struct celula *prox;
    struct celula *ant;
};

struct lista_cuidador {
    Celula* prim;
    Celula* ult;
    int size;
};


Celula* Celula_cuidador_Inicializa ( Cuidador* cuidador ) {

    Celula* celula = (Celula*) calloc(1, sizeof( Celula ));
    celula->cuidador = cuidador;
    celula->prox = NULL;
    celula->ant = NULL;

    return celula;
}

Lista_cuidador* Lista_cuidador_Inicializa () {

    Lista_cuidador* lista = (Lista_cuidador*) calloc(1, sizeof(Lista_cuidador));
    lista->prim = NULL;
    lista->ult = NULL;
    lista->size = 0;

    return lista;
}

void Lista_cuidador_add_final (Lista_cuidador* lista, Cuidador* cuidador ) {

    Celula* aux = Celula_cuidador_Inicializa( cuidador );

    aux->ant = lista->ult;

    //se a lista estiver vazia
    if( lista->prim == NULL ){
        lista->prim = aux;
    }
    else {
        lista->ult->prox = aux;
    }

    lista->ult = aux;
    lista->size++;
}


void Lista_cuidador_remove ( Lista_cuidador* lista, char* nome ) {

    //se a lista NAO estiver vazia
    if( lista->prim != NULL ){
        Celula* p = lista->prim;

        while( p!= NULL && strcmp( Cuidador_retorna_nome(p->cuidador), nome ) ) {
            p = p->prox;
        }

        // se achou um nó com nome dado
        if( p != NULL ) {
            
            //se esta na primeira posicao
            if( lista->prim == p ) {
                lista->prim = p->prox;
                
                //se ha apenas um elemento
                if( lista->ult == p ) {
                    lista->ult = NULL;
                }
                else {
                    lista->prim->ant = NULL;
                }
            }
            // se esta no final
            else if ( lista->ult == p ){
                p->ant->prox = NULL;
                lista->ult = p->ant;
            }
            else {
                p->ant->prox = p->prox;
                p->prox->ant = p->ant;
            }

            free(p);
            lista->size--;
        }
    }
}

void Lista_cuidador_destroi ( Lista_cuidador** lista_ref ) {
    
    Lista_cuidador* lista = *lista_ref;

    Celula* p = lista->prim;
    Celula* aux = NULL;

    while( p != NULL ) {
        aux = p;
        p = p->prox;
        free(aux);
    }

    free(lista);

    *lista_ref = NULL;
}


void Lista_cuidador_imprime ( const Lista_cuidador* lista ) {
    Celula* p = lista->prim;

    // enquanto p não chegou ao fim da lista, isto é,
    // enquanto p estiver apontando para um nó da lista
    while (p != NULL) {
        Cuidador_imprime( p->cuidador );
        p = p->prox;
    }
    puts("");

}

Cuidador* Retorna_cuidador_pelo_nome( Lista_cuidador* lista, char* nome ) {

    //se a lista NAO estiver vazia
    if( lista->prim != NULL ){
        Celula* p = lista->prim;

        while( p!= NULL && strcmp( Cuidador_retorna_nome (p->cuidador), nome ) ) {
            p = p->prox;
        }

        // se achou um nó com nome dado
        if( p != NULL ) return p->cuidador;

        printf("nao ha um cuidador com esse nome\n");
    }
    printf("lista vazia\n");
    return NULL;
}

Cuidador* Lista_cuidador_Retorna_cuidador_pelo_indice( Lista_cuidador* lista, int indice ) {

    //se a lista NAO estiver vazia e for um indice valido
    if( lista->prim != NULL && indice < lista->size ){
        Celula* p = lista->prim;

        for( int i = 0; i < indice; i++ ) {
            p = p->prox;
        }

        return p->cuidador;

    }
    printf("lista vazia ou indice invalido!\n");
    return NULL;
}

int Lista_cuidador_num_elementos( const Lista_cuidador* lista ) {
    return lista->size;
}