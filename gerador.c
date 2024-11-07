#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_PRODUTOS 100

typedef struct _Produto Produto;

struct _Produto {
    char descricao[40];
    int quantidadeEstoque;
    int minimoEstoque;
    float precoVenda;
};

void gerarDescricao(char *descricao, int id) {
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

Produto gerarProdutoAleatorio(int id) {
    Produto p;
    gerarDescricao(p.descricao, id);
    p.quantidadeEstoque = rand() % 100 + 1;  // Quantidade em estoque entre 1 e 100
    p.minimoEstoque = rand() % 20 + 1;       // Mínimo em estoque entre 1 e 20
    p.precoVenda = (rand() % 10000) / 100.0; // Preço de venda entre 0.00 e 100.00
    return p;
}

int main() {
    FILE *arquivo;
    Produto p;
    int i;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Abre o arquivo binário para escrita
    arquivo = fopen("estoque.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Gera 100 produtos aleatórios e grava no arquivo
    for (i = 0; i < NUM_PRODUTOS; i++) {
        p = gerarProdutoAleatorio(i);
        fwrite(&p, sizeof(Produto), 1, arquivo);
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Arquivo 'estoque.bin' gerado com %d produtos.\n", NUM_PRODUTOS);

    return 0;
}
