#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "idoso.h"
#include "lista_idoso.h"
#include "cuidador.h"
#include "lista_cuidador.h"

Lista_idoso* Le_rede_de_apoio ( FILE * Rede_de_apoio );
Lista_cuidador* Le_rede_de_cuidadores ( FILE * cuidadores_txt, Lista_idoso* lista_de_idosos );
void Le_dados_sensores( char* diretorio_arquivos ,Lista_idoso* lista_de_idosos, Lista_cuidador* lista_de_cuidadores ,int num_leituras );

int main(int argc, char * argv[]) {

    FILE *Rede_de_apoio, *Rede_de_cuidadores;

    Lista_idoso* Lista_de_idosos;
    Lista_cuidador* Lista_de_cuidadores;

    char diretorio_entradas[1000],
    diretorio_saidas[1000],
    diretorio_apoio_txt[1000],
    diretorio_cuidadores_txt[1000];

    //cria o diretorio onde estao os arquivos de teste
	sprintf( diretorio_entradas,"%sEntradas", argv[1]);
    sprintf( diretorio_saidas,"%sSaidas", argv[1]);
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

    Le_dados_sensores( argv[1], Lista_de_idosos, Lista_de_cuidadores, atoi(argv[2]) );

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

    while( caractere_controle != '\n' && caractere_controle != ' ' ){
        fscanf( apoio_txt, "%[a-zA-z0-9]", nome);
        fscanf( apoio_txt, "%c", &caractere_controle);

        printf("nome: '%s'\n", nome);
        printf("caractere: '%c'\n\n", caractere_controle);

        idoso = Aloca_idoso( nome );
        Lista_idoso_add_final( lista_rede_apoio, idoso );
    }

    if( caractere_controle != '\n' ){
        fscanf( apoio_txt, "[^\n]");
        fscanf( apoio_txt, "\n");
    }


    while( fscanf( apoio_txt, "%[a-zA-z0-9];%[a-zA-z0-9]", nome, nome2 ) == 2 ) {
        idoso1 = Retorna_idoso_pelo_nome( lista_rede_apoio, nome);
        idoso2 = Retorna_idoso_pelo_nome( lista_rede_apoio, nome2);
        Adiciona_amigo( idoso1, idoso2);

        printf("nome: '%s'\n", nome);
        printf("nome2: '%s'\n", nome2);
        printf("caractere: '%c'\n\n", caractere_controle);

        fscanf( apoio_txt, "[^\n]");
        fscanf( apoio_txt, "\n");
    }

    return lista_rede_apoio;
}

Lista_cuidador* Le_rede_de_cuidadores ( FILE * cuidadores_txt, Lista_idoso* lista_de_idosos ) {

    Lista_cuidador* lista_rede_cuidadores;
    lista_rede_cuidadores = Lista_cuidador_Inicializa();
    Cuidador* cuidador;
    Idoso* idoso;

    int i = 0;

    char caractere_controle;
    char nome[100], nome2[100];

    while( caractere_controle != '\n' && caractere_controle != ' '){
        fscanf( cuidadores_txt, "%[a-zA-z0-9]", nome);
        fscanf( cuidadores_txt, "%c", &caractere_controle);

        printf("nome: '%s'\n", nome);
        printf("caractere: '%c'\n\n", caractere_controle);

        cuidador = Aloca_cuidador( nome );
        Lista_cuidador_add_final( lista_rede_cuidadores, cuidador );

        printf("%d\n", i);
        i++;
    }

    if( caractere_controle != '\n' ){
        fscanf( cuidadores_txt, "[^\n]");
        fscanf( cuidadores_txt, "\n");
    }

    while( fscanf( cuidadores_txt, "%[a-zA-z0-9];", nome) == 1 ) {
        caractere_controle = '0';

        idoso = Retorna_idoso_pelo_nome( lista_de_idosos, nome);

        printf("nome: '%s'\n", nome);

        while( caractere_controle != '\n' && caractere_controle != ' ' ){
            fscanf( cuidadores_txt, "%[a-zA-z0-9]", nome2);
            fscanf( cuidadores_txt, "%c", &caractere_controle);

            printf("nome2: '%s'\n", nome2);
            printf("caractere: '%c'\n\n", caractere_controle);

            cuidador = Retorna_cuidador_pelo_nome( lista_rede_cuidadores, nome2);
            Adiciona_cuidador(idoso, cuidador);
        } 
    }

    return lista_rede_cuidadores;
}


void Le_dados_sensores( char* diretorio_arquivos ,Lista_idoso* lista_de_idosos, Lista_cuidador* lista_de_cuidadores ,int num_leituras ) {

    Idoso* amigo_mais_proximo;
    Cuidador* cuidador_mais_proximo;

    // variaveis para os idosos
    int num_idosos = 0, i;
    num_idosos = Lista_idoso_num_elementos(lista_de_idosos);

    printf("n idosos: %d\n", num_idosos);

    char nome_idoso[100], diretorio_arquivo_idoso[100];
    Idoso* idoso_aux;
    FILE* arquivo_entrada_idosos[num_idosos];
    FILE* arquivo_saida_idosos[num_idosos];

    // variaveis para salvar as leituras
    float temp;
    int lat, lon, queda;
    char temp_s[5], lat_s[10], lon_s[10], queda_s[5];

    // abre os arquivos de sensores dos idosos para leitura
    for( i = 0; i < num_idosos; i++ ) {

        idoso_aux = Lista_Idoso_Retorna_idoso_pelo_indice( lista_de_idosos, i );

        //cria endereco do arquivo para fazer a leitura dos dados do idoso
        strcpy( nome_idoso, Retorna_nome_idoso( idoso_aux ));
        sprintf( diretorio_arquivo_idoso, "%sEntradas/%s.txt",diretorio_arquivos, nome_idoso);
        printf("%s\n", diretorio_arquivo_idoso);

        //abre o arquivo com o nome do idoso da vez
        arquivo_entrada_idosos[i] = fopen( diretorio_arquivo_idoso, "r");
        if( !arquivo_entrada_idosos[i] ){
            printf("Nao foi possivel ler o arquivo '%s' ! \n", diretorio_arquivo_idoso );
            exit(1);
        }


        // criar arquivos de saida para cada idoso
        sprintf( diretorio_arquivo_idoso, "%sSaidas/%s-saida.txt",diretorio_arquivos, nome_idoso);
        printf("%s\n", diretorio_arquivo_idoso);

        //abre o arquivo com o nome do idoso da vez
        arquivo_saida_idosos[i] = fopen( diretorio_arquivo_idoso, "w");
        if( !arquivo_saida_idosos[i] ){
            printf("Nao foi possivel abrir o arquivo '%s' ! \n", diretorio_arquivo_idoso );
            exit(1);
        }
    }


    // variaveis para os cuidadores
    int num_cuidadores = 0;
    num_cuidadores = Lista_cuidador_num_elementos( lista_de_cuidadores );

    printf("n cuidadores: %d\n\n", num_cuidadores);
    Lista_cuidador_imprime(lista_de_cuidadores);

    char nome_cuidador[100], diretorio_arquivo_cuidadores[100];
    Cuidador* cuidador_aux;
    FILE* arquivo_entrada_cuidadores[num_cuidadores];

    // abre os arquivos de sensores dos cuidadores para leitura
    for( i = 0; i < num_cuidadores; i++ ) {

        idoso_aux = Lista_Idoso_Retorna_idoso_pelo_indice( lista_de_idosos, i );
        cuidador_aux = Lista_cuidador_Retorna_cuidador_pelo_indice( lista_de_cuidadores, i );

        //cria endereco do arquivo para fazer a leitura dos dados do cuidadores
        strcpy( nome_cuidador, Retorna_nome_cuidador( cuidador_aux ));
        sprintf( diretorio_arquivo_cuidadores, "%sEntradas/%s.txt",diretorio_arquivos, nome_cuidador);
        printf("%s\n", diretorio_arquivo_cuidadores);

        //abre o arquivo com o nome do cuidador da vez
        arquivo_entrada_cuidadores[i] = fopen( diretorio_arquivo_cuidadores, "r");
        if( !arquivo_entrada_cuidadores[i] ){
            printf("Nao foi possivel ler o arquivo '%s' ! \n", diretorio_arquivo_cuidadores );
            exit(1);
        }
    }

    for( int n = 0; n < num_leituras; n++ ) {
        printf("Leitura numero: %d\n\n", n+1);

        // leitura dos dados dos cuidadores
        for( i = 0; i < num_cuidadores; i++ ) {

            cuidador_aux = Lista_cuidador_Retorna_cuidador_pelo_indice( lista_de_cuidadores, i );

            // fazer a leitura dos dados para o cuidador
            fscanf(arquivo_entrada_cuidadores[i], "%[^;];%[^\n]\n", lat_s, lon_s);
            lat     = atoi (lat_s);
            lon     = atoi (lon_s);

            Cuidador_atualiza_informacoes( cuidador_aux, lat, lon );
            printf("%s:\n", Retorna_nome_cuidador( cuidador_aux ));
            printf("lat: %d\nlon: %d\n\n\n", lat, lon );

        }

        // leitura dos dados dos idosos
        for( i = 0; i < num_idosos; i++ ) {
    
            idoso_aux = Lista_Idoso_Retorna_idoso_pelo_indice( lista_de_idosos, i );

            if( !Idoso_eh_falecido( idoso_aux) ){

                // fazer a leitura dos dados para o idoso
                if( fscanf(arquivo_entrada_idosos[i], "%[^;];%[^;];%[^;];%[^\n]\n", temp_s, lat_s, lon_s, queda_s ) == 4 ){
                    temp    = atof (temp_s);
                    lat     = atoi (lat_s);
                    lon     = atoi (lon_s);
                    queda   = atoi (queda_s);

                    Idoso_atualiza_informacoes( idoso_aux, temp, lat, lon, queda );
                    printf("%s:\n", Retorna_nome_idoso( idoso_aux ));
                    printf("temp: %f\nlat: %d\nlon: %d\nqueda: %d\n\n\n", temp, lat, lon, queda);
                }
                else {
                    Idoso_faleceu( idoso_aux );
                    fprintf( arquivo_saida_idosos[i], "falecimento\n");
                    printf("Idoso %s faleceu.\n\n", Retorna_nome_idoso( idoso_aux ) );
                }
            }
        }

        // toma as devidas providencias necessarias e escreve os arquivos de saida
        for( i = 0; i < num_idosos; i++ ) {

            idoso_aux = Lista_Idoso_Retorna_idoso_pelo_indice( lista_de_idosos, i );

            printf("Idoso: %s\nTemp: %f\n\n", Retorna_nome_idoso(idoso_aux), Idoso_temperatura_atual(idoso_aux));

            if( !Idoso_eh_falecido( idoso_aux) ){
            // verifica se eh necessario chamar um cuidador
                if( Idoso_sofreu_queda( idoso_aux )     || 
                    Idoso_com_febre_alta( idoso_aux )   || 
                    Idoso_com_sequencia_4_febres_baixas( idoso_aux )) {

                    printf("chamou cuidador\n");
                    printf("sofreu queda: %d\n", Idoso_sofreu_queda( idoso_aux ));
                    printf("febre alta: %d\n", Idoso_com_febre_alta( idoso_aux ));
                    printf("4 febre baixa: %d\n\n", Idoso_com_sequencia_4_febres_baixas( idoso_aux ));

                    cuidador_mais_proximo = Idoso_retorna_cuidador_mais_proximo( idoso_aux );

                    if( Idoso_sofreu_queda( idoso_aux ) ) {
                        fprintf( arquivo_saida_idosos[i], "queda, acionou %s\n", Retorna_nome_cuidador(cuidador_mais_proximo));
                    }
                    else if ( Idoso_com_febre_alta( idoso_aux ) ) {
                        fprintf( arquivo_saida_idosos[i], "febre alta, acionou %s\n", Retorna_nome_cuidador(cuidador_mais_proximo));
                        Idoso_reseta_sequncia_febres_baixas( idoso_aux );
                    }
                    else {
                        fprintf( arquivo_saida_idosos[i], "febre baixa pela quarta vez, acionou %s\n", Retorna_nome_cuidador(cuidador_mais_proximo));
                        Idoso_reseta_sequncia_febres_baixas( idoso_aux );
                    }

                }
                else if ( Idoso_com_febre_baixa( idoso_aux ) ){

                    printf("chamou amigo\n\n");

                    if( Idoso_tem_amigos( idoso_aux )){

                        amigo_mais_proximo = Idoso_retorna_amigo_mais_proximo( idoso_aux );
                        fprintf( arquivo_saida_idosos[i], "febre baixa, acionou amigo %s\n", Retorna_nome_idoso(amigo_mais_proximo));
                    }
                    else {
                        fprintf( arquivo_saida_idosos[i], "Febre baixa mas, infelizmente, o idoso está sem amigos na rede\n");
                    }

                    // fprintf( arquivo_saida_idosos[i],"sequencia de febres baixas: %d\n", Idoso_sequencia_de_febres_baixas(idoso_aux));
                }
                else {

                    printf("tudo ok\n\n");

                    fprintf( arquivo_saida_idosos[i], "tudo ok\n");
                }
            }
        }
    }

    // fecha os arquivos dos dados dos sensores dos idosos
    for( i = 0; i < num_idosos; i++ ) {
        fclose( arquivo_entrada_idosos[i]);
        fclose( arquivo_saida_idosos[i]  );

        printf("falecido = %d\n", Idoso_eh_falecido(Lista_Idoso_Retorna_idoso_pelo_indice(lista_de_idosos, i)));
    }

    // fecha os arquivos dos dados dos sensores dos cuidadores
    for( i = 0; i < num_cuidadores; i++ ) {
        fclose( arquivo_entrada_cuidadores[i]);
    }
    
}