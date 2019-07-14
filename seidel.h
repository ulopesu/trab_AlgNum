#ifndef SEIDEL_H_
#define SEIDEL_H_
#include <stdbool.h>

void seidel(double **matriz, double *b, int n, double *xSeidel, int *cS);
bool terminar(double xi, double x0);


#endif /* SEIDEL_H_ */
