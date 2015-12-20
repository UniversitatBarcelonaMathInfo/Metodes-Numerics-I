/*Marcos Salgado Corbillon


 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-30

int indmaxrel(double **a, int k, int n);
int lu(double **a, int n, int *perm, double tol);

int main(void){
	int n=8,i,j,sig;
	double tol=PREC,prod=1, det=1;
	double **a;
	double *u, *v;
	int *perm;
	v={0.1,0.4,0.9,0.5,0.3,0.9,0.5,0.6};
	
	/*dim. i reserva de memoria*/
	printf("quina es la dimensio q dels vectors? \n");	
	a=(double**)calloc(n,sizeof(double *));
	l=(double**)calloc(n,sizeof(double *));
	u=(double**)calloc(n,sizeof(double *));
	lu=(double**)calloc(n,sizeof(double *));
	if(a==NULL){
	  printf("no s'ha pogut guardar memoria \n");
	  exit(-2);
	}
	for(i=0;i<n;i++){
	  a[i]=(double*)calloc(n,sizeof(double));
	  l[i]=(double*)calloc(n,sizeof(double));
	  u[i]=(double*)calloc(n,sizeof(double));
	  lu[i]=(double*)calloc(n,sizeof(double));
	  if(a[i]==NULL){
	    printf("no s'ha pogut guardar memoria \n");
	    exit(-3);
	  }
	}
	u=(double*)calloc(n,sizeof(double));
	v=(double*)calloc(n,sizeof(double));
	perm=(int*)calloc(n,sizeof(int));
	if(u==NULL || v==NULL || perm==NULL){
	  printf("no s'ha pogut guardar memoria \n");
	  exit(-4);
	}
	/*dades*/
	/*printf("quines son les %d components del vector columna? \n", n); 
	for(i=0;i<n;i++){
	  scanf("%lf", &u[i]);
	}
	printf("quines son les %d components del vector fila? \n", n); 
	for(i=0;i<n;i++){
	  scanf("%lf", &v[i]);
	}  
	*/
	for(i=0;i<n;i++){
	    perm[i]=i;
	}
	for(i=0;i<n;i++){
	  for(j=0;j<n;j++){
	    a[i][j]=v[i]*v[j];
	  }
	}	
	for(i=0;i<n;i++){
	  a[i][i]+=i+1;
	}
	/*crida*/
	sig=lu(a,n,perm, tol);
	if(sig==0){
	  printf("det(A)=0 \n");
	  return 0;
	}
	
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
	if(prodmat(n,n,n,n,u,l,lu)==1){
	  printf("ERROR \n");
	  exit(-6);
	}
	printf("matriu UL: \n"); 
	for(i=0;i<n;i++){
	  for(j=0;j<n;j++){
	    printf("%17.3le", lu[i][j]);
	  }printf("\n");
	}printf("\n");
	
	

	/*liberación de memoria*/
	free(u);
	free(v);
	free(perm);
	for(i=0;i<n;i++){
	  free(a[i]);
	}
	free(a);
	return 0;
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
      

int lu(double **a, int n, int *perm, double tol){
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
	    }
	  }	  
	  if(fabs(a[k][k])<tol){
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
