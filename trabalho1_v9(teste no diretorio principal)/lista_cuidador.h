#ifndef LISTACUIDADOR_H
#define LISTACUIDADOR_H

#include <stdio.h>
#include <stdlib.h>
#include "cuidador.h"

/* Tipo Celula para implementacao do tipo Lista_cuidador
  Estrutura interna do tipo:
  - cuidador (ponteiro para o cuidador)
  - prox (ponteiro para a proxima celula da lista)
  - ant (ponteiro para a celula anterior da lista)
*/
typedef struct celula Celula;

/* Tipo Lista_cuidador
  Estrutura interna do tipo:
  - prim (ponteiro para a primeira celula da lista)
  - ult (ponteiro para a ultima celula da lista)
  - size (int)
*/
typedef struct lista_cuidador Lista_cuidador;

/*Inicializa uma Celula para o cuidador
* inputs: ponteiro para o cuidador
* output: um ponteiro para o tipo Celula
* pre-condicao: cuidador valido
* pos-condicao: tipo Celula criado
*/
Celula* Celula_cuidador_Inicializa ( Cuidador* cuidador );

/*Inicializa uma Lista_cuidador
* inputs: nenhum
* output: um ponteiro para o tipo Lista_cuidador
* pre-condicao: nenhuma
* pos-condicao: tipo Lista_cuidador criado e retornado
*/
Lista_cuidador* Lista_cuidador_Inicializa ();

/*Insere um cuidador no final da lista de cuidadores
* inputs: cuidador a ser inserido na lista e a lista
* output: nenhum
* pre-condicao: cuidador e lista validas
* pos-condicao: lista contem o cuidador inserido no final
*/
void Lista_cuidador_add_final (Lista_cuidador* lista, Cuidador* cuidador );

/*Retira um cuidador de nome "nome" da lista de cuidadores
* inputs: a lista e o nome do cuidador a ser retirado da lista
* output: nenhum
* pre-condicao: lista nao nula
* pos-condicao: lista nao contem o cuidador de nome "nome"
*/
void Lista_cuidador_remove ( Lista_cuidador* lista, char* nome );

/*Libera toda a memoria alocada para a lista
* inputs: endereco da lista de cuidadores
* output: Lista vazia (NULL)
* pre-condicao: lista nao nula
* pos-condicao: memoria alocada liberada
*/
void Lista_cuidador_destroi ( Lista_cuidador** lista_ref );

/*Imprime os nomes de todos os cuidadores da lista de cuidadores
* inputs: ponteiro para a lista de cuidadores
* output: nenhum
* pre-condicao: lista nao nula
* pos-condicao: nomes dos cuidadores impressos na saida padrao
*/
void Lista_cuidador_imprime ( const Lista_cuidador* lista );

/*Retorna o cuidador de nome "nome" da lista de cuidadores
* inputs: a lista e o nome do cuidador a ser retornado
* output: cuidador de nome "nome"
* pre-condicao: lista nao nula
* pos-condicao: o cuidador de nome "nome" foi retornado e a lista nao foi modificada
*/
Cuidador* Retorna_cuidador_pelo_nome( Lista_cuidador* lista, char* nome );

/*Retorna o cuidador da posicao 'indice' da lista de cuidadores
* inputs: a lista e o indice do cuidador a ser retornado
* output: cuidador do indice 'indice'
* pre-condicao: lista nao nula
* pos-condicao: o cuidador do indice passado foi retornado e a lista nao foi modificada
*/
Cuidador* Lista_cuidador_Retorna_cuidador_pelo_indice( Lista_cuidador* lista, int indice );

/*Retorna a quantidade de cuidadores presentes na lista
* inputs: lista de cuidadores
* output: quantidade de cuidadores
* pre-condicao: lista existe
* pos-condicao: quantidade de cuidadores foi retornado e a lista nao foi modificada
*/
int Lista_cuidador_num_elementos( const Lista_cuidador* lista );

#endif