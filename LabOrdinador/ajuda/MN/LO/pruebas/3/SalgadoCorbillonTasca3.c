/*Marcos Salgado Corbillon
NIUB:14953956 */

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double horner(double z, double *x, double *c, int n);
int difdiv(double *x,double *f, int n);
void nodes (int n, double a, double b, double *x);
double funcio(double x, int niub);

int main(void){
	int i,j, niub;
	double *x,*f;
	scanf("%d", &niub);
	x=(double*)calloc(7,sizeof(double));
	f=(double*)calloc(7,sizeof(double));
	for(i=0;i<7;i++){
	  nodes(i,0,1,x);
	  for(j=0;j<=i;j++){
		f[j]=funcio(x[j],niub);
	  }
	  if(difdiv(x,f,i)!=0){
	    continue;
	  }
	  printf("%d  ",i);
	  printf("%lf",horner(0,x,f,i));
	  printf("\n");
	}printf("\n");
	return 0;
}

void nodes (int n, double a, double b, double *x){
	int i;
	for(i=0;i<=n;i++){
		x[i]=(1./2)*(1.+cos(((2*i+1.)/(n+1.))*M_PI/2));
	}
}   
int difdiv(double *x,double *f, int n){
	int i,k;
	for(k=1;k<=n;k++){
		for(i=n;i>=k;i--){
			if(fabs((x[i]-x[i-k]))<1.e-12){
				printf("ERROR \n");
				return -1;
			}
			f[i]=(f[i]-f[i-1])/(x[i]-x[i-k]);
		}
	}return 0;
}

double horner(double z, double *x, double *c, int n){
	double p=c[n];
	int i;
	for(i=n-1;i>=0;i--){
		p=p*(z-x[i])+c[i];
	}
	return p;
}
