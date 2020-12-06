#include "pch.h"
int readstage(int n)
{
	FILE* stage;
	char cmdstring[20] = "stage0.txt";
	cmdstring[5] = '0' + n;
	if ((stage = fopen(cmdstring, "r")) == NULL)
	{
		return 0;
	}
	for (int k = 0; k < BRICKLINE; k++)
	{
		for (int i = 0; i < BRICKROW; i++)
			fscanf(stage, "%d ", &map[k][i]);
	}
	fclose(stage);
	return 1;
}

int readsave(void)
{
	FILE* save;
	if ((save = fopen("save.txt", "r")) == NULL)
	{
		return 0;
	}
	for (int k = 0; k < BRICKLINE; k++)
	{
		for (int i = 0; i < BRICKROW; i++)
			fscanf(save, "%d ", &map[k][i]);
	}
	fscanf(save, "%d", &stage);
	fclose(save);
	return 1;
}

void initial(int type)
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
	if (type == 1)//1为读取关卡
	{
		if (readstage(++stage) == 0) exit(0);
	}
	else if (type == 2)//2为读取存档
	{
		if (readsave() == 0) exit(0);
	}

	bricknumber = 0;
	for (int k = 0; k < BRICKLINE; k++)
		for (int i = 0; i < BRICKROW; i++)
		{
			if (map[k][i]) bricknumber++;
		}
	
}