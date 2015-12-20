#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-15

double fun(double *x);
double der( double *x);
int newton(double* x);

double M,e=1;

int main(void){
	int niter=0,i;
	double x; // es la E buscada
	for(i=0; i<=190;i++){
	  M=0.001+i*1.e-4; 
	  x=M;
	  while(niter!=30 && fabs(fun(&x))>PREC){ 
	    if(newton(&x)!=0){
	      break;
	    }
	    niter++;
	  }
	  printf("%lf %10lf%4d \n", M, x, niter);
	  niter=0;
	}
	return 0;
}
	
	

double fun( double *x){
  return(M-*x-e*sin(*x));
}

double der( double *x){
  return(-1-e*cos(*x));
}

int newton(double *x){
  if(fabs(der(x))>PREC){
    *x=*x-(fun(x)/der(x));
    return 0;
  }
  else return -1;
}




