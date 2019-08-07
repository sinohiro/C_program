#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ABC 40

/* 移動物体の構造体 */
typedef struct {
	double px, py;	// Position（位置）
	double vx, vy;	// Velocity（速度）
	double sx, sy;	// Size（サイズ)
	int life;
} Mobj;		// Mobile Object（移動物体）

/* 移動物体の初期化 */
void InitMobj(Mobj *obj,
		double px, double py, double vx, double vy, double sx, double sy, int li)
{
	obj->px = px; obj->py = py;
	obj->vx = vx; obj->vy = vy;
	obj->sx = sx; obj->sy = sy;
	obj->life = li;
}

void Drawme(Mobj *me)
{
	if(me->life == 0)return; 
	int	i;

	attrset(COLOR_PAIR(1));
	if(me->life > 50)attrset(COLOR_PAIR(5));
	move((int)(me->py), (int)((me->px)-(me->sx)));
	for (i = -(int)(me->sx); i <= (int)(me->sx); i++) {
		addch('#');
	} 
}

void Drawteki(Mobj *teki)
{
	if(teki->life <= 0)return;
	attrset(COLOR_PAIR(2));
	mvaddch((int)(teki->py), (int)(teki->px), '#');
}

void DrawMtama(Mobj *tama)
{
	if(tama->life <= 0)return;
	attrset(COLOR_PAIR(4));
	if(tama->life > 50)attrset(COLOR_PAIR(6));
	mvaddch((int)(tama->py), (int)(tama->px), '*');
}

void DrawEtama(Mobj *tama)
{
	if(tama->life <= 0)return;
	attrset(COLOR_PAIR(3));
	mvaddch((int)(tama->py), (int)(tama->px), '*');
}
void Moveme(Mobj *me)
{
	int	w, h;

	getmaxyx(stdscr, h, w);

	me->px += me->vx;
	me->py += me->vy;

	if(me->px > w - me->sx-1) me->px = w- me->sx-1;
	if(me->px < me->sx) me->px = me->sx;
	if(me->py > h - me->sy) me->py = h - me->sy;
	if(me->py < 0) me->py = 0;

}
/*
void Moveteki(Mobj *teki)
{
	int	w, h;

	getmaxyx(stdscr, h, w);

	if ((teki->px) < (teki->sx)) teki->vx = +fabs(teki->vx);
	if (((double)(w-1) - teki->px) < (teki->sx)) teki->vx = -fabs(teki->vx);
	if ((teki->py) < (teki->sy)) teki->vy = +fabs(teki->vy);
	if (((double)(h/2) - teki->py) < (teki->sy)) teki->vy = -fabs(teki->vy);

	teki->px += teki->vx;
	teki->py += teki->vy;
}
*/

int ChkHit(Mobj *teki, Mobj *tama)
{
	if(teki->life <=0)return(0);
	if(tama->life <=0)return(0);
	if(fabs(teki->px - tama->px) < teki->sx &&
			fabs(teki->py - tama->py) < teki->sy)  return (1);
	return (0);
}

int Shoot(Mobj *obj, double px, double py, double vx, double vy,int hoge)
{

	if(obj->life != 0) return(1);
	if(hoge ==0)return(1);
	obj->px = px-1;
	obj->py = py;
	obj->vx = vx;
	obj->vy = vy;
	obj->life = hoge; 
	return(0);
}

int Control(Mobj *obj)
{
	int key;
	obj->vx = 0; obj->vy = 0;
	key = getch();
	switch (key) {
		case KEY_UP :		obj->vy = -1.0; break;
		case KEY_DOWN :		obj->vy =  1.0; break;
		case KEY_LEFT :		obj->vx = -1.0; break;
		case KEY_RIGHT :	obj->vx =  1.0; break;
		case 'q': case 'Q': case '\e': return ('q'); break;
		default: break;
	}
	return (key);
}

int Move(Mobj *obj)
{
	if(obj->life == 0) return(1);

	obj->px += obj->vx;
	obj->py += obj->vy;

	return (0);
}


int Kill(Mobj *obj)
{
	if(obj->life <= 0) return(1);

	obj->life -= 1;
	return(0);
}
int Rand(int min, int max)
{
	return (min + (int)((max - min + 1.0)*rand()/(RAND_MAX + 1.0)));
}




/* ゲームの本体 */
int Game()
{
	Mobj me, teki[ABC], Mtama[ABC],Etama[ABC];
	int w, h;
	int i,a,m;
	int r[5];
	int b=0;
	int key;

	// 初期設定
	getmaxyx(stdscr, h, w);
	InitMobj(&me, (double)w/2.0, (double)(h-4), 0.0, 0.0, 0.5, 0.5, 1);
	for(m=0;m<3;m++){
		for(i=0;i<20;i++){
			InitMobj(&teki[i+(m*20)], i*3+5, m*2+1, -0.03, 0.0, 1.0, 1.0, 1);
		}
	}
	for(i=0;i<ABC;i++){
		InitMobj(&Mtama[i],0,0,0.0,0,0,0,0);
		InitMobj(&Etama[i],0,0,0.0,0,0,0,0);
	}
	timeout(0);

	while (1) {
		a=0;
		if(me.life == 0)break;

		erase();
		Drawme(&me);
		for(i=0;i<ABC;i++){
			Drawteki(&teki[i]);
			DrawMtama(&Mtama[i]);
			DrawEtama(&Etama[i]);
		}
		move(0, 0);
		refresh();


		srand(time(NULL));

		if ((key=Control(&me)) == 'q') return(0);
		Moveme(&me);
		if(key == 'b')timeout(-1);
		if(key == 'g')timeout(0);
		if(key == 'n')me.life = 1300;
		if(key == 'c' && me.life>50){
			for(i=0 ; i<ABC; i++){
				if(Shoot(&Mtama[i],me.px,me.py,0.0,-0.5,me.life)==0)break;
			}
		}
		if(key == 'e'&& me.life>50){
			for(m=0;m<ABC;m++){
				Shoot(&Mtama[m],teki[m].px, teki[m].py +10,0.0,-0.4,me.life);
			}
		}
		if(key == ' '){
			for(i=0;i<5;i++){
				if(Shoot(&Mtama[i],me.px,me.py,0.0,-0.5,me.life)==0)break;
			}
		}
		for(i=0;i<ABC;i++){
			if(teki[i].life != 0){	
				if(teki[i].px > w -2){
					for(m=0;m<ABC;m++){
						teki[m].py += 1;
						teki[m].px -= 1;
						teki[m].vx *= -1;
					}
				}
				if(teki[i].px < 2){
					for(m=0;m<ABC;m++){
						teki[m].py += 1;
						teki[m].px += 2;
						teki[m].vx *= -1;
					}
				}
				if(teki[i].py > h)return(0);
			}

			Move(&teki[i]);
			for(m=0;m<4;m++){
				r[m] = Rand(0,29);
			}
			for(m=0;m<ABC;m++){
				if (ChkHit(&teki[i], &Mtama[m]) != 0){
					Kill(&Mtama[m]);
					Kill(&teki[i]);
				}
			}
			if(Rand(0,100) < 7){
				r[5] = r[Rand(0,4)];
				if(Shoot(&Etama[i],teki[r[5]].px+1,teki[r[5]].py+1,0.0,0.3,teki[r[5]].life)==0);
			}

			Move(&Mtama[i]);
			Move(&Etama[i]);

			if (Mtama[i].py < 0) Mtama[i].life =0;
			if (Etama[i].py > h) Kill(&Etama[i]);

			if(ChkHit(&me,&Etama[i]) !=0){
				Kill(&me);
				Kill(&Etama[i]);
			}
			if(ChkHit(&teki[i],&me) != 0){
				Kill(&me);
				Kill(&teki[i]);
			}
			if(teki[i].life == 1)a++;

		}
		if(a%10 == 0 && a != b){
			for(i=0;i<ABC;i++){
				teki[i].vx *= 1.5;
			}
			b = a;
		}
		if(a == 0)return(2);

		usleep(20000);
	}
	return(0);
}

int main()
{
	int key;
	int hoge = 1;
	/* curses の設定 */
	initscr();
	curs_set(0);		// カーソルを表示しない
	noecho();		// 入力されたキーを表示しない
	cbreak();		// 入力バッファを使わない(Enter 不要の入力)
	keypad(stdscr, TRUE);	// カーソルキーを使用可能にする


	/* カラーの設定 */
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_CYAN);		// 水色の■
	init_pair(2, COLOR_YELLOW, COLOR_YELLOW);	// 黄色の■
	init_pair(3, COLOR_RED,COLOR_RED);		//hogeの■
	init_pair(4, COLOR_BLUE,COLOR_BLUE);
	init_pair(5, COLOR_GREEN ,COLOR_GREEN);
	init_pair(6, COLOR_MAGENTA,COLOR_MAGENTA);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);	// 白字／黒地
	bkgd(COLOR_PAIR(10));

	/* ゲーム本体 */
	while(1){
		move(1,0);
		addstr("[a] start\n");
		addstr("[q] quit");
		key = getch();
		if(key == 'a')hoge = Game();
		if(hoge == 0){
			clear();
			attrset(COLOR_PAIR(10));
			addstr("game over\n");
		}
		if(hoge == 2){
			clear();
			attrset(COLOR_PAIR(10));
			addstr("clear\n");
		}
		if(key == 'q')break;
	}
	/* 終了 */
	endwin();
	return (0);
}
