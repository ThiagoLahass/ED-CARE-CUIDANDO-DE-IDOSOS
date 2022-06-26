#ifndef CUIDADOR_H
#define CUIDADOR_H

#include <stdio.h>
#include <stdlib.h>

/* Tipo Cuidador
  Estrutura interna do tipo:
  - nome (string)
  - latitude (float)
  - longitude (float)
*/
typedef struct cuidador Cuidador;

/*Inicializa (Aloca) um Cuidador
* inputs: nome
* output: um ponteiro para o tipo Cuidador
* pre-condicao: nome valido
* pos-condicao: variavel do tipo Cuidador criada e retornada por um ponteiro, com o campo nome copiado
*/
Cuidador* Cuidador_aloca ( char* nome );

/*Retorna o nome do cuidador
* inputs: ponteiro para o cuidador
* output: nome do cuidador
* pre-condicao: cuidador existe
* pos-condicao: cuidador e seu nome nao modificados
*/
char*  Cuidador_retorna_nome (Cuidador* cuidador);

/*Imprime o nome do cuidador
* inputs: ponteiro para o cuidador
* output: nenhum
* pre-condicao: cuidador existe  
* pos-condicao: cuidador e seu nome nao modificados
*/
void   Cuidador_imprime (Cuidador* cuidador);

/*Libera memoria alocada para o cuidador
* inputs: cuidador
* output: nenhum
* pre-condicao: cuidador existe  
* pos-condicao: toda a memoria alocada para o cuidador foi liberada
*/
void   Cuidador_desaloca (Cuidador* cuidador);

/*Atualiza as informacoes de latitude e longitude do cuidador
* inputs: ponteiro para o cuidador, latitude e longitude atuais
* output: nenhum
* pre-condicao: cuidador existe
* pos-condicao: latitude e longitude atualizadas
*/
void Cuidador_atualiza_informacoes ( Cuidador* cuidador, int lat, int lon );

/*Retorna a latitude atual do cuidador
* inputs: ponteiro para o cuidador
* output: latitude atual
* pre-condicao: cuidador existe
* pos-condicao: cuidador nao modificado e latitude retornada
*/
int Cuidador_latitude_atual ( Cuidador* cuidador );

/*Retorna a longitude atual do cuidador
* inputs: ponteiro para o cuidador
* output: longitude atual
* pre-condicao: cuidador existe
* pos-condicao: cuidador nao modificado e longitude retornada
*/
int Cuidador_longitude_atual ( Cuidador* cuidador );

#endif