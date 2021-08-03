#include "pch.h"
#include "top.h"

int Top::score = 0;

Top::Top(int btnx, int btny, int wid, int len, const char* text) :Button(btnx, btny, wid, len, text), high() {}

void Top::pressfuc()
{
	if (!press) return;
	Game::clean();
	title();
	read();
	toppoint();
	FlushBatchDraw();
	(void)_getch();
	Game::clean();
}

void Top::save()
{
	FILE* highscore = fopen("highscore.txt", "r");
	int high[4] = { 0,0,0,0 };
	if (highscore != NULL)
		for (int i = 0; i < 3; i++)
			fscanf_s(highscore, "%d", &high[i]);

	high[3] = score;
	qsort(high, 4, sizeof(high[0]), compare);
	if (highscore != NULL) fclose(highscore);

	highscore = fopen("highscore.txt", "w");
	for (int i = 0; i < 3; i++) fprintf_s(highscore, "%d ", high[i]);
	fclose(highscore);
}

void Top::display()
{
	settextstyle(60, 30, "Consolas");
	settextcolor(BLACK);
	outtextxy(663, 103, "SCORE:");
	settextcolor(WHITE);
	outtextxy(660, 100, "SCORE:");

	char num[5] = "0000";
	int tscore = score;
	for (int i = 3; tscore > 0 && i >= 0; i--)
	{
		num[i] = (tscore % 10 + '0');
		tscore /= 10;
	}
	settextcolor(BLACK);
	outtextxy(843, 103, num);
	settextcolor(YELLOW);
	outtextxy(840, 100, num);
}

void Top::title()
{
	setbkmode(TRANSPARENT);
	settextstyle(100, 0, "Œ¢»Ì—≈∫⁄");
	settextcolor(0x555555);
	outtextxy(333, 53, "”Œœ∑≈≈––");
	settextcolor(WHITE);
	outtextxy(330, 50, "”Œœ∑≈≈––");
}

void Top::read()
{
	FILE* highscore = fopen("highscore.txt", "r");
	if (highscore != NULL)
	{
		for (int i = 0; i < 3; i++) fscanf_s(highscore, "%d", &high[i]);
		fclose(highscore);
	}
	else for (int i = 0; i < 3; i++) high[i] = 0;
}

void Top::toppoint()
{
	settextstyle(60, 0, "Consolas");
	for (int k = 0; k < 3; k++)
	{
		char num[7] = "1.0000";
		num[0] = k + '1';
		int tscore = high[k];
		for (int i = 5; tscore > 0 && i >= 2; i--)
		{
			num[i] = (tscore % 10 + '0');
			tscore /= 10;
		}
		outtextxy(390, 180 + 100 * k, num);
	}
}
int Top::compare(const void* p1, const void* p2)
{
	return *(int*)p2 - *(int*)p1;
}
