#define _CRT_SECURE_NO_WARNINGS 1
#include "stdio.h"

int input(){
	int ninnzuu = 0;

	printf("乗車人数を入力してください\n");
	scanf("%d",&ninnzuu);
	return ninnzuu;
}
int input2(){
	int noruzikann = 0;

	printf("乗り始める時間を入力してください\n");
	scanf("%d",&noruzikann);
	if(noruzikann>24){
		puts("25以上は入力できません\n");
		puts("24以下を入力してください\n");
		scanf("%d",&noruzikann);
	}
	return noruzikann;
}
int input3(){
	int km = 0;

	printf("乗車する距離を入力してください\n");
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

	printf("料金は%d円です\n", goukei);
	scanf("%d", &goukei);

	return 0;

}