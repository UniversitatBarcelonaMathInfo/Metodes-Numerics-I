#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-30

int resoltrisup(int n,double **a,double *b,double *x);
void prodvecmat(int n,double **a,double *x,double *c);
int indmaxrel(double **a, int k, int n);
int mlu(double **a, int n, int *perm,double *b, double tol);
int prodmat(int n1,int m1,int n2,int m2, double**a,double**b,double**c);

int main(void){
	int n,i,j,k,sig;
	double norma=0,max=0, aux, tol=PREC,prod=1,ax;
	double **a, **aa, **l, **u, **lu, **pa, **c, **d;
	double *b, *x, *e, *fila;
	int *perm;
	
	/*dim. i reserva de memoria*/
	scanf("%d", &n);
	if(n<=0){
	  printf("ERROR en les dades\n");
	  exit(-1);
	}
	a=(double**)calloc(n,sizeof(double *));
	aa=(double**)calloc(n,sizeof(double *));
	u=(double**)calloc(n,sizeof(double *));
	l=(double**)calloc(n,sizeof(double *));
	lu=(double**)calloc(n,sizeof(double *));
	pa=(double**)calloc(n,sizeof(double *));
	c=(double**)calloc(n,sizeof(double *));
	d=(double**)calloc(n,sizeof(double *));
	if(a==NULL||aa==NULL || l==NULL || u==NULL || lu==NULL || pa==NULL || c==NULL || d==NULL){
	  printf("no s'ha pogut guardar memoria -2\n");
	  exit(-2);
	}
	for(i=0;i<n;i++){
	  a[i]=(double*)calloc(n,sizeof(double));
	  aa[i]=(double*)calloc(n,sizeof(double));
	  u[i]=(double*)calloc(n,sizeof(double));
	  l[i]=(double*)calloc(n,sizeof(double));
	  lu[i]=(double*)calloc(n,sizeof(double));
	  pa[i]=(double*)calloc(n,sizeof(double));
	  c[i]=(double*)calloc(n,sizeof(double));
	  d[i]=(double*)calloc(n,sizeof(double));
	  if(a[i]==NULL || aa[i]==NULL || u[i]==NULL || l[i]==NULL || lu[i]==NULL || pa[i]==NULL || c[i]==NULL || d[i]==NULL){
	    printf("no s'ha pogut guardar memoria -3\n");
	    exit(-3);
	  }
	}
	b=(double*)calloc(n,sizeof(double));
	x=(double*)calloc(n,sizeof(double));
	e=(double*)calloc(n,sizeof(double));
	perm=(int*)calloc(n,sizeof(int));
	fila=(double*)calloc(n,sizeof(double));
	if(b==NULL || x==NULL || e==NULL || fila==NULL){
	  printf("no s'ha pogut guardar memoria -4\n");
	  exit(-4);
	}
	for(i=0;i<n;i++){
	  perm[i]=i;
	}
	
	/*dades*/
	for(i=0;i<n;i++){
		b[i]=0.;
		for(j=0;j<n;j++){
		  scanf("%lf",&ax);
			a[i][j]=ax;
			aa[i][j]=a[i][j];
			b[i]+=a[i][j];
		}
	}
	/*crida*/
	sig=mlu(a,n,perm,b, tol);
	if(sig==0){
	  printf("no es posible fer PA=LU \n");
	  exit(-5);
	}
	

	/*impresio*/
	printf("matriu A reduida formada per L (part inferior) y U: \n"); 
	for(i=0;i<n;i++){
	  for(j=0;j<n;j++){
	    printf("%17.3le", a[i][j]);
	  }
	  printf("\n");
	}
	printf("\n");
	printf("perm:");
	for(i=0;i<n;i++){
	  printf("%3d",perm[i]);
	}
	printf("\n");
	printf("matriu PA: \n"); 
	for(i=0;i<n;i++){
	  k=perm[i];
	  for(j=0;j<n;j++){
	    pa[i][j]=aa[k][j];
	  }
	}
	  for(i=0;i<n;i++){
	    for(j=0;j<n;j++){
	      printf("%17.3le", pa[i][j]);
	    }
	    printf("\n");
	  }
	    

	  printf("\n");
	
	printf("\n");
	// para ahorrar L,U,LU podia imprimirse LU a partir de A
	for(i=0;i<n;i++){
	  for(j=0;j<n;j++){
	    if(j<=i){
	      l[i][j]=a[i][j];
	    }else{
	      l[i][j]=0;
	    }
	  }l[i][i]=1;
	}
	for(i=0;i<n;i++){
	  for(j=0;j<=i;j++){
	     if(j<=i){
	       u[j][i]=a[j][i];
	     }else{
	       u[j][i]=0;
	     }
	  }
	}
	if(prodmat(n,n,n,n,l,u,lu)==1){
	  printf("ERROR \n");
	  exit(-6);
	}
	printf("matriu LU: \n"); 
	for(i=0;i<n;i++){
	  for(j=0;j<n;j++){
	    printf("%17.3le", lu[i][j]);
	  }printf("\n");
	}printf("\n");
	

	printf("matriu U: \n"); 
	for(i=0;i<n;i++){
	  for(j=0;j<n;j++){
	    printf("%17.3le", u[i][j]);
	  }printf("\n");
	}printf("\n");
	
	printf("matriu L: \n"); 
	for(i=0;i<n;i++){
	  for(j=0;j<n;j++){
	    printf("%17.3le", l[i][j]);
	  }printf("\n");
	}printf("\n");
	
	/*det*/
	for(i=0;i<n;i++){
	  prod=u[i][i];
	}prod*=sig;
	printf("determinant: %lf",prod);
	printf("\n");
	
	/*error*/
	if(prodmat(n,n,n,n,pa,lu,c)==1){
	  printf("ERROR \n");
	  exit(-7);
	}if(prodmat(n,n,n,n,lu,pa,d)==1){
	  printf("ERROR \n");
	  exit(-8);
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
	}max=fila[0];
	for(i=0;i<n;i++){
	  if(max<fila[i]){
	    max=fila[i];
	  }
	}
	printf("norma del suprem: %21.14le \n", max);	
	
	/*error2*/
	if(resoltrisup(n,u,b,x)==1){
	  printf("no es resoluble \n");
	  exit(-9);
	}
	prodvecmat(n,aa,x,e);
	for(i=0;i<n;i++){
	  norma+=(e[i]-b[i])*(e[i]-b[i]);
	}norma=sqrt(norma);
	printf("dim n= %d \n",n);
	printf("el vector x es:\n");
	for(i=0; i<n;i++){
	  printf(" %+21.14le \n", x[i]);
	}printf("norma: %lf \n", norma);
	
	/*liberación de memoria*/
	free(b);
	free(x);
	free(e);
	for(i=0;i<n;i++){
	  free(a[i]);
	  free(aa[i]);
	  free(l[i]);
	  free(u[i]);
	  free(lu[i]);
	  free(pa[i]);
	  free(c[i]);
	  free(d[i]);
	}
	free(a);
	free(aa);
	free(l);
	free(u);
	free(lu);
	free(pa);
	free(c);
	free(d);
	return 0;
}

int inv matriu(int n, double **a, double **b){

	
	  
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
      

int mlu(double **a, int n, int *perm,double *b, double tol){
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
	    }b[i]-=a[i][k]*b[k];
	  }	  
	}
	return (sig);
}
