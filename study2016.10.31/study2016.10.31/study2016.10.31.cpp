#include "stdio.h"

int ireru(){
	 int a;
	 a=0;
	 printf("�v�Z�������l��1���͂��Ă�������\n");
     scanf("%d",&a);

	   return a;
}

int ireru2(){
   int b;
   b=0;
   printf("�v�Z�������l��1���͂��Ă�������\n");
   scanf("%d",&b);

	   return b;
}


int hantei(int a , int b){
	int c=0;

	if(a > b){
	c = a - b;
	}else if(a < b){
		c = b - a;
     }

	return c;
}

int main(void){

	int suuzi1;
	int suuzi2;
	int c;

	suuzi1 = ireru();
	suuzi2 = ireru2();

	c = hantei(suuzi1 , suuzi2);
	if (suuzi1> suuzi2){
		printf("�傫���ق���%d�ł�\n",suuzi1);
	}else if(suuzi1< suuzi2){
	    printf("�傫���ق���%d�ł�\n",suuzi2);
	}
	printf("������%d�ł�",c);
	scanf("%d",&c);

	return 0;
}
