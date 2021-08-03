#pragma once
#include "ball.h"

class Flash
{
public:
	Flash(int x, int y, int size);
	static void control();
	int x;
	int y;
	static bool exist;
	static Flash* flash;
private:
	void property();
	int size;
	IMAGE mask, picture;
};