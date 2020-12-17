#pragma once
#define HIGH 480  
#define WIDTH1 960
#define WIDTH2 640
#define BRICKROW 11
#define BRICKLINE 12
#define BACKROUNDCOLOR WHITE
#define BRICKCOLOR GREEN
#define BOARDCOLOR LIGHTBLUE
#define SPEED 2
#define Heartx WIDTH2/2
#define Hearty HIGH/2

extern int ballx, bally, x_move, y_move, radius, ballcolor;
extern int boardx, boardy, boardhigh, boardwidth, boardleft, boardright, boardtop, boardbottom;
extern int brickhigh, brickwidth, bricknumber;
extern int nowheart, heartx, hearty, heartvanish;
extern int stage, colortype, score;
extern int map[BRICKLINE][BRICKROW], color[BRICKLINE][BRICKROW];
extern clock_t t, t_save;