#pragma once
#include "button.h"
#include "music.h"
#include "difficulty.h"
#include "musicbtn.h"
#include "time.h"
#include "game.h"

class Settings :
	public Button
{
public:
	Settings(int btnx, int btny, int wid, int len, const char* text);
	void pressfuc();
private:
	void title();
};

extern Music mu_background, mu_crash, mu_dead;