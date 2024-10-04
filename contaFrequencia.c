#include <stdio.h>

int main(int argc, char** argv){
	FILE *entrada;
	int array[256];
	for(int i = 0; i < 256; i++){
		array[i] = 0;
	}
	entrada = fopen(argv[1], "rb");
	int c = fgetc(entrada);
	while (c != -1){
		array[c]++;
		c = fgetc(entrada);
	}
	fclose(entrada);
		for(int i = 0; i < 256; i++){
		printf("Simbolo %3d: Aparece %d vezes\n", i, array[i]);
	}
}
