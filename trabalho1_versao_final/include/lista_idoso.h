#ifndef LISTAIDOSO_H
#define LISTAIDOSO_H

#include <stdio.h>
#include <stdlib.h>
#include "idoso.h"

/* Tipo Celula para implementacao do tipo Lista_idoso
  Estrutura interna do tipo:
  - idoso (ponteiro para o idoso)
  - prox (ponteiro para a proxima celula da lista)
  - ant (ponteiro para a celula anterior da lista)
*/
typedef struct celula Celula;

/* Tipo Lista_idoso
  Estrutura interna do tipo:
  - prim (ponteiro para a primeira celula da lista)
  - ult (ponteiro para a ultima celula da lista)
  - size (int)
*/
typedef struct lista_idoso Lista_idoso;

/*Inicializa uma Celula para o idoso
* inputs: ponteiro para o idoso
* output: um ponteiro para o tipo Celula
* pre-condicao: idoso valido
* pos-condicao: tipo Celula criado
*/
Celula* Celula_idoso_Inicializa ( Idoso* idoso );

/*Inicializa uma Lista_idoso
* inputs: nenhum
* output: um ponteiro para o tipo Lista_idoso
* pre-condicao: nenhuma
* pos-condicao: tipo Lista_idoso criado e retornado
*/
Lista_idoso* Lista_idoso_Inicializa ();

/*Insere um idoso no final da lista de idosos
* inputs: idoso a ser inserido na lista e a lista
* output: nenhum
* pre-condicao: idoso e lista validas
* pos-condicao: lista contem o idoso inserido no final
*/
void Lista_idoso_add_final (Lista_idoso* lista, Idoso* idoso );

/*Retira um idoso de nome "nome" da lista de idosos
* inputs: a lista e o nome do idoso a ser retirado da lista
* output: nenhum
* pre-condicao: lista nao nula
* pos-condicao: lista nao contem o idoso de nome "nome"
*/
void Lista_idoso_remove ( Lista_idoso* lista, char* nome );

/*Libera toda a memoria alocada para a lista
* inputs: endereco da lista de idosos
* output: Lista vazia (NULL)
* pre-condicao: lista nao nula
* pos-condicao: memoria alocada liberada
*/
void Lista_idoso_destroi ( Lista_idoso** lista_ref );

/*Imprime os nomes de todos os idosos da lista de idosos
* inputs: ponteiro para a lista de idosos
* output: nenhum
* pre-condicao: lista nao nula
* pos-condicao: nomes dos idosos impressos na saida padrao
*/
void Lista_idoso_imprime ( const Lista_idoso* lista );

/*Retorna o idoso de nome "nome" da lista de idosos
* inputs: a lista e o nome do idoso a ser retornado
* output: idoso de nome "nome"
* pre-condicao: lista nao nula
* pos-condicao: o idoso de nome "nome" foi retornado e a lista nao foi modificada
*/
Idoso* Retorna_idoso_pelo_nome( Lista_idoso* lista, char* nome );

/*Retorna o idoso da posicao 'indice' da lista de idosos
* inputs: a lista e o indice do idoso a ser retornado
* output: idoso do indice 'indice'
* pre-condicao: lista nao nula
* pos-condicao: o idoso do indice passado foi retornado e a lista nao foi modificada
*/
Idoso* Lista_Idoso_Retorna_idoso_pelo_indice( Lista_idoso* lista, int indice );

/*Retorna a quantidade de idosos presentes na lista
* inputs: lista de idosos
* output: quantidade de idosos
* pre-condicao: lista existe
* pos-condicao: quantidade de idosos foi retornado e a lista nao foi modificada
*/
int Lista_idoso_num_elementos( const Lista_idoso* lista );


#endif