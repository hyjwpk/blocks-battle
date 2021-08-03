#pragma once
#include "button.h"
#include "game.h"

class Script :
	public Button
{
public:
	Script(int btnx, int btny, int wid, int len, const char* text);
	void pressfuc();
private:
	void title();
	void roundrect();
	void text();
};