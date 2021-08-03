#pragma once
#include "button.h"
#include "game.h"

class Start :
	public Button
{
public:
	Start(int btnx, int btny, int wid, int len, const char* text);
	void pressfuc();
};