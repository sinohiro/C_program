#define _CRT_SECURE_NO_WARNINGS 1
#include "stdio.h"

int anauns(){

int ninzuu=0;
int noruzikan=0;
int km=0;

printf("æÔl”‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
scanf("%d",&ninzuu);
printf("æÔ‚·‚éŠÔ‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
scanf("%d",&noruzikan);
printf("‰½kmæÔ‚·‚é‚©“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
scanf("%d",&km);

return ninzuu, noruzikan, km;
}

int kihon(int km){

int okane;
int kasan;
int m;

m = km*1000;
kasan = m/130;
okane = kasan * 80;

return okane;
}


int main(void){
	int goukei = 0;
	int okane = 0;
	
	anauns();
	goukei = kihon(okane);
	

	printf("—¿‹à‚Í%d‰~‚Å‚·\n", goukei);
	scanf("%d", &goukei);

	return 0;

}