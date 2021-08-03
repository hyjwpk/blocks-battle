#include "pch.h"
#include "settings.h"

Settings::Settings(int btnx, int btny, int wid, int len, const char* text) :Button(btnx, btny, wid, len, text) {}

void Settings::pressfuc()
{
	if (!press) return;
	Game::clean();

	Button* btn[3] = {
		new Difficulty(425, 240, 120, 30, "难度:１") ,
		new Musicbtn(425, 280, 120, 30, "音乐:开") ,
		new Time(425, 320, 120, 30, "限时:关") };

	while (true)
	{
		title();
		Button::showButton(btn, 3);
		for (int i = 0; i < 3; i++) btn[i]->pressfuc();
		if (_kbhit() && _getch() == 27) break;
	}
	Game::clean();
}

void Settings::title()
{
	setbkmode(TRANSPARENT);
	settextstyle(100, 0, "微软雅黑");
	settextcolor(0x555555);
	outtextxy(333, 53, "游戏设置");
	settextcolor(WHITE);
	outtextxy(330, 50, "游戏设置");
}