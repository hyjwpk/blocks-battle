#pragma once
#include "heart.h"
#include "board.h"

class Ball
{
public:
	Ball(double x, double y, double x_move = 0, double y_move = -2, int radius = 10, COLORREF color = BLUE);
	void move();
	void crash();
	void print();
	double x;
	double y;
	double x_move;
	double y_move;
	int radius;
	COLORREF color;
	static Ball* ball;
	static int speed;
};