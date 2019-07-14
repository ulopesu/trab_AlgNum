#ifndef GAUSS_H_
#define GAUSS_H_

    void triangularizacao(int n, double **matriz, double *b, int *cG, int *cS);
    void pivotear(double **matriz, double *b, int j, int n);
    void gauss(int n, double **matriz, double *b, double *xGauss, int *cG);

#endif /* GAUSS_H_ */

