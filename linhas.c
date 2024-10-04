#include<stdio.h>

int main(int argc, char** argv){
	FILE *entrada;
	int c, qtdLinhas = 0;
	entrada = fopen(argv[1], "rb");
	c = fgetc(entrada);
	while (c!=-1){
	if (c == 10){
		qtdLinhas++;
		}
	c = fgetc(entrada);	
	}
	fclose(entrada);
	printf("%d linhas", qtdLinhas);
	return 0;
}
