#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "idoso.h"
#include "lista_idoso.h"
#include "cuidador.h"
#include "lista_cuidador.h"

Lista_idoso* Le_rede_de_apoio ( FILE * Rede_de_apoio );
Lista_cuidador* Le_rede_de_cuidadores ( FILE * cuidadores_txt, Lista_idoso* lista_de_idosos );
void Le_dados_sensores( char* diretorio_entradas ,Lista_idoso* lista_de_idosos, int num_leituras );

int main(int argc, char * argv[]) {

    FILE *Rede_de_apoio, *Rede_de_cuidadores;

    Lista_idoso* Lista_de_idosos;
    Lista_cuidador* Lista_de_cuidadores;

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

    Lista_de_idosos = Le_rede_de_apoio( Rede_de_apoio );

    // Lista_idoso_imprime( Lista_de_idosos );
    // Idoso* idoso_teste = Retorna_idoso_pelo_nome(Lista_de_idosos, "Joao");
    // Imprime_lista_amigos(idoso_teste);

    //abre o arquivo cuidadores.txt para leitura    
    Rede_de_cuidadores = fopen( diretorio_cuidadores_txt, "r");
    if( !Rede_de_cuidadores ){
        printf("Nao foi possivel ler o arquivo %s ! \n", diretorio_cuidadores_txt );
        return 1;
    }

    Lista_de_cuidadores = Le_rede_de_cuidadores( Rede_de_cuidadores,  Lista_de_idosos);

    // Idoso* idoso_teste = Retorna_idoso_pelo_nome( Lista_de_idosos, "Pedro" );
    // Imprime_lista_cuidadores(idoso_teste);

    Le_dados_sensores( argv[1], Lista_de_idosos, 10);

    fclose( Rede_de_apoio );
    fclose( Rede_de_cuidadores );

    return 0;
}

Lista_idoso* Le_rede_de_apoio ( FILE * apoio_txt ) {

    Lista_idoso* lista_rede_apoio;
    lista_rede_apoio = Lista_idoso_Inicializa();
    Idoso* idoso, *idoso1, *idoso2;

    char caractere_controle = '0';
    char nome[100], nome2[100];

    while( caractere_controle != '\n' ){
        fscanf( apoio_txt, "%[a-zA-z0-9]", nome);
        fscanf( apoio_txt, "%c", &caractere_controle);

        idoso = Aloca_idoso( nome );
        Lista_idoso_add_final( lista_rede_apoio, idoso );
    }

    while( fscanf( apoio_txt, "%[a-zA-z0-9];%[a-zA-z0-9]\n", nome, nome2 ) == 2 ) {
        idoso1 = Retorna_idoso_pelo_nome( lista_rede_apoio, nome);
        idoso2 = Retorna_idoso_pelo_nome( lista_rede_apoio, nome2);
        Adiciona_amigo( idoso1, idoso2);
    }

    return lista_rede_apoio;
}

Lista_cuidador* Le_rede_de_cuidadores ( FILE * cuidadores_txt, Lista_idoso* lista_de_idosos ) {

    Lista_cuidador* lista_rede_cuidadores;
    lista_rede_cuidadores = Lista_cuidador_Inicializa();
    Cuidador* cuidador;
    Idoso* idoso;

    char caractere_controle = '0';
    char nome[100], nome2[100];

    while( caractere_controle != '\n' ){
        fscanf( cuidadores_txt, "%[a-zA-z0-9]", nome);
        fscanf( cuidadores_txt, "%c", &caractere_controle);

        cuidador = Aloca_cuidador( nome );
        Lista_cuidador_add_final( lista_rede_cuidadores, cuidador );
    }

    while( fscanf( cuidadores_txt, "%[a-zA-z0-9];", nome) == 1 ) {
        caractere_controle = '0';

        idoso = Retorna_idoso_pelo_nome( lista_de_idosos, nome);

        while( caractere_controle != '\n' ){
            fscanf( cuidadores_txt, "%[a-zA-z0-9]", nome2);
            fscanf( cuidadores_txt, "%c", &caractere_controle);

            cuidador = Retorna_cuidador_pelo_nome( lista_rede_cuidadores, nome2);
            Adiciona_cuidador(idoso, cuidador);
        }        
    }

    return lista_rede_cuidadores;
}


void Le_dados_sensores( char* diretorio_entradas, Lista_idoso* lista_de_idosos, int num_leituras ) {

    // lista_de_idosos = Le_rodada_de_dados( diretorio_testes, lista_de_idosos, num_leituras );
    int num_idosos = 0, i;
    num_idosos = Lista_idoso_num_elementos(lista_de_idosos);
    char nome[100], arquivo_entrada[100];
    Idoso* idoso_aux;

    for( i = 0; i < num_idosos; i++ ) {
        idoso_aux = Lista_Idoso_Retorna_idoso_pelo_indice( lista_de_idosos, i );
        strcpy( nome, Retorna_nome_idoso( idoso_aux ));
        sprintf( arquivo_entrada, "%s/%s.txt",diretorio_entradas, nome);
        printf("%s\n", arquivo_entrada);
    }
}