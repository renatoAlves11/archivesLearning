//Integrantes: Beatriz Rangel Cerutti, Milena Caroline da Silva Soares, Pedro Henrique Peixoto do Amaral , Renato Alves de Sousa e Sarah Stephany da Cruz Souza Campos
#include <stdio.h>
#include <string.h>

typedef struct Produto {
    char descricao[40];
    int quantidadeEstoque, minimoEstoque;
    float precoVenda;
} Produto;

void IncluirProduto(Produto p, FILE *arquivo);
void RegistrarVenda (int codProd, int qtd, FILE *arquivo);
void BuscaCodigo(int codProd, FILE *arquivo);
void BuscaDescricao(FILE * arquivo, char descricaoBuscada[40]);
void RelatorioMinimo(FILE* arq);


int main() 
{
    FILE *arquivo;
    Produto p;
    int opc;
    int codProd;
    int qtdVendida;
    char descricaoBuscada[40];
    
    

    // Abre o arquivo binário para escrita
    arquivo = fopen("estoque.bin", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    
    // Menu
    do{
        printf("\nControle de Estoque\n\n1- Incluir Produto\n2- Registrar Venda\n3- Buscar por Codigo\n4- Buscar por Descricao\n5- Relatorio\n6- Sair\nEscolha uma opcao: ");
        scanf("%d", &opc);
        switch(opc) {
          case 1:
              printf("Digite a descricao:\n");
              scanf(" %39[^\n]s", p.descricao);
            
              printf("Digite a quantidade em estoque, quantidade minima em estoque e o preco de venda de cada produto:\n");
              scanf("%d %d %f", &p.quantidadeEstoque, &p.minimoEstoque, &p.precoVenda);
              
              IncluirProduto(p, arquivo);
              break;
          case 2:
              printf("Digite o codigo do produto e a quantidade vendida: \n");
              scanf("%d %d",&codProd, &qtdVendida);
              RegistrarVenda(codProd, qtdVendida, arquivo);
              break;
          case 3:
              printf("Digite o codigo do produto: \n");
              scanf("%d", &codProd);
              BuscaCodigo(codProd, arquivo);
              break;
          case 4:
              printf("Digite a descricao (ou parte dela): \n");
              scanf("%39s", descricaoBuscada);
              BuscaDescricao(arquivo, descricaoBuscada);
              break;
          case 5:
              RelatorioMinimo(arquivo);
              break;
        }
    }while(opc != 6);
    
 // Fecha o arquivo
    fclose(arquivo);
    return 0;
}

void IncluirProduto(Produto p, FILE *arquivo)
{
    fseek(arquivo, 0, SEEK_END);
    fwrite(&p, sizeof(Produto) , 1, arquivo);
}

//Altera a quantidade no estoque de um produto
void RegistrarVenda(int codProd, int qtdVendida, FILE *arquivo)
{
    Produto aux;
    fseek(arquivo, codProd * sizeof(Produto), SEEK_SET); //codProd comeca em 0
    fread(&aux, sizeof(Produto), 1, arquivo);
    if(qtdVendida > aux.quantidadeEstoque) {
        printf("O produto nao tem estoque o suficiente.\n");
    }
    else {
      aux.quantidadeEstoque -= qtdVendida;
      fseek(arquivo, codProd * sizeof(Produto), SEEK_SET);
      fwrite(&aux, sizeof(aux), 1, arquivo);
    }
   
}

//Dado o código do produto(posição no arquivo), exibe os dados desse produto.
void BuscaCodigo(int codProd, FILE *arquivo) {
    Produto aux;
    fseek(arquivo, codProd * sizeof(Produto), SEEK_SET);
    if(fread(&aux, sizeof(Produto), 1, arquivo) > 0) {
        printf("[Descricao]: %s / [Quantidade em estoque]: %d / [Estoque minimo]: %d / [Preco Venda]: %.2f\n", aux.descricao, aux.quantidadeEstoque, aux.minimoEstoque, aux.precoVenda);
    }
    else {
        printf("Codigo inexistente!\n");
    } 
}

//Achar o produto através de seu nome
void BuscaDescricao(FILE *arquivo, char descricaoBuscada[40]){
    rewind(arquivo);
    Produto aux;
    char* ponteiroSubstring;
    int boolAchou = 0;

    while(fread(&aux, sizeof(Produto), 1, arquivo) > 0) {
        ponteiroSubstring = strstr(aux.descricao, descricaoBuscada);
        
        if(ponteiroSubstring) {
            printf("[Descricao]: %s / [Quantidade em estoque]: %d / [Estoque minimo]: %d / [Preco Venda]: %.2f\n", aux.descricao, aux.quantidadeEstoque, aux.minimoEstoque, aux.precoVenda);
            boolAchou = 1;
        }    
    } 
        
    if(feof(arquivo) && boolAchou == 0) {
        printf("O produto com o termo ' %s ' nao existe no estoque atual\n", descricaoBuscada);
    }
}

//Relatório com os produtos abaixo da quantidade mínima de estoque
void RelatorioMinimo(FILE* arquivo){

    Produto aux;
    rewind(arquivo);
    int prodAbaixoMin = 0;
    printf("Relatorio com os produtos abaixo da quantidade minima de estoque: \n");

    while(fread(&aux, sizeof(Produto), 1, arquivo) > 0){
        if(aux.quantidadeEstoque < aux.minimoEstoque){
            printf("[Descricao]: %s / [Quantidade em estoque]: %d / [Estoque minimo]: %d / [Preco Venda]: %.2f\n", aux.descricao, aux.quantidadeEstoque, aux.minimoEstoque, aux.precoVenda);
            prodAbaixoMin = 1;
        }
    }

    if(prodAbaixoMin == 0){
        printf("Nao ha produtos abaixo do estoque minimo atual\n");
    }

}
