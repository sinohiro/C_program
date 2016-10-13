#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
	int P = 0; /* P=player */
	int C = 0; /* C=com */
	int count = 0;
	int lost = 0;
	int win = 0;
	int r; /* r=乱数 */
	int n; /* n=乱数2 */
	int b = 0;
	int Jk = 0;
	int Jkn = 0;
	int k10 = 0;
	int k10n = 0;
	char s = 0;

	srand((unsigned)time(NULL));

	printf("Ret's stert brack jack\n");

	printf("ルールは簡単、どれだけ得点を21にできるかです。\n");

	printf("最初のカードは自動的に引かれます。\n");

	printf("あなたの番です\n");

	while (P >= 0) {
		b = rand() % 52 + 1; //Jkの確立

		if (b != 1 || Jk == 1) {
			r = rand() % 13 + 1;
			P = P + r;
			count = count + 1;

			if (r > 10) {
				k10n = k10n + 1;
				P = P - r;
				printf("11以上を引いたので後ほど10か1を選んでください\n");

			}

			printf("あなたの引いたカードの得点は%dです\n\n", r);

			printf("あなたは10か1かを選べるカードを%d枚持っています\n\n", k10n);

			printf("あなたの %d 回目の得点は %d です\n", count, P); 
		}


		if (b == 1) {
			printf("Jokerを引きました\n");
			Jk = 1;
			count = count + 1;
		}


		if (P > 22) {
			printf("%d\n22を越えました\nYouLost...\n", P);
			lost = 1;
			break;
		}
		else if (P == 22) {
			break;
		}

		printf("もう一枚引きますか？\ny/n\n");
		char a, str[20];
		scanf("%s", str);
		a = str[0];
		if (a == 'n') {
			break;
		}
	}

	while (k10n != 0) {
		printf("あなたは11以上のカードを%d枚引きました\n", k10n);
		printf("%d枚目のカードを10か1にするか入力してください\n",k10n);

		scanf("%d", &k10);

		if (k10 != 10 && k10 != 1) {
			printf("10か1を入力してください\n");
		}
		if (k10 == 10) {
			printf("あなたは10を入力しました\n");
			P = P + k10;
			k10 == 0;
			k10n = k10n - 1;
		}

		if (k10 == 1) {
			printf("あなたは1を入力しました\n");
			P = P + k10;
			k10 == 0;
			k10n = k10n - 1;
		}

		if (k10n == 0) {
			break;
		}
	}


	while (Jk == 1) {

		printf("Jkの数字を何にしますか？10以下を入力してください\n");

		scanf("%d", &Jkn);

		if (Jkn < 10) {

			printf("あなたが入力した数字は[%d]です", Jkn);
			P = P + Jkn;
			break;
		}

		if (Jkn > 10) {
			printf("10以下を入力してください\n");

		}
	}



	if (lost != 1) {

		printf("\nあなたの最終得点です\n%d\n", P);


		count = 0;

		printf("\n\nあいての番です\n");
	}


		while (C >= 0) {
			r = rand() % 13 + 1;
			C = C + r;
			count = count + 1;

			printf("\n相手の %d 回目の得点は %d です\n", count, C);

			if (C > 22) {
				printf("\n22を越えました\nYouWin!\n");
				win = 1;
				break;
			}

			if (9 <= C || C <= 13) {
				n = rand() % 10 + 1;
				if (n == 1)
					break;
			}
			else if (14 <= C || C <= 16) {
				n = rand() % 5 + 1;
				if (n == 1)
					break;
			}
			else if (17 <= C || C <= 19) {
				n = rand() % 2 + 1;
				if (n == 1)
					break;
			}
			else if (20 <= C || C <= 21) {
				n = rand() % 20 + 1;
				if (n != 1)
					break;
			}
			else if (C == 22) {
				break;
			}
		}

		if (win != 1) {

			printf("あいての最終得点です\n%d\n\n\n\n", C);

			if (P > C) {
				printf("%d VS %d !\nYouWin!\n", P, C);
			}
			else if (P < C) {
				printf("%d VS %d !\nYouLost...\n", P, C);
			}
			else {
				printf("%d VS %d !\nDraw\n", P, C);
			}

		}
	
	scanf("%c", &s);
	scanf("%c", &r);

	return 0;
}
