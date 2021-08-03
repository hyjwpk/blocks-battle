#include "pch.h"
#include "star.h"

STAR::STAR()
{
	x = rand() % 960;
	y = rand() % 580;
	step = rand() % 5 + 1;
	color = step * 255 / 6;
	color = RGB(color, color, color);
}

void Star::animation()
{
	setbkcolor(BLACK);
	cleardevice();

	for (float LB = 0; LB <= 1; LB += 0.02f)
	{
		setbkcolor(HSLtoRGB(0, 0, LB));
		cleardevice();
		for (int i = 0; i < MAXSTAR; i++)
		{
			float H, S, L;
			RGBtoHSL(star[i].color, &H, &S, &L);
			if (L >= LB) moveStar(i);
		}
		FlushBatchDraw();
		Sleep(20);
	}
}

void Star::moveStar(int i)
{
	star[i].x += star[i].step;
	if (star[i].x > 960)	star[i] = *(new STAR);
	putpixel((int)star[i].x, star[i].y, star[i].color);
}
