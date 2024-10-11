#include <stdio.h>
#include <string.h>

#pragma pack(1) //compilador arredonda tamanho de valores para tamanho das palavras da memoria
//pragma pack garante a utilização de (x) bytes por um dado, sem a utilização extra de memória pelo compilador
//eof é uma LEITURA FRUSTRADA

//ftell - mostra valor da cabeça de leitura do arquivo

//fseek - { SEEK_SET: início do arquivo;
	  //SEEK_CUR: posição atual do arquivo
	  //SEEK_END: fim do arquivo}
	  //altera valor da cabeça de leitura do arquivo

typedef struct _Pessoa Pessoa;

struct _Pessoa{
	int id;
	char nome[15];
	int idade;
	float peso;
	};

int main(){
	FILE* file;
	Pessoa p, b;
	p.id =12332;
	strcpy(p.nome, "Renato");
	p.idade = 19;
	p.peso = 74.2;
	file = fopen("texto.dat", "wb+");
	fwrite(&p, sizeof(Pessoa), 1, file);
	fseek(file, 0, SEEK_SET);
	fread(&b, sizeof(Pessoa), 1, file);
	printf("%ld\n", ftell(file));
	fclose(file);
	return 0;
}
