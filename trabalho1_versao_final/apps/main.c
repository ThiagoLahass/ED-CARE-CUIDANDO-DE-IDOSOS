#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_idoso.h"
#include "lista_cuidador.h"

/*Faz a leitura da rede de apoio dos idosos
* inputs: arquivo onde estao os dados da rede
* output: um ponteiro para o tipo Lista_idoso
* pre-condicao: arquivo existe e foi aberto
* pos-condicao: tipo Lista_idoso criado e retornado
*/
Lista_idoso* Le_rede_de_apoio ( FILE * Rede_de_apoio );

/*Faz a leitura da rede de cuidadores dos idosos
* inputs: arquivo onde estao os dados da rede de cuidadores
* output: um ponteiro para o tipo Lista_cuidador
* pre-condicao: arquivo existe e foi aberto
* pos-condicao: tipo Lista_cuidador criado e retornado
*/
Lista_cuidador* Le_rede_de_cuidadores ( FILE * cuidadores_txt, Lista_idoso* lista_de_idosos );

/*Faz a leitura dos arquivo dos dados dos sensores
* inputs: lista de idosos, uma lista de cuidadores, e o numero de leituras
* output: nenhum
* pre-condicao: as listas existem e o diretorio existe
* pos-condicao: a leitura dos dados foi feita
*/
void Le_dados_sensores( Lista_idoso* lista_de_idosos, Lista_cuidador* lista_de_cuidadores ,int num_leituras );

/*Faz a liberacao de toda a memoria alocada pelas listas, idosos e cuidadores
* inputs: lista de idosos e lista de cuidadores
* output: nenhum
* pre-condicao: as listas existem
* pos-condicao: toda memoria foi liberada
*/
void Libera_memoria( Lista_idoso* lista_de_idosos, Lista_cuidador* lista_de_cuidadores );

int main(int argc, char * argv[]) {

    FILE *Rede_de_apoio, *Rede_de_cuidadores;

    Lista_idoso* Lista_de_idosos;
    Lista_cuidador* Lista_de_cuidadores;

    char diretorio_apoio_txt[50], diretorio_cuidadores_txt[50];

    //cria o diretorio onde estao os arquivos de teste
    snprintf( diretorio_apoio_txt, sizeof(diretorio_apoio_txt), "Entradas/apoio.txt");
    snprintf( diretorio_cuidadores_txt,sizeof(diretorio_cuidadores_txt), "Entradas/cuidadores.txt");

    //abre o arquivo apoio.txt para leitura
    Rede_de_apoio = fopen( diretorio_apoio_txt, "r");
    if( !Rede_de_apoio ){
        printf("Nao foi possivel ler o arquivo %s ! \n", diretorio_apoio_txt );
        return 1;
    }

    Lista_de_idosos = Le_rede_de_apoio( Rede_de_apoio );

    //abre o arquivo cuidadores.txt para leitura    
    Rede_de_cuidadores = fopen( diretorio_cuidadores_txt, "r");
    if( !Rede_de_cuidadores ){
        printf("Nao foi possivel ler o arquivo %s ! \n", diretorio_cuidadores_txt );
        return 1;
    }

    Lista_de_cuidadores = Le_rede_de_cuidadores( Rede_de_cuidadores,  Lista_de_idosos);

    Le_dados_sensores( Lista_de_idosos, Lista_de_cuidadores, atoi(argv[1]) );

    fclose( Rede_de_apoio );
    fclose( Rede_de_cuidadores );

    Libera_memoria( Lista_de_idosos, Lista_de_cuidadores );

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

        idoso = Idoso_aloca( nome );
        Lista_idoso_add_final( lista_rede_apoio, idoso );
    }

    if( caractere_controle != '\n' ){
        fscanf( apoio_txt, "[^\n]");
        fscanf( apoio_txt, "\n");
    }


    while( fscanf( apoio_txt, "%[a-zA-z0-9];%[a-zA-z0-9]", nome, nome2 ) == 2 ) {
        idoso1 = Retorna_idoso_pelo_nome( lista_rede_apoio, nome);
        idoso2 = Retorna_idoso_pelo_nome( lista_rede_apoio, nome2);
        Idoso_adiciona_amigo( idoso1, idoso2);

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

    char caractere_controle = '0';
    char nome[100], nome2[100];

    while( caractere_controle != '\n' && caractere_controle != ' '){
        fscanf( cuidadores_txt, "%[a-zA-z0-9]", nome);
        fscanf( cuidadores_txt, "%c", &caractere_controle);

        cuidador = Cuidador_aloca ( nome );
        Lista_cuidador_add_final( lista_rede_cuidadores, cuidador );
    }

    if( caractere_controle != '\n' ){
        fscanf( cuidadores_txt, "[^\n]");
        fscanf( cuidadores_txt, "\n");
    }

    while( fscanf( cuidadores_txt, "%[a-zA-z0-9];", nome) == 1 ) {
        caractere_controle = '0';

        idoso = Retorna_idoso_pelo_nome( lista_de_idosos, nome);
        while( caractere_controle != '\n' && caractere_controle != ' ' ){
            fscanf( cuidadores_txt, "%[a-zA-z0-9]", nome2);
            fscanf( cuidadores_txt, "%c", &caractere_controle);
            cuidador = Retorna_cuidador_pelo_nome( lista_rede_cuidadores, nome2);
            Idoso_adiciona_cuidador(idoso, cuidador);
        } 
    }

    return lista_rede_cuidadores;
}


