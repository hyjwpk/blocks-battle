#include "pch.h"
#include "initial.h"


#define MAXSTAR 200	

struct STAR
{
	double	x;
	int		y;
	double	step;
	int		color;
};

STAR star[MAXSTAR];


void InitStar(int i)
{
	star[i].x = 0;
	star[i].y = rand() % 580;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}


void MoveStar(int i)
{
	putpixel((int)star[i].x, star[i].y, 0);

	star[i].x += star[i].step;
	if (star[i].x > 960)	InitStar(i);

	putpixel((int)star[i].x, star[i].y, star[i].color);
}

int readstage(int n)//n为关卡数
{
	static char* pText;
	switch (n)
	{
	case 1:
		pText = (char*)LoadResource(NULL, FindResource(NULL, MAKEINTRESOURCE(IDR_TEXT1), TEXT("TEXT")));
		break;
	case 2:
		pText = (char*)LoadResource(NULL, FindResource(NULL, MAKEINTRESOURCE(IDR_TEXT2), TEXT("TEXT")));
		break;
	case 3: 
		pText = (char*)LoadResource(NULL, FindResource(NULL, MAKEINTRESOURCE(IDR_TEXT3), TEXT("TEXT")));
		break;
	case 4:
		pText = (char*)LoadResource(NULL, FindResource(NULL, MAKEINTRESOURCE(IDR_TEXT4), TEXT("TEXT")));
		break;
	case 5:
		pText = (char*)LoadResource(NULL, FindResource(NULL, MAKEINTRESOURCE(IDR_TEXT5), TEXT("TEXT")));
		break;
	case 6:
		pText = (char*)LoadResource(NULL, FindResource(NULL, MAKEINTRESOURCE(IDR_TEXT6), TEXT("TEXT")));
		break;
	case 7:
		pText = (char*)LoadResource(NULL, FindResource(NULL, MAKEINTRESOURCE(IDR_TEXT7), TEXT("TEXT")));
		break;
	case 8:
		pText = (char*)LoadResource(NULL, FindResource(NULL, MAKEINTRESOURCE(IDR_TEXT8), TEXT("TEXT")));
		break;
	default:
		return 0;
		break;
	}
	

	TCHAR tmp[_MAX_PATH];
	GetTempPath(_MAX_PATH, tmp);
	_tcscat(tmp, _T("stage.txt"));


	FILE *stage;
	stage = fopen(tmp, "w");
	fprintf(stage, "%s", pText);
	fclose(stage);

	stage = fopen(tmp, "r");
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
	DeleteFile(tmp);
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
	fscanf(save, "%d", &t_save);
	fscanf(save, "%lf %lf %lf %lf", &ballx, &bally, &x_move, &y_move);

	fclose(save);
	return 1;
}

void initial(int type)//1为读取关卡,2为读取存档
{

	boardhigh		= HIGH / 25;

	if (tough == 0)
	{
		boardwidth = WIDTH2 / 3;

	}
	else if (tough == 1)
	{
		boardwidth = WIDTH2 / 4;

	}
	else if (tough == 2)
	{
		boardwidth = WIDTH2 / 5;

	}


	boardx			= WIDTH2 / 2;
	boardy			= HIGH - boardhigh / 2;
	boardleft		= boardx - boardwidth / 2;
	boardright		= boardx + boardwidth / 2;
	boardtop		= boardy - boardhigh / 2;
	boardbottom		= boardy + boardhigh / 2;

	radius = 10;
	ballx = WIDTH2 / 2;
	bally = (double)boardtop-radius;
	ballcolor = BLUE;

	brickwidth	= WIDTH2 / BRICKROW;
	brickhigh	= brickwidth / 2;

	heartvanish = 0;
	flashvanish = 0;

	nowheart = 3;
	t = 0;
	switch(type)
	{
	case 1:
		t_save = 0;
		if (readstage(++stage) == 0)
		{
			sortscore();
			clean();
			stage = 0;
			score = 0;
			t = 0;
			EndBatchDraw();
			settextstyle(100, 0, "Consolas");
			RECT r;
			r = { 0, 0, WIDTH1, HIGH };
			drawtext("Congratulations", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			_getch();
			menu();
		}
		break;
	case 2:
		if (readsave() == 0) menu();
		t = clock();
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

	setbkcolor(BLACK);
	cleardevice();

	for (int i = 0; i < MAXSTAR; i++)
	{
		InitStar(i);
		star[i].x = rand() % 640;
	}

	
	for(int k=0;k<=50;k++)
	{
		for (int i = 0; i < MAXSTAR; i++)
			MoveStar(i);
		FlushBatchDraw();
		Sleep(20);
	}
	float L = 0;
	while (L <= 1)
	{
		L += 0.05;
		setbkcolor(HSLtoRGB(0, 0, L));
		cleardevice();
		FlushBatchDraw();
		Sleep(50);
	}
	
}