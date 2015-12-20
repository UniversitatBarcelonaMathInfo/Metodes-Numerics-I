#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-15

double fun(double *x);
double der( double *x);
int newton(double* x);
int secant(double* x0, double* x1);
int iter(double* x);

double M,e;

int main(void){
	int numitmax,i=0;
	double x;
	scanf("%d", &numitmax); //30
	scanf("%lf", &x);
	while(i!=numitmax && fabs(fun(&x))>PREC){ //buclee per M (+ e)
	    if(newton(&x)!=0){
	      printf("ERROR \n");
	      exit(1);
	    }
	    printf("%lf \n", x);
	    i++;
	}
	return 0;
}
	
	

double fun( double *x){
  //return(*x+*x**x**x); // 1 sol. real: 0 simple
  //return(*x**x+*x**x**x**x); // 1 sol. real: 0 doble 
  //return(*x**x**x-9**x); // 0,+3,-3
  //return(*x+*x**x**x+*x**x**x**x); //0 simple, -1 triple
  return(*x**x**x**x**x**x-
}

double der( double *x){
  //return(1+3**x**x); 
  //return(2**x+4**x**x**x);
  //return(3**x**x-9);
  //return(1+3**x**x+3**x**x**x);
}

int newton(double *x){
  if(fabs(der(x))>PREC){
    *x=*x-(fun(x)/der(x));
    return 0;
  }
  else return -1;
}



int secant(double *x0, double *x1){
  double aux;
  if(fabs(fun(x1)-fun(x0))>PREC){
    aux=*x1;
    *x1=*x1-fun(x1)*(*x1-*x0)/(fun(x1)-fun(x0));
    *x0=aux;
    return 0;
  }
  else return -1;
}
  

  
  
	
	
