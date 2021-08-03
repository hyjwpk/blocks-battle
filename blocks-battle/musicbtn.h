#pragma once
#include "button.h"
#include "music.h"
constexpr auto OPEN = 0;
constexpr auto CLOSE = 1;

class Musicbtn :
	public Button
{
public:
	Musicbtn(int btnx, int btny, int wid, int len, const char* text);
	void pressfuc();
	static int soundmode;
private:
	void changeButtonText();
	void updateSet();
};

extern Music mu_background;