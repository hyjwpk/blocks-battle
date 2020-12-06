#include "pch.h"
extern void heart(int x0, int y0, int size);

void clean(void)
{
	setbkcolor(BACKROUNDCOLOR);
	cleardevice();
}

void heart(int x0, int y0, int size)
{
	double  m, n, x, y;
	for (double i = 0; i <= (double)2 * size; i += 0.1)
	{
		//产生极坐标点
		m = i;
		n = -size * (((sin(i) * sqrt(fabs(cos(i)))) / (sin(i) + 1.4142135624)) - 2 * sin(i) + 2);
		//转换为笛卡尔坐标
		x = n * cos(m) + x0;
		y = n * sin(m) + y0;
		putpixel((int)x, (int)y, RED);
	}
}

void print(void)
{
	//IMAGE background;//定义一个图片名.
	//loadimage(&background, _T("IMAGE"), _T("Background"), WIDTH, HIGH, 1);//从图片文件获取图像
	//putimage(0, 0, &background);//绘制图像到屏幕，图片左上角坐标为(0,0)
	setcolor(WHITE);

	setfillcolor(ballcolor);
	fillcircle(ballx, bally, radius);

	setfillcolor(BOARDCOLOR);
	bar(boardleft, boardtop, boardright, boardbottom);

	if (nowheart == 3)
	{
		heart(800, 10, 10);
		heart(850, 10, 10);
		heart(900, 10, 10);
	}
	if (nowheart == 2)
	{
		heart(850, 10, 10);
		heart(900, 10, 10);
	}
	if (nowheart == 1)
	{
		heart(900, 10, 10);
	}

	setfillcolor(BRICKCOLOR);
	float H = 0;		// 色相
	float S = 1;		// 饱和度
	float L = 0.5f;		// 亮度
	for (int k = 0; k < BRICKLINE; k++)
		for (int i = 0; i < BRICKROW; i++)
		{
			if (map[k][i])	 // 砖块存在，绘制砖块
			{
				H += 5;
				setfillcolor(HSLtoRGB(H, S, L));
				fillrectangle(i * brickwidth, k * brickhigh, i * brickwidth + brickwidth, (k + 1) * brickhigh);
			}
		}

	FlushBatchDraw();
}