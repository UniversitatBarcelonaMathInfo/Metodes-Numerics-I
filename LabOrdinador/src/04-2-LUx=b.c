#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ShowMatrixDouble ( int, double** );
void ShowVectorDouble ( int, double* );
double ** ReservaMemoriaMatrixDouble ( int );
void freeMemoriaMatrixDouble ( int, double ** );
double ** RandomGenerateMatrixDouble ( int );
double ** ReadGenerateMatrixDouble ( int );
void ProducteLU ( int, double **, double ** );

double * ReservaMemoriaVectorDouble ( int );
double * ReadGenerateVectorDouble ( int );

void TriangularInferiorLy_b ( int, double **, double * );
void TriangularSuperiorUx_y ( int, double **, double * );

void SloveLUx_b ( int, double **, double * );
/*
http://www.wolframalpha.com/input/?i={{1%2C0%2C0}%2C{3%2C1%2C0}%2C{7%2C2%2C1}}+*+{{2}%2C{3}%2C{5}}
1 0 0  2    2
3 1 0  3 =  9
7 2 1  5   25

http://www.wolframalpha.com/input/?i={{7%2C11%2C2}%2C{0%2C25%2C13}%2C{0%2C0%2C9}}*{{2}%2C{3}%2C{5}}
7 11  2 2    57
0 25 13 3 = 140
0  0  9 5    45
*/

int main ()
{
	int n;
	double **a, *b;
	clock_t total_t;

	srand ( time ( NULL ) ); /* permet generar nombres aleatoris */

	total_t = clock(); /* http://www.tutorialspoint.com/c_standard_library/c_function_clock.htm */

	scanf ( "%d", &n );
	a = ReadGenerateMatrixDouble ( n );
	b = ReadGenerateVectorDouble ( n );

	ShowMatrixDouble ( n, a );
	ShowVectorDouble ( n, b );

	TriangularInferiorLy_b ( n, a, b );
	ShowVectorDouble ( n, b );

freeMemoriaMatrixDouble ( n, a );
free ( b );
	a = ReadGenerateMatrixDouble ( n );
	b = ReadGenerateVectorDouble ( n );

	ShowMatrixDouble ( n, a );
	ShowVectorDouble ( n, b );

	TriangularSuperiorUx_y ( n, a, b );
	ShowVectorDouble ( n, b );

freeMemoriaMatrixDouble ( n, a );
free ( b );
	scanf ( "%d", &n );
	a = ReadGenerateMatrixDouble ( n );
	b = ReadGenerateVectorDouble ( n );

	ShowMatrixDouble ( n, a );
	ShowVectorDouble ( n, b );

	SloveLUx_b ( n, a, b );
	ShowVectorDouble ( n, b );

	printf( "Total time taken by CPU: %.30lf Seconds\n%d\n", ((double )total_t)/CLOCKS_PER_SEC, (int)total_t );
freeMemoriaMatrixDouble ( n, a );
free ( b );
return 0;
}

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
	printf ( "\n" );
}
void ShowVectorDouble ( n, v )
	int n;
	double *v;
{
	int i;
	for ( i = 0; i < n; i++ )
		printf ( "%11.3e", v[i] );
	printf ( "\n\n" );
}
double ** ReservaMemoriaMatrixDouble ( n )
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
void freeMemoriaMatrixDouble ( n, M )
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
	a = ReservaMemoriaMatrixDouble ( n );
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
	a = ReservaMemoriaMatrixDouble ( n );
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
double * ReservaMemoriaVectorDouble ( n )
	int n;
{
	double *v;
	v = ( double * ) malloc ( n * sizeof ( double ) );
	if ( v == NULL ) exit ( 1 );
return v;
}
double * ReadGenerateVectorDouble ( n )
	int n;
{
	int i;
	double *v;
	v = ReservaMemoriaVectorDouble ( n );
	for ( i = 0; i < n; i++ )
		scanf ( "%le", &v[i] );
return v;
}
void TriangularInferiorLy_b ( n, L, b )
	int n;
	double **L;
	double *b;
{
	int i, j;
	for ( i = 1; i < n; i++ )
		for ( j = 0; j < i; j++ )
			b[i] -= L[i][j] * b[j];
}
void TriangularSuperiorUx_y ( n, U, y )
	int n;
	double **U;
	double *y;
{
	int i, j;
	for ( i = 0; i < n; i++ )
		if ( U[i][i] == 0 )
		{
			printf ( "Error, 0 a la diagonal\n" );
			ShowMatrixDouble ( n, U );
			exit ( 1 );
		}
	for ( i = n -1; i >= 0; i-- )
	{
		for ( j = i +1; j < n; j++ )
			y[i] -= U[i][j] * y[j];
		y[i] /= U[i][i];
	}
}
void SloveLUx_b ( n, a, b )
	int n;
	double **a;
	double *b;
{
	TriangularInferiorLy_b ( n, a, b );
	TriangularSuperiorUx_y ( n, a, b );
}
