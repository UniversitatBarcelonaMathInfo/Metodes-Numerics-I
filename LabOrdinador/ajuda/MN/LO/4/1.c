#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-30

int resoltrisup(int n,double **a,double *b,double *x);
void prodvecmat(int n,double **a,double *x,double *c);

int main(void){
	int n,i,j,k;
	double norma=0, aux;
	double **a, **aa;
	double *b, *x, *c;
	/*dim. i reserva de memoria*/
	scanf("%d", &n);
	if(n<=0){
	  printf("ERROR en les dades\n");
	  exit(-1);
	}a=(double**)calloc(n,sizeof(double *));
	aa=(double**)calloc(n,sizeof(double *));
	if(a==NULL||aa==NULL){
	  printf("no s'ha pogut guardar memoria\n");
	  exit(-2);
	}
	for(i=0;i<n;i++){
	  a[i]=(double*)calloc(n,sizeof(double));
	  aa[i]=(double*)calloc(n,sizeof(double));
	  if(a[i]==NULL || aa[i]==NULL){
	    printf("no s'ha pogut guardar memoria\n");
	    exit(-3);
	  }
	}b=(double*)calloc(n,sizeof(double));
	x=(double*)calloc(n,sizeof(double));
	c=(double*)calloc(n,sizeof(double));
	if(b==NULL || x==NULL || c==NULL){
	  printf("no s'ha pogut guardar memoria\n");
	  exit(-4);
	}
	/*dades*/
	for(i=0;i<n;i++){
		b[i]=0.;
		for(j=0;j<n;j++){
			a[i][j]=1./(i+j+1);
			aa[i][j]=a[i][j];
			b[i]+=a[i][j];
		}
	}
	/*Gaus*/
	for(k=0;k<n-1;k++){
	  if(fabs(a[k][k])<PREC){
	    printf("pivot nul, index: %d \n",k);
	    return(-5);
	  }for(i=k+1;i<n;i++){
	    aux=a[i][k]/a[k][k];
	    for(j=k+1;j<n; j++){
	      a[i][j]-=aux*a[k][j];
	    }b[i]-=aux*b[k];
	  }
	}
	/*programa*/
	if(resoltrisup(n,a,b,x)==1){
	  printf("no es resoluble \n");
	}
	prodvecmat(n,aa,x,c);
	for(i=0;i<n;i++){
	  norma+=(c[i]-b[i])*(c[i]-b[i]);
	}norma=sqrt(norma);
	/*impresio*/
	printf("dim n= %d \n",n);
	for(i=0; i<n;i++){
	  printf(" %+21.14le \n", x[i]);
	}printf("norma: %lf \n", norma);
	/*liberación de memoria*/
	free(b);
	free(x);
	free(c);
	for(i=0;i<n;i++){
	  free(a[i]);
	  free(aa[i]);
	}free(a);
	free(aa);
	
	return 0;
}
int resoltrisup(int n, double **a, double *b, double *x){
	int i,j;
	double aux=0;
	if(fabs(a[n-1][n-1])<PREC){
	  printf("pivot nul, index: %d \n",n-1);
	  return(1);
	}
	x[n-1]=b[n-1]/a[n-1][n-1];
	for(i=n-2;i>=0;i--){
	  if(fabs(a[i][i])<PREC){
	    printf("pivot nul, index: %d \n",i);
	    return(1);
	  }aux=b[i];
	  for(j=i+1;j<n;j++){
	    aux-=x[j]*a[i][j];
	  }x[i]=aux/a[i][i];
	}return 0;
}void prodvecmat(int n, double **a, double *x, double *c){
	int i,j;
	for(j=0;j<n;j++){
		for(i=0;i<n;i++){
			c[i]=a[i][j]*x[i];
		}
	}
}
	
	