void Le_dados_sensores( Lista_idoso* lista_de_idosos, Lista_cuidador* lista_de_cuidadores ,int num_leituras ) {

    //flag para ver se eh necessario fazer a leitura dos dados dos idosos
    int flag = 1;
    
    Idoso* amigo_mais_proximo;
    Cuidador* cuidador_mais_proximo;

    // variaveis para os idosos
    int num_idosos = 0, i = 0;
    num_idosos = Lista_idoso_num_elementos(lista_de_idosos);
    char nome_idoso[100], diretorio_arquivo_idoso[200];
    Idoso* idoso_aux;
    FILE* arquivo_entrada_idosos[num_idosos];
    FILE* arquivo_saida_idosos[num_idosos];

    // variaveis para salvar as leituras
    float temp = 0;
    int lat = 0, lon = 0, queda = 0;
    char temp_s[20], lat_s[10], lon_s[10], queda_s[4];

    // abre os arquivos de sensores dos idosos para leitura
    for( i = 0; i < num_idosos; i++ ) {

        idoso_aux = Lista_Idoso_Retorna_idoso_pelo_indice( lista_de_idosos, i );

        //cria endereco do arquivo para fazer a leitura dos dados do idoso
        strcpy( nome_idoso, Idoso_retorna_nome( idoso_aux ));
        snprintf( diretorio_arquivo_idoso, sizeof(diretorio_arquivo_idoso), "Entradas/%s.txt", nome_idoso);

        //abre o arquivo com o nome do idoso da vez
        arquivo_entrada_idosos[i] = fopen( diretorio_arquivo_idoso, "r");
        if( !arquivo_entrada_idosos[i] ){
            printf("Nao foi possivel ler o arquivo '%s' ! \n", diretorio_arquivo_idoso );
            exit(1);
        }


        // criar arquivos de saida para cada idoso
        snprintf( diretorio_arquivo_idoso, sizeof(diretorio_arquivo_idoso), "Saidas/%s-saida.txt", nome_idoso);

        //abre o arquivo com o nome do idoso da vez
        arquivo_saida_idosos[i] = fopen( diretorio_arquivo_idoso, "w");
        if( !arquivo_saida_idosos[i] ){
            printf("Nao foi possivel abrir o arquivo '%s' ! \n", diretorio_arquivo_idoso );
            exit(1);
        }
    }


    // variaveis para os cuidadores
    int num_cuidadores = 0, n = 0;
    num_cuidadores = Lista_cuidador_num_elementos( lista_de_cuidadores );
    char nome_cuidador[100], diretorio_arquivo_cuidadores[200];
    Cuidador* cuidador_aux;
    FILE* arquivo_entrada_cuidadores[num_cuidadores];

    // abre os arquivos de sensores dos cuidadores para leitura
    for( i = 0; i < num_cuidadores; i++ ) {

        idoso_aux = Lista_Idoso_Retorna_idoso_pelo_indice( lista_de_idosos, i );
        cuidador_aux = Lista_cuidador_Retorna_cuidador_pelo_indice( lista_de_cuidadores, i );

        //cria endereco do arquivo para fazer a leitura dos dados do cuidadores
        strcpy( nome_cuidador, Cuidador_retorna_nome( cuidador_aux ));
        snprintf( diretorio_arquivo_cuidadores, sizeof(diretorio_arquivo_cuidadores), "Entradas/%s.txt", nome_cuidador);

        //abre o arquivo com o nome do cuidador da vez
        arquivo_entrada_cuidadores[i] = fopen( diretorio_arquivo_cuidadores, "r");
        if( !arquivo_entrada_cuidadores[i] ){
            printf("Nao foi possivel ler o arquivo '%s' ! \n", diretorio_arquivo_cuidadores );
            exit(1);
        }
    }

    for( n = 0; n < num_leituras; n++ ) {
        // leitura dos dados dos cuidadores
        for( i = 0; i < num_cuidadores; i++ ) {

            cuidador_aux = Lista_cuidador_Retorna_cuidador_pelo_indice( lista_de_cuidadores, i );

            // fazer a leitura dos dados para o cuidador
            if( fscanf(arquivo_entrada_cuidadores[i], "%[^;];%[^\n]\n", lat_s, lon_s) != 2 ) {
                flag = 0;
            }
            lat     = atoi (lat_s);
            lon     = atoi (lon_s);

            Cuidador_atualiza_informacoes( cuidador_aux, lat, lon );
        }

        // leitura dos dados dos idosos

        // a ler dos dados dos idosos e tomar as devidas providencias so eh necessario
        // quando foi possivel fazer a leitura dos dados dos cuidadores, o que eh indicado
        // pela variavel 'flag'
        if( flag == 1 ) {
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
                    }
                    
                    
                    else if( strcmp( temp_s, "falecimento\n") == 0){
                        Idoso_faleceu( idoso_aux );
                        fprintf( arquivo_saida_idosos[i], "falecimento\n");
                    }
                }
            }

            // toma as devidas providencias necessarias e escreve os arquivos de saida
            for( i = 0; i < num_idosos; i++ ) {
                idoso_aux = Lista_Idoso_Retorna_idoso_pelo_indice( lista_de_idosos, i );
                if( !Idoso_eh_falecido( idoso_aux) ){
                    // verifica se eh necessario chamar um cuidador
                    if( Idoso_sofreu_queda( idoso_aux )     || 
                        Idoso_com_febre_alta( idoso_aux )   || 
                        Idoso_com_sequencia_4_febres_baixas( idoso_aux )) {

                        cuidador_mais_proximo = Idoso_retorna_cuidador_mais_proximo( idoso_aux );

                        if( Idoso_sofreu_queda( idoso_aux ) ) {
                            fprintf( arquivo_saida_idosos[i], "queda, acionou %s\n", Cuidador_retorna_nome(cuidador_mais_proximo));
                        }
                        else if ( Idoso_com_febre_alta( idoso_aux ) ) {
                            fprintf( arquivo_saida_idosos[i], "febre alta, acionou %s\n", Cuidador_retorna_nome(cuidador_mais_proximo));
                            Idoso_reseta_sequncia_febres_baixas( idoso_aux );
                        }
                        else {
                            fprintf( arquivo_saida_idosos[i], "febre baixa pela quarta vez, acionou %s\n", Cuidador_retorna_nome(cuidador_mais_proximo));
                            Idoso_reseta_sequncia_febres_baixas( idoso_aux );
                        }
                    }
                    else if ( Idoso_com_febre_baixa( idoso_aux ) ){
                        if( Idoso_tem_amigos( idoso_aux )){

                            amigo_mais_proximo = Idoso_retorna_amigo_mais_proximo( idoso_aux );
                            fprintf( arquivo_saida_idosos[i], "febre baixa, acionou amigo %s\n", Idoso_retorna_nome(amigo_mais_proximo));
                        }
                        else {
                            fprintf( arquivo_saida_idosos[i], "Febre baixa mas, infelizmente, o idoso está sem amigos na rede\n");
                        }
                    }
                    else {
                        fprintf( arquivo_saida_idosos[i], "tudo ok\n");
                    }
                }
            }
        }
    }

    // fecha os arquivos dos dados dos sensores dos idosos
    for( i = 0; i < num_idosos; i++ ) {
        fclose( arquivo_entrada_idosos[i]);
        fclose( arquivo_saida_idosos[i]  );
    }

    // fecha os arquivos dos dados dos sensores dos cuidadores
    for( i = 0; i < num_cuidadores; i++ ) {
        fclose( arquivo_entrada_cuidadores[i]);
    }
    
}


void Libera_memoria( Lista_idoso* lista_de_idosos, Lista_cuidador* lista_de_cuidadores ) {
    
    int num_cuidadores = Lista_cuidador_num_elementos( lista_de_cuidadores );
    int num_idosos = Lista_idoso_num_elementos( lista_de_idosos );

    //libera a lista de cuidador de cada idoso
    int i = 0;
    Cuidador* cuidador_aux;
    Idoso* idoso_aux;
    
    for( i = 0; i < num_idosos; i++ ) {
        idoso_aux = Lista_Idoso_Retorna_idoso_pelo_indice( lista_de_idosos, i );
        Idoso_desaloca( idoso_aux );
    }

    Lista_idoso_destroi( &lista_de_idosos );

    for( i = 0; i < num_cuidadores; i++ ) {
        cuidador_aux = Lista_cuidador_Retorna_cuidador_pelo_indice( lista_de_cuidadores, i );
        Cuidador_desaloca( cuidador_aux );
    }

    Lista_cuidador_destroi( &lista_de_cuidadores );
}