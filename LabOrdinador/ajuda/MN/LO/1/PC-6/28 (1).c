#include<stdio.h>
float f (float x);
float g (float x);
float e (float x);
float h (float x):
int main (void){
	float h0,r=2,x0,der,i,n;
	printf("dona h0,x0,n \n");
	scanf("%f %f %f",&h0, &x0,&n);
	h0=h0/r;
	for(i=1;i<=n;i++){
		der=(f(x0+h0)-f(x0))/h0;
		printf("%f, %f \n",h0, der);
		h0=h0/r;
	}return 0;
}float f(float x){
	float y;
	y=x*x-3;
	return y;
}float e (float x){
	float y;
	y=exp[x];
	return y;
}float h (float x){
	float y;
	y=sin[x]+x*x;
	return y;
}float g (float x){
        float y;
        y=sqrt[2+x];
        return y;
}


	
