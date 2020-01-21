/*  Calcul d'una successio en precisio simple  fixats a , b , x0  */
#include <stdio.h>
#include <math.h>
/*
 * Compilar arxiu 
 * gcc -c file.c -ansi -pedantic -O -Wall
 * gcc file.o..... -o programa.exe -lm
 */
int main ( void ) {
	int n;
	double a, b, x0, y0, x1, y1, t, aux0, aux1 ;
	/*a = 1.f;
	b = 1.f;
	x0 = 0.3f;
	aux0 = x0 / a;
    */
    scanf ("%lf %lf %lf" ,&a ,&b ,& x0 );
    aux0 = x0 / a;
    if ( fabs ( aux0 ) > 1.){
        printf (" No es pot fer l ’ arrel quadrada \n" );
        return 1;
    }   
	y0 = b * sqrt (1.f - aux0 * aux0);
	aux1 = y0 / b ;
	printf ("%3s %18s\n", "#n", "t");
	t = aux0 * aux0 + aux1 * aux1;
	printf ("%3d %18.6e\n", 0, t);
	for (n = 1; n <= 60; n++) {
		aux0 = x0 / a;
		aux1 = y0 / b;
		x1 = 2.f * x0 * y0 / b ;
		y1 = b * (aux0 * aux0 - aux1 * aux1);
		aux0 = x1 / a ;
		aux1 = y1 / b ;
		t = aux0 * aux0 + aux1 * aux1 ;
		printf ("%3d %18.6e\n", n, t);
		x0 = x1 ;
		y0 = y1 ;
	}
	return 0;
}

/* RESPOSTES
 * 
 * 3: Quan enlloc de float, posem double obtenim una
 * major precisió, ja que tenim 8 Bytes(més espai que abans) per emmagatzemar 
 * el nombre
 * 
 * 
 */

