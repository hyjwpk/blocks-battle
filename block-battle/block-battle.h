#include "pch.h"
int ballx, bally, x_move, y_move, radius, ballcolor;
int boardx, boardy, boardhigh, boardwidth, boardleft, boardright, boardtop, boardbottom;
int brickhigh, brickwidth, bricknumber;
int nowheart, heartx, hearty, heartvanish;
int stage, colortype,score;
int map[BRICKLINE][BRICKROW], color[BRICKLINE][BRICKROW];
extern void menu(void);