#include <stdio.h>
#include <stdlib.h>
#include "organizacao.h"
#include "gauss.h"
#include "seidel.h"

int main(int argc, char const *argv[]){
    int n, cG, cS;
    double dA, dB, dC, dD, Dp, **matriz, *b, *xGauss, *xSeidel;
    

    pegarValores(&n, &dA, &dB, &Dp, &dC, &dD);
    prepararSistemaLinear(n, dA, dB, Dp, dC, dD, &matriz, &b, &xGauss, &xSeidel);
    

    printf("\n\nn= %d. \ndA= %lf. \ndB= %lf. \ndC= %lf. \ndD= %lf. \nDp= %lf.\n", n, dA, dB, Dp, dD, dC);
    fflush(stdout);
    
    
    //TRIANGULARIZACAO
    triangularizacao(n, matriz, b, &cG, &cS);
    
    //METODOS
    gauss(n, matriz, b, xGauss, &cG);
    
    seidel(matriz, b, n, xSeidel, &cS);
    
    //SAIDA
    mostrarSaida(n, xGauss, cG, xSeidel, cS);
    
    //LIBERAR MEMORIA
    liberarTudo(n, &matriz, &b, &xGauss, &xSeidel);
    return 0;
}