#define _CRT_SECURE_NO_WARNINGS 1
#include "stdio.h"

int anauns(){

int ninzuu=0;
int noruzikan=0;
int km=0;

printf("��Ԑl������͂��Ă�������\n");
scanf("%d",&ninzuu);
printf("��Ԃ��鎞�Ԃ���͂��Ă�������\n");
scanf("%d",&noruzikan);
printf("��km��Ԃ��邩���͂��Ă�������\n");
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
	

	printf("������%d�~�ł�\n", goukei);
	scanf("%d", &goukei);

	return 0;

}