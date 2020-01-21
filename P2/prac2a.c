#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac2funs.h"


int main(void){
    
    
    double tol, x;
    int iters, newton_result;
    double *sol = malloc(sizeof(double*));
    
    printf("Dóna la tolerància: \n");
    scanf("%le", &tol);
    printf("Indica el nombre d'iteracions màxim: \n");
    scanf("%d", &iters);
    printf("Proporciona una x inicial per a Newton: \n");
    scanf("%le", &x);
    newton_result = newton(x, sol, tol, iters);
    if (newton_result < 1){
        printf("La solució és: %16.7e\n", *sol);
        free(sol);
        return newton_result;
    }
    printf("Solució no trobada\n");
    return newton_result;
    
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
    
    return pow(x,2) + sin(x) - acos(-1); 
    
}

double df(double x){
    
    return 2*x + cos(x);
    
}
