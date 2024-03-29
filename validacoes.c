#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cliente.h"
#include "validacoes.h"

//Retorno: [1] - Se o cpf for válido | [0] - Se o cpf for inválido

int validaCPF(char* cpf){
    int i, j, digito10 = 0, digito11 = 0;

    if(strlen(cpf) != 11){
        return 0;
    }
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
        (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
        (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
        (strcmp(cpf,"99999999999") == 0)){
        return 0;
    }
    else{
        /*digito 10*/
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--){
            digito10 += (cpf[i]-48) * j;
        digito10 %= 11;
        }
        if(digito10 < 2)
            digito10 = 0;
        else
            digito10 = 11 - digito10;
        if((cpf[9]-48) != digito10)
            return 0; 

        else{
        /*digito 2*/
        for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--){
            digito11 += (cpf[i]-48) * j;
        digito11 %= 11;
        }
        if(digito11 < 2)
            digito11 = 0;
        else
            digito11 = 11 - digito11;
        if((cpf[10]-48) != digito11)
            return 0;
        else
        return 1;
        }
    }

}

//Retorno: [1] - Se o cpf cadastrado | [0] - Se o cpf nao for cadastrado

Cliente* buscaClienteCPF(char* cpf){
    int achou = 0;
    FILE* fpCliente;
    Cliente* cli;
    fpCliente = fopen("cliente.dat","rb");
    if(fpCliente == NULL){
        return 0;
    } else{
    cli = (Cliente*) malloc(sizeof(Cliente));
    while((!achou) && (fread(cli, sizeof(Cliente), 1, fpCliente))){
        if((strcmp(cli->cpf, cpf) == 0) && (cli->status == 'a')){
            achou = 1;
        }
    }
    fclose(fpCliente);
    free(cli);
    if(achou){
        return cli;
    } else{
        return 0;
    }
    }
}
