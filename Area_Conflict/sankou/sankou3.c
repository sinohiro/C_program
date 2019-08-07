
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define EMAX 200 //敵の同時存在数	       	
#define AMMOMAX 3 //自弾の最大同時存在数



//*****************************************************************************
/* 移動物体の構造体 */
typedef struct {
    double px, py;	// Position（位置）
    double vx, vy;	// Velocity（速度）
    double sx, sy;	// Size（サイズ）
    int life;             //0died 1HaveLife
    int buff;             //atode
} Mobj;		// Mobile Object（移動物体）

/* 移動物体の初期化 */
void InitMobj(Mobj *obj,
	double px, double py, 
	double vx, double vy,
	double sx, double sy,
	int life)
{
    obj->px = px; obj->py = py;
    obj->vx = vx; obj->vy = vy;
    obj->sx = sx; obj->sy = sy;
    obj->life = life;
}

//****************************************************************************
/* 表示 */
void DrawI(Mobj *r)
{  
    attrset(COLOR_PAIR(3));
    if(r->life == 0)attrset(COLOR_PAIR(11));

    move((int)(r->py), (int)((r->px)-(r->sx)));

    addch('@'); 
}

void DrawEN(Mobj *EN)
{
    if(EN->life == 0) return;
    attrset(COLOR_PAIR(5));

    move((int)(EN->py),(int)(EN->px));

    addch('E');

}


void Drawmyammo(Mobj *ammo)		// 描画
{
    if(ammo->life != 1) return;

    attrset(COLOR_PAIR(3));
    move((int)(ammo->py), (int)(ammo->px));
    addch('^');	
}


//　　ここまで描画関数

//***************************************************************************::
/*  動作させる関数群*/
int MoveI(Mobj *r)
{
    int	w, h;

    if (r->life == 0) return (1);	// 死亡中なら無視
    getmaxyx(stdscr, h, w);

    // 移動
    r->px += r->vx;
    r->py += r->vy;

    if(r->px < r->sx)       r->px++;
    if(r->px > w-r->sx-1)   r->px--;

    if(r->py <  h/2 -r->sy) r->py++;
    if(r->py > h -r->sy)    r->py--;

    return(0);
}

/* ammo*/
int Moveammo(Mobj *ammo)		// 動作
{
    ammo->px += ammo->vx;
    ammo->py += ammo->vy;
    return(0);
}


//   ここまで動作関数群

//**********************************************************************
int CHKHIT(Mobj *r, Mobj *b)//当たり判定の関数（チェック）
{
    if(r->life == 0
	    ||
	    b->life == 0)return(1);

    if (fabs(r->px - b->px) > (r->sx + b->sx)
	    ||
	    fabs(r->py - b->py) > (r->sy + b->sy)) return (1);
    return (0);
}

//***********************************************************************
int Control(Mobj *r)//打鍵されたボタンを返す関数
{
    int key;

    key = getch();
    r->vx = r->vy = 0.0;
    switch (key) {
	case KEY_UP :		r->vy = -1.0; break;
	case KEY_DOWN :      	r->vy =  1.0; break;
	case KEY_LEFT :      	r->vx = -1.0; break;
	case KEY_RIGHT :	r->vx =  1.0; break;

	case 's': case 'S':            return ('s'); break;    
	case 'q': case 'Q': case '\e': return ('q'); break;
	default: break;
    }
    return (key);

}

//***********************************************************************
// 発射関数
int Shoot(Mobj *obj, double px, double py, double vx, double vy,int life)
{
    if (obj->life != 0) return (1);	// すでに活動中なら無視

    obj->px = px;	// 位置の初期化
    obj->py = py;
    obj->vx = vx;	// 速度の初期化
    obj->vy = vy;
    obj->life = life;

    return (0);
}

//**********************************************************************
int Kill(Mobj *obj)//動体を生存から死亡へ変更する関数
{ 
    obj->life = 0;
    return(0);
}
//**********************************************************************


// min 以上，max 以下の整数乱数
int Rand(int min, int max)
{
    return (min + (int)((max - min + 1.0)*rand()/(RAND_MAX + 1.0)));
}




int title()
{
    int w,h,y,z,key;
    getmaxyx(stdscr,h,w);
    y = h/4;
    z = 5;
    attrset(COLOR_PAIR(6));
    mvaddstr(y+1, z,"  ###   ##   ##   ###  ### #####  ##         ##  ###   ##      ##        ");
    mvaddstr(y+2, z," #####  ##   ##  ## ##  #   #  ## ##   ###   ## #####  ##      ##        ");
    mvaddstr(y+3, z,"##   ## ##   ## ##   ## #   #   #  ## ## ## ## ##   ## ##      ##        ");
    mvaddstr(y+4, z,"##   ## ##   ## ##   ## #   #   #  ## ## ## ## ##   ## ##      ##        ");
    mvaddstr(y+5, z,"#######  ## ##   ## ##  #   #  ##   ###   ###  ####### ##      ##        ");
    mvaddstr(y+6, z,"##   ##   ###     ###  ### #####    ###   ###  ##   ## ####### #######   ");
    mvaddstr(y+7, z,"                                                                         ");
    mvaddstr(y+8, z,"              Please Press Key                                           ");
    mvaddstr(y+9, z,"                           s   Game Start                                ");
    mvaddstr(y+10,z,"                           e   Exit                                      ");
    mvaddstr(y+11,z,"   1 sec = 1 Score   Break Wall = -1~                                    ");
    mvaddstr(y+12,z,"                                                                         ");
    mvaddstr(y+13,z,"                                                                         ");

    timeout(-1);
    key = getch();

    return(key);
    refresh();
}




int GAMEOVER()
{
    int w,h,y,z,key;
    getmaxyx(stdscr,h,w);
    y = h/4;
    z = 5;
    usleep(100000);

    attrset(COLOR_PAIR(2));
    mvaddstr(y+1, z,"       ## ######    ###    ### ###  ######  ####   ##   ## ###### ######     ");
    mvaddstr(y+2, z,"      ## ##    ##  ## ##  ## ### ## #      ##  ##  ##   ## #      #    ##    ");
    mvaddstr(y+3, z,"     ##  ##       ##   ## ##  #  ## ####  ##    ## ##   ## ####   #    ##    ");
    mvaddstr(y+4, z,"    ##   ##   ### ##   ## ##  #  ## ####  ##    ## ##   ## ####   ######     ");
    mvaddstr(y+5, z,"   ##    ##    ## ####### ##     ## #      ##  ##   ## ##  #      #    ##    ");
    mvaddstr(y+6, z,"  ##      ######  ##   ## ##     ## ######  ####     ###   ###### #     #   ");
    mvaddstr(y+7, z," ##              THANK YOU FOR PLAYING !!  PREASE PRESS E.                   ");
    mvaddstr(y+8, z,"########################################################################     ");


    timeout(-1);

    key = getch();

    return(key);
    refresh();
}


void Score(int score)
{
    int w, h;

    getmaxyx(stdscr, h, w);
    attrset(COLOR_PAIR(4));
    mvprintw(0, 0, "TIME : %d", score);

}


void Game()
{   

    Mobj I, ammo[AMMOMAX];		//ziki
    Mobj EN[EMAX]; 
    int  w, h, key, i, i2,asd=0,asd2=0;
    int cnt=10000;
    int score = 0;
    time_t t1, t2;

SRT:

    srand(time(NULL));	// 乱数のシャッフル（時間的に変化）
    // 初期設定
    getmaxyx(stdscr, h, w);
    InitMobj(&I, (double)w/2.0, (double)(h-4), 0.0, 0.0, 0.0, 1.0,1);
    //自弾初期化
    for(i=0;i < AMMOMAX;i++)
    {
	InitMobj(&ammo[i], 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0);
    }
    //敵初期化
    for(i=0;i < EMAX;i++)
    {
	InitMobj(&EN[i], 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0);
    }
    time(&t1);
    timeout(0);
    score=0;
    asd=0;
    asd2=0;


    while (1) {
	// キャラクタの表示
	erase();
	DrawI(&I);

	Score(score);//スコアという名の経過時間表示と思わせたスコア表示
	//自弾表示
	for(i=0;i < AMMOMAX;i++)
	{
	    Drawmyammo(&ammo[i]);
	}

	//敵表示
	for(i=0;i < EMAX;i++)
	{
	    DrawEN(&EN[i]);
	}


	while(I.life ==0)
	{
	    erase();
	    while(1)
	    {
		key = GAMEOVER();
		if(key =='E')break;
	    }//E osumede gameover no mama

	    refresh();
	    while(1)
	    {
		key = title();
		if(key == 's')goto SRT;
		if(key == 'e')break;
	    }//maa sonomama 
	    break;
	}   
	if(I.life == 0)break;//kokode game owari

	move(0, 0);		// カーソルを隅へ移動（curs_set() が無効でも，画面の乱れを最小化）
	refresh();

	// キー入力／キャラクタの移動
	//zikikankei
	if ((key=Control(&I)) == 'q') break;
	MoveI(&I);

	for(i=0;i < EMAX;i++)
	{
	    if(CHKHIT(&I, &EN[i]) == 0)Kill(&I);
	}

	//Myammo
	for(i=0;i < AMMOMAX;i++)
	{

	    if (key == 's') Shoot(&ammo[i], I.px, I.py, 0.0, -0.05, I.life);
	    Moveammo(&ammo[i]);
	    if (ammo[i].py < 0 )Kill(&ammo[i]);

	    for(i2=0;i2 < EMAX;i2++)
	    {

		if(CHKHIT(&ammo[i], &EN[i2]) == 0)
		{
		    Kill(&ammo[i]);
		    Kill(&EN[i2]);
		    score -= 1;	
		} 

	    }

	}  


	//teki
	for(i=0;i < EMAX;i++)
	{	
	    Moveammo(&EN[i]);
	    Shoot(&EN[i], Rand(0, w), 0.0, 0.0, 0.07, 1);
	    if(EN[i].py > h)Kill(&EN[i]);
	}


	// 動作速度調整    
	usleep(cnt);   
	time(&t2);

	asd = (int)difftime(t2,t1) - asd2; //ima - 1tumae = 1sec
	asd2 = (int)difftime(t2,t1);//1tumae

	score += asd;


    }

}


int main()
{
    char key;


    /* curses の設定 */
    initscr();
    curs_set(0);		// カーソルを表示しない
    noecho();		// 入力されたキーを表示しない
    cbreak();		// 入力バッファを使わない(Enter 不要の入力)
    keypad(stdscr, TRUE);	// カーソルキーを使用可能にする

    /* カラーの設定 */
    start_color();
    init_pair(1, COLOR_RED, COLOR_RED);	       
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);	
    init_pair(3, COLOR_RED,COLOR_BLACK);		
    init_pair(4, COLOR_WHITE,COLOR_BLUE);
    init_pair(5, COLOR_GREEN ,COLOR_GREEN);
    init_pair(6, COLOR_CYAN,COLOR_BLACK);
    init_pair(10, COLOR_WHITE, COLOR_BLACK);	// 白字／黒地
    init_pair(11, COLOR_BLACK, COLOR_WHITE);	// 白地

    bkgd(COLOR_PAIR(10));

    //キーボード入力でどこに進むか決める
    while(1)
    {
	key = title();

	if(key == 's')break;
	if(key == 'e')goto END;
    }
    /* ゲーム本体 */
    Game();  
    /* 終了 */
END:
    endwin();
    return (0);
}


