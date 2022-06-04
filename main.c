#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "idoso.h"
#include "lista_idoso.h"
#include "cuidador.h"
#include "lista_cuidador.h"

Lista_idoso* Le_rede_de_apoio ( FILE * Rede_de_apoio );

int main(int argc, char * argv[]) {

    FILE * Rede_de_apoio;
    Lista_idoso* Lista_rede_de_apoio;

    char diretorio_entradas[1000],
    diretorio_saidas[1000],
    diretorio_apoio_txt[1000],
    diretorio_cuidadores_txt[1000];

    //cria o diretorio onde estao os arquivos de teste
	sprintf( diretorio_entradas,"%s/Entradas", argv[1]);
    sprintf( diretorio_saidas,"%s/Saidas", argv[1]);
    sprintf( diretorio_apoio_txt, "%s/apoio.txt", diretorio_entradas);
    sprintf( diretorio_cuidadores_txt, "%s/cuidadores.txt", diretorio_entradas);

    //abre o arquivo apoio.txt para leitura
    Rede_de_apoio = fopen( diretorio_apoio_txt, "r");
    if( !Rede_de_apoio ){
        printf("Nao foi possivel ler o arquivo %s ! \n", diretorio_apoio_txt );
        return 1;
    }

    Lista_rede_de_apoio = Le_rede_de_apoio( Rede_de_apoio );

    Lista_idoso_imprime( Lista_rede_de_apoio );

    return 0;
}

Lista_idoso* Le_rede_de_apoio ( FILE * apoio_txt ) {

    Lista_idoso* lista_rede_apoio;
    lista_rede_apoio = Lista_idoso_Inicializa();
    Idoso* idoso;

    char caractere_controle;
    char *nome, *nome2;

    while(1){
        fscanf( apoio_txt, "%[^;\n]", nome);
        fscanf( apoio_txt, "%c", &caractere_controle);
        
        if( caractere_controle == "\n" ) break;

        idoso = Aloca_idoso( nome );
        Lista_idoso_add_final( lista_rede_apoio, idoso );
    }

    while( fscanf( apoio_txt, "%[^;];%[^\n]\n", nome, nome2 ) == 2 ) {
        Adiciona_amigo( 
            Retorna_idoso_pelo_nome( lista_rede_apoio, nome), 
            Retorna_idoso_pelo_nome( lista_rede_apoio, nome2)
        );
    }

    return lista_rede_apoio;
}