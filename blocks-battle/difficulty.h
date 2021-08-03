#pragma once
#include "button.h"
#include "ball.h"
constexpr auto EASY = 0;
constexpr auto MEDIUM = 1;
constexpr auto HARD = 2;

class Difficulty :
	public Button
{
public:
	Difficulty(int btnx, int btny, int wid, int len, const char* text);
	void pressfuc();
	static int tough;
	static void updateSet();
private:
	void changeButtonText();
};