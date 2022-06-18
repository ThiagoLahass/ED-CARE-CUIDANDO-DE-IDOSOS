#ifndef IDOSO_H
#define IDOSO_H

#include <stdio.h>
#include <stdlib.h>
#include "cuidador.h"
#include "lista_cuidador.h"

typedef struct idoso Idoso;

Idoso* Aloca_idoso ( char* nome );
char*  Retorna_nome_idoso (Idoso* idoso);
void   Imprime_idoso (Idoso* idoso);
void   Desaloca_idoso (Idoso* idoso);

void Adiciona_amigo ( Idoso* idoso, Idoso* novo_amigo);
void Remove_amigo ( Idoso* idoso1, Idoso* idoso2 );

void Adiciona_cuidador( Idoso* idoso, Cuidador* cuidador );

void Imprime_lista_amigos( Idoso* idoso );
void Imprime_lista_cuidadores( Idoso* idoso );

int Idoso_eh_falecido( Idoso* idoso );
void Idoso_faleceu( Idoso* idoso );

void Idoso_atualiza_informacoes( Idoso* idoso, float temp, int lat, int lon, int queda );

Lista_cuidador* Idoso_retorna_lista_cuidadores( Idoso* idoso );

float Idoso_temperatura_atual ( Idoso* idoso );

int Idoso_latitude_atual ( Idoso* idoso );

int Idoso_longitude_atual ( Idoso* idoso );

int Idoso_sofreu_queda( Idoso* idoso );

int Idoso_sequencia_de_febres_baixas( Idoso* idoso );

void Idoso_reseta_sequncia_febres_baixas( Idoso* idoso );

int Idoso_com_febre_alta( Idoso* idoso );

int Idoso_com_febre_baixa( Idoso* idoso );

int Idoso_com_sequencia_4_febres_baixas( Idoso* idoso );

Cuidador* Idoso_retorna_cuidador_mais_proximo( Idoso* idoso );

Idoso* Idoso_retorna_amigo_mais_proximo( Idoso* idoso );

int Idoso_tem_amigos( Idoso* idoso );

#endif