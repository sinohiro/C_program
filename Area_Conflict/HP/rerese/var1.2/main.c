#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

//移動系　構造体
typedef struct{
    	double px, py; //位置
	double vx, vy; //速度
	double sx, sy; //サイズ
	int life;
} Mobj;		       // Mobile Object

void InitMobj(Mobj *obj, double px, double py, double vx, double vy, double sx, double sy, int li){
    
    obj->px = px; obj->py = py; 
    obj->vx = vx; obj->vy = vy; 
    obj->sx = sx; obj->sy = sy; 
    obj->life = li; 
}

void Drawme(Mobj *me){

    if(me->life == 0)return; 
    int     i;  

    attrset(COLOR_PAIR(1));
    if(me->life > 50)attrset(COLOR_PAIR(5));
    move((int)(me->py), (int)((me->px)-(me->sx)));
    for (i = -(int)(me->sx); i <= (int)(me->sx); i++) {
	addch('#');
    }   
}

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

int Control(Mobj *obj){
    int key;
    obj->vx = 0; obj->vy = 0;
    key = getch();
    switch (key) {
	case KEY_UP:		obj->vy = -1.0; break;
	case KEY_DOWN:        	obj->vy =  1.0; break;
	case KEY_LEFT:        	obj->vx = -1.0; break;
	case KEY_RIGHT:		obj->vx =  1.0; break;
	case 'q':				break;
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

	 


int Game(){
    	Mobj me;
	int h, w;
	int key;

	getmaxyx(stdscr, h, w);
	InitMobj(&me, (double)w/2.0, (double)(h-4), 0.0, 0.0, 0.5, 0.5, 1);

	timeout(0);

	while (1) {
		erase();
		Drawme(&me);

		move(0, 0);
		refresh();

		if ((key = Control(&me)) == 'q') return(0);
		Moveme(&me);
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
}


void InitColor(int bg){
	start_color();

	/* 文字用 */
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
	initscr();	// 端末制御を開始.
	noecho();	// 入力されたキーを表示しない
	cbreak();	// 入力バッファを使わない(Enter 不要の入力)
	curs_set(0);	// カーソルを表示しない
	keypad(stdscr, TRUE);

	InitColor(COLOR_BLACK);

	while (1) {
		if (Title() == 'q')break;
			Game();
	}

	endwin();
	return (0);
}
