#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double horner(double z, double *x, double *c, int n);
int difdiv(double *x,double *f, int n);
void nodes (int n, double a, double b, double *x);
double fun(double z);

int main(void){
	int n=7,m,i,k;
	double a,b,max=0;
	double *x,*y,*f,*g,*z;
	scanf("%d", &n);
	scanf("%lf %lf", &a, &b);
	x=(double*)calloc(n+1,sizeof(double));
	nodes(n,a,b,x);
	f=(double*)calloc(n+1,sizeof(double));
	for(i=0;i<=n;i++){
		scanf("%lf", &f[i]);
	}
	difdiv(x,f,n);
	printf("%lf  \n",horner(3.5,x,f,n));
	z=(double*)calloc(7000,sizeof(double));
	for(k=0;k<7001;k++){
	  z[i]=horner(k*0.001,x,f,n)
	}
	for(k=0;k<7001;k++){
	  if(z[i]>max){
	    max=z[i];
	  }
	} 
	print("%lf \n", max);
	/*scanf("%d", &m);
	y=(double*)calloc(m+1,sizeof(double));
	nodes(m,a,b,y);
	g=(double*)calloc(m+1,sizeof(double));
	for(i=0;i<=m;i++){
		g[i]=horner(y[i],x,f,n);
	}
	difdiv(y,g,m);
	printf("%lf  ",horner(0.5,y,g,m));
	*/
	
	/*
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
	*/
}

double fun(double z){
	return (sin(z));
}

void nodes (int n, double a, double b, double *x){
	int i;
	for(i=0;i<8;i++){
	  x[i]=i;
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
