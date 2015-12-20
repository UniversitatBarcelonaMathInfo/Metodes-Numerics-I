#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int prodmat(int n1,int m1,int n2,int m2, double**a,double**b,double**c);
void max(double *a,int p, int q, double *maxim);

int main(void){
	int n,i,j,k;
	double norma=0, aux;
	double **a, **b, **c,**d;
	double *fila, *maxim;
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
			a[i][j]=1./(double)(1+j+i);
			b[i][j]=i-j;
		}
	}
	/*programa*/
	if(prodmat(n,n,n,n,a,b,c)==1){
	  printf("ERROR \n");
	}if(prodmat(n,n,n,n,b,a,d)==1){
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
	}max(fila,0,n-1, maxim);
	printf("norma del suprem: %21.14le \n", *maxim);
	for(i=0;i<n;i++){
	  printf("%21.14le \n",fila[i]);
	}
	/*liberación de memoria*/
	for(i=0;i<n;i++){
	  free(a[i]);
	  free(b[i]);
	  free(c[i]);
	  free(d[i]);
	}
	free(a);
	free(b);
	free(c);
	free(d);
	return 0;
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
}void max(double *a,int p, int q, double *maxim){
  int r;
  double *max1,*max2;
  if(p==q){
    *maxim=a[q];
  }else{
    if(p+1==q){
      if(a[p]<a[q]){
	*maxim=a[q];
      }else{
	*maxim=a[p];
      }
    }else{
      r=(p+q)/2;
      max(a,p,r,max1);
      max(a,r+1,q,max2);
      if(*max1<*max2){
	*maxim=*max2;
      }else{
	*maxim=*max1;
      }
    }
  }

 /*max(a,*max1,*max2,maxim);} */
}