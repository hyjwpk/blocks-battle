#include "pch.h"
#include "time.h"

int Time::timesetting = MODE0;
clock_t Time::t = 0;
clock_t Time::t_save = 0;

Time::Time(int btnx, int btny, int wid, int len, const char* text) :Button(btnx, btny, wid, len, text)
{
	changeButtonText();
	updateSet();
}

void Time::pressfuc()
{
	if (!press) return;
	timesetting++;
	timesetting %= 3;
	changeButtonText();
	updateSet();
}

void Time::display()
{
	int time = (clock() - t) / CLOCKS_PER_SEC + t_save;
	if (timesetting == MODE1) time = 500 - time;
	if (timesetting == MODE2) time = 50 - time;
	if (time < 0)
	{
		t = clock();
		Heart::value--;
	}
	print(time);
}

void Time::print(int time)
{
	settextstyle(60, 30, "Consolas");
	settextcolor(BLACK);
	outtextxy(663, 203, "TIME£º");
	settextcolor(WHITE);
	outtextxy(660, 200, "TIME£º");

	char num[5] = "0000";
	for (int i = 3; time > 0 && i >= 0; i--)
	{
		num[i] = (time % 10 + '0');
		time /= 10;
	}
	settextcolor(BLACK);
	outtextxy(843, 203, num);
	settextcolor(YELLOW);
	outtextxy(840, 200, num);
}

void Time::changeButtonText()
{
	if (timesetting == MODE0) text = "ÏÞÊ±:¹Ø";
	else if (timesetting == MODE1) text = "£µ£°£°£ó";
	else if (timesetting == MODE2) text = "£µ£°£ó";
}
