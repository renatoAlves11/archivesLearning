#include <stdio.h>
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

int main(){
    FILE* file = fopen("cep_ordenado1.dat", "rb");
    if(file == NULL){
        printf("Arquivo não pôde ser aberto");
        return 1;
    }

    Endereco end;
    char buscado [8];
    printf("Digite o cep buscado:\n");
    scanf("%s", buscado);

    fseek(file, 0, SEEK_END);
    int tam = ftell(file);
    int qtdEnds = tam/sizeof(Endereco);
    int meio = qtdEnds/2, inicio = 0, fim = qtdEnds-1, result;

    fseek(file, sizeof(Endereco) * meio, SEEK_SET);
    fread(&end, sizeof(Endereco), 1, file);

    while(inicio < fim){
        result = strncmp(end.cep, buscado, 8);
        if(result == 0){
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", end.logradouro, end.bairro, end.cidade, end.uf, end.sigla, end.cep);
            break;
        }
        else if(result < 0){
            inicio = meio+1;
            meio = (fim+inicio)/2;
            fseek(file, sizeof(Endereco) * meio, SEEK_SET);
            fread(&end, sizeof(Endereco), 1, file);
        }
        else{
            fim = meio-1;
            meio = (fim+inicio)/2;
            fseek(file, sizeof(Endereco) * meio, SEEK_SET);
            fread(&end, sizeof(Endereco), 1, file);
        }
    }

    if(inicio < fim){
        printf("CEP não encontrado\n");
        return 0;
    }

    return 0;
}