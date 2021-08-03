#pragma once
#include "board.h"

class Heart
{
public:
	Heart(int x, int y, int size);
	static void control();
	int x;
	int y;
	static bool exist;
	static Heart* heart;
	static int value;
private:
	static void display();
	void property();
	int size;
	IMAGE mask, picture;
};