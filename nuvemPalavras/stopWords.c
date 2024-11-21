#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct _Registro{
    int qtd;
    char palavra[11];
} Registro;

int main(){
    FILE* palavras = fopen("palavras.txt", "rb");
    FILE* stopWords = fopen("stopWords.txt", "r");
    FILE* noSWords = fopen("noSWords.txt", "wb");
    char tempWord [11];
    Registro tempReg;
    // fseek(stopWords, 0, SEEK_END);
    // int tam = ftell(stopWords);
    // int sWords [tam/11];
    if(palavras == NULL || stopWords == NULL || noSWords == NULL){
        printf("Erro ao abrir arquivo\n");
        return 0;
    }

    fread(&tempReg, sizeof(Registro), 1, palavras);
    fscanf(stopWords, "%s", tempWord);
    while(!feof(palavras)){
        if(strncmp(tempWord, tempReg.palavra, 11) == 0){
            fscanf(stopWords, "%s", tempWord);
            fread(&tempReg, sizeof(Registro), 1, palavras);
            continue;
        }
        fwrite(&tempReg, sizeof(Registro), 1, noSWords);
        printf("%s\n", tempReg.palavra);
        fread(&tempReg, sizeof(Registro), 1, palavras);
    }


    fclose(palavras);
    fclose(stopWords);
    fclose(noSWords);
    return 0;
}