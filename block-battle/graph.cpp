#include "pch.h"
#include "graph.h"

void clean(void)
{
	IMAGE background;
	loadimage(&background, L".\\resourses\\picture\\background.jpg", WIDTH1, HIGH, 1);
	putimage(0, 0, &background);
}

void heart(int x0, int y0, int size)
{
	IMAGE mask, picture;
	loadimage(&mask, L".\\resourses\\picture\\heart2.png", size, size);
	loadimage(&picture, L".\\resourses\\picture\\heart.png", size, size);
	putimage(x0, y0, &mask, SRCAND);
	putimage(x0, y0, &picture, SRCPAINT);
}

void stagetitle(int n)//n为关卡数
{
	wchar_t cmdstring[50] = L".\\resourses\\picture\\stage.png";
	//cmdstring[25] = '0' + n;
	IMAGE img;
	loadimage(&img, cmdstring, 500, 200);
	putimage(250, 150, &img);
	wchar_t s[] = L"   ";
	s[1] = '0' + n;
	settextcolor(BGR(0XFFE597));
	settextstyle(110, 0, L"Consolas");
	outtextxy(525, 190, s);
	FlushBatchDraw();
	Sleep(1000);
}

void printheart(void)
{
	if (ballx <= Heartx + 50 && ballx >= Heartx - 50 && bally <= Hearty + 50 && bally >= Hearty - 50 && heartvanish == 0)
	{
		hearty = Hearty;
		heartvanish = 1;
	}
	if (heartvanish == 1)
	{
		heart(Heartx, ++hearty, 25);
	}

	if ((hearty - radius) <= boardbottom && (hearty + radius) >= boardtop && Heartx >= boardleft && Heartx <= boardright && heartvanish == 1)
	{
		heartvanish = 0;
		if (nowheart < 3)
		{
			nowheart++;
		}
	}

	switch (nowheart)
	{
	case 3:
		heart(800, 10, 50);
	case 2:
		heart(850, 10, 50);
	case 1:
		heart(900, 10, 50);
	}
}

void printscore(void)
{
	settextcolor(RED);
	settextstyle(60, 30, L"Consolas");
	outtextxy(640, 100, L"SCORE:");

	wchar_t num[5] = L"0000";
	int tscore = score;
	int i = 3;
	while (tscore>0&&i>=0)
	{
		num[i--]= (wchar_t)(tscore % 10 + '0');
		tscore /= 10;
	}
	outtextxy(840, 100, num);

	settextcolor(LIGHTRED);

	outtextxy(930, 100, num[3]);
}

void printtime(void)
{
	int time;
	if (t == 0) time = t_save;
	else
		time = (clock() - t) / CLOCKS_PER_SEC+t_save;
	settextcolor(GREEN);
	settextstyle(40, 20, L"Consolas");
	outtextxy(640, 200, L"TIME:");

	wchar_t num[6] = L"00000";
	int i = 4;
	while (time > 0 && i >= 0)
	{
		num[i--] = (wchar_t)(time % 10 + '0');
		time /= 10;
	}
	outtextxy(800, 200, num);
}

void timelimit(void)
{
	int time;
	if (t == 0) time = 100;
	else
		time = 100 - (clock() - t) / CLOCKS_PER_SEC;

	settextcolor(GREEN);
	settextstyle(40, 20, L"Consolas");
	outtextxy(700, 200, L"TIME:");

	wchar_t num[6] = L"00000";
	int i = 4;
	while (time > 0 && i >= 0)
	{
		num[i--] = (wchar_t)(time % 10 + '0');
		time /= 10;
	}
	outtextxy(800, 200, num);
	settextcolor(GREEN);
	settextstyle(40, 0, L"微软雅黑");
	outtextxy(900, 200, L"秒");
	if (time == 0)
	{
		nowheart--;
		time = 100;
	}
}

void rainbow(int type,float *H,float *S,float *L)
{
	if (type == 0)
	{
		*H = 0;		// 色相
		*S = 1;		// 饱和度
		*L = 0.5f;		// 亮度
	}
	else if (type == 1)
	{
		*H += 5;
		setfillcolor(HSLtoRGB(*H, *S, *L));
	}
}

void fail(void)
{
	
	clean();

	settextcolor(LIGHTRED);
	settextstyle(100, 50, L"Consolas");
	outtextxy(250, 100, L"YOU LOSE!");

	settextcolor(BLACK);
	settextstyle(40, 20, L"Consolas");
	outtextxy(300, 200, L"Wanna try again?");

	mciSendString(L"close cmusic", NULL, 0, NULL);
	mciSendString(L"open .\\resourses\\sound\\gameover.wav alias cmusic", NULL, 0, NULL);
	mciSendString(L"play cmusic", NULL, 0, NULL);

	settextcolor(GREEN);
	settextstyle(30, 15, L"Consolas");
	outtextxy(350, 300, L"(Y)YES   (N)NO");

	FlushBatchDraw();

	switch (_getch())
	{
	case 'Y':case 'y':
		stage = 0;
		score = 0;
		break;
	case 'N':case 'n':
		exit(0);
	}
}

void print(void)
{
	float H, S, L; 		// 色相 饱和度 亮度
	setcolor(WHITE);

	setfillcolor(ballcolor);
	solidcircle(ballx, bally, radius);

	setfillcolor(BOARDCOLOR);
	solidrectangle(boardleft, boardtop, boardright, boardbottom);

	setfillcolor(BRICKCOLOR);
	rainbow(0,&H,&S,&L);
	for (int k = 0; k < BRICKLINE; k++)
	{
		for (int i = 0; i < BRICKROW; i++)
		{
			if (map[k][i])	 // 砖块存在，绘制砖块
			{
				if (colortype == 1) rainbow(1, &H, &S, &L);
				if (colortype == 0) setfillcolor(BGR(color[k][i]));
				solidrectangle(i * brickwidth, k * brickhigh, i * brickwidth + brickwidth, (k + 1) * brickhigh);
			}
		}
	}

	printheart();

	printscore();

	printtime();
	
	FlushBatchDraw();
}

