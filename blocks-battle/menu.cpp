#include "pch.h"
#include "menu.h"

void Menu::menuControl()
{
	Game::clean();
	if (Musicbtn::soundmode == 0) mu_background.playMusic();
	Button* btn[6] = {
		new Start(425, 240, 120, 30, "开始") ,
		new Load(425, 280, 120, 30, "继续") ,
		new Settings(425, 320, 120, 30, "设置") ,
		new Script(425, 360, 120, 30, "说明") ,
		new Top(425, 400, 120, 30, "排行"),
		new Exit(425, 440, 120, 30, "退出") };

	BeginBatchDraw();
	while (true)
	{
		title();
		Button::showButton(btn, 6);
		if (pressMenuButton(btn)) break;
	}
}

void Menu::title()
{
	setbkmode(TRANSPARENT);
	settextstyle(100, 0, "微软雅黑", 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(0x555555);
	outtextxy(178, 53, "BLOCKS-BATTLE");
	settextcolor(WHITE);
	outtextxy(175, 50, "BLOCKS-BATTLE");
}

bool Menu::pressMenuButton(Button* btn[])
{
	for (int i = 0; i < 6; i++) btn[i]->pressfuc();
	if (btn[0]->press || btn[1]->press || btn[5]->press) return true;
	else return false;
}