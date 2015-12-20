/*Marcos Salgado Corbillón 


*/

#include<stdio.h>
#include<stdlib.h>
double*prodMatTriVect(int n, double *a, double *b,double *c, double *w);
int main(void){
	int n,i;
	double *a,*b,*c,*u,*mu;
	FILE*entrada;
	char nom[50];
	printf("nom del fitxer d'entrada:\n");
	scanf("%s",nom);
	entrada=fopen(nom,"r");
	fscanf(entrada,"%d", &n);
	a=(double*)malloc(n*sizeof(double));
        if(a==NULL){
                printf("memoria insuficient");
                exit(1);
	}b=(double*)malloc(n*sizeof(double));
        if(b==NULL){
                printf("memoria insuficient");
                exit(2);
        }c=(double*)malloc((n-1)*sizeof(double));
        if(c==NULL){
                printf("memoria insuficient");
                exit(3);
        }u=(double*)malloc(n*sizeof(double));
        if(u==NULL){
                printf("memoria insuficient");
                exit(4);
        }fscanf(entrada,"%lg %lg", &a[0],&c[0]);
	for(i=1;i<(n-1);i++){
		fscanf(entrada, "%lg %lg %lg", &b[i], &a[i], &c[i]);
	}fscanf(entrada, "%lg %lg", &b[n-1], &a[n-1]);
	for(i=0;i<n;i++){
		fscanf(entrada, "%lg", &u[i]);     
	}mu=prodMatTriVect(n,a,b,c,u);
	printf("vector producte:\n");
	for(i=0;i<n;i++){
		printf("%12.3e",mu[i]);
	}printf("\n");
	free(a);
	free(b);
	free(c);
	free(u);
	free(mu);
	fclose(entrada);
	return 0;
}double*prodMatTriVect(int n, double *a, double *b,double *c, double *w){
	int i;
	double*mu;
	mu=(double*)malloc(n*sizeof(double));
        if(mu==NULL){
                printf("memoria insuficient");
                exit(5);
	}mu[0]=a[0]*w[0]+c[0]*w[1];
	for(i=1;i<(n-1);i++){
		mu[i]=b[i]*w[i-1]+a[i]*w[i]+c[i]*w[i+1];
	}mu[n-1]=b[n-1]*w[n-2]+a[n-1]*w[n-1];
	return(mu);
}
