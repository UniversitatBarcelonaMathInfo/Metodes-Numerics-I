#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double hornerp(double z, double *x, double *c, int n);
double hornerq(double z, double *x, double *c, int n);
int difdivherm(double *x,double *f, int n);
void nodes (int n, double a, double b, double *x);
double fun(double z);
double der(double z);

int main(void){
	int n,i;
	double a,b,max=0, maxq=0;
	double *x,*f,*z;
	scanf("%d", &n);
	scanf("%lf %lf", &a, &b);
	x=(double*)calloc(2*n+2,sizeof(double));
	nodes(n,a,b,x);
	f=(double*)calloc(2*n+2,sizeof(double));
	for(i=0;i<=(2*n+1);i+=2){
		f[i]=fun(x[i]);
		f[i+1]=der(x[i]);
	}
	if(difdivherm(x,f,2*n+1)!=0){
	  exit(1);
	}
	z=(double*)calloc(501,sizeof(double));
	z[0]=a;
	z[1]=(b-a)/500;
	for(i=1;i<=500;i++){
		z[i]=z[i-1]+z[1];
	}
	for(i=0;i<=500;i++){
	  if(fabs(fun(z[i])-hornerp(z[i],x,f,2*n+1))>max){
	    max=fabs(fun(z[i])-hornerp(z[i],x,f,2*n+1));
	  }
	}
	for(i=0;i<=500;i++){
	  if(fabs(der(z[i])-hornerq(z[i],x,f,2*n+1))>max){
	    maxq=fabs(der(z[i])-hornerq(z[i],x,f,2*n+1));
	  }
	} 
	for(i=0;i<=500;i++){
	  printf("%lf  ",z[i]);
	  printf("%lf  ",fun(z[i]));
	  printf("%lf  ",der(z[i]));
	  printf("%lf  ",hornerp(z[i],x,f,2*n+1));
	  printf("%lf  ",hornerq(z[i],x,f,2*n+1));
	  printf("%lf  ",fabs(fun(z[i])-hornerp(z[i],x,f,2*n+1)));
	  printf("%lf",fabs(der(z[i])-hornerq(z[i],x,f,2*n+1)));
	  printf("\n");
	}printf("\n");
	//printf("error p: %lf \n", max);
	//printf("error q: %lf \n", maxq);
	return 0;
}

double fun(double z){
	return (sin(z));
}
double der(double z){
	return (cos(z));
}

void nodes (int n, double a, double b, double *x){
	int i;
	x[0]=a;
	x[1]=a;
	x[2]=(b-a)/n;
	x[3]=(b-a)/n;
	for(i=4;i<=2*n;i+=2){
		x[i]=x[i-1]+x[2];
		x[i+1]=x[i-1]+x[2];
	}
}

int difdivherm(double *x,double *f, int m){
	int i,k=1;
	for(i=m-1;i>=k;i-=2){
		if(fabs((x[i]-x[i-k]))<1.e-12){
			printf("ERROR");
			return -1;
		}
		f[i]=(f[i]-f[i-2])/(x[i]-x[i-k]);
	}
	for(k=2;k<=m;k++){
		for(i=m;i>=k;i--){
			if(fabs((x[i]-x[i-k]))<1.e-12){
				printf("ERROR");
				return -1;
			}
			f[i]=(f[i]-f[i-1])/(x[i]-x[i-k]);
		}
	}return 0;
}

double hornerp(double z, double *x, double *c, int n){
	double p=c[n], q=0;
	int i;
	for(i=n-1;i>=0;i--){
		q=q*(z-x[i])+p;
		p=p*(z-x[i])+c[i];
	}
	return p;
}
double hornerq(double z, double *x, double *c, int n){
	double p=c[n], q=0;
	int i;
	for(i=n-1;i>=0;i--){
		q=q*(z-x[i])+p;
		p=p*(z-x[i])+c[i];
	}
	return q;
}
