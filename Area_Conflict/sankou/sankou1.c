
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define N_SHOT 3     // 砲弾の最大数
#define N_ENEMY 30
#define N_KABE 24


/*移動物体の構造体　*/
typedef struct {
    double px, py;
    double vx, vy;
    double sx, sy;
    int life;
} Object;

/* 物体の初期化 */
void InitObject(Object *obj,
	double px, double py, double vx, double vy, double sx, double sy, int life)
{
    obj->px = px; obj->py = py;
    obj->vx = vx; obj->vy = vy;
    obj->sx = sx; obj->sy = sy;
    obj->life = life;
}

void InitEnemy(Object *enemy,
	double px, double py, double vx, double vy, int life)
{
    InitObject(enemy, px, py, vx, vy, 5.0, 1.0, life);
}

/*void InitEnemies(Object enemy[], int n,
  double px, double py, double vx, double vy, int life)
  {
  int  i;

  for (i = 0; i < n; i++) {
  InitObject(&enemy[i], px, py, vx, vy, 5.0, 1.0, life);
  }
  }
 */
/* 弾の初期化 */
void InitShot(Object *shot,
	double px, double py, double vx, double vy, int life)
{
    InitObject(shot, px, py, vx, vy, 0.0, 0.0, life);
}

void InitShots(Object shot[], int n,
	double px, double py, double vx, double vy, int life)
{
    int  i;

    for (i = 0; i < n; i++) {
	InitObject(&shot[i], px, py, vx, vy, 0.0, 0.0, life);
    }
}


// 乱数の初期化
void InitRand()
{
    srand(time(NULL));
}

// m 以上 n 未満の整数乱数
int Rand(int m, int n)
{
    return (((int)((n-m)*(rand()/(RAND_MAX + 1.0)))) + m);
}
/*描画関数*/
void DrawParts(int y, int x, char *s)
{
    int w, h;
    getmaxyx(stdscr, h, w);
    if (y < 0) return;
    if (y >= h) return;
    while (*s != '\0') {
	if (x < 0); else;
	if (x >= w); else;
	if (*s != ' ') mvaddch(y, x, *s);
	s++;
	x++;
    }
}

/*本体の表示*/
void DrawHontai(Object *hontai)
{
    int x, y;

    attrset(COLOR_PAIR(1));
    x = (int)(hontai->px);
    y = (int)(hontai->py);

    DrawParts(y-2, x, " ^  ");
    DrawParts(y-1  , x, "^W^ ");
}

/*弾の表示*/
void DrawShot(Object *shot)
{
    if(shot->life != 1)return;
    attrset(COLOR_PAIR(3));
    mvaddch((int)(shot->py), (int)(shot->px), '|');
}
void DrawShots(Object shot[], int n)
{
    int  i;

    for (i = 0; i < n; i++) {
	if (shot[i].life != 0) DrawShot(&shot[i]);
    }
}

/* 敵の表示 */
void DrawEnemy(Object *enemy)
{
    int  x, y;

    attrset(COLOR_PAIR(2));
    x = (int)(enemy->px) - 5;
    y = (int)(enemy->py);
    DrawParts(y  , x, "[-U-]");
}

void DrawEnemies(Object enemy[], int n)
{
    int  i;

    for (i = 0; i < n; i++) {
	if (enemy[i].life != 0) DrawEnemy(&enemy[i]);
    }
}
/*壁の表示*/
void DrawKabe(Object *kabe1)
{
    int x, y;

    if(kabe1->life == 0)return;

    attrset(COLOR_PAIR(1));
    x = (int)(kabe1->px);
    y = (int)(kabe1->py);
    DrawParts(y-3  , x, "II");
    DrawParts(y-2  , x, "II");
    DrawParts(y-1  , x, "II");
    DrawParts(y  , x, "II");
}

void DrawKabes(Object *kabe2)
{
    int x, y;

    if(kabe2->life == 0)return;

    attrset(COLOR_PAIR(1));
    x = (int)(kabe2->px);
    y = (int)(kabe2->py);
    DrawParts(y-3  , x, "II");
    DrawParts(y-2  , x, "II");
    DrawParts(y-1  , x, "II");
    DrawParts(y  , x, "II");
}

void DrawLine(Object *line)
{
    int x, y;

    attrset(COLOR_PAIR(3));
    x = (int)(line->px);
    y = (int)(line->py);
    DrawParts(y  , x, "----<>----<>----<>----<>----<>----<>----<>----<>----<>----<>");
}

/* 本体の移動 */
void MoveHontai(Object *hontai)
{
    int     w, h;

    getmaxyx(stdscr, h, w);

    // 移動
    hontai->px += hontai->vx;
    if (hontai->px <= 0)	hontai->px = 0;
    if (hontai->px >= w-3) hontai->px = w-3;	
}

/* 物体の運動 */
void MoveObject(Object *obj)
{
    obj->px += obj->vx;
    obj->py += obj->vy;
}

/*弾の移動*/
void MoveShot(Object *obj)
{
    int w, h;

    getmaxyx(stdscr, h, w);
    MoveObject(obj);
    if (((int)(obj->py) < 0) || ((int)(obj->py) >= h)) obj->life = 0;
}

/* 敵の運動 */
void MoveEnemy(Object *obj)
{
    int w, h;

    getmaxyx(stdscr, h, w);
    MoveObject(obj);
    if ((int)(obj->px) < 4)  (obj->vx *= -1, obj->py += 1);

    if ((int)(obj->px) > w)  (obj->vx *= -1, obj->py += 1);

}

/* 衝突の判定 */
int ChkHit(Object *obj1, Object *obj2)
{
    if (fabs(obj1->px - obj2->px) > (obj1->sx + obj2->sx)) return (0);
    if (fabs(obj1->py - obj2->py) > (obj1->sy + obj2->sy)) return (0);
    return (1);
}

//スコア関数
void DrawBullet(int h, int w, int bullet)
{
    attrset(COLOR_PAIR(2));

    mvprintw(h, w, "bullet:%d", bullet);
}

/* ゲームの本体 */
void Game()
{
    Object	shot[N_SHOT], hontai;
    Object  enemy[N_ENEMY];
    Object	kabe1,kabe2,line;
    int     w, h;
    int	i,j,k,l,m,n;
    int	x=30;
    int	key, fire,ready;
    int bullet = 50;

    srand(time(NULL));

    // 初期設定
    getmaxyx(stdscr, h, w);
    InitShots(shot, N_SHOT, 0.0, 0.0, 0.0, 0.0, 0);
    InitObject(&hontai, (double)w/2.0, (double)(h-4), 0.0, 0.0, 0.0, 1.0, 1);

    for (m = 0;  m< N_ENEMY; m++) {
	InitEnemy(&enemy[m],  (double)Rand(5.0,w-2), (double)Rand(1,20),0.6 , 0.0, 1);
    }

    InitObject(&kabe1,(double)(w-2), (double)(h-8), 0.0, 0.0, 1.0, 2.0, 10);
    InitObject(&kabe2,(double)(0.0), (double)(h-8), 0.0, 0.0, 1.0, 2.0, 10);
    InitObject(&line, (double)(0.0), (double)(h-12),0.0, 0.0, 0.0, 0.0,1);

    ready = 0;

    timeout(0);
    while (1) {
	/*表示*/
	erase();
	getmaxyx(stdscr, h, w);
	DrawShots(shot, N_SHOT);
	DrawEnemies(enemy, N_ENEMY);
	DrawHontai(&hontai);
	DrawKabe(&kabe1);
	DrawKabes(&kabe2);
	DrawLine(&line);
	DrawBullet(0, 5, bullet);
	refresh();	
	// キー入力//
	fire = 0; ;
	key = getch();
	hontai.vx = 0.0;
	switch (key) {
	    case KEY_LEFT :  hontai.vx = -1.0; break;
	    case KEY_RIGHT : hontai.vx =  1.0; break;
	    case 's' :      fire = 1; break;      // 発射
	    case 'q' : return;
	}


	if (ready <= 0) {
	    if (fire == 1) {
		for (i = 0; i < N_SHOT; i++) {
		    if (shot[i].life == 0) {
			InitShot(&shot[i],hontai.px+1, hontai.py, 0, -0.7, 1);
			ready = 5;
			bullet -= 1;
			if (bullet ==0) {
			    GameOver();
			    return;
			}
			break;
		    }
		}
	    }
	} else {
	    ready--;
	}

	for (i = 0; i < N_SHOT; i++) {
	    if (shot[i].life == 0) {
		continue;
	    }

	    for (j = 0; j < N_ENEMY; j++) {
		if (enemy[j].life != 0) {
		    if (ChkHit(&shot[i], &enemy[j]) != 0) {
			shot[i].life = 0;
			enemy[j].life = 0;
			x -= 1;
			if (x == 0) { 
			    GameClear();
			    return;
			}
			break;
		    }
		}
	    }
	    if (kabe1.life != 0) {
		if (ChkHit(&shot[i], &kabe1) != 0) {
		    shot[i].life = 0;
		    kabe1.life -= 1;
		    break;
		}
	    }
	    if (kabe2.life != 0) {
		if (ChkHit(&shot[i], &kabe2) != 0) {
		    shot[i].life = 0;
		    kabe2.life -= 1;
		    break;
		}
	    }
	}
	for (i = 0; i < N_SHOT; i++) {
	    if (shot[i].life != 0) MoveShot(&shot[i]);
	}
	for (j = 0; j < N_ENEMY; j++) {
	    if (enemy[j].life != 0) {
		MoveEnemy(&enemy[j]);
	    }
	}
	for (n = 0; n < N_ENEMY; n++) {
	    if (ChkHit(&enemy[n], &line) != 0) {
		GameOver();
		return;
	    }
	}
	if (hontai.life != 0)
	    MoveHontai(&hontai);	
	// 動作速度調整
	usleep(20000);  // 20,000μ秒＝20 m秒＝0.02秒 停止
    }
}


/* 色の初期化 */
void InitColor(int bg)
{
    start_color();

    /* 文字表示用の色 */
    init_pair(0, COLOR_BLACK, bg);
    init_pair(1, COLOR_RED, bg);
    init_pair(2, COLOR_GREEN, bg);
    init_pair(3, COLOR_YELLOW, bg);
    init_pair(4, COLOR_BLUE, bg);
    init_pair(5, COLOR_MAGENTA, bg);
    init_pair(6, COLOR_CYAN, bg);
    init_pair(7, COLOR_WHITE, bg);

    /* ブロックキャラクタ表示用の色 */
    init_pair(10, COLOR_BLACK, COLOR_BLACK);
    init_pair(11, COLOR_RED, COLOR_RED);
    init_pair(12, COLOR_GREEN, COLOR_GREEN);
    init_pair(13, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(14, COLOR_BLUE, COLOR_BLUE);
    init_pair(15, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(16, COLOR_CYAN, COLOR_CYAN);
    init_pair(17, COLOR_WHITE, COLOR_WHITE);

    /* 背景の色 */
    bkgd(COLOR_PAIR(7));
}
/*タイトル*/
/*タイトル*/
int Title()
{
    int	h, w, key;

    getmaxyx(stdscr, h, w);

    erase();
    attrset(COLOR_PAIR(3));
    mvprintw(3, w/2-25, " SSSS  H   H  OOO   OOO  TTTTT EEEEE RRRR");
    mvprintw(4, w/2-25, "S    S H   H O   O O   O   T   E     R   R");
    mvprintw(5, w/2-25, " S     H   H O   O O   O   T   E     R   R");
    mvprintw(6, w/2-25, "  S    HHHHH O   O O   O   T   EEEEE RRRR");
    mvprintw(7, w/2-25, "   S   H   H O   O O   O   T   E     R R");
    mvprintw(8, w/2-25, "S    S H   H O   O O   O   T   E     R  R");
    mvprintw(9, w/2-25, " SSSS  H   H  OOO   OOO    T   EEEEE R   R");
    attrset(COLOR_PAIR(2));

    mvprintw(16, w/2-4, "[s] Start");
    mvprintw(17, w/2-4, "[q] Quit");
    mvprintw(18, w/2-4, "size[60*54]");

    refresh();

    key = getch();
    return(key);
}

//ゲームオーバー
int GameOver()
{
    int     h, w;

    getmaxyx(stdscr, h, w);

    erase();
    attrset(COLOR_PAIR(2));

    mvprintw(4, w/2-19,  "GGGG   A   M   M EEEEE  OOO  V   V EEEEE RRRR");
    mvprintw(5, w/2-19,  "G     A A  MM MM E     O   O V   V E     R   R");
    mvprintw(6, w/2-19,  "G GG A   A M M M EEEEE O   O V   V EEEEE RRRR");
    mvprintw(7, w/2-19,  "G  G AAAAA M   M E     O   O  V V  E     R R");
    mvprintw(8, w/2-19,  "GGGG A   A M   M EEEEE  OOO    V   EEEEE R  R");

    mvprintw(16, w/2-12, "Please press the [e] key");

    refresh();
    timeout(-1);

    while (getch() != 'e') { 
	endwin();
    }
}

int GameClear()
{
    int     h, w, bullet;

    getmaxyx(stdscr, h, w);

    erase();
    attrset(COLOR_PAIR(2));

    mvprintw(4, w/2-19,  " GGG    A   M   M EEEEE ");
    mvprintw(5, w/2-19,  "G      A A  MM MM E     ");
    mvprintw(6, w/2-19,  "G  GG A   A M M M EEEEE ");
    mvprintw(7, w/2-19,  "G   G AAAAA M   M E     ");
    mvprintw(8, w/2-19,  " GGG  A   A M   M EEEEE ");

    mvprintw(10, w/2-5,  " CCCC  L     EEEEE   A   RRRR");
    mvprintw(11, w/2-5,  "C      L     E      A A  R   R");
    mvprintw(12, w/2-5,  "C      L     EEEEE A   A RRRR" );
    mvprintw(13, w/2-5,  "C      L     E     AAAAA R  R");
    mvprintw(14, w/2-5,  " CCCC  LLLLL EEEEE A   A R   R");

    //DrawBullet(16,w/2-12,bullet*100); //得点

    mvprintw(20, w/2-12, "Please press the [e] key");

    refresh();
    timeout(-1);
    while (getch() != 'e') {
	endwin();
    }
}
int main()
{
    /* curses の設定 */
    initscr();
    curs_set(0);            // カーソルを表示しない
    noecho();               // 入力されたキーを表示しない
    cbreak();               // 入力バッファを使わない(Enter 不要の入力)
    keypad(stdscr, TRUE);   // カーソルキーを使用可能にする
    InitColor(COLOR_BLACK);
    /* ゲーム本体 */  
    while(1) {
	if (Title() == 's') Game();
	if (Title() == 'q') break;	
    }
    /* 終了 */
    endwin();
    return (0);
}

