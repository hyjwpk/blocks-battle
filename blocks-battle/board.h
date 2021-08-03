#pragma once
#include "difficulty.h"
#include "mouse.h"
#include "load.h"
#include "stage.h"
#include "top.h"
#include "menu.h"

class Board
{
public:
	Board(int boardx = WIDTH2 / 2, int boardy = HIGH - HIGH / 25 / 2, int boardhigh = HIGH / 25);
	void setlrtb(int boardx, int boardy, int boardhigh = HIGH / 25);
	void move();
	void crash();
	void print();
	int boardx, boardy, boardhigh, boardwidth, boardleft, boardright, boardtop, boardbottom;
	static Board* board;

};