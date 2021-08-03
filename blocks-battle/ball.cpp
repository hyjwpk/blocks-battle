#include "pch.h"
#include "ball.h"

Ball* Ball::ball = NULL;
int Ball::speed = 10;

Ball::Ball(double x, double y, double x_move, double y_move, int radius, COLORREF color)
{
	this->x = x;
	this->y = y;
	this->x_move = x_move;
	this->y_move = y_move;
	this->radius = radius;
	this->color = BLUE;
}

void Ball::move()
{
	x = x + x_move;
	y = y + y_move;
}

void Ball::crash()
{
	if (x - radius + x_move <= 0 || x + radius + x_move >= WIDTH2) x_move = -x_move;
	if (y - radius + y_move <= 0) y_move = -y_move;
	if (y + radius + y_move >= HIGH)
	{
		Heart::value--;
		x = Board::board->boardx;
		y = (double)Board::board->boardtop - radius;
	}

}

void Ball::print()
{
	setcolor(WHITE);
	setfillcolor(color);
	solidcircle((int)x, (int)y, radius);
}
