#include <stdio.h>
#include <string.h>


typedef struct _Produto {
    char descricao [40];
    int quantidadeEstoque;
    int minimoEstoque;
    float precoVenda;
} Produto;

int menu();
void incluiProduto(FILE *);
void registraVenda(FILE *);
void buscaPorCod(FILE *);
void buscaPorDescricao(FILE*);
void geraRelatorio(FILE*);

int main(){
    int op;
    FILE * file = fopen("estoque.bin", "rb+");
    if(file == NULL){
        file = fopen("estoque.txt", "wb+");
        if(file == NULL){
            printf("Arquivo não pôde ser aberto\n");
            return 1;
        }
    }
    do{
        op = menu();
        rewind(file);
        switch(op){
            case 1: incluiProduto(file); break;
            case 2: registraVenda(file); break;
            case 3: buscaPorCod(file); break;
            case 4: buscaPorDescricao(file); break;
            case 5: geraRelatorio(file); break;
            case 6: break;
            default: printf("Digite uma opção válida\n\n"); menu();
        }
    } while(op != 6);
    fclose(file);
    return 0;
}

int menu(){
    int op;
    printf("Selecione a operação:\n\n1 - Incluir Produto\n2 - Registrar Venda\n3 - Buscar por Código\n4 - Buscar por Descrição\n5 - Relatório de produtos com estoque abaixo do mínimo\n6 - Sair\n");
    scanf("%d", &op);
    return op;
}

void incluiProduto(FILE * file){
    Produto prod;
    getchar();
    printf("Digite a descrição do produto:\n");
    fgets(prod.descricao, sizeof(prod.descricao), stdin);
    printf("Digite quantidade em estoque do produto:\n");
    scanf("%d", &prod.quantidadeEstoque);
    printf("Digite quantidade mínima do produto\n");
    scanf("%d", &prod.minimoEstoque);
    printf("Digite preço de venda do produto\n");
    scanf("%f", &prod.precoVenda);

    fseek(file, 0, SEEK_END);
    fwrite(&prod, sizeof(Produto), 1, file);
}

void registraVenda(FILE * file){
    int cod, qtdVendida;
    Produto prod;
    printf("Digite o código do produto:\n");
    scanf("%d", &cod);
    printf("Digite a quantidade vendida:\n");
    scanf("%d", &qtdVendida);

    fseek(file, cod * sizeof(Produto), SEEK_SET);
    if(fread(&prod, sizeof(Produto), 1, file) == 0){
        printf("Código inválido!\n");
        return;
    }
    if((prod.quantidadeEstoque - qtdVendida) >= prod.minimoEstoque){
        prod.quantidadeEstoque -= qtdVendida;
        printf("%d produtos %s vendidos\n", qtdVendida, prod.descricao);
    }
    else{
        int vendida = prod.quantidadeEstoque - prod.minimoEstoque;
        printf("%d produtos %s vendidos\n", vendida, prod.descricao);
        prod.quantidadeEstoque = prod.minimoEstoque;
    }

    fseek(file, cod * sizeof(Produto), SEEK_SET);
    fwrite(&prod, sizeof(Produto), 1, file);
}

void buscaPorCod(FILE * file){
    int cod;
    Produto prod;
    printf("Digite o código\n");
    scanf("%d", &cod);

    fseek(file, cod * sizeof(Produto), SEEK_SET);
    if(fread(&prod, sizeof(Produto), 1, file) == 0){
        printf("Código inválido!\n");
        return;
    }
    
    printf("Descrição: %s\nQuantidade Em Estoque: %d\n Mínimo em estoque: %d\n Preço de Venda: %.2f\n", prod.descricao, prod.quantidadeEstoque, prod.minimoEstoque,prod.precoVenda);
}

void buscaPorDescricao(FILE * file){
    Produto prod;
    char descricao [40];
    printf("Digite palavra chave a ser buscada:\n");
    scanf("%s", descricao);
    fread(&prod, sizeof(Produto), 1, file);
    while(!feof(file)){
        if(strstr(prod.descricao, descricao)){
            printf("%s\n", prod.descricao);
        }
        fread(&prod, sizeof(Produto), 1, file);
    }
}

void geraRelatorio(FILE * file){
    Produto prod;
    fread(&prod, sizeof(Produto), 1, file);
    while(!feof(file)){
        if(prod.quantidadeEstoque < prod.minimoEstoque){
            printf("Descrição: %s\nQuantidade Em Estoque: %d\n Mínimo em estoque: %d\n Preço de Venda: %.2f\n\n", prod.descricao, prod.quantidadeEstoque, prod.minimoEstoque,prod.precoVenda);
        }
        fread(&prod, sizeof(Produto), 1, file);
    }
}