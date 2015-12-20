#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-30

int inv_matriu(int n, double **a, double **b);
int resoltrisup(int n,double **a,double *b,double *x);
void prodvecmat(int n,double **a,double *x,double *c);
int indmaxrel(double **a, int k, int n);
int mlu(double **a, int n, int *perm, double tol);
int prodmat(int n1,int m1,int n2,int m2, double**a,double**b,double**c);

int main(void){
	int n,i,j,k=1;
	double **a, **b;
	
	/*dim. i reserva de memoria*/
	scanf("%d", &n);
	if(n<=0){
	  printf("ERROR en les dades\n");
	  exit(-1);
	}
	a=(double**)calloc(n,sizeof(double *));
	b=(double**)calloc(n,sizeof(double *));
	if(a==NULL|| b==NULL){
	  printf("no s'ha pogut guardar memoria -2\n");
	  exit(-2);
	}
	for(i=0;i<n;i++){
	  a[i]=(double*)calloc(n,sizeof(double));
	  b[i]=(double*)calloc(n,sizeof(double));
	  if(a[i]==NULL || b[i]==NULL){
	    printf("no s'ha pogut guardar memoria -3\n");
	    exit(-3);
	  }
	}
	/*dades*/
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			a[i][j]=k;
			k++;
		}
	}
	/*crida*/
	if(inv_matriu(n,a,b)==1){
	  printf("no es posible invertir A \n");
	  exit(-5);
	}
	

	/*impresio*/
	printf("matriu B: \n"); 
	for(i=0;i<n;i++){
	  for(j=0;j<n;j++){
	    printf("%17.3le", b[j][i]);
	  }
	  printf("\n");
	}
	
	/*liberación de memoria*/
	for(i=0;i<n;i++){
	  free(a[i]);
	  free(b[i]);
	}
	free(a);
	free(b);
	return 0;
}

int inv_matriu(int n, double **a, double **b){
	int i,j,k,sig;
	double norma=0,max=0, aux, tol=PREC,prod=1,ax;
	double **id;
	double *y;
	int *perm;
	
	/*reserva de memoria*/
	id=(double**)calloc(n,sizeof(double *));
	if(id==NULL){
	  printf("no s'ha pogut guardar memoria -2\n");
	  exit(-2);
	}
	for(i=0;i<n;i++){
	  id[i]=(double*)calloc(n,sizeof(double));
	  if(id[i]==NULL){
	    printf("no s'ha pogut guardar memoria -3\n");
	    exit(-3);
	  }
	}
	perm=(int*)calloc(n,sizeof(int));
	y=(double*)calloc(n,sizeof(double));
	if(perm==NULL || y==NULL){
	  printf("no s'ha pogut guardar memoria -4\n");
	  exit(-4);
	}
	for(i=0;i<n;i++){
	  perm[i]=i;
	} 
	for(i=0;i<n;i++){
	    id[i][i]=1;
	}

	/*crida*/
	sig=mlu(a,n,perm, tol);
	if(sig==0){
	  printf("no es posible fer PA=LU \n");
	  return 1;
	}
	
	/*calculo de la inv*/
	for(i=0;i<n;i++){
	  resoltriinf(n,a,id[perm[i]],y);  
	  resoltrisup(n,a,y,b[i]);
	}
	return 0;	
}
	
int resoltrisup(int n, double **a, double *b, double *x){
	int i,j;
	double aux=0;
	if(fabs(a[n-1][n-1])<PREC){
	  printf("pivot nul,-1 index: %d \n",n-1);
	  return(1);
	}
	x[n-1]=b[n-1]/a[n-1][n-1];
	for(i=n-2;i>=0;i--){
	  if(fabs(a[i][i])<PREC){
	    printf("pivot nul,-2 index: %d \n",i);
	    return(1);
	  }aux=b[i];
	  for(j=i+1;j<n;j++){
	    aux-=x[j]*a[i][j];
	  }x[i]=aux/a[i][i];
	}return 0;
}

int resoltriinf(int n, double **a, double *b, double *x){
	int i,j;
	double aux=0;
	x[0]=b[0];
	for(i=1;i<n;i++){
	  aux=b[i];
	  for(j=0;j<i;j++){
	    aux-=x[j]*a[i][j];
	  }x[i]=aux;
	}return 0;
}

void prodvecmat(int n, double **a, double *x, double *c){
	int i,j;
	for(j=0;j<n;j++){
		for(i=0;i<n;i++){
			c[i]=a[i][j]*x[i];
		}
	}
}

int prodmat(int n1,int m1,int n2,int m2, double**a,double**b,double**c){
	int i,j,k,n,p,m;
	if(m1!=n2){
	  return 1;
	}n=n1;
	p=m1;
	m=m2;
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

int indmaxrel(double **a, int k, int n){
  int i,j,v;
  double max=0;
  double *s;
  
  s=(double*)calloc(n,sizeof(double));
  for(i=0;i<n;i++){
    s[i]=0;
  }
  
  for(i=k;i<n;i++){
    for(j=k;j<n;j++){
      if(s[i]<fabs(a[i][j])){
	s[i]=fabs(a[i][j]);
      }
     }
  }
 

  for(i=k;i<n;i++){
     if(max< fabs(a[i][k])/s[i]){
       max= fabs(a[i][k])/s[i];
       v=i;
     }
  }
  
  return v;
}
      

int mlu(double **a, int n, int *perm, double tol){
    int i,j,k,l,sig=1;
    double aux;
    
	for(k=0;k<n-1;k++){
	  i=indmaxrel(a,k,n);
	  if(k!=i){
	    aux=perm[k];
	    perm[k]=perm[i];
	    perm[i]=aux;
	    sig*=-1;
	    for(l=0 ;l<n;l++){
	      aux=a[k][l];
	      a[k][l]=a[i][l];
	      a[i][l]=aux;
	    }//mejor con vectores que componente a componente
	  }	  
	  if(fabs(a[k][k])<tol){
	    printf("pivot nul, index: %d \n",k);
	    return(0);
	  }
	  for(i=k+1;i<n;i++){
	    a[i][k]=a[i][k]/a[k][k]; //sota la diagonal k, enmagatzem els multiplicadors
	    for(j=k+1;j<n; j++){
	      a[i][j]-=a[i][k]*a[k][j];
	    }
	  }	  
	}
	return (sig);
}
