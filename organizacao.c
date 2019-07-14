#include <stdio.h>
#include <stdlib.h>
#include "organizacao.h"
#include <math.h>

void pegarValores(int *n, double *dA, double *dB, double *Dp, double *dC, double *dD){

    while (1){
        printf("Insira Dimensao n(>=3):\n");
        fflush(stdout);
        scanf("%d", n);
        if (*n < 3){
            printf("Valor Invalido! n= %d\n", *n);
            fflush(stdout);
        }else{
            break;
        }
    }

    while (1){
        printf("Insira dA(!=0): \n");
        fflush(stdout);
        scanf("%lf", dA);
        if (*dA == 0.0){
            printf("Valor Invalido! dA= 0.\n");
            fflush(stdout);
        }else{
            break;
        }
    }

    while (1){
        printf("Insira dB(!=0): \n");
        fflush(stdout);
        scanf("%lf", dB);
        if (*dB == 0.0){
            printf("Valor Invalido! dB= 0.\n");
            fflush(stdout);
        }else{
            break;
        }
    }
    
    while (1){
        printf("Insira Dp(!=0): \n");
        fflush(stdout);
        scanf("%lf", Dp);
        if (*Dp == 0.0){
            printf("Valor Invalido! Dp= 0.\n");
            fflush(stdout);
        }else{
            break;
        }
    }
    
    while (1){
        printf("Insira dC(!=0): \n");
        fflush(stdout);
        scanf("%lf", dC);
        if (*dC == 0.0){
            printf("Valor Invalido! dC= 0.\n");
            fflush(stdout);
        }else{
            break;
        }
    }

    while (1){
        printf("Insira dD(!=0): \n");
        fflush(stdout);
        scanf("%lf", dD);
        if (*dD == 0.0){
            printf("Valor Invalido! dD= 0.\n");
            fflush(stdout);
        }else{
            break;
        }
    }
}


void prepararSistemaLinear(int n, double dA, double dB, double Dp, double dC, double dD, double ***matriz, double **b, double **xGauss, double **xSeidel){
    
    //ALOCAR E PREENCHER MATRIZ
    double **matrizAux;
    matrizAux = (double**)malloc(sizeof(double*)*n);
    for (int i = 0; i < n; ++i) { 
            matrizAux[i]=(double*)malloc(sizeof(double)*n);
            for (int j = 0; j < n; ++j) {
                    if(i-j==2){
                            matrizAux[i][j]=dA;
                    }else if (i-j==1) {
                            matrizAux[i][j]=dB;
                    }else if (i==j) {
                            matrizAux[i][j]=Dp;
                    }else if (i-j==-2) {
                            matrizAux[i][j]=dD;
                    }else if (i-j==-1) {
                            matrizAux[i][j]=dC;
                    }else{
                            matrizAux[i][j]=0;
                    }
            }
    }
    *matriz = matrizAux;
    
    //ALOCAR E PREENCHER B
    double *bAux;
    bAux = (double*)malloc(sizeof(double)*n);
    double soma;
    for(int i=0; i<n; i++){
        soma = 0;
        for(int j=0; j<n; j++){
            soma += matrizAux[i][j];
        }
        bAux[i] = soma;
    }
    *b = bAux; 
    
    
    //ALOCAR X's
    *xGauss = (double*)malloc(sizeof(double)*n);
    *xSeidel = (double*)malloc(sizeof(double)*n);
    
}

void liberarTudo(int n, double ***matriz, double **b, double **xGauss, double **xSeidel){
    double **matrizAux;
    matrizAux = *matriz;
    
    for (int i = 0; i < n; ++i) { //MOSTRAR MATRIZ
        free(matrizAux[i]);
    }
    
    free(*b);
    free(*xGauss);
    free(*xSeidel);
    free(matrizAux);
    
    *matriz = NULL;
    *b = NULL;
    *xGauss = NULL;
    *xSeidel = NULL;
}

void mostrarMatriz(int n, double **matriz, double *b){
    printf("\n");
    for (int i = 0; i < n; ++i) { //MOSTRAR MATRIZ
        for (int j = 0; j < n; ++j) {
                printf("%.2lf ",matriz[i][j]);
                fflush(stdout);
        }
        printf("  %.2lf\n", b[i]);
        fflush(stdout);
    }
    printf("\n");
}
              
            
void mostrarSaida(int n, double *xGauss, int cG, double *xSeidel, int cS){
    double somaEG, maiorG, somaES, maiorS, somaXG, somaXS;
    double eMaxG, eMedG, *eG;
    double eMaxS, eMedS, *eS;
    eG = (double*) malloc(sizeof(double)*n);
    eS = (double*) malloc(sizeof(double)*n);
    
    //CALCULO DE ERROS
    somaEG = somaES = somaXG = somaXS = 0;
    for(int i = 0; i < n; i++){
        somaXG += xGauss[i];
        somaXS += xSeidel[i];
        
        eG[i] = fabs(xGauss[i]-1.0);
        somaEG+=eG[i];
        
        eS[i] = fabs(xSeidel[i]-1.0);
        somaES+=eS[i];
        
        if(i == 0){
            maiorG = eG[i];
            maiorS = eS[i];
        } 
        if(eG[i] > maiorG){
            maiorG = eG[i];
        }
        if(eS[i] > maiorS){
            maiorS = eS[i];
        }
    }
    eMaxG = maiorG;
    eMedG = somaEG/n;
    
    eMaxS = maiorS;
    eMedS = somaES/n;
    
    
    /*
    //MOSTRAR X
    for(int i=0; i<n; i++){ 
        printf("\nxGauss%d: %lf", i, xGauss[i]);
        printf("\nxSeidel%d: %lf", i, xSeidel[i]);
    }
    */
    
     
    printf("\n\n     ----GAUSS---\n");
    printf("N:%d.\n", n);         //TIRAR NA NA APRESENTACAO
    printf("SomaXG: %lf\n", somaXG); //TIRAR NA NA APRESENTACAO
    printf("Numero de Operacoes: %d\n", cG);
    printf("eMax= %lf\neMed= %lf\n", eMaxG, eMedG);
    
    printf("\n\n     ---SEIDEL---\n");
    printf("N:%d.\n", n);         //TIRAR NA NA APRESENTACAO
    printf("SomaXS: %lf\n", somaXS); //TIRAR NA NA APRESENTACAO
    printf("Numero de Operacoes: %d\n", cS);
    printf("eMax= %lf\neMed= %lf\n", eMaxS, eMedS);
    
   free(eG);
   free(eS);
   return;
}