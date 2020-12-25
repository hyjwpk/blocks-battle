#pragma once
#include "music.h"

#define HIGH 580  
#define WIDTH1 960 //窗口长度
#define WIDTH2 640//游戏区域长度

#define BRICKROW 11
#define BRICKLINE 12

#define BACKROUNDCOLOR WHITE
#define BOARDCOLOR LIGHTBLUE


extern double ballx, bally, x_move, y_move;
extern int radius, ballcolor;
extern int boardx, boardy, boardhigh, boardwidth, boardleft, boardright, boardtop, boardbottom;
extern int brickhigh, brickwidth, bricknumber;
extern int nowheart, heartx, hearty, heartvanish;
extern int stage, colortype, score;
extern int map[BRICKLINE][BRICKROW], color[BRICKLINE][BRICKROW];
extern clock_t t, t_save;
extern Music mu_background,mu_crash, mu_dead;
extern int tough, soundmode, timesetting, speed,control;
extern int flashx, flashy, flashvanish;