#include "pch.h"
double ballx, bally, x_move, y_move;
int radius, ballcolor;
int boardx, boardy, boardhigh, boardwidth, boardleft, boardright, boardtop, boardbottom;
int brickhigh, brickwidth, bricknumber;
int nowheart, heartx, hearty, heartvanish;
int stage, colortype,score;
int map[BRICKLINE][BRICKROW], color[BRICKLINE][BRICKROW];
clock_t t, t_save;
extern void menu(void);