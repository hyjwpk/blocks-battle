#include "pch.h"
#include "music.h"
#pragma comment(lib,"Winmm.lib")//µ˜”√Winmm.libø‚≤•∑≈“Ù¿÷

//ball
double ballx, bally, x_move, y_move;
int radius, ballcolor;
//board
int boardx, boardy, boardhigh, boardwidth, boardleft, boardright, boardtop, boardbottom;
//brick
int brickhigh, brickwidth, bricknumber;
//heart
int nowheart, heartx, hearty, heartvanish;
//game
int stage, colortype, score;
int map[BRICKLINE][BRICKROW], color[BRICKLINE][BRICKROW];
clock_t t, t_save;

Music mu_background(IDR_MP31, "background");
Music mu_crash(IDR_MP32, "crash");
Music mu_dead(IDR_MP33, "dead");

extern void menu(void);
extern DWORD WINAPI Thread_GetMouseMsg(PVOID pMyPara);