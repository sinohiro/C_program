#include "stdio.h"

int input(){
	int buymoney = 0;

	printf("買ったものの金額を入力してください\n");
	scanf("%d",&buymoney);
	printf("あなたが入力した金額は%d円です\n",buymoney);
	return buymoney;
}

int input2(){
	int buyday = 0;

	printf("買い物をした日を入力してください\n");
	scanf("%d",&buyday);
	if(buyday>26){
	printf("1ヶ月の日数は26までの設定になっています\n");
	printf("26以下の数字を入力してください\n");
	scanf("%d",&buyday);
	}else if(buyday<26){
	printf("あなたが入力したのは%d日です\n",buyday);
	}
	return buyday;
}

int BorS(int buymoney){
	int bairitu = 0;

	if(buymoney<200000){
	bairitu = 5000;
	}else if(buymoney>=200000){
	bairitu = 10000;
	}
	printf("BorSは%d...ok\n",bairitu);
	return bairitu;
}

int tesuu(int bairitu, int buyday, int buymoney){
	int buyday2;
	int tesuu;

	buyday2 = 26 - buyday;
	tesuu = buymoney*0.15*buyday2/365;
	printf("tesuuは%d...ok\n",tesuu);
	return tesuu;
}
int keisann(int bairitu, int tesuu2){
	int tukibuy = 0;

	tukibuy = bairitu + tesuu2;
	printf("keisann...ok\n");
	return tukibuy;
}
int output(int tukibuy, int tesuu2){
	printf("1ヶ月の総支払額は%dです\n",tukibuy);
	printf("手数料は%dです\n",tesuu2);
	return 0;
}
int main (void){
	int buymoney2;
	int buyday2;
	int bairitu2;
	int tesuu2;
	int tukibuy2;

     buymoney2 = input();
	 buyday2 = input2();
	 bairitu2 = BorS(buymoney2);
	 tesuu2 = tesuu(bairitu2, buyday2, buymoney2);
	 tukibuy2 = keisann(bairitu2, tesuu2);
	 output(tukibuy2, tesuu2);

	 return 0;
}