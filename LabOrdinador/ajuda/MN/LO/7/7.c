#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double horner(double z, double *x, double *c, int n);
int difdiv(double *x,double *f, int n);
void nodes (int n, double a, double b, double *x);
double fun(double z);

int main(void){
	int n,i;
	double a,b,max=0;
	double *x,*f,*z;
	scanf("%d", &n);
	scanf("%lf %lf", &a, &b);
	x=(double*)calloc(n+1,sizeof(double));
	nodes(n,a,b,x);
	f=(double*)calloc(n+1,sizeof(double));
	for(i=0;i<=n;i++){
		f[i]=fun(x[i]);
	}
	difdiv(x,f,n);
	z=(double*)calloc(1000,sizeof(double));
	z[0]=(b-a)/1000;
	for(i=1;i<1000;i++){
		z[i]=z[i-1]+z[0];
	}
	for(i=0;i<1000;i++){
	  if(fabs(fun(z[i])-horner(z[i],x,f,n))>max){
	    max=fabs(fun(z[i])-horner(z[i],x,f,n));
	  }
	} 
	for(i=0;i<1000;i++){
	  printf("%lf  ",z[i]);
	  printf("%lf  ",fun(z[i]));
	  printf("%lf  ",horner(z[i],x,f,n));
	  printf("%lf",fabs(fun(z[i])-horner(z[i],x,f,n)));
	  printf("\n");
	}printf("\n");
	printf("error: %lf \n", max);
	return 0;
}

double fun(double z){
	return (sin(z));
}

void nodes (int n, double a, double b, double *x){
	int i;
	x[0]=a;
	x[1]=(b-a)/n;
	for(i=2;i<=n;i++){
		x[i]=x[i-1]+x[1];
	}
}

int difdiv(double *x,double *f, int n){
	int i,k;
	for(k=1;k<=n;k++){
		for(i=n;i>=k;i--){
			if(fabs((x[i]-x[i-k]))<1.e-12){
				printf("ERROR");
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
