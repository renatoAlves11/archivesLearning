/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define NUM_PRODUTOS 100

typedef struct Produto{
   char descricao[40];
  int quantidadeEstoque, minimoEstoque;
  float precoVenda;
} Produto;

void IncluirProduto(Produto* p, FILE * arquivo);
void RegistrarVenda (int codProd, int qtd, FILE * arquivo);
void BuscaCodigo(int codProd, FILE * arquivo);
void BuscaDescricao(int codProd, FILE * arquivo);
void RelatorioMinimo(FILE* arq);

/*void gerarDescricao(char *descricao, int id) 
{
    char *materiais[] = {
        "Cimento", "Tijolo", "Areia", "Brita", "Tubo PVC", "Fio elétrico",
        "Parafuso", "Prego", "Rolo de pintura", "Lata de tinta", 
        "Broca", "Martelo", "Chave de fenda", "Serra", "Escada", 
        "Lixa", "Placa de gesso", "Cola", "Silicone", "Verniz"
    };
    char descricaoCompleta[40];
    sprintf(descricaoCompleta, "%s %05d", materiais[rand() % 20], rand() % 10000);
    strcpy(descricao, descricaoCompleta);
}



Produto gerarProdutoAleatorio(int id) 
{
    Produto p;
    gerarDescricao(p.descricao, id);
    p.quantidadeEstoque = rand() % 100 + 1;  // Quantidade em estoque entre 1 e 100
    p.minimoEstoque = rand() % 20 + 1;       // Mínimo em estoque entre 1 e 20
    p.precoVenda = (rand() % 10000) / 100.0; // Preço de venda entre 0.00 e 100.00
    return p;
}*/

int main() 
{
    FILE *arquivo;
    Produto p;
    int i;
    int opc;
    strcpy(p.descricao,"Cimento");
    p.quantidadeEstoque=10;
    p.minimoEstoque=3;
    p.precoVenda=2.99;
    int codProd=2;
    int qtd = 1;
    
    // Inicializa o gerador de números aleatórios
    //srand(time(NULL));

    // Abre o arquivo binário para escrita
    arquivo = fopen("estoque.bin", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
/*
    // Gera 100 produtos aleatórios e grava no arquivo
    for (i = 0; i < NUM_PRODUTOS; i++) {
        p = gerarProdutoAleatorio(i);
        fwrite(&p, sizeof(Produto), 1, arquivo);
    }
*/
   

    printf("Arquivo 'estoque.bin' gerado com %d produtos.\n", NUM_PRODUTOS);
    
    // Menu
    do{
        printf("1- Incluir Produto\n2- Registrar Venda\n3- Buscar Código\n4- Buscar por Descricao\n5- Relatorio\n");
        scanf("%d", &opc);
        switch(opc)
    {
            case 1:
                IncluirProduto(&p, arquivo);
                break;
            case 2:
                RegistrarVenda(codProd, qtd, arquivo);
                break;
            case 3:
                BuscaCodigo(codProd, arquivo);
                break;
            case 4:
            
                break;
            case 5:
            
                break;
            case 0:
                return 0;
                break;
        }
    }while(opc != 0);
    
 // Fecha o arquivo
    fclose(arquivo);
    return 0;
}

void IncluirProduto(Produto *p, FILE * arquivo)
{
    printf("Digite o produto");
    fseek(arquivo, sizeof(Produto), SEEK_END);
    fwrite(&p,sizeof(p),1,arquivo);
    
}

void RegistrarVenda(int codProd, int qtd, FILE * arquivo)
{
    Produto aux;
    fseek(arquivo, codProd*sizeof(Produto),SEEK_SET);
    fread(&aux, sizeof(Produto),1,arquivo);
    if(qtd > aux.quantidadeEstoque)
    {
        printf("deu ruim");
    }
    else
    {
         aux.quantidadeEstoque -= qtd;
        fseek(arquivo, codProd*sizeof(Produto),SEEK_SET);
        fwrite(&aux,sizeof(aux),1,arquivo);
    }
   
    
}

void BuscaCodigo(int codProd, FILE * arquivo)
{
    Produto aux;
     fseek(arquivo, codProd*sizeof(Produto),SEEK_SET);
     fread(&aux, sizeof(Produto),1,arquivo);
     printf("%s %d %d %.2f",aux.descricao,aux.quantidadeEstoque,aux.minimoEstoque,aux.precoVenda);
}

void BuscaDescricao(int codProd, FILE * arquivo){
    
    Produto aux;
    char* ponteiro;
    char descricaoBuscada[40];
    printf("Digite o produto que você queira buscar: \n");
    scanf("%s", descricaoBuscada);
    
    fread(&aux, sizeof(Produto),1,arquivo);
    
    while(!feof(arquivo)){
        ponteiro = strstr(aux.descricao, descricaoBuscada);
        if(ponteiro != NULL){
            printf("%s", aux.descricao);
        }
        fread(&aux, sizeof(Produto),1,arquivo);
    }
    
}
