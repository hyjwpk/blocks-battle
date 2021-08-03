#pragma once
#include "button.h"
#include "game.h"

class Top :
	public Button
{
public:
	Top(int btnx, int btny, int wid, int len, const char* text);
	void pressfuc();
	static void save();
	static void display();
	static int score;
private:
	void title();
	void read();
	void toppoint();
	static int compare(const void* p1, const void* p2);
	int high[4];
};