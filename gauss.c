#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"
#include "organizacao.h"


void pivotear(double **matriz, double *b, int j, int n){
    int max;
    double aux;
    
    max=j;
    for(int i=j; i<n; i++){
        if(matriz[i][j] > matriz[max][j]) {
            max=i;
        }       
    }
    if(max != j){
        for(int x=j; x<n; x++) {
            aux=matriz[max][x]; matriz[max][x]=matriz[j][x]; matriz[j][x]=aux;      
        }
        aux=b[max]; b[max]=b[j]; b[j]=aux;
    }
}

void triangularizacao(int n, double **matriz, double *b, int *cG, int *cS){
    *cG = *cS = 0;
    double m =0 ;
  
    for (int i = 0; i < n; ++i) { 
        pivotear(matriz, b, i, n); 
        //mostrarMatriz(n, matriz, b);
        for (int j = i+1; j<=i+2 && j<n; j++) { //colunas
            if(matriz[j][i]!=0){
                m = (matriz[j][i]/matriz[i][i]);
                *cG = *cS += 1;
            } else {
                m = 0;
            }
            
            for (int k = i; k<n; k++) { //linhas
                if(matriz[i][k]!=0 && m!=0){
                    matriz[j][k] -= (matriz[i][k])*m; //OPERACAO EM A
                    *cG = *cS += 2;
                }
            }
            
            if(b[i]!=0 && m!=0){
                b[j] -= b[i]*m; //OPERACAO EM B
                *cG = *cS += 2;
            }
        }
    }
}

void gauss(int n, double **matriz, double *b, double *xGauss, int *cG){
    //SUBSTITUICAO REGRESSIVA
    if((b[n-1])!=0){
        xGauss[n-1]= b[n-1]/matriz[n-1][n-1];
        *cG += 1;
    }else{
        xGauss[n-1]=0;
    }

    double soma;
    for(int i=n-2; i>=0; i--){ 
        soma = b[i];
        for(int j=i+1; j<n; j++){
            if(matriz[i][j]!=0 && xGauss[j]!=0){           
                soma -= matriz[i][j]*xGauss[j];
                *cG += 2; 
            }
        }
        if(soma!=0){
            xGauss[i] = soma/matriz[i][i];
            *cG += 1;
        }else{ 
            xGauss[i] = 0;
        }
    }
}