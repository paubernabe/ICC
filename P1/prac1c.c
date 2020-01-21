#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac1funs.h"

int ldlt(int n, double **A, double tol);

int main (void)
{
    
    int m, n, i, j, r;
    double **A, **At, **AtA;
    double norm;
    double tole = 1.e-15;
    double *b, *x, *y, *z, *Atb;
    
    printf (" Doneu la dimensió m =\n");
    scanf ("%d", &m);
    while(m < 1){
      printf ("Dimensió incorrecta, doneu la dimensió m =\n");
        scanf ("%d", &m);  
    }
    printf (" Doneu la dimensió n =\n");
    scanf ("%d", &n);
    while(n < 1 || n > m){
      printf ("Dimensió incorrecta o major que dimensió m, doneu la dimensió n =\n");
        scanf ("%d", &n);  
    }
    
    b = (double*) malloc (m * sizeof(double));
    Atb = (double*) malloc (n * sizeof(double));
    x = (double*)malloc(n * sizeof(double*));
    y = (double*)malloc(n * sizeof(double*));
    z = (double*)malloc(n * sizeof(double*));



    if(b==NULL || x==NULL || y==NULL || z == NULL){
       printf("No hi ha prou memòria");
       exit(1); 
    }
    A = (double**) malloc (m * sizeof(double*));
    At = (double**) malloc (n * sizeof(double*));
    AtA = (double**) malloc (m * sizeof(double*));

    if (A == NULL || At == NULL || AtA == NULL){
        printf("No hi ha prou memòria");
        exit(1);
    }
    for (i = 0; i < m; i++) {
        A[i] = (double *) malloc (n * sizeof (double));
        if (A[i] == NULL) {
            printf ("No hi ha prou memoria\n");
            exit (2);
        }
    }

    for (i = 0; i < n; i++){
        At[i] = (double *) malloc (m * sizeof (double));
        if (At[i] == NULL) {
            printf ("No hi ha prou memoria\n");
            exit (2);
        }
    }
    
    for(i=0; i<n; i++){
        AtA[i] = (double *) malloc (n * sizeof (double));
        if (AtA[i] == NULL) {
            printf ("No hi ha prou memoria\n");
            exit (2);
        }
  
    }

    
    printf (" Doneu els (%d x %d) elements de la matriu A\n", m, n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf ("%le", &A[i][j]);
            At[j][i] = A[i][j];
        }
    }
    
    printf (" Doneu els (%d) elements del vector b\n", m);
    for (i = 0; i < m; i++) {
        scanf ("%le", &b[i]);
    }

    
    
    printf("Ja podem obtenir la matriu resultant de A * At i el vector resultant de At * b\n");
    
    prodMatMat (n,m,n, A, At, AtA);
    prodMatVec(n,m,At,b,Atb);
    
    r = ldlt(n, AtA, tole);
    if (r == 1){
        printf("No s'ha pogut descomposar la matriu\n");
        exit(1);
    }
    
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf ("%16.7e ", AtA[i][j]);
        }
        printf("\n");
    }
    
    printf("Resolem primer de tot la diagonal inferior\n");
    resTinf(n, AtA, Atb, x); 
    
    printf("Seguidament resolem la diagonal\n");
    for (i=0; i<n; i++){    
        y[i] = x[i]/AtA[i][i];
    }
    
    printf("Per últim resolem la diagonal superior\n");
    resTsup(n, AtA, y, z); 
    
    
    printf("VECTOR SOLUCIO: \n");
    
    for(i=0; i<n; i++){
        
        printf("%16.7e\n", z[i]);
    }
    
    printf("Multipliquem L*vector solució(x*) i ho emmagatzemem a y\n");
    prodMatVec (n,n,A,z,y);
    
    
    printf("NORMA VECTOR SOLUCIÓ LDLT ||A*vector solució - b||: ");
    for(i=0; i<n; i++){
        y[i] = y[i] - b[i];
    }
    norm = norma2(n, y);
    printf("%16.7e\n", norm);
    
    
    free(x);
    free(y);
    free(z);
    free(b);
    
    for (i = 0; i < n; i++) {
        free(A[i]);
        free(At[i]);
        free(AtA[i]);
    }
    free(A);
    free(At);
    free(AtA);
    
    
    
    
}
    

int ldlt(int n, double **A, double tol){
    int i, j, k;
    
    for (k = 0; k < n; k++){
        for (j = 0; j < k; j++){
            A[k][k] -= pow(A[k][j], 2) * A[j][j];
        }
        
        if (fabs(A[k][k]) < tol){
            return 1;
        }
        
        for (i = k + 1; i < n; i++){
            for (j = 0; j < k; j++){
                A[i][k] -= A[i][j] * A[k][j] * A[j][j];
            }
            A[i][k] = A[i][k] / A[k][k];
            A[k][i] = A[i][k];
        }
    }
    return 0;
}
    
    

    

    
    
