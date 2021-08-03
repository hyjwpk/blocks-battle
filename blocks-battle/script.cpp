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
	settextstyle(100, 0, "΢���ź�");
	settextcolor(0x555555);
	outtextxy(333, 53, "��Ϸ˵��");
	settextcolor(WHITE);
	outtextxy(330, 50, "��Ϸ˵��");
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
	settextstyle(30, 0, "΢���ź�");
	outtextxy(320, 180, "ʹ�÷���������ٿغ�����С��");
	outtextxy(320, 240, "��Ϸ�а�ESC���浵�����ز˵�");
	outtextxy(320, 300, "ʹ��ADZC��������ƶ�,W��ͣ");
	outtextxy(320, 360, "�ٶ��з����ӳɣ���ʱ�и��ʼӳ�");
	FlushBatchDraw();
}