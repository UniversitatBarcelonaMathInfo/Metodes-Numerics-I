#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-30

double fun(double x);
double dernum(int ind, double x, double h);
double extrapol(int p, int q, double fh, double fqh);


int main(void){
	int ind, m,i;
	double q=0.5, x,h;
	printf("quin metode vols?  \n");
	scanf("%d", &ind);
	printf("abscisa:  \n");
	scanf("%lf", &x);
	printf("discretitzacio:  \n");
	scanf("%lf",&h);
	printf("nombre de reiteracions:  \n");
	scanf("%d",&m);
	for(i=0;i<m-1;i++){
	  leer p_i
	  extrapol(p, q, dernum(ind,x,h), dernum(ind,x,q*h));
	  
	}
	return 0;
}


		
double fun(double x){
  return(cos(x));
}

double dernum(int ind, double x, double h){
  if(ind=1){
    return((fun(x+h)-fun(x))/h);
  }if(ind=2){
    return((fun(x+h)-fun(x-h))/(2*h));
  }if(ind=3){
    return((fun(x+h)-2*fun(x)+fun(x-h))/(h*h));
  }
}
double extrapol(int p, int q, double fh, double fqh){
  int i;
  for(i=1;i<p;i++){
    q*=q;
  }
  return (q*fh-fqh)/(q-1);
}

	  
	