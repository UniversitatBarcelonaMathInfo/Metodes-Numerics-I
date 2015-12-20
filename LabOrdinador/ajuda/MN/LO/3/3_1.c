#include<stdio.h>
#include<stdlib.h>
int main(void){
	int n,i,j;
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
		scanf("%f", &vec[i]);
		vec2[i]=0;
		for(j=0;j<n;j++){
			scanf("%f",&mat[i][j]);
		}
	}for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			vec2[i]+=mat[i][j]*vec[j];
		}
	}for(i=0;i<n;i++){
		printf("%f",vec2[i]);
	}printf("\n");
	return 0;
}
