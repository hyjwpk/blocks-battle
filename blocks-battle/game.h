#pragma once
#include "music.h"
#include "menu.h"
#include "difficulty.h"
#include "star.h"
#include "time.h"
#include "heart.h"
#include "top.h"
#include "stage.h"
#include "game.h"
#include "flash.h"
#include "board.h"
#include "brick.h"

class Game
{
public:
	static void play();
	static void initial(int type);
	static void clean();
	static void print();
	static void crash();
private:
	static void fail();
	static void win();
};