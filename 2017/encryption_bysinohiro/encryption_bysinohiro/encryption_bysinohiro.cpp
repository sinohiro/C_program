#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>


int input() {
	int todo;

	puts("�A���t�@�x�b�g���蕶���Í����V�X�e��");
	puts("�������܂����H");
	puts("1:�����Í��� 2:���������� 3:�I��");
	scanf("%d", &todo);

	return todo;
}

void zurasu(char *str) {
	int i;
	int len;
	int pattern;
	
	// �A���t�@�x�b�g�̂�X�������炷
	puts("�Í��p�^�[�����w�肵�Ă�������(1�`10)");
	scanf("%d", &pattern);
	puts("�Í�����������������͂��Ă�������");
	puts("(�A���t�@�x�b�g����)");
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
		// 1�s�Âǂݍ���
		while (NULL != fgets(str, sizeof(str), stdin)) {
			zurasu(str);
			printf("%s", str);
		}
	}

	return 0;
}