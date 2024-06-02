#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>


int input() {
	int todo;

	puts("アルファベット限定文字暗号化システム");
	puts("何をしますか？");
	puts("1:文字暗号化 2:文字復号化 3:終了");
	scanf("%d", &todo);

	return todo;
}

void zurasu(char *str) {
	int i;
	int len;
	int pattern;
	
	// アルファベットのみX文字ずらす
	puts("暗号パターンを指定してください(1～10)");
	scanf("%d", &pattern);
	puts("暗号化したい文字を入力してください");
	puts("(アルファベット限定)");
	//scanf("%d", &len);
	len = strlen(str);
	for (i = 0; i<len; i++)
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = (str[i] - 'a' + pattern) % 26 + 'a';
	return;
}
int main(void) {
	int todo2 = 0;

	todo2 = input();

	if (todo2 == 1) {
		char str[256];
		// 1行づつ読み込む
		while (NULL != fgets(str, sizeof(str), stdin)) {
			zurasu(str);
			printf("%s", str);
		}
	}

	return 0;
}