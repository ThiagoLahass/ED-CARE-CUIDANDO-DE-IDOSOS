#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_idoso.h"
#include "idoso.h"

struct celula{
    Idoso* idoso;
    struct celula *prox;
    struct celula *ant;
};

struct lista_idoso{
    Celula* prim;
    Celula* ult;
    int size;
};

Celula* Celula_idoso_Inicializa ( Idoso* idoso ) {

    Celula* celula = (Celula*) calloc(1, sizeof( Celula ));
    celula->idoso = idoso;
    celula->prox = NULL;
    celula->ant = NULL;

    return celula;
}

Lista_idoso* Lista_idoso_Inicializa () {

    Lista_idoso* lista = (Lista_idoso*) calloc(1, sizeof(Lista_idoso));
    lista->prim = NULL;
    lista->ult = NULL;
    lista->size = 0;

    return lista;
}


Idoso* Retorna_idoso_pelo_nome( Lista_idoso* lista, char* nome ) {

    //se a lista NAO estiver vazia
    if( lista->prim != NULL ){
        Celula* p = lista->prim;

        while( p!= NULL && strcmp( Retorna_nome_idoso (p->idoso), nome ) ) {
            p = p->prox;
        }

        // se achou um nó com nome dado
        if( p != NULL ) return p->idoso;

        printf("nao ha um idoso com esse nome\n");
    }
    printf("lista vazia\n");
    return NULL;
}

void Lista_idoso_add_final (Lista_idoso* lista, Idoso* idoso ) {

    Celula* aux = Celula_idoso_Inicializa( idoso );
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

void Lista_idoso_remove ( Lista_idoso* lista, char* nome ) {

    //se a lista NAO estiver vazia
    if( lista->prim != NULL ){
        Celula* p = lista->prim;

        while( p!= NULL && strcmp( Retorna_nome_idoso (p->idoso), nome ) ) {
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

void Lista_idoso_destroi ( Lista_idoso** lista_ref ) {
    
    Lista_idoso* lista = *lista_ref;

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

void Lista_idoso_imprime ( const Lista_idoso* lista ) {
    Celula* p = lista->prim;

    // enquanto p não chegou ao fim da lista, isto é,
    // enquanto p estiver apontando para um nó da lista
    while (p != NULL) {
        Imprime_idoso( p->idoso );
        p = p->prox;
    }
    puts("");

}

int Lista_idoso_num_elementos( const Lista_idoso* lista ) {
    return lista->size;
}

Idoso* Lista_Idoso_Retorna_idoso_pelo_indice( Lista_idoso* lista, int indice ) {

    //se a lista NAO estiver vazia e for um indice valido
    if( lista->prim != NULL && indice < lista->size ){
        Celula* p = lista->prim;

        for( int i = 0; i < indice; i++ ) {
            p = p->prox;
        }

        return p->idoso;

    }
    printf("lista vazia ou indic invalido!\n");
    return NULL;
}
