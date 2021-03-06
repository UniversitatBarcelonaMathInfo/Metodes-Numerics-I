#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-16

double fun(double *x);
double der( double *x);
int newton(double* x);
int secant(double* x0, double* x1);
int iter(double* x);

double niub=14953956;

int main(void){
	int numitmax=30,i=0;
	double x0,x1;
	scanf("%lf %lf", &x0, &x1);
	while(i!=numitmax && fabs(funcio(x0,niub))>PREC && fabs(funcio(x1,niub))>PREC){
	    if(secant(&x0,&x1)!=0){
	      printf("ERROR \n");
	      exit(1);
	    }
	    printf("%5lf %5lf %5lf %5lf\n", x0, x1, funcio(x0,niub), funcio(x1,niub));
	    i++;
	}
	return 0;
}
	
	

double fun( double *x){
  //return(*x+*x**x**x); // 1 sol. real: 0 simple
  //return(*x**x+*x**x**x**x); // 1 sol. real: 0 doble 
  return(*x**x**x-9**x); // 0,+3,-3
  //return(*x+*x**x**x+*x**x**x**x); //0 simple, -1 triple
}

double der( double *x){
  //return(1+3**x**x); 
  //return(2**x+4**x**x**x);
  return(3**x**x-9);
  //return(1+3**x**x+3**x**x**x);
}

int newton(double *x){
  if(fabs(der(x))>PREC){
    *x=*x-(funcio(x)/der(x));
    return 0;
  }
  else return -1;
}



int secant(double *x0, double *x1){
  double aux;
  if(fabs(funcio(x1,niub)-funcio(x0,niub))>PREC){
    aux=*x1;
    *x1=*x1-funcio(x1,niub)*(*x1-*x0)/(funcio(x1,niub)-funcio(x0,niub));
    *x0=aux;
    return 0;
  }
  else return -1;
}
  

  
//compilar: gcc main.c funcio.o -o main.exe -Wall -lm ...
//#include<funcio.h>
  
	
	
