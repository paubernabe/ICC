#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "prac2funs.h"

int main(void){
    
    int n = 3;
    int init_cond = 100;
    int iters, i, j, newton_result;
    double *x,*sol;
    double tol, cub, cub2, random_value;
    
    printf("Dóna la tolerància: \n");
    scanf("%le", &tol);
    printf("Indica el nombre d'iteracions màxim: \n");
    scanf("%d", &iters);
    
    cub = 1.0;
    
    x = (double*) malloc (n * sizeof(double));
    sol = (double*) malloc (n * sizeof(double));

    
    if (x == NULL){
        printf("No hi ha prou espai a memòria\n");
        exit(1);
    }
    
    /** inicialitzem srand**/
    srand48((long int)time(NULL));
    
    /* procurem que el cub estigui en l'interval [-cub, cub]*/
    
    if ((int)cub + 1 == 0){
        cub2 = cub*2;
    }
    else{
        cub2 = cub + 1;
    }
    
    /* creem 100 condicions inicials */
    
    for (i = 0; i < init_cond; i++){
        
        for (j=0; j < n; j++){
            random_value = drand48() * -cub2 + cub;
            x[j] = random_value;
        }

        newton_result = newton3(x, sol, tol, iters);
        if(newton_result > 0){
            printf("Condicio nº %d ||Newton NO convergeix (%d) || Solució: \n", i, newton_result);
        }
        else{
            printf("Condicio nº %d || Newton convergeix (%d) || Solució: \n", i, newton_result);

        }
        for (j = 0; j < n; j++){
            printf("%16.7e\n ", sol[j]);
 
        }
        
    }
    
    free(x);
    free(sol);
    
    return 0;
    
}


int newton3(double *x, double *sol, double tol, int iter){
    
    int current_iters = 0;
    int i, j, result;
    int n = 3;
    double *f, **df, **dfT, **dfTdf, *dfTf, *inf, *dig, *nextx;
    
    nextx = (double*) malloc (n * sizeof(double));
    f = (double*) malloc (n * sizeof(double));
    inf = (double*) malloc (n * sizeof(double));
    dig = (double*) malloc (n * sizeof(double));
    dfTf = (double*) malloc (n * sizeof(double));
    if(inf == NULL || dig == NULL || nextx == NULL || f == NULL || dfTf == NULL){
        printf("No hi ha prou espai a memòria\n");
        exit(1);
    }
    
    df = (double**) malloc (n * sizeof(double*));
    dfT = (double**) malloc (n * sizeof(double*));
    dfTdf = (double**) malloc (n * sizeof(double*));
    if (df == NULL || dfT == NULL || dfTdf == NULL){
            printf("No hi ha prou espai a memòria\n");
            exit(1);
    }
    
    for (i = 0; i < n; i++){
        df[i] = (double*) malloc (n * sizeof(double));
        dfT[i] = (double*) malloc (n * sizeof(double));
        dfTdf[i] = (double*) malloc (n * sizeof(double));
        if (df[i] == NULL || dfT[i] == NULL || dfTdf[i] == NULL){
            printf("No hi ha prou espai a memòria\n");
            exit(1);
        }
    }
    
    
    
    while(iter > current_iters){
        
        F(x, f);
        dF(x, df);
        
        /** fem la transposada de df **/
        for(i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                dfT[i][j] = df[j][i];
            }
        }
        prodMatMat(n, n, n, dfT, df, dfTdf);
        prodMatVec(n, n, dfT, f, dfTf);
        
        /* descomposicio LDLT */
        
        result = ldlt(n, dfTdf, 1e-7);
        if(result == 1){
            /* condicio sortida */
            free(nextx);
            free(f);
            free(dfTf);
            free(inf);
            free(dig);
            for(i = 0; i < n; i++){
                free(df[i]);
                free(dfT[i]);
                free(dfTdf[i]);
            }
            printf("No es pot descomposar\n");
            return 1;
        }
        
        /* resolem el sistema*/
        
        /* 1.diagonal inferior */
        
        resTinf(n, dfTdf, dfTf, inf);
        
        /* 2.diagonal */
        
        for (i=0; i<n; i++){    
            dig[i] = inf[i]/dfTdf[i][i];
        }
        
        /* 3.diagonal superior i solucio del sistema */
        
        resTsup(n, dfTdf, dig, sol);
        
        /* xk+1 = xk - sol */
        
        for (i = 0; i < n; i++){
            nextx[i] = x[i] - sol[i];
        }
        if (norma2(n, nextx) - norma2(n, x) < tol || norma2(n, f) < tol){
            

            for(i = 0; i < n; i++){
                sol[i] = nextx[i];
            }

            free(nextx);
            free(f);
            free(dfTf);
            free(inf);
            free(dig);
            for(i = 0; i < n; i++){
                free(df[i]);
                free(dfT[i]);
                free(dfTdf[i]);
        
            }
            return 0;
        }
        
        /* xk+1 serà xk */
        for (i = 0; i < n; i++){
            x[i] = nextx[i];
        }
        
        
        
        current_iters++;
    }
    
    free(nextx);
    free(f);
    free(dfTf);
    free(inf);
    free(dig);
    for(i = 0; i < n; i++){
        free(df[i]);
        free(dfT[i]);
        free(dfTdf[i]);
    }
    
    return 1;
    

}
void F(double *x, double *f){
    
    f[0] = x[0] + x[1] + x[2] - 1;
    f[1] = x[1] + x[2];
    f[2] = pow(x[0], 2) + 0.75 * x[1];
    
}
void dF(double *x, double **df){
    
    df[0][0] = 1 + x[1] + x[2];
    df[0][1] = x[0] + 1 + x[2];
    df[0][2] = x[0] + x[1] + 1;
    
    df[1][0] = 0;
    df[1][1] = x[1] + 1;
    df[1][2] = 1 + x[2];
    
    df[2][0] = 2*x[0] + 0.75 * x[1];
    df[2][1] = pow(x[0], 2) + 0.75;
    df[2][2] = 0;
    
    
        
    

}
