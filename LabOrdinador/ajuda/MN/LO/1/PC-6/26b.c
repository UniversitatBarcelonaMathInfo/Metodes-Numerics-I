#include<stdio.h>
int main(void){
	double suma1=0,suma2=0,n,j;
	scanf("%lf",&n);
	for(j=1;j<=n;j++){
		suma1+=1/(j*j);
	}for(j=n;j>=1; j--){
		suma2+=1/(j*j);
	}printf("suma de 1 a n: %lf \nsuma de n a 1: %lf \n",suma1,suma2);
	return 0;
}
