#include<stdio.h>
int main (void){
	double x,i=0,y,ant;
	y=1/(2.f);
	x=1.f+y;
	while(x!=1.f){
		ant=y;
		y=y/(2.f);
		x=1.f+y;
		i++;
	}
	printf("epsilon= 2^-%lf= %lf \n",i,ant);
	return(0);
}
	
