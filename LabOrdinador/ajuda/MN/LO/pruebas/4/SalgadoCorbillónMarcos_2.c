#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-15

double fun(double *x);
double der( double *x);
int newton(double* x);

double M,e;

int main(void){
      int niter=0,i,j;
      double x[191]; // es la E buscada
      e=0;
      for(i=0; i<=190;i++){
	M=0.001+i*1.e-4; 
	x[i]=M;
	while(niter!=30 && fabs(fun(&x[i]))>PREC){ 
	  if(newton(&x[i])!=0){
	    break;
	  }
	  niter++;
	}
	niter=0;
      }
      for(j=1;j<1000;j++){
	e=j*1.e-3;
	for(i=0; i<=190;i++){
	  M=0.001+i*1.e-4; 
	  while(niter!=30 && fabs(fun(&x[i]))>PREC){ 
	    if(newton(&x[i])!=0){
	      break;
	    }
	    niter++;
	  }
	  niter=0;
	}
      }
      e=1;
      for(i=0; i<=190;i++){
	M=0.001+i*1.e-4; 
	while(niter!=30 && fabs(fun(&x[i]))>PREC){ 
	  if(newton(&x[i])!=0){
	    break;
	  }
	  niter++;
	}
	printf("%lf %10lf%4d \n", M, x[i], niter);
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




