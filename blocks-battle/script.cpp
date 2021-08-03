#include "pch.h"
#include "script.h"

Script::Script(int btnx, int btny, int wid, int len, const char* text) :Button(btnx, btny, wid, len, text) {}

void Script::pressfuc()
{
	if (!press) return;
	Game::clean();
	title();
	roundrect();
	text();
	(void)_getch();
	Game::clean();
}

void Script::title()
{
	setbkmode(TRANSPARENT);
	settextstyle(100, 0, "微软雅黑");
	settextcolor(0x555555);
	outtextxy(333, 53, "游戏说明");
	settextcolor(WHITE);
	outtextxy(330, 50, "游戏说明");
	FlushBatchDraw();
}

void Script::roundrect()
{
	setfillcolor(0xeeeeee);
	setlinecolor(0xcccccc);
	for (int i = 1; i <= 60; i++)
	{
		fillroundrect((WIDTH1 - 400) / 2, HIGH / 2 - 270 / 2 * i / 60, (WIDTH1 + 400) / 2, HIGH / 2 + 270 / 2 * i / 60, 60, 20);
		FlushBatchDraw();
		Sleep(3);
	}
}

void Script::text()
{
	settextcolor(BLACK);
	settextstyle(30, 0, "微软雅黑");
	outtextxy(320, 180, "使用方向键或鼠标操控横板击打小球");
	outtextxy(320, 240, "游戏中按ESC键存档并返回菜单");
	outtextxy(320, 300, "使用ADZC键大幅度移动,W暂停");
	outtextxy(320, 360, "速度有分数加成，限时有概率加成");
	FlushBatchDraw();
}