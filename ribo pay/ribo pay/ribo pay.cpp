#include "stdio.h"

int input(){
	int buymoney = 0;

	printf("”ƒ‚Á‚½‚à‚Ì‚Ì‹àŠz‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
	scanf("%d",&buymoney);
	printf("‚ ‚È‚½‚ª“ü—Í‚µ‚½‹àŠz‚Í%d‰~‚Å‚·\n",buymoney);
	return buymoney;
}

int input2(){
	int buyday = 0;

	printf("”ƒ‚¢•¨‚ğ‚µ‚½“ú‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
	scanf("%d",&buyday);
	if(buyday>26){
	printf("1ƒ–Œ‚Ì“ú”‚Í26‚Ü‚Å‚Ìİ’è‚É‚È‚Á‚Ä‚¢‚Ü‚·\n");
	printf("26ˆÈ‰º‚Ì”š‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
	scanf("%d",&buyday);
	}else if(buyday<26){
	printf("‚ ‚È‚½‚ª“ü—Í‚µ‚½‚Ì‚Í%d“ú‚Å‚·\n",buyday);
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
	printf("BorS‚Í%d...ok\n",bairitu);
	return bairitu;
}

int tesuu(int bairitu, int buyday, int buymoney){
	int buyday2;
	int tesuu;

	buyday2 = 26 - buyday;
	tesuu = buymoney*0.15*buyday2/365;
	printf("tesuu‚Í%d...ok\n",tesuu);
	return tesuu;
}
int keisann(int bairitu, int tesuu2){
	int tukibuy = 0;

	tukibuy = bairitu + tesuu2;
	printf("keisann...ok\n");
	return tukibuy;
}
int output(int tukibuy, int tesuu2){
	printf("1ƒ–Œ‚Ì‘x•¥Šz‚Í%d‚Å‚·\n",tukibuy);
	printf("è”—¿‚Í%d‚Å‚·\n",tesuu2);
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