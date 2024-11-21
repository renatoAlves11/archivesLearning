#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
} Endereco;

int compara (const void * x1, const void * x2){
    return strncmp(((Endereco*)x1)->cep, ((Endereco*)x2)->cep, 8);
}

int main(){
    FILE* file = fopen("cep.dat", "rb");
    FILE* ordenado = fopen("cep_ordenado1.dat", "wb");
    if(file == NULL || ordenado == NULL){
        printf("ERRO\n");
    }
    fseek(file, 0, SEEK_END);
    int tam = ftell(file);

    if (tam == -1) {
        printf("Erro ao determinar o tamanho do arquivo.\n");
        fclose(file);
        fclose(ordenado);
        return 1;
    }

    int qtdEnd = tam/sizeof(Endereco);

    Endereco * ends = (Endereco *)malloc(sizeof(Endereco) * qtdEnd);
    rewind(file);
    fread(ends, sizeof(Endereco), qtdEnd, file);
    // for(int i = 0; i < qtdEnd; i++){
    //     printf("%s\n", ends[i].cep);
    // }

    qsort(ends, qtdEnd, sizeof(Endereco), compara);

    fwrite(ends, sizeof(Endereco), qtdEnd, ordenado);

    fclose(file);
    fclose(ordenado);
    return 0;
}