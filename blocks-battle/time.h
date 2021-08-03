#pragma once
#include "button.h"
#include "heart.h"
constexpr auto MODE0 = 0;
constexpr auto MODE1 = 1;//500s
constexpr auto MODE2 = 2;//50s

class Time :
	public Button
{
public:
	Time(int btnx, int btny, int wid, int len, const char* text);
	void pressfuc();
	static void display();
	static int timesetting;
	static clock_t t;
	static clock_t t_save;
private:
	static void print(int time);
	void changeButtonText();
};