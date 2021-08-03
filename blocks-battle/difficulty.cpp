#include "pch.h"
#include "difficulty.h"

int Difficulty::tough = EASY;

Difficulty::Difficulty(int btnx, int btny, int wid, int len, const char* text) :Button(btnx, btny, wid, len, text)
{
	changeButtonText();
}

void Difficulty::pressfuc()
{
	if (!press) return;
	tough++;
	tough %= 3;
	changeButtonText();
}

void Difficulty::changeButtonText()
{
	if (tough == EASY) text = "难度:１";
	else if (tough == MEDIUM) text = "难度:２";
	else if (tough == HARD) text = "难度:３";
}

void Difficulty::updateSet()
{
	if (tough == EASY)
	{
		Ball::ball->y_move = -2;
		Ball::speed = 10;
	}
	else if (tough == MEDIUM)
	{
		Ball::ball->y_move = -3;
		Ball::speed = 15;
	}
	else if (tough == HARD)
	{
		Ball::ball->y_move = -4;
		Ball::speed = 20;
	}
}