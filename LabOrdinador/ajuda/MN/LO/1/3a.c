#include<stdio.h>
int main(void){
	float i,n, suma=1;
	scanf("%f",&n);	
	for(i=2; i<n; i++){
		suma+=1/i;
	}printf("%f \n",suma);
	
	return 0;
}
