// Teresina = 221100
// Curitiba = 410690

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 2048

// index,CODMUNRES,data_nasc,PESO,SEMAGESTAC,adeq_peso_id_gestac,SEXO,IDANOMAL,RACACOR,ESCMAEAGR1,ESTCIVMAE,IDADEMAE,CONSULTAS,PARTO,STTRABPART,KOTELCHUCK,APGAR5,TPROBSON

struct DadosNascimento {
    int index;
    int CODMUNRES;
    char data_nasc[11];
    int PESO;
    int SEMAGESTAC;
    float adeq_peso_id_gestac;
    int SEXO;
    int IDANOMAL;
    int RACACOR;
    int ESCMAEAGR1;
    int ESTCIVMAE;
    int IDADEMAE;
    int CONSULTAS;
    int PARTO;
    int STTRABPART;
    int KOTELCHUCK;
    int APGAR5;
    int TPROBSON;
};

void separaData(char* data, int *dia, int *mes, int *ano)
{
    *ano = atoi(strtok(data,"-"));
    *mes = atoi(strtok(NULL,"-"));
    *dia = atoi(strtok(NULL,"-"));
}

float totalPesoTeresina = 0;
float totalPesoCuritiba = 0;
int contadorTeresina = 0;
int contadorCuritiba = 0;
int ano = 2015;

void processa(struct DadosNascimento* dn) {
    int dia, mes, meuAno;
    separaData(dn->data_nasc, &dia, &mes, &meuAno);

    //printf("%d %d %d %d\n",dn->CODMUNRES, dia, mes, ano);
    
    if(dn->CODMUNRES == 221100){
        contadorTeresina++;
        totalPesoTeresina += dn->PESO;
    }
    else if(dn->CODMUNRES == 410690){
        contadorCuritiba++;
        totalPesoCuritiba += dn->PESO;
    }
}


int main()
{
    char *prox = NULL;
    int lc = 0;
    static char buffer[MAX];
    struct DadosNascimento dn;
    char* linha[18];
    int i;
    float mediaTeresina, mediaCuritiba;
    FILE *f = fopen("sinasc.csv","r");
    fgets(buffer,MAX,f);
    fgets(buffer,MAX,f);
    while(!feof(f)) {
        linha[0] = strtok_r(buffer,",\n",&prox);
        for(i=1; i<18; i++) {
            linha[i] = strtok_r(NULL,",\n",&prox);
            if(linha[i]==NULL) {
                linha[i]="";
            }
        }
        dn.index = atoi(linha[0]);
        dn.CODMUNRES = atoi(linha[1]);
        strcpy(dn.data_nasc,linha[2]);
        dn.PESO = atoi(linha[3]);
        dn.SEMAGESTAC = atoi(linha[4]);
        dn.adeq_peso_id_gestac = atof(linha[5]);
        dn.SEXO = atoi(linha[6]);
        dn.IDANOMAL = atoi(linha[7]);
        dn.RACACOR = atoi(linha[8]);
        dn.ESCMAEAGR1 = atoi(linha[9]);
        dn.ESTCIVMAE = atoi(linha[10]);
        dn.IDADEMAE = atoi(linha[11]);
        dn.CONSULTAS = atoi(linha[12]);
        dn.PARTO = atoi(linha[13]);
        dn.STTRABPART = atoi(linha[14]);
        dn.KOTELCHUCK = atoi(linha[15]);
        dn.APGAR5 = atoi(linha[16]);
        dn.TPROBSON = atoi(linha[17]);
        processa(&dn);
 
        fgets(buffer,MAX,f);
        
    }
    mediaTeresina = totalPesoTeresina/contadorTeresina;
    mediaCuritiba = totalPesoCuritiba/contadorCuritiba;
    
    printf("A média de peso em Teresina é: %.2f", mediaTeresina);
    printf("A média de peso em Curitiba é: %.2f", mediaCuritiba);
    
    
    fclose(f);
    return 0;
}
