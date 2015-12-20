#include<stdio.h>
#include<stdlib.h>
int main(void){
	int n;
	float i,j,suma;
	float **mat;
	float *vec;
	float *vec2;
	scanf("%d",&n);
	mat=(float**)malloc(n*sizeof(float*));
	if(mat==NULL){
		exit(1);
	}
	for(i=0;i<n;i++){
		mat[i]=(float*)malloc(n*sizeof(float));
	}vec=(float*)malloc(n*sizeof(float));
	vec2=(float*)malloc(n*sizeof(float));
	for(i=0;i<n;i++){
		vec[i]=i;
		for(j=i;j<n;j++){
			mat[i][j]=1/(i+j+1);
		}
	}for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			suma+=mat[n-1-i][n-1-j];
			vec2[n-1-i]+=vec[n-1-i]/mat[n-i-1][n-1-i]-suma/mat[n-1-i][n-1-i];
		}
	}for(i=0;i<n;i++){
		printf("%f",vec2[i]);
	}printf("\n");
	return 0;
}
