#include <stdio.h>
#include <stdlib.h>
#include "prac1funs.h"
#include <math.h>



int main (void)
{
    
    int n;
    double **L, *b, *x, *y;
    int i, j;
    double norm;
    
    printf (" Doneu la dimensió n =\n");
    scanf ("%d", &n);
    while(n < 1){
      printf ("Dimensió incorrecta, doneu la dimensió n =\n");
        scanf ("%d", &n);  
    }
    L = (double**) malloc (n * sizeof(double*));
    if (L == NULL){
        printf("No hi ha prou memòria");
        exit(1);
    }
    for (i = 0; i < n; i++) {
            L[i] = (double *) malloc (n * sizeof (double));
            if (L[i] == NULL) {
                    printf ("No hi ha prou memoria\n");
                    exit (2);
            }
    }
    
    b = (double*) malloc (n * sizeof(double*));
    x = (double*) malloc (n * sizeof(double*));
    y = (double*) malloc (n * sizeof(double*));

    
    if (b == NULL || x == NULL) {
            printf ("No hi ha prou memoria\n");
            exit (3);
    }
    
    printf (" Doneu els (%d x %d) elements de la matriu A\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf ("%le", &L[i][j]);
        }
    }
    printf("\n");
    printf("Matriu introduïda : \n");
    for (i=0; i<n; i++)
    {
    for(j=0; j<n; j++)
        {
         printf("%16.7e     ", L[i][j]);
        }
    printf("\n");
    }
    
    printf (" Doneu els %d elements del vector b\n", n);
    for (i = 0; i < n; i++)
        scanf ("%le", &b[i]);
    
    printf("Vector resultant matriu inferior (x)\n");
    
    resTinf(n, L, b, x);
    
    
    printf("Ara multipliquem la matriu L pel vector solucio del sistema inferior\n");
    
    prodMatVec (n,n,L,x,y);
    for(i = 0; i<n; i++){
        printf("%16.7e\n", y[i]);
    }
    
    printf("Norma de ||Lx - b||\n");
    for (i=0; i<n; i++){
        y[i] = y[i] - b[i];
    }
    norma2(n, y);
    printf("Norma: %16.7e\n", norm);
    
    
    printf("Transposem la matriu L per a que sigui superior\n");
    double tmp;
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            if (i > j){
                tmp = L[i][j];
                L[i][j] = L[j][i];
                L[j][i] = tmp;
            }
        }
    }
    
    printf("Vector resultant matriu superior\n");
    
    
    resTsup(n, L, b, x);
    
    for(i=0; i<n; i++){
        
        printf("%16.7e\n", x[i]);
    }
    
    printf("Ara multipliquem la matriu L pel vector solucio del sistema superior\n");
    
    prodMatVec (n,n,L,x,y);
    
    printf("Norma de ||Lx - b||\n");
    for (i=0; i<n; i++){
        y[i] = y[i] - b[i];
    }
    norma2(n, y);
    printf("Norma: %f\n", norm);
    
    free(x);
    free(y);
    free(b);
    for (i = 0; i < n; i++) {
        free(L[i]);
    }
    free(L);
    
}

