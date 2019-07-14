#include <stdio.h>
#include <stdlib.h>
#include "seidel.h"
#include <math.h>

#define tol 0.00000000001

bool terminar(double xi, double x0){
    double temp=fabs(xi-x0)/fabs(xi);
    if(temp<=tol){
        return true;
    }
    return false;
}


void seidel(double **matriz, double *b, int n, double *xSeidel, int *cS){
    double *xA=(double*)malloc(sizeof(double)*n);
    double soma;
    int contador;

    //VALORES INICIAIS
    for (int i= 0; i < n; i++) {
        if(b[i]!=0){
            xSeidel[i] = b[i]/matriz[i][i];
            *cS += 1;
        }else{
            xSeidel[i]=0;
        }
        xA[i] = 1;
    }
    
    //ITERACOES
    while(true) {
        for (int i = 0; i < n; i++) {
            soma = 0;
            for (int j = 0; j < n; j++) {
                if(i!=j && matriz[i][j]!=0 && xSeidel[j]!=0){
                    soma += matriz[i][j]*xSeidel[j];
                    *cS+=2;
                }
            }

            if(soma==0 && b[i]!=0){
                xSeidel[i] = b[i] / matriz[i][i];
                *cS += 1;
            } else {
                xSeidel[i] = (b[i]-soma) / matriz[i][i];
                *cS += 2;
            }           
        }
       

        //CONFERE SE ACABOU ATRAVES DA TOLERANCIA
        contador = 1;
        for(int i = 0; i < n ; i++) {
            if(terminar(xSeidel[i], xA[i])){
                contador++;
            }else{
                break;
            }     
            if(contador == n){//TRUE = ACABOU
                free(xA);
                return;
            } 
        } 
        
        //ATUALIZA X-ANTIGO
        for(int i = 0; i < n ; i++){
            xA[i] = xSeidel[i];
        }
        
    }
}