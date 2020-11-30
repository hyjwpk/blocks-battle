#include <conio.h>
#include <graphics.h>

#define High 480  
#define Width 640
#define BRICKNUMBER 15 
#define BLOCKLINE 5
#define BACKROUNDCOLOR WHITE
#define BRICKCOLOR GREEN
#define BOARDCOLOR LIGHTBLUE
#define SPEED 3

int ballx, bally, x_move, y_move, radius;
int boardx, boardy,boardhigh, boardwidth,boardleft, boardright, boardtop, boardbottom;
int brickhigh, brickwidth;
int ballcolor = BLUE;
int map[BLOCKLINE][BRICKNUMBER];


void initial(void)
{
	ballx=Width/2;
	bally=High/2;
	x_move=y_move=SPEED;
	radius=10; 

	boardx=Width/2;
	boardhigh=High/20;
	boardy=High-boardhigh/2;
	boardwidth=Width/2;
	boardleft=boardx-boardwidth/2;
	boardright=boardx+boardwidth/2;
	boardtop=boardy-boardhigh/2;
	boardbottom=boardy+boardhigh/2;

	brickwidth=Width/BRICKNUMBER;
	brickhigh=brickwidth/2;

	for(int k=0;k<BLOCKLINE;k++)
		for (int i=0;i<BRICKNUMBER;i++)
			map[k][i] = 1;
	
}

void clean(void)
{
	setcolor(BACKROUNDCOLOR);
	setfillcolor(BACKROUNDCOLOR);
	fillcircle(ballx, bally, radius);
	bar(boardleft, boardtop, boardright, boardbottom);
	for (int k = 0;k < BLOCKLINE;k++)
		for (int i = 0;i < BRICKNUMBER;i++)
		{
			if (map[k][i])
			{
				fillrectangle(i * brickwidth,k*brickhigh,i * brickwidth + brickwidth,(k+1)*brickhigh);
			}
		}
}

void print(void)
{
	IMAGE background;//定义一个图片名.
	loadimage(&background, _T("IMAGE"), _T("Background"), Width, High, 1);//从图片文件获取图像
	putimage(0, 0, &background);//绘制图像到屏幕，图片左上角坐标为(0,0)
	setcolor(WHITE);
	setfillcolor(ballcolor);
	fillcircle(ballx, bally, radius);
	setfillcolor(BOARDCOLOR);
	bar(boardleft, boardtop, boardright, boardbottom);
	setcolor(WHITE);
	setfillcolor(BRICKCOLOR);
	float H = 0;		// 色相
	float S = 1;		// 饱和度
	float L = 0.5f;		// 亮度
	for (int k = 0;k < BLOCKLINE;k++)
		for (int i = 0;i < BRICKNUMBER;i++)
		{
			if (map[k][i])	 // 砖块存在，绘制砖块
			{
				H += 5;
				setfillcolor(HSLtoRGB(H, S, L));
				fillrectangle(i * brickwidth, k * brickhigh, i * brickwidth + brickwidth, (k+1)*brickhigh);
			}
		}
	FlushBatchDraw();
	Sleep(1);
}

void ballmove(void)
{
	ballx = ballx + x_move;
	bally = bally + y_move;
}

void crash(void) 
{
	if ((bally+radius+y_move)>=boardtop&&ballx>=boardleft&&ballx<=boardright)
		y_move=-y_move;
	if (((ballx-radius+x_move)<=0)||((ballx+radius+x_move)>=Width))
		x_move=-x_move;
	if (((bally-radius+y_move)<=0))
		y_move=-y_move;
	if ((bally + radius + y_move) >= High)
	{
		ballx = Width / 2;
		bally = High / 2;
		for (int k = 0;k < BLOCKLINE;k++)
			for (int i = 0;i < BRICKNUMBER;i++)
				map[k][i] = 1;
	}
	float H = 0;		// 色相
	float S = 1;		// 饱和度
	float L = 0.5f;		// 亮度
	for (int k = 0;k < BLOCKLINE;k++)
		for (int i = 0;i < BRICKNUMBER;i++)
		{
			
			if (map[k][i])
			{
				H += 5;
				if (((bally+y_move)<=(k+1)*brickhigh+radius)&&(ballx>=i*brickwidth)&&(ballx<=(i+1)*brickwidth))
				{
					ballcolor = HSLtoRGB(H, S, L);
					map[k][i] = 0;
					y_move = -y_move;
				}
			}
		}
}

void boardmove()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 75:
				if (boardleft > 0)
				{
					boardx = boardx - 15;  // 位置左移
					boardleft = boardx - boardwidth / 2;
					boardright = boardx + boardwidth / 2;
				}
				break;
			case 77:
				if (boardright < Width)
				{
					boardx = boardx + 15;  // 位置右移
					boardleft = boardx - boardwidth / 2;
					boardright = boardx + boardwidth / 2;
				}
				break;
		}
	}
}

void menu(void)
{
	initgraph(Width, High);
	setbkcolor(BACKROUNDCOLOR);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	_tcscpy_s(f.lfFaceName, _T("Consolas"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	setbkcolor(LIGHTBLUE);
	RECT r = { 0, 210, 639, 249 };
	drawtext(_T("<- left,-> right\nPress any key to start your game"), &r, DT_CENTER | DT_VCENTER);
	_getch();//用户键盘输入时开始游戏
	r = { 0, 249, 639, 268 };
	drawtext(_T("Game start!"), &r, DT_CENTER | DT_VCENTER);
	Sleep(1000);//等待1s
	setbkcolor(BACKROUNDCOLOR);
	cleardevice();
}

int main()
{
	initial();
	menu();
	BeginBatchDraw();
	while (1)
	{
		clean();
		boardmove();
		crash(); 
		ballmove();
		print(); 
	}
	EndBatchDraw();
	closegraph();
	return 0;
}
