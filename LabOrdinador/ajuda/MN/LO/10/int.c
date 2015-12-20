#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-30

double fun(double x);
double dernum(int ind, double x, double h);

int main(void){
	int ind, m,n,i,j;
	double q=0.5,h,a,b,r,rh;
	printf("extrems de l'interval  \n");
	scanf("%lf %lf",&a, &b);
	printf("nombre de divisions: \n");
	scanf("%d", &n);
	printf("nombre de reiteracions:  \n");
	scanf("%d",&m);
	h=(b-a)/n;
	
	for(j=0;j<m;j++){
	  r=trapezi(a,h);
	  rh=trapezi(a,qh);
	  printf("%lf \n", r);
	  extrapol(4,j,r,rh);
	  
	}
	return 0;
}
	
		
double fun(double x){
  return(sin(x)*sin(x)); //exacte
}
double extrapol(int p, int q, double fh, double fqh){
  int i;
  for(i=0;i<p;i++){
    q*=q;
  }
  return (q*fh-fqh)/(q-1);
}

double trapezi(a,h){
  int i;
  double r=0;
  for(i=0;i<=n;i=i+2){
    r+=fun(a+i*h);
  }
  r*=1./2.;
  for(i=1;i<=n;i=i+2){
    r+=fun(a+i*h);
  }
  r*=h;
  return(r);
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
	  
	