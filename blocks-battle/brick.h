#pragma once
#include "color.h"
#include "ball.h"

class Brick
{
public:
	static void print();
	static void crash();
	static int brickhigh, brickwidth, lowest;
	static int map[BRICKLINE][BRICKROW], color[BRICKLINE][BRICKROW], bricknumber;
};