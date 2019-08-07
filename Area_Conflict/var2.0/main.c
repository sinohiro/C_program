#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

#define MAX 40
#define MAXAMMO 5

//移動系　構造体
typedef struct{
	double px, py; //位置
	double vx, vy; //速度
	double sx, sy; //サイズ
	int life;
} Mobj;		       // Mobile Object

//初期化
void InitMobj(Mobj *obj, double px, double py, double vx, double vy, double sx, double sy, int li){

    obj->px = px; obj->py = py;
    obj->vx = vx; obj->vy = vy;
    obj->sx = sx; obj->sy = sy;
    obj->life = li;
}

//------------------------display
void Display_me(Mobj *me){
	if(me->life == 0)return;
	int i;

	attrset(COLOR_PAIR(2));
	if (me->life > 50)attrset(COLOR_PAIR(5));
	move((int)(me->py), (int)((me->px)-(me->sx)));
	for (i = -(int)(me->sx); i <= (int)(me->sx); i++) {
	addch('#');
 	}
}

void Display_en(Mobj *en){
	if(en->life <= 0) return;
	attrset(COLOR_PAIR(5));
	mvaddch((int)(en->py), (int)(en->px), 'E');
}

void Display_myammo(Mobj *ammo){
  if(ammo->life <= 0) return;
	attrset(COLOR_PAIR(3));
	if(ammo->life > 50)attrset(COLOR_PAIR(6));
	mvaddch((int)(ammo->py), (int)(ammo->px), '*');
}

void Display_enammo(Mobj *ammo){
  if(ammo->life <= 0)return;
	attrset(COLOR_PAIR(4));
	mvaddch((int)(ammo->py), (int)(ammo->px), '*');
}

//------------------------Move
void Moveme(Mobj *me){
  int h, w;

	getmaxyx(stdscr, h, w);

	me->px += me->vx;
	me->py += me->vy;

	if(me->px > w - me->sx-1) me->px = w- me->sx-1;
	if(me->px < me->sx) me->px = me->sx;
	if(me->py > h - me->sy) me->py = h - me->sy;
	if(me->py < 0) me->py = 0;
}

int Moveammo(Mobj *ammo){
    ammo->px += ammo->vx;
    ammo->py += ammo->vy;
    return(0);
}

//------------------------Hit?
int Hit(Mobj *en, Mobj *ammo){
	if(en->life <= 0)return(0);
	if(ammo->life <= 0)return(0);
	if(fabs(en->px - ammo->px) < en->sx && fabs(en->py + en->py) < en->sy) return (1);

	return (0);
}

//------------------------Crl

int Control(Mobj *obj){
  int key;
  obj->vx = 0; obj->vy = 0;
	key = getch();
	switch (key) {
		case KEY_UP:						obj->vy = -1.0; break;
		case KEY_DOWN:        	obj->vy =  1.0; break;
		case KEY_LEFT:        	obj->vx = -1.0; break;
		case KEY_RIGHT:					obj->vx =  1.0; break;
		case 'q':																break;
		case 's':									 return ('s');break;
		default: break;
  }
  return (key);
}

//------------------------Shoot

int Shoot(Mobj *obj, double px, double py, double vx, double vy,int result)
{
    if (obj->life != 0) return (1);
		if (result == 0)		return (1);
    obj->px = px;	// 位置の初期化
    obj->py = py;
    obj->vx = vx;	// 速度の初期化
    obj->vy = vy;
    obj->life = result;
    return (0);
}

//------------------------Kill?

int Kill(Mobj *obj){
  if(obj->life <= 0) return(1);

	obj->life -= 1;
	return (0);
}

int Move(Mobj *obj)
{
	if(obj->life == 0) return(1);

  obj->px += obj->vx;
  obj->py += obj->vy;

  return (0);
}

int Rand(int min, int max){
  return (min + (int)((max - min + 1.0)*rand()/(RAND_MAX + 1.0)));
}

	 


int Game(){
  Mobj me, en[MAX],myammo[MAX], enammo[MAX];
	int h, w;
	int i;
	int a;
	int maxline;
	int r[5];
	int b=0;
	int key;

	getmaxyx(stdscr, h, w);
	//自キャラ初期位置
	InitMobj(&me, (double)w/2.0, (double)(h-4), 0.0, 0.0, 0.5, 0.5, 1);

	for(maxline = 0; maxline < 3; maxline++){
		for(i = 0;i < 20;i++){
			InitMobj(&en[i+(maxline*20)], i*3+5, maxline*2+1, -0.03, 0.0, 1.0, 1.0, 1);
		}
	}

	for(i = 0; i < MAX; i++){
		InitMobj(&myammo[i], 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0);
		InitMobj(&enammo[i], 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0);
	}
	timeout(0);



	while (1) {
		a = 0;
		if (me.life == 0)break;

		erase();
		Display_me(&me);

		for(i = 0; i < MAX; i++){
			Display_en(&en[i]);
			Display_myammo(&myammo[i]);
			Display_enammo(&enammo[i]);
		}

		move(0, 0);
		refresh();

		srand(time(NULL));

		if ((key = Control(&me)) == 'q') return(0);
		Moveme(&me);
		if(key == 'b')timeout(-1);  // debug The World
		if(key == 'g')timeout(0);   // debug END
		if(key == 'n')me.life = 1300;
		if(key == 'c' && me.life>50){
			for(i = 0; i < MAX; i++){
				if(Shoot(&myammo[i],me.px,me.py,0.0,-0.5,me.life)==0)break;
			}
		}
		if(key == 'e'&& me.life>50){
			for(maxline = 0;maxline < MAX; maxline++){
				Shoot(&myammo[maxline],en[maxline].px, en[maxline].py +10,0.0,-0.4,me.life);
			}
		}
		if(key == ' '){
			for(i = 0; i < 5; i++){
				if(Shoot(&myammo[i],me.px,me.py,0.0,-0.5,me.life)==0)break;
			}
		}
		for(i = 0; i < MAX; i++){
			if(en[i].life != 0){
				if(en[i].px > w -2){
					for(maxline = 0; maxline < MAX; maxline++){
						en[maxline].py += 1;
						en[maxline].px -= 1;
						en[maxline].vx *= -1;
					}
				}
				if(en[i].px < 2){
					for(maxline = 0; maxline < MAX; maxline++){
						en[maxline].py += 1;
						en[maxline].px += 2;
						en[maxline].vx *= -1;
					}
				}
				if(en[i].py > h)return(0);
			}

			Move(&en[i]);
			for(maxline = 0; maxline < 4; maxline++){
				r[maxline] = Rand(0,29);
			}
			for(maxline = 0; maxline < MAX; maxline++){
				if (Hit(&en[i], &myammo[maxline]) != 0){
					Kill(&myammo[maxline]);
					Kill(&en[i]);
				}
			}
			if(Rand(0,100) < 7){
				r[5] = r[Rand(0,4)];
				if(Shoot(&enammo[i],en[r[5]].px+1,en[r[5]].py+1,0.0,0.3,en[r[5]].life)==0);
			}

			Move(&myammo[i]);
			Move(&enammo[i]);

			if (myammo[i].py < 0) myammo[i].life =0;
			if (enammo[i].py > h) Kill(&enammo[i]);

			if(Hit(&me,&enammo[i]) !=0){
				Kill(&me);
				Kill(&enammo[i]);
			}
			if(Hit(&en[i],&me) != 0){
				Kill(&me);
				Kill(&en[i]);
			}
			if(en[i].life == 1)a++;

		}
		if(a%10 == 0 && a != b){
			for(i = 0; i < MAX; i++){
				en[i].vx *= 1.5;
			}
			b = a;
		}
		if(a == 0)return(2);

		usleep(20000);

	}
	return(0);
}

int Title(){
	int h, w, key;

	getmaxyx(stdscr, h, w);

	erase();
	attrset(COLOR_PAIR(1));
	mvaddstr(h/2-2, (w-15)/2, "Area_Conflict");
	attrset(COLOR_PAIR(2));
	mvaddstr(h/2,   (w-21)/2, "[Space] start");
	mvaddstr(h/2+1, (w-16)/2, " [Q] quit");
	attrset(COLOR_PAIR(3));
	mvaddstr(h/2+3, (w-21)/2, "[Space] [W] [S] [A] [D]");
	mvaddstr(h/2+4, (w-21)/2, " fire    up  down  left  right");
	attrset(COLOR_PAIR(7));
	mvaddstr(h/2+8, (w-30)/2, "c 2018-2019 Clanguage / sinohiro");
	move(0, 0);

	timeout(-1);
	key = getch();

	return (key);
	printf("Title_Ok\n");
}


void InitColor(int bg){
	start_color();

	init_pair(0, COLOR_BLACK, bg);
	init_pair(1, COLOR_RED, bg);
	init_pair(2, COLOR_GREEN, bg);
	init_pair(3, COLOR_YELLOW, bg);
	init_pair(4, COLOR_BLUE, bg);
	init_pair(5, COLOR_MAGENTA, bg);
	init_pair(6, COLOR_CYAN, bg);
	init_pair(7, COLOR_WHITE, bg);

	bkgd(COLOR_PAIR(7));
}

int main(){

	int result = 1;
	initscr();	// 端末制御を開始.
	noecho();	// 入力されたキーを表示しない
	cbreak();	// 入力バッファを使わない(Enter 不要の入力)
	curs_set(0);	// カーソルを表示しない
	keypad(stdscr, TRUE);

	InitColor(COLOR_BLACK);

	while (1) {
		if (Title() == 'q')break;
			result = Game();

		if(result == 0){
      clear();
      attrset(COLOR_PAIR(10));
      addstr("game over\n");
    }
    if(result == 2){
      clear();
      attrset(COLOR_PAIR(10));
      addstr("clear\n");
    }
	}

	endwin();
	return (0);
}
