#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac2funs.h"


int main(void){
    
    
    double tol, M, h, x;
    int iters, newton_result, i, m;
    double *sol = malloc(sizeof(double*));
    
    printf("Dóna la tolerància: \n");
    scanf("%le", &tol);
    printf("Indica el nombre d'iteracions màxim: \n");
    scanf("%d", &iters);
    printf("Proporciona una M per a l'interval [-M, M] : \n");
    scanf("%le", &M);
    m = 1e2;
    h = 2*M/m; /*calculem el pas */
    for (i = 0; i<m; i++){
        x = -M + i * h;
        newton_result = newton(x, sol, tol, iters);
        if (newton_result < 1){
            printf("Iteració: %d || Solució : %16.7e || Convergeix\n", i, *sol);
        
        }else{
           printf("Iteració: %d || NO Convergeix\n", i); 
        }
    }   
    free(sol);
    return 0;
}


int newton(double x, double *sol, double tol, int iter){
    
    double x0, nextx, current_fx, derivative_fx;
    int current_iters = 0;
    x0 = x;
    
    while(iter > current_iters){
        derivative_fx = df(x0);
        if(fabs(derivative_fx) < tol)
            return 1;
        current_fx = f(x0);
        nextx = x0 - (current_fx / derivative_fx);
        if (fabs(nextx - x0) < tol || fabs(current_fx) < tol){
            *sol = nextx;
            return 0;
        }
        x0 = nextx;
        current_iters++;
        
    }

    return 1;
    
    
}

double f(double x){
    
    return pow(x,2) - 1;
    
}

double df(double x){
    
    return 2*x;
    
}
