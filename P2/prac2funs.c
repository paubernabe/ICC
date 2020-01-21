#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac2funs.h"

void resTinf(int n, double **L, double *b, double *x){
    int i,j;
    for (i=0; i<n; i++){
        x[i] = b[i];
        for(j=0; j<i; j++){
            x[i] -= x[j] * L[i][j];
        }
    }
}

void resTsup (int n, double **U, double *b, double *x){
    int i,j;
    for (i=n-1; i>=0; i--){
        x[i] = b[i];
        for(j=n-1; j>i; j--){
            x[i] -= x[j] * U[i][j];
        }
    }
}

void prodMatVec (int m, int n, double **A, double *x, double *y){
    int i,j;
    for (i = 0; i < m; i++){
        y[i] = 0;
        for (j = 0; j < n; j++){
            y[i] += x[j] * A[i][j];
        }
    }
}

void prodMatMat (int m, int n, int p, double **A, double **B, double **C){
    int i, j, k;
    for (i = 0; i < m; i++){
        for (j = 0; j < p; j++){
            C[i][j] = 0;
            for (k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[j][k]; 
            }
        }
    }

}

double norma2 (int n, double *z){
    int i;
    double sum = 0.0;
    for(i=0; i<n; i++){
        sum += pow(z[i], 2);
    }
    
    sum = sqrt(sum);
    return sum;
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




