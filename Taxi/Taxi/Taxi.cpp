#define _CRT_SECURE_NO_WARNINGS 1
#include "stdio.h"

int input(){
	int ninnzuu = 0;

	printf("��Ԑl������͂��Ă�������\n");
	scanf("%d",&ninnzuu);
	return ninnzuu;
}
int input2(){
	int noruzikann = 0;

	printf("���n�߂鎞�Ԃ���͂��Ă�������\n");
	scanf("%d",&noruzikann);
	if(noruzikann>24){
		puts("25�ȏ�͓��͂ł��܂���\n");
		puts("24�ȉ�����͂��Ă�������\n");
		scanf("%d",&noruzikann);
	}
	return noruzikann;
}
int input3(){
	int km = 0;

	printf("��Ԃ��鋗������͂��Ă�������\n");
	scanf("%d",&km);
	return km;
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
	int ninnzuu2 = 0;
	int noruzikann2 = 0;
	int km2 = 0;
	int goukei = 0;
	int okane = 0;
	
	ninnzuu2 = input();
	noruzikann2 = input2();
	km2 = input3();

	goukei = kihon(km2);

	printf("������%d�~�ł�\n", goukei);
	scanf("%d", &goukei);

	return 0;

}