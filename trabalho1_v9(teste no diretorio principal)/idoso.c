#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "idoso.h"
#include "lista_idoso.h"

struct idoso{
	char*           nome; 
    Lista_idoso*    lista_amigos;
    Lista_cuidador* lista_cuidadores;
    float temperatura;
    int latitude;
    int longitude;
    int queda;
    int falecimento;
    int sequencia_febre_baixa;
};

static double Calcula_distancia( float x1, float y1, float x2, float y2 );

Idoso* Idoso_aloca ( char* nome ) {
    Idoso* idoso = (Idoso*) calloc (1, sizeof(Idoso) );
    idoso->nome = strdup(nome);
    idoso->lista_amigos = Lista_idoso_Inicializa();
    idoso->lista_cuidadores = Lista_cuidador_Inicializa();
    idoso->temperatura = 0;
    idoso->latitude = 0;
    idoso->longitude = 0;
    idoso->queda = 0;
    idoso->falecimento = 0;
    idoso->sequencia_febre_baixa = 0;

    return idoso;
}

char*  Idoso_retorna_nome (Idoso* idoso) {
    return idoso->nome;
}

void   Idoso_imprime (Idoso* idoso){
    printf("Nome: %s\n", idoso->nome );
}

void   Idoso_desaloca (Idoso* idoso) {
    free(idoso->nome);
    Lista_idoso_destroi( &(idoso->lista_amigos) );
    Lista_cuidador_destroi( &(idoso->lista_cuidadores));
    free(idoso);
}

void Idoso_adiciona_amigo ( Idoso* idoso, Idoso* novo_amigo) {
    Lista_idoso_add_final(idoso->lista_amigos, novo_amigo);
    Lista_idoso_add_final(novo_amigo->lista_amigos, idoso);
}

void Idoso_adiciona_cuidador( Idoso* idoso, Cuidador* cuidador ) {
    Lista_cuidador_add_final( idoso->lista_cuidadores, cuidador );
}

void Imprime_lista_amigos( Idoso* idoso ) {
    Lista_idoso_imprime(idoso->lista_amigos);
}

void Imprime_lista_cuidadores( Idoso* idoso ) {
    Lista_cuidador_imprime( idoso->lista_cuidadores );
}

//Remove cuidador nao eh necessario pois nao
//existe a possiblidade de um cuidador morrer no contexto dado

int Idoso_eh_falecido( Idoso* idoso ){
    return idoso->falecimento;
}

void Idoso_faleceu( Idoso* idoso ){
    idoso->falecimento = 1;

    int num_amigos = 0, i = 0;
    num_amigos = Lista_idoso_num_elementos( idoso->lista_amigos );
    Idoso* amigo;

    for( i = 0; i < num_amigos; i++ ){
        amigo = Lista_Idoso_Retorna_idoso_pelo_indice( idoso->lista_amigos, 0 );   
        Lista_idoso_remove( idoso->lista_amigos, Idoso_retorna_nome( amigo ));
        Lista_idoso_remove( amigo->lista_amigos, Idoso_retorna_nome( idoso ));
    } 
}

void Idoso_atualiza_informacoes( Idoso* idoso, float temp, int lat, int lon, int queda ) {
    idoso->temperatura  = temp;
    idoso->latitude     = lat;
    idoso->longitude    = lon;
    idoso->queda        = queda;

    if( queda == 0 ){ 
        if( temp >= 37 && temp < 38 ) {
            idoso->sequencia_febre_baixa++;
        }
        else if( temp >= 38 ) {
            idoso->sequencia_febre_baixa = 0;
        }
    }
}

Lista_cuidador* Idoso_retorna_lista_cuidadores( Idoso* idoso ){
    return idoso->lista_cuidadores;
}

float Idoso_temperatura_atual ( Idoso* idoso ){
    return idoso->temperatura;
}

int Idoso_latitude_atual ( Idoso* idoso ){
    return idoso->latitude;
}

int Idoso_longitude_atual ( Idoso* idoso ){
    return idoso->longitude;
}

int Idoso_sofreu_queda( Idoso* idoso ){
    return idoso->queda;
}

int Idoso_sequencia_de_febres_baixas( Idoso* idoso ){
    return idoso->sequencia_febre_baixa;
}

int Idoso_com_febre_alta( Idoso* idoso ) {
    return ( idoso->temperatura >= 38 );
}

int Idoso_com_febre_baixa( Idoso* idoso ) {
    return ( idoso->temperatura >= 37 && idoso->temperatura < 38 );
}

int Idoso_com_sequencia_4_febres_baixas( Idoso* idoso ) {
    return (idoso->sequencia_febre_baixa == 4);
}

void Idoso_reseta_sequncia_febres_baixas( Idoso* idoso ) {
    idoso->sequencia_febre_baixa = 0;
}

Cuidador* Idoso_retorna_cuidador_mais_proximo( Idoso* idoso ){
    int num_cuidadores = 0, i = 0;
    double distancia_atual = 0, menor_distancia = 1000000000000000;
    num_cuidadores = Lista_cuidador_num_elementos( idoso->lista_cuidadores );
    Cuidador* cuidador_atual, *cuidador_mais_proximo;

    for( i = 0; i < num_cuidadores; i++ ){
        cuidador_atual = 
        Lista_cuidador_Retorna_cuidador_pelo_indice( Idoso_retorna_lista_cuidadores( idoso ), i);

        distancia_atual = 
        Calcula_distancia   (   Idoso_latitude_atual( idoso ), 
                                Idoso_longitude_atual( idoso ),
                                Cuidador_latitude_atual(cuidador_atual), 
                                Cuidador_longitude_atual(cuidador_atual)
                            );
        
        if( distancia_atual < menor_distancia ){
            menor_distancia = distancia_atual;
            cuidador_mais_proximo = cuidador_atual;
        }
    }

    return cuidador_mais_proximo;
}

Idoso* Idoso_retorna_amigo_mais_proximo( Idoso* idoso ){
    int num_amigos = 0, i = 0;
    double distancia_atual = 0, menor_distancia = 1000000000000000;
    num_amigos = Lista_idoso_num_elementos( idoso->lista_amigos );
    Idoso* amigo_atual, *amigo_mais_proximo;

    for( i = 0; i < num_amigos; i++ ){
        amigo_atual = Lista_Idoso_Retorna_idoso_pelo_indice( idoso->lista_amigos, i );

        distancia_atual = 
        Calcula_distancia   (   Idoso_latitude_atual( idoso ), 
                                Idoso_longitude_atual( idoso ),
                                Idoso_latitude_atual(amigo_atual), 
                                Idoso_longitude_atual(amigo_atual)
                            );
        
        if( distancia_atual < menor_distancia ){
            menor_distancia = distancia_atual;
            amigo_mais_proximo = amigo_atual;
        }
    }

    return amigo_mais_proximo;
}

int Idoso_tem_amigos( Idoso* idoso ) {
    return ( Lista_idoso_num_elementos( idoso->lista_amigos ) > 0 );
}

static double Calcula_distancia( float x1, float y1, float x2, float y2 ){
    return sqrt( pow((x2-x1),2) + pow((y2-y1),2) );
}