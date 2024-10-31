#include<stdio.h>



//int (*X)(int, int); X = soma; X é uma variável que recebe funções que recebem 2 inteiros e retornam 1; nesse caso, X é a função soma;

//int compara (const void * e1, const void * e2); assinatura imutavel

//void * = ponteiro para qualquer coisa, castavel(type cast) 

//qsort(e, qtd, sizeof(Endereco),compara) - e = ponteiro; qtd = qtd objetos; sizeof; função de comparação

int soma (int a, int b){
	return a+b;
}

int main(){
    int (*X)(int,int);
    X = soma;
    printf("%d", X(10,10));
    return 0;
}
