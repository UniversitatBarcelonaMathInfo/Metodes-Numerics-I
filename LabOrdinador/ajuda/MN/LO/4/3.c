#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//#define PREC 1.e-30 

int prodmat(int n1,int m1,int n2,int m2, double**a,double**b,doublec**);

int main(void){
	int n,i,j,k;
	double norma=0, aux;
	double **a, **b, **c,**d;
	double *fila;
	/*dim. i reserva de memoria*/
	scanf("%d", &n);
	if(n<=0){
	  printf("ERROR en les dades\n");
	  exit(-1);
	}a=(double**)calloc(n,sizeof(double *));
	b=(double**)calloc(n,sizeof(double *));
	c=(double**)calloc(n,sizeof(double *));
	d=(double**)calloc(n,sizeof(double *));
	if(a==NULL||b==NULL || c==NULL||d==NULL){
	  printf("no s'ha pogut guardar memoria\n");
	  exit(-2);
	}
	for(i=0;i<n;i++){
	  a[i]=(double*)calloc(n,sizeof(double));
	  b[i]=(double*)calloc(n,sizeof(double));
	  c[i]=(double*)calloc(n,sizeof(double));
	  d[i]=(double*)calloc(n,sizeof(double));
	  if(a[i]==NULL || b[i]==NULL || c[i]==NULL || d[i]==NULL){
	    printf("no s'ha pogut guardar memoria\n");
	    exit(-3);
	  }
	}fila=(double*)calloc(n,sizeof(double));
	if(fila==NULL){
	  printf("no s'ha pogut guardar memoria\n");
	  exit(-4);
	}
	/*dades*/
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			a[i][j]=1;
			b[i][j]=2;
		}
	}
	/*programa*/
	if(prodmat(n,n,n,n, double**a,double**b,double**c)==1){
	  printf("ERROR \n");
	}if(prodmat(n,n,n,n, double**b,double**a,double**d)==1){
	  printf("ERROR \n");
	}
	for(i=0;i<n;i++){
		fila[i]=0;
		for(j=0;j<n;j++){
		  a[i][j]=c[i][j]-d[i][j];
		}
	}for(i=0;i<n;i++){
		for(j=0;j<n;j++){
		  fila[i]+=fabs(a[i][j]);
		}
	}
	
	
	
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




int prodmat(int n1,int m1,int n2,int m2, double**a,double**b,doublec**){
	int i,j,k;
	if(m1==n2){
	  return 1;
	}
	for(i=0;i<n;i++){
                c[i]=(double*)malloc(p*sizeof(double));
                if(c[i]==NULL){
                        printf("no s'ha pogut guardar memoria\n");
                        exit(6);
                }
	}for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			c[i][j]=0;
			for(k=0;k<p;k++){
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}return(0);
}