/* Marcos Salgado Corbillón 
43565715N
14953956*/


#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main (void){
	int n=0,i;
	float a,a2,c,s;
	printf("dona'm un angle positiu \n");
	scanf("%f", &a);
	a2=a;
	if(a<=0){
		printf("ERROR en les dades: l'angle ha de ser estrictament positiu \n");
		exit(1);
	}while(a>=0.01){
		a=a/2;
		n++;
	}i=n;
	if(i==0){
		c=cos(a);
		s=sin(a);
	}else{
		c=(cos(a)*cos(a)-1/2.)*2;
		s=sin(a)*cos(a)*2;
		i--;
	}while(i!=0){
		s=s*c*2;
		c=(c*c-1/2.)*2;
		i--;
	}printf("Angle a: %e \nLa quantitat de vegades que s’ha dividit a per 2: %d \ncos(a) calculat:%f \ncos(a) directe: %f \nsin(a) calculat:%f \nsin(a) directe: %f \n", a2, n, c,cos(a2),s, sin(a2));
	return 0;
} 	

