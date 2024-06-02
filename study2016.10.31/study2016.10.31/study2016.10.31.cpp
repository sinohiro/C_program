#include "stdio.h"

int ireru(){
	 int a;
	 a=0;
	 printf("ŒvŽZ‚µ‚½‚¢’l‚ð1‚Â“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
     scanf("%d",&a);

	   return a;
}

int ireru2(){
   int b;
   b=0;
   printf("ŒvŽZ‚µ‚½‚¢’l‚ð1‚Â“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
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
		printf("‘å‚«‚¢‚Ù‚¤‚Í%d‚Å‚·\n",suuzi1);
	}else if(suuzi1< suuzi2){
	    printf("‘å‚«‚¢‚Ù‚¤‚Í%d‚Å‚·\n",suuzi2);
	}
	printf("“š‚¦‚Í%d‚Å‚·",c);
	scanf("%d",&c);

	return 0;
}
