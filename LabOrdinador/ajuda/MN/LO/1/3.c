#include<stdio.h>
int main(void){
	float i,n, suma=1;
	scanf("%f",&n);	
	for(i=n; i>1; i--){
		suma+=1/i;
	}printf("%f \n",suma);
	
	return 0;
}
