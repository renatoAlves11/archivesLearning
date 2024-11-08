#include <stdio.h>
#include<string.h>

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


int main(){
    FILE* enderecos;
    FILE* idxArq;
    int tam, qtd, inicio, fim, meio, result;
    char buscado [8];
    endIdx aux;
    Endereco endBuscado;

    if((idxArq = fopen("idxArq.dat", "rb")) == NULL){
        printf("Arquivo não pôde ser aberto\n");
        return 1;
    }
    fseek(idxArq, 0, SEEK_END);
    tam = ftell(idxArq);
    qtd = tam/sizeof(endIdx);
    inicio = 0;
    fim = qtd-1;
    printf("Digite cep\n");
    scanf("%s", buscado);

    while(fim >= inicio){
        meio = (inicio + fim)/2;
        fseek(idxArq, sizeof(endIdx)*meio, SEEK_SET);
        fread(&aux, sizeof(endIdx), 1, idxArq);
        result = strncmp(buscado, aux.cep, 8);
        if(result == 0){
            break;
        }
        else if(result > 0){
            inicio = meio+1;
        }
        else{
            fim = meio-1;
        }
    }

    if(fim < inicio){
        printf("CEP não encontrado\n");
        return 0;
    }
    if((enderecos = fopen("cep.dat", "rb")) == NULL){
    printf("Arquivo não pôde ser aberto\n");
    return 1;
    }
    fseek(enderecos, sizeof(Endereco) * aux.idx, SEEK_SET);
    fread(&endBuscado, sizeof(Endereco), 1, enderecos);
    printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", endBuscado.logradouro, endBuscado.bairro, endBuscado.cidade, endBuscado.uf, endBuscado.sigla, endBuscado.cep);

    fclose(enderecos);
    fclose(idxArq);

    return 0;
}