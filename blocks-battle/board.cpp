#include "pch.h"
#include "board.h"

Board* Board::board = NULL;

Board::Board(int boardx, int boardy, int boardhigh)
{
	this->boardx = boardx;
	this->boardy = boardy;
	this->boardhigh = boardhigh;
	if (Difficulty::tough == 0) boardwidth = WIDTH2 / 3;
	else if (Difficulty::tough == 1) boardwidth = WIDTH2 / 4;
	else if (Difficulty::tough == 2) boardwidth = WIDTH2 / 5;
	setlrtb(boardx, boardy);
}

void Board::setlrtb(int boardx, int boardy, int boardhigh)
{
	this->boardx = boardx;
	this->boardy = boardy;
	this->boardhigh = boardhigh;
	boardleft = boardx - boardwidth / 2;
	boardright = boardx + boardwidth / 2;
	boardtop = boardy - boardhigh / 2;
	boardbottom = boardy + boardhigh / 2;
}

void Board::move()
{
	int boardx = Mouse::msg.x, boardy = Mouse::msg.y;
	if (boardy - boardhigh / 2 < (Brick::lowest + 1) * Brick::brickhigh) boardy = (Brick::lowest + 1) * Brick::brickhigh + boardhigh / 2;
	if (boardy + boardhigh / 2 > HIGH) boardy = HIGH - boardhigh / 2;
	if (boardx - boardwidth / 2 < 0) boardx = boardwidth / 2;
	if (boardx + boardwidth / 2 > WIDTH2) boardx = WIDTH2 - boardwidth / 2;
	setlrtb(boardx, boardy);
}

void Board::crash()
{
	if ((Ball::ball->y - Ball::ball->radius) <= boardbottom && (Ball::ball->y + Ball::ball->radius + Ball::ball->y_move) >= boardtop && Ball::ball->x >= boardleft && Ball::ball->x <= boardright)
	{
		Ball::ball->y_move = -fabs(Ball::ball->y_move);
		Ball::ball->x_move = (Ball::ball->x - boardx) / boardwidth * Ball::ball->speed;
	}

	if (Ball::ball->y > boardtop && Ball::ball->y < boardbottom && Ball::ball->x >= boardleft && Ball::ball->x <= boardright)
	{
		Ball::ball->y = (double)boardtop - Ball::ball->radius;
	}
}

void Board::print()
{
	setcolor(WHITE);
	setfillcolor(BOARDCOLOR);
	solidrectangle(boardleft, boardtop, boardright, boardbottom);
}
