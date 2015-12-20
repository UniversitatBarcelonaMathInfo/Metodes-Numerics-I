/*Marcos Salgado Corbillon


*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PREC 1.e-30

int indmaxrel(double **a, int k, int n);
int lu(double **a, int n, int *perm, double tol);

int main(void){
	int n,i,j,sig;
	double tol=PREC,prod=1, det=1;
	double **a;
	double *u, *v;
	int *perm;
	
	/*dim. i reserva de memoria*/
	printf("quina es la dimensio q dels vectors? \n");	
	scanf("%d", &n);
	if(n<=0){
	  printf("ERROR en les dades\n");
	  exit(-1);
	}
	a=(double**)calloc(n,sizeof(double *));
	if(a==NULL){
	  printf("no s'ha pogut guardar memoria \n");
	  exit(-2);
	}
	for(i=0;i<n;i++){
	  a[i]=(double*)calloc(n,sizeof(double));
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
	for(i=0;i<n;i++){
	  perm[i]=i;
	}
	printf("quines son les %d components del vector columna? \n", n); 
	for(i=0;i<n;i++){
	  scanf("%lf", &u[i]);
	}
	printf("quines son les %d components del vector fila? \n", n); 
	for(i=0;i<n;i++){
	  scanf("%lf", &v[i]);
	}  
	for(i=0;i<n;i++){
	  for(j=0;j<n;j++){
	    a[i][j]=u[i]*v[j];
	  }
	}	
	for(i=0;i<n;i++){
	  a[i][i]+=1;
	}
	/*crida*/
	sig=lu(a,n,perm, tol);
	if(sig==0){
	  printf("det(A)=0 \n");
	  return 0;
	}
	/*det*/
	for(i=0;i<n;i++){
	  det*=a[i][i];
	}det*=sig;
	printf("det(A)= %lf \n",det);
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
