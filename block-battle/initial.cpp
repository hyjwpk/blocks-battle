#include "pch.h"
#include "initial.h"
int readstage(int n)//n为关卡数
{
	FILE* stage;
	char cmdstring[50] = ".\\resourses\\document\\stage1.txt";
	cmdstring[26] = '0' + n;
	if ((stage = fopen(cmdstring, "r")) == NULL)
	{
		return 0;
	}

	for (int k = 0; k < BRICKLINE; k++)
	{
		for (int i = 0; i < BRICKROW; i++)
		{
			fscanf(stage, "%d", &map[k][i]);
		}
	}

	fscanf(stage,"%d",&colortype);
	if (colortype == 0)//0为自定义色彩模式，1为彩虹色模式
	{
		for (int k = 0; k < BRICKLINE; k++)
		{
			for (int i = 0; i < BRICKROW; i++)
			{
				fscanf(stage, "%x", &color[k][i]);
			}
		}
	}

	fclose(stage);
	return 1;
}

int readsave(void)
{
	FILE* save;
	if ((save = fopen(".\\resourses\\document\\save.txt", "r")) == NULL)
	{
		return 0;
	}

	for (int k = 0; k < BRICKLINE; k++)
	{
		for (int i = 0; i < BRICKROW; i++)
		{
			fscanf(save, "%d", &map[k][i]);
		}
	}

	fscanf(save, "%d", &stage);

	fscanf(save, "%d", &colortype);
	if (colortype == 0)//0为自定义色彩模式，1为彩虹色模式
	{
		for (int k = 0; k < BRICKLINE; k++)
		{
			for (int i = 0; i < BRICKROW; i++)
			{
				fscanf(save, "%x", &color[k][i]);
			}
		}
	}

	fscanf(save, "%d", &score);
	fscanf(save, "%d", &nowheart);

	fclose(save);
	return 1;
}

void initial(int type)//1为读取关卡,2为读取存档
{

	boardhigh		= HIGH / 20;
	boardwidth		= WIDTH2 / 2;
	boardx			= WIDTH2 / 2;
	boardy			= HIGH - boardhigh / 2;
	boardleft		= boardx - boardwidth / 2;
	boardright		= boardx + boardwidth / 2;
	boardtop		= boardy - boardhigh / 2;
	boardbottom		= boardy + boardhigh / 2;

	x_move = y_move = SPEED;
	radius = 10;
	ballx = WIDTH2 / 2;
	bally = boardtop-radius;
	ballcolor = BLUE;

	brickwidth	= WIDTH2 / BRICKROW;
	brickhigh	= brickwidth / 2;

	nowheart = 3;
	switch(type)
	{
	case 1:
		if (readstage(++stage) == 0)
		{
			clean();
			stage = 0;
			score = 0;
			EndBatchDraw();
			settextstyle(100, 0, L"Consolas");
			RECT r;
			r = { 0, 0, WIDTH1, HIGH };
			drawtext(L"Congratulations", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			_getch();
			menu();
		}
		break;
	case 2:
		if (readsave() == 0) exit(0);
		break;
	}

	bricknumber = 0;
	for (int k = 0; k < BRICKLINE; k++)
	{
		for (int i = 0; i < BRICKROW; i++)
		{
			if (map[k][i])
			{
				bricknumber++;
			}
		}
	}

	
	
}