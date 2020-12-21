#include "pch.h"
#include "graph.h"

void clean(void)
{
	IMAGE background;
	loadimage(&background, "JPG",MAKEINTRESOURCE(IDR_JPG1), WIDTH1, HIGH, 1);
	putimage(0, 0, &background);
}

void heart(int x0, int y0, int size)
{
	IMAGE mask, picture;
	loadimage(&mask, "PNG", MAKEINTRESOURCE(IDB_PNG2), size, size);
	loadimage(&picture, "PNG", MAKEINTRESOURCE(IDB_PNG1), size, size);
	putimage(x0, y0, &mask, SRCAND);
	putimage(x0, y0, &picture, SRCPAINT);
}

void stagetitle(int n)//n为关卡数
{
	char s[] = "STAGE  ";
	s[6] = '0' + n;
	settextstyle(105, 0, "Consolas");
	settextcolor(0x555555);
	outtextxy(288, 226, s);
	settextcolor(WHITE);
	outtextxy(285, 223, s);
	FlushBatchDraw();
	Sleep(1000);
}

void printheart(void)
{
	if (heartvanish == 1)
	{
		heart(heartx, ++hearty, 25);
	}

	if (hearty > HIGH) heartvanish = 0;

	if ((hearty - radius) <= boardbottom && (hearty + radius) >= boardtop && heartx >= boardleft && heartx <= boardright && heartvanish == 1)
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
	
	settextstyle(60, 30, "Consolas");
	settextcolor(BLACK);
	outtextxy(663, 103, "SCORE:");
	settextcolor(WHITE);
	outtextxy(660, 100, "SCORE:");

	char num[5] = "0000";
	int tscore = score;
	int i = 3;
	while (tscore>0&&i>=0)
	{
		num[i--]= (tscore % 10 + '0');
		tscore /= 10;
	}
	settextcolor(BLACK);
	outtextxy(843, 103, num);
	settextcolor(YELLOW);
	outtextxy(840, 100, num);
}

void printtime(void)
{
	int time;
	if (t == 0) time = t_save;
	else
		time = (clock() - t) / CLOCKS_PER_SEC+t_save;
	
	settextstyle(60, 30, "Consolas");
	settextcolor(BLACK);
	outtextxy(663, 203, "TIMES:");
	settextcolor(WHITE);
	outtextxy(660, 200, "TIMES:");

	char num[5] = "0000";
	int i = 3;
	while (time > 0 && i >= 0)
	{
		num[i--] = (time % 10 + '0');
		time /= 10;
	}
	settextcolor(BLACK);
	outtextxy(843, 203, num);
	settextcolor(YELLOW);
	outtextxy(840, 200, num);
}

//void timelimit(void)
//{
//	int time;
//	if (t == 0) time = 100;
//	else
//		time = 100 - (clock() - t) / CLOCKS_PER_SEC;
//
//	settextstyle(40, 20, "Consolas");
//	settextcolor(BLACK);
//	outtextxy(703, 203, "TIME:");
//	settextcolor(WHITE);
//	outtextxy(700, 200, "TIME:");
//
//	char num[6] = "00000";
//	int i = 4;
//	while (time > 0 && i >= 0)
//	{
//		num[i--] = (time % 10 + '0');
//		time /= 10;
//	}
//	outtextxy(800, 200, num);
//	settextcolor(GREEN);
//	settextstyle(40, 0, "微软雅黑");
//	outtextxy(900, 200, "秒");
//	if (time == 0)
//	{
//		nowheart--;
//		time = 100;
//	}
//}

void rainbow(int type,float *H,float *S,float *L)
{
	if (type == 0)
	{
		*H = 0;		// 色相
		*S = 0.6;		// 饱和度
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

	mu_background.stopmusic();
	mu_dead.playonce();

	Button btn_restart(320, 380, 120, 30, "重试");
	Button btn_fail(520, 380, 120, 30, "退出");

	while (1) {
		setbkmode(TRANSPARENT);
		settextstyle(100, 0, "微软雅黑", 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
		settextcolor(0x555555);
		outtextxy(303, 173, "YOU LOSE");
		settextcolor(LIGHTRED);
		outtextxy(300, 170, "YOU LOSE");
		btn_restart.Show();
		btn_fail.Show();;

		FlushBatchDraw();

		if (btn_restart.press)
		{
			stage = 0;
			score = 0;
			mu_background.playmusic();
			EndBatchDraw();
			menu();
			break;
		}
		if (btn_fail.press)
		{
			exit(0);
			break;
		}
	}

}

void print(void)
{
	float H, S, L; 		// 色相 饱和度 亮度
	setcolor(WHITE);

	setfillcolor(ballcolor);
	solidcircle((int)ballx, (int)bally, radius);

	setfillcolor(BOARDCOLOR);
	solidrectangle(boardleft, boardtop, boardright, boardbottom);


	rainbow(0,&H,&S,&L);
	for (int k = 0; k < BRICKLINE; k++)
	{
		for (int i = 0; i < BRICKROW; i++)
		{
			if (map[k][i])	 // 砖块存在，绘制砖块
			{
				setfillcolor(BLACK);
				solidrectangle(i * brickwidth, k * brickhigh, (i + 1) * brickwidth , (k + 1) * brickhigh);
				if (colortype == 1) rainbow(1, &H, &S, &L);
				if (colortype == 0) setfillcolor(BGR(color[k][i]));
				solidrectangle(i * brickwidth, k * brickhigh, (i+1) * brickwidth-3, (k + 1) * brickhigh-3);
			}
		}
	}

	printheart();

	printscore();

	printtime();
	
	FlushBatchDraw();
}

