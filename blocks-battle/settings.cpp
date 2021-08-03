#include "pch.h"
#include "settings.h"

Settings::Settings(int btnx, int btny, int wid, int len, const char* text) :Button(btnx, btny, wid, len, text) {}

void Settings::pressfuc()
{
	if (!press) return;
	Game::clean();

	Button* btn[3] = {
		new Difficulty(425, 240, 120, 30, "�Ѷ�:��") ,
		new Musicbtn(425, 280, 120, 30, "����:��") ,
		new Time(425, 320, 120, 30, "��ʱ:��") };

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
	settextstyle(100, 0, "΢���ź�");
	settextcolor(0x555555);
	outtextxy(333, 53, "��Ϸ����");
	settextcolor(WHITE);
	outtextxy(330, 50, "��Ϸ����");
}