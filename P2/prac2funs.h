
#include <stdio.h>
#include <stdlib.h>
void resTinf (int n, double **L, double *b, double *x);
void resTsup (int n, double **U, double *b, double *x);
void prodMatVec (int m, int n, double **A, double *x, double *y);
void prodMatMat (int m, int n, int p, double **A, double **B, double **C);
double norma2 (int n, double *z);
int ldlt(int n, double **A, double tol);

/* P2 FUNCTIONS */
int newton(double x, double *sol, double tol, int iter);
double f(double x);
double df(double x);
void F(double *x, double *f);
void dF(double *x, double **df);
int newton3(double *x, double *sol, double tol, int iter);
void srand48(long int seed);
double drand48(void);
