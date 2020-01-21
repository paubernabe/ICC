#include <stdio.h>
#include <stdlib.h>
#include "prac1funs.h"
#include <math.h>

int ldlt(int n, double **A, double tol);

int main (void)
{
    
    int n, i, j, ret;
    double **L, **Lcopy;
    double *b, *x, *y, *z;
    double tole = 0.1;
    double norm;

    printf (" Doneu la dimensió n =\n");
    scanf ("%d", &n);
    while(n < 1){
      printf ("Dimensió incorrecta, doneu la dimensió n =\n");
        scanf ("%d", &n);  
    }
    b = (double*)malloc(n * sizeof(double*));
    x = (double*)malloc(n * sizeof(double*));
    y = (double*)malloc(n * sizeof(double*));
    z = (double*)malloc(n * sizeof(double*));



    if(b==NULL || x==NULL || y==NULL || z==NULL){
       printf("No hi ha prou memòria");
       exit(1); 
    }
    L = (double**) malloc (n * sizeof(double*));
    Lcopy = (double**) malloc (n * sizeof(double*));
    if (L == NULL || Lcopy == NULL){
        printf("No hi ha prou memòria");
        exit(1);
    }
    for (i = 0; i < n; i++) {
        L[i] = (double *) malloc (n * sizeof (double));
        Lcopy[i] = (double *) malloc (n * sizeof (double));
        if (L[i] == NULL || Lcopy[i] == NULL) {
                printf ("No hi ha prou memoria\n");
                exit (2);
            }
    }
    
    printf (" Doneu els (%d x %d) elements de la matriu simetrica A\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf ("%lf", &L[i][j]);
            Lcopy[i][j] = L[i][j];
            if (L[i][j] != L[j][i] && i > j){
                printf("Matriu no simètrica \n");
                return 1;
            }
        }
    }
    printf (" Doneu els (%d) elements del vector b\n", n);
    for(i = 0; i<n; i++){
        scanf ("%le", &b[i]);
    }
    
    ret = ldlt(n, L, tole);
    if (ret == 1){
        printf("No s'ha pogut descomposar la matriu\n");
        exit(1);
    }
    
    printf("Matriu després de LDLt : \n");
    for (i=0; i<n; i++)
    {
    for(j=0; j<n; j++)
        {
         printf("%16.7e     ", L[i][j]);
        }
    printf("\n");
    }
    printf("Resolem primer de tot la diagonal inferior\n");
    resTinf(n, L, b, x); 
    printf("Seguidament resolem la diagonal\n");
    for (i=0; i<n; i++){    
        y[i] = x[i]/L[i][i];
    }
    printf("Per últim resolem la diagonal superior\n");
    resTsup(n, L, y, z); 
    
    printf("VECTOR SOLUCIÓ: \n");
    for (i=0; i<n; i++){
        
        printf("%16.7e\n", z[i]);
        
    }
    
    printf("Multipliquem L*vector solució i ho emmagatzemem a y\n");
    prodMatVec (n,n,Lcopy,z,y);

    printf("NORMA VECTOR SOLUCIÓ LDLT ||L*vector solució - b|| \n");
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
        free(L[i]);
        free(Lcopy[i]);
    }
    free(L);
    free(Lcopy);
    
    
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

    
    
    
    
    
