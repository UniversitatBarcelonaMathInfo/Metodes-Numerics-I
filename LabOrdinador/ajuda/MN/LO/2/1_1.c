#include<stdio.h>

int main(void){
	float prec,x,i,terme,ult;
	int signe;
	scanf("%f", &x); 
	scanf("%f",&prec);
	ult=x*x/2;
	signe=-1;
	i=3;
	while(ult>prec){
		ult=signe*terme*x*x/(i*(i+1));
		terme+=ult;
		signe*=-1;
		i=i+2;
	}printf("%f \n", terme);
	return 0;
}
