#pragma once
#include "button.h"
#include "game.h"
#include "color.h"
#include "ball.h"

class Load :
	public Button
{
public:
	Load(int btnx, int btny, int wid, int len, const char* text);
	void pressfuc();
	static void save();
	static bool read();
};