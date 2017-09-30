/*
http://www.wolframalpha.com/

LU decomposition of {Matriu desitjada}

Pero podem fer una multiplicacio // tambe testejat amb l'ajut del wolfram
{{1,0,0,0},{2,1,0,0},{3,7,1,0},{4,5,11,1}} * {{7,15,8,9},{0,3,7,21},{0,0,30,8},{0,0,0,6}}
=
{
	{	 7,	15,	  8,	  9	},
	{	14,	33,	 23,	 39	},
	{	21,	66,	103,	182	},
	{	28,	75,	397,	235	}
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ShowMatrixDouble ( int, double** ); /* Aparentment funciona correctament */
double ** ReserveMemorieMatrixDouble ( int ); /* Ara que entenc com funciona el malloc, esta ben fet, comprovat que els digits estiguin be */
void freeMemorieMatrixDouble ( int, double ** ); /* Allibera correctament, tot i fer la trampeta..., potser millor fer un for... */
double ** RandomGenerateMatrixDouble ( int ); /* funciona adecuadament, necessita del srand ( time ( NULL ) ) */
double ** ReadGenerateMatrixDouble ( int ); /* funciona adecuadament, llegeix el que li demanes */

void ProducteLU ( int, double **, double ** ); /* nomes he fet un test, po d'una matriu 4x4, aixi que espero i desitjo que realment funciona ;) */

void test ( void )
{
	int i, j, n;
	double **A;

	srand ( time ( NULL ) ); /* permet generar nombres aleatoris */

	n = 4;
	A = ReserveMemorieMatrixDouble ( n );
	for ( i = 0; i < n; i++ )
		for ( j = 0; j < n; j++ )
			A[i][j] = i*n + j%n;

	ShowMatrixDouble ( n, A );
	freeMemorieMatrixDouble ( n, A );
}

int main ( int argc, char *argv[] )
{
	int n;
	double **A, **b;
	clock_t total_t;
	test ();

	scanf ( "%d", &n ); /* aparentment funciona, m'agradaria descobrir com funciona el scanf */

	A = ReadGenerateMatrixDouble ( n );
	b = ReserveMemorieMatrixDouble ( n );

	total_t = clock(); /* http://www.tutorialspoint.com/c_standard_library/c_function_clock.htm */
	
	ProducteLU ( n, A, b );

	total_t = clock () - total_t;
	printf( "Total time taken by CPU: %.30lf Seconds\n%d\n", ((double )total_t)/CLOCKS_PER_SEC, (int)total_t );

	ShowMatrixDouble ( n, A );
	printf ( "Resultat\n\n" );
	ShowMatrixDouble ( n, b );
freeMemorieMatrixDouble ( n, A );
freeMemorieMatrixDouble ( n, b );
return 0;
}
/* unsigned long n = strtoul("29E94B25", NULL, 16); */



void ShowMatrixDouble ( n, a )
	int n; /* tamany de la matriu M_{nxn} */
	double **a; /* matriu que se vol mostrar */
{
	int i, j;
	for ( i = 0; i < n; i++ )
	{
		for ( j = 0; j < n; j++ )
			printf ( "%11.3e", a[i][j] ); /* 11 = 1 espai separacio + (-) + show + . + 3 decimals + 4 exp */
		printf ( "\n" );
	}
}
double ** ReserveMemorieMatrixDouble ( n )
	int n; /* tamany de la matriu M_{nxn} */
{
	int i;
	double **o;
	o = ( double ** ) malloc ( n * sizeof ( double * ) );
	if ( o == NULL ) { printf ( "No ha pogut reservar memoria!!\nn = %d\n", n ); exit ( 1 ); }
	for ( i = 0; i < n; i++ )
	{
		o[i] = ( double * ) malloc ( n * sizeof ( double ) );
		if ( o[i] == NULL ) { printf ( "No ha pogut reservar memoria!!\nn = %d\ni = %d\n", n, i ); exit ( 1 ); }
	}
return o;
}
void freeMemorieMatrixDouble ( n, M )
	int n;
	double **M;
{
	while ( n-- )
		free ( M[n] );
	free ( M );
}
double ** RandomGenerateMatrixDouble ( n )
	int n;
{
	int i, j;
	double **a;
	a = ReserveMemorieMatrixDouble ( n );
	for ( i = 0; i < n; i++ )
		for ( j = 0; j < n; j++ )
			a[i][j] = ( 2.0 *rand () ) / RAND_MAX - 1; /* [-1, 1] */
return a;
}
double ** ReadGenerateMatrixDouble ( n )
	int n;
{
	int i, j;
	double **a;
	a = ReserveMemorieMatrixDouble ( n );
	for ( i = 0; i < n; i++ )
		for ( j = 0; j < n; j++ )
			scanf ( "%lf", &a[i][j] );
return a;
}
void ProducteLU ( n, a, o )
	int n; /* dimencio de A i O */
	double **a; /* matriu LU */
	double **o; /* matriu on se guardara el producte */
{
	int i, j, k;
	for ( i = 0; i < n; i++ ) /* Definim la matriu nula */
		for ( j = 0; j < n; j++ )
			o[i][j] = 0;
	for ( k = 0; k < n; k++ ) /* Ara podem calcular la matriu */
	{
		for ( j = k; j < n; j++ ) /* Fem la suma inicial */
			o[k][j] = a[k][j];
		for ( i = 0; i < k; i++ ) /* Definim la matriu */
			for ( j = i; j < n; j++ )
				o[k][j] += a[k][i] * a[i][j]; /* a[k][i] \in L, a[k][i] \in U */
	}
}
