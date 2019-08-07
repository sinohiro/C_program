#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>


int Game(int h, int w){
	erase();
	getmaxyx(stdscr, h, w);
	mvaddstr(h/2, w/2, "Hello_World");
	refresh();
	getch();
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
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	InitColor(COLOR_BLACK);

	int h, w;

	while (1) {
		if (Title() == 'q')break;
			Game(h,w);
	}

	endwin();
	return (0);
}
