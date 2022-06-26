#ifndef IDOSO_H
#define IDOSO_H

#include <stdio.h>
#include <stdlib.h>
#include "cuidador.h"
#include "lista_cuidador.h"

/* Tipo Idoso
  Estrutura interna do tipo:
  - nome (string)
  - Lista para amigos (ponteiro para lista)
  - Lista para cuidadores (ponteiro para lista)
  - temperatura (float)
  - latitude (float)
  - longitude (float)
  - queda (int)
  - falecimento (int)
  - sequencia de febres baixas (int)
*/
typedef struct idoso Idoso;

/*Inicializa (Aloca) um Idoso
* inputs: nome
* output: um ponteiro para o tipo Idoso
* pre-condicao: nome valido
* pos-condicao: variavel do tipo Idoso criada e retornada por um ponteiro, com o campo nome copiado
*/
Idoso* Idoso_aloca ( char* nome );

/*Retorna o nome do idoso
* inputs: ponteiro para o idoso
* output: nome do idoso
* pre-condicao: cuidador existe
* pos-condicao: cuidador e seu nome nao modificados
*/
char*  Idoso_retorna_nome (Idoso* idoso);

/*Imprime o nome do idoso
* inputs: ponteiro para o idoso
* output: nenhum
* pre-condicao: idoso existe  
* pos-condicao: idoso e seu nome nao modificados
*/
void   Idoso_imprime (Idoso* idoso);

/*Libera memoria alocada para o idoso
* inputs: ponteiro para o idoso
* output: nenhum
* pre-condicao: idoso existe  
* pos-condicao: toda a memoria alocada para o idoso foi liberada
*/
void   Idoso_desaloca (Idoso* idoso);

/*Adiciona um novo amigo na lista de amigos do idoso
* inputs: ponteiro para o idoso e ponteiro para o amigo
* output: nenhum
* pre-condicao: idoso e o novo amigo existem
* pos-condicao: amigo adicionado na lista de amigos do idoso
*/
void Idoso_adiciona_amigo ( Idoso* idoso, Idoso* novo_amigo);

/*Adiciona um novo cuidador na lista de cuidadores do idoso
* inputs: ponteiro para o idoso e ponteiro para o cuidador
* output: nenhum
* pre-condicao: idoso e o cuidador existem
* pos-condicao: cuidador adicionado na lista de cuidadores do idoso
*/
void Idoso_adiciona_cuidador( Idoso* idoso, Cuidador* cuidador );

/*Imprime todos os amigos do idoso
* inputs: ponteiro para o idoso
* output: nenhum
* pre-condicao: idoso existe  
* pos-condicao: idoso e sua lista de amigos nao modificados
*/
void Imprime_lista_amigos( Idoso* idoso );

/*Imprime todos os cuidadores do idoso
* inputs: ponteiro para o idoso
* output: nenhum
* pre-condicao: idoso existe  
* pos-condicao: idoso e sua lista de cuidadores nao modificados
*/
void Imprime_lista_cuidadores( Idoso* idoso );

/*Retorna se o idoso ja faleceu (1) ou nao (0)
* inputs: ponteiro para o idoso
* output: nenhum
* pre-condicao: idoso existe
* pos-condicao: idoso nao modificado
*/
int Idoso_eh_falecido( Idoso* idoso );

/*Modifica o status de falecimento do idoso para 1
* inputs: ponteiro para o idoso
* output: nenhum
* pre-condicao: idoso existe
* pos-condicao: aspecto falecimento do idoso setado como 1
*/
void Idoso_faleceu( Idoso* idoso );

/*Atualiza as informacoes de temperatura, latitude, longitude e se o idoso sofreu queda
* inputs: ponteiro para o idoso, latitude, longitude e se houve queda (queda == 1) ou nao(queda == 0)
* output: nenhum
* pre-condicao: idoso existe
* pos-condicao: informacoes atualizadas
*/
void Idoso_atualiza_informacoes( Idoso* idoso, float temp, int lat, int lon, int queda );

/*Retorna a lista de cuidadores do idoso
* inputs: ponteiro para o idoso
* output: ponteiro para lista de cuidadores do idoso
* pre-condicao: idoso existe
* pos-condicao: idoso e sua lista de cuidadores nao modificados
*/
Lista_cuidador* Idoso_retorna_lista_cuidadores( Idoso* idoso );

/*Retorna a temperatura atual do idoso
* inputs: ponteiro para o idoso
* output: temperatura atual
* pre-condicao: idoso existe
* pos-condicao: idoso nao modificado e temperatura retornada
*/
float Idoso_temperatura_atual ( Idoso* idoso );

/*Retorna a latitude atual do idoso
* inputs: ponteiro para o idoso
* output: latitude atual
* pre-condicao: idoso existe
* pos-condicao: idoso nao modificado e latitude retornada
*/
int Idoso_latitude_atual ( Idoso* idoso );

/*Retorna a longitude atual do idoso
* inputs: ponteiro para o idoso
* output: longitude atual
* pre-condicao: idoso existe
* pos-condicao: idoso nao modificado e longitude retornada
*/
int Idoso_longitude_atual ( Idoso* idoso );

/*Retorna se o idoso sofreu queda (1) ou nao (0)
* inputs: ponteiro para o idoso
* output: status de queda atual
* pre-condicao: idoso existe
* pos-condicao: idoso nao modificado e status de queda retornado
*/
int Idoso_sofreu_queda( Idoso* idoso );

/*Retorna quantas febres baixas seguidas o idoso teve
* inputs: ponteiro para o idoso
* output: numero de febres baixas seguidas
* pre-condicao: idoso existe
* pos-condicao: idoso nao modificado
*/
int Idoso_sequencia_de_febres_baixas( Idoso* idoso );

/*Retorna 1 se o idoso esta com febre alta, ou 0 se nao esta
* inputs: ponteiro para o idoso
* output: status de febre alta do idoso
* pre-condicao: idoso existe
* pos-condicao: idoso nao modificado
*/
int Idoso_com_febre_alta( Idoso* idoso );

/*Retorna 1 se o idoso esta com febre baixa, ou 0 se nao esta
* inputs: ponteiro para o idoso
* output: status de febre baixa do idoso
* pre-condicao: idoso existe
* pos-condicao: idoso nao modificado
*/
int Idoso_com_febre_baixa( Idoso* idoso );

/*Retorna 1 se o idoso teve uma sequencia de 4 febres baixas, ou 0 se nao
* inputs: ponteiro para o idoso
* output: 1 se teve 4 febres baixas seguidas, ou 0 caso contrario
* pre-condicao: idoso existe
* pos-condicao: idoso nao modificado
*/
int Idoso_com_sequencia_4_febres_baixas( Idoso* idoso );

/*Reseta o numero de febres seguidas do idoso para zero
* inputs: ponteiro para o idoso
* output: nenhum
* pre-condicao: idoso existe
* pos-condicao: numero de febres baixas seguidas do idoso igual a zero
*/
void Idoso_reseta_sequncia_febres_baixas( Idoso* idoso );

/*Retorna um ponteiro para o cuidador mais proximo do idoso
* inputs: ponteiro para o idoso
* output: ponteiro para o cuidador
* pre-condicao: idoso existe
* pos-condicao: cuidador mais proximo retornado
*/
Cuidador* Idoso_retorna_cuidador_mais_proximo( Idoso* idoso );

/*Retorna um ponteiro para o amigo mais proximo do idoso
* inputs: ponteiro para o idoso
* output: ponteiro para o amigo
* pre-condicao: idoso existe
* pos-condicao: amigo mais proximo retornado
*/
Idoso* Idoso_retorna_amigo_mais_proximo( Idoso* idoso );

/*Retorna 1 se o idoso tem amigos, ou 0 se nao
* inputs: ponteiro para o idoso
* output: 1 se o idoso tem amigos, ou 0 caso contrario
* pre-condicao: idoso existe
* pos-condicao: idoso nao modificado
*/
int Idoso_tem_amigos( Idoso* idoso );

#endif