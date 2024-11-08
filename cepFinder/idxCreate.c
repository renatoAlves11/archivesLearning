#include <stdio.h>
#include<string.h>
#include<stdlib.h>

struct endIdx_ {
    char cep[8];
    int idx;
};

typedef struct endIdx_ endIdx;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

typedef struct _Endereco Endereco;

int compara(const void* idx1, const void* idx2){
    return strncmp(((endIdx*)idx1)->cep, ((endIdx*)idx2)->cep, 8);
}

int main(){
    FILE* enderecos;
    FILE* idxArq;
    int qtd, size, counter = 0;
    Endereco end;

    if((enderecos = fopen("cep.dat", "rb")) == NULL){
        printf("Arquivo não pôde ser aberto\n");
        return 1;
    }

    fseek(enderecos, 0, SEEK_END);
    size = ftell(enderecos);
    qtd = size/sizeof(Endereco);
    endIdx* vetIdx = (endIdx*) malloc(sizeof(endIdx) * qtd);
    rewind(enderecos);

    fread(&end, sizeof(Endereco), 1, enderecos);
    while(!feof(enderecos)){
        strncpy(vetIdx[counter].cep, end.cep, 8);
        vetIdx[counter].idx = counter;
        counter++;
        fread(&end, sizeof(Endereco), 1, enderecos);
    }

    qsort(vetIdx, qtd, sizeof(endIdx), compara);

    if((idxArq = fopen("idxArq.dat", "wb")) == NULL){
        printf("Arquivo não pôde ser aberto\n");
    }

    fwrite(vetIdx, sizeof(endIdx), qtd, idxArq);

    fclose(enderecos);
    fclose(idxArq);
    free(vetIdx);
    printf("OK\n");
    return 0;
}