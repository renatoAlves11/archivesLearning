#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Registro {
    int qtd;
    char palavra [11];
} Registro;

typedef struct _No{
    Registro reg;
    struct _No * pointer;
} No;

typedef No * noPtr;

int inLista(char * str, noPtr aux){
    if(aux == NULL){
        return 0;
    }
    while(aux != NULL){
        if(strcmp(aux->reg.palavra, str) == 0){
            aux->reg.qtd++;
            return 1;
        }
        aux = aux->pointer;
    }
    return 0;
}

void addReg(char * str, noPtr* head){
    noPtr aux = *head;
    noPtr p = (noPtr) malloc(sizeof(No));
    strcpy(p->reg.palavra, str);
    p->reg.qtd = 1;
    p->pointer = NULL;
    if(aux == NULL){
        *head = p;
    }
    else{
        while(aux->pointer != NULL){
            aux = aux->pointer;
        }
        aux->pointer = p;
    }
}

void sortLista(noPtr * head){
    if(head == NULL){
        return;
    }
    noPtr aux1 = *head;
    noPtr aux2;
    Registro troca;
    while (aux1 != NULL){
        aux2 = aux1->pointer;
        while (aux2 != NULL){
            if(aux2->reg.qtd > aux1->reg.qtd){
                strcpy(troca.palavra,aux2->reg.palavra);
                troca.qtd = aux2->reg.qtd;
                strcpy(aux2->reg.palavra,aux1->reg.palavra);
                aux2->reg.qtd = aux1->reg.qtd;
                strcpy(aux1->reg.palavra,troca.palavra);
                aux1->reg.qtd = troca.qtd;
            }
            aux2 = aux2->pointer;
        }
        aux1 = aux1->pointer;
    }

}

void liberaLista(noPtr head){
    noPtr temp;
    while(head != NULL){
        temp = head;
        head = head->pointer;
        free(temp);
    }
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r");
    noPtr head = NULL;
    char * buffer = (char*) malloc(8192);
    if(file == NULL){
        printf("Arquivo não pôde ser aberto\n");
    }
    fgets(buffer, 8192, file);
    char * str = strtok(buffer, " ");
    while(str != NULL){
        if(inLista(str, head) == 0){
            addReg(str, &head);
        }
        str = strtok(NULL, " ");
    }
    sortLista(&head);
    FILE * fileDest = fopen("destino.txt", "w");
    noPtr aux = head;
    while(aux != NULL){
        fwrite(aux->reg.palavra, 11, 1, fileDest);
        fwrite(&aux->reg.qtd, 4, 1, fileDest);
        printf("%s %d\n", aux->reg.palavra, aux->reg.qtd);
        aux = aux->pointer;
    }

    liberaLista(head);

    fclose(fileDest);
    fclose(file);
    return 0;
}

//fgets: função que lê uma string, ele para de lê quando encontra uma quebra de linha(\n). Se não tiver uma quebra de linha, quer dizer que o fgets não conseguiu ler a linha toda.
//fgets(buffer, tamanho do buffer, arquivo)