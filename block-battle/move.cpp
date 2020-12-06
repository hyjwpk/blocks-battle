#include "pch.h"

void ballmove(void)
{
	ballx = ballx + x_move;
	bally = bally + y_move;
}
void crash(void)
{
	if ((bally - radius) <= boardbottom && (bally + radius + y_move) >= boardtop && ballx >= boardleft && ballx <= boardright)
	{
		y_move = -abs(y_move);
	}

	if (((ballx - radius + x_move) <= 0) || ((ballx + radius + x_move) >= WIDTH2))
		x_move = -x_move;
	if (((bally - radius + y_move) <= 0))
		y_move = -y_move;

	if ((bally + radius + y_move) >= HIGH)
	{
		nowheart--;
		ballx = boardx;
		bally = boardtop - radius;
	}

	float H = 0;		// 色相
	float S = 1;		// 饱和度
	float L = 0.5f;		// 亮度
	for (int k = 0; k < BRICKLINE; k++)
		for (int i = 0; i < BRICKROW; i++)
		{
			if (map[k][i])
			{
				H += 5;
				if (((bally + y_move + radius) >= k * brickhigh + radius) && ((bally + y_move - radius) <= (k + 1) * brickhigh) && (ballx >= i * brickwidth) && (ballx <= (i + 1) * brickwidth))
				{
					ballcolor = HSLtoRGB(H, S, L);
					map[k][i] = 0;
					bricknumber--;
					y_move = -y_move;
				}
				else if ((bally>= k * brickhigh ) && (bally <= k * brickhigh + brickhigh) && (ballx+x_move >= i * brickwidth) && (ballx + x_move <= (i+1) * brickwidth))
					{
						ballcolor = HSLtoRGB(H, S, L);
						map[k][i] = 0;
						bricknumber--;
						x_move = -x_move;
					}
			}
		}
}
void boardmove(void)
{
	if (_kbhit())
	{
		char ch = _getch();
		switch (ch)
		{
		case 'A':case 'a':
			boardx		= boardwidth / 2;
			boardleft	= boardx - boardwidth / 2;
			boardright	= boardx + boardwidth / 2;
			break;
		case 'D':case 'd':
			boardx		= WIDTH2 - boardwidth / 2;
			boardleft	= boardx - boardwidth / 2;
			boardright	= boardx + boardwidth / 2;
			break;
		case 27:
			FILE * save;
			save = fopen("save.txt", "w");
			for (int k = 0; k < BRICKLINE; k++)
			{
				for (int i = 0; i < BRICKROW; i++)
					fprintf(save, "%d ", map[k][i]);
				fputs("\n", save);
			}
			fprintf(save,"%d", stage);
			fclose(save);
			exit(0);
			break;
		default:
			if (ch == -32)
				switch (_getch())
				{
				case 72:
					if (boardtop - 15 > 0)
					{
						boardy		= boardy - 15;  // 位置上移
						boardtop	= boardy - boardhigh / 2;
						boardbottom	= boardy + boardhigh / 2;
					}
					break;
				case 75:
					if (boardleft - 15 > 0)
					{
						boardx		= boardx - 15;  // 位置左移
						boardleft	= boardx - boardwidth / 2;
						boardright	= boardx + boardwidth / 2;
					}
					break;
				case 77:
					if (boardright + 15 < WIDTH2)
					{
						boardx		= boardx + 15;  // 位置右移
						boardleft	= boardx - boardwidth / 2;
						boardright	= boardx + boardwidth / 2;
					}
					break;
				case 80:
					if (boardbottom + 15 <= HIGH)
					{
						boardy = boardy + 15;  // 位置下移
						boardtop = boardy - boardhigh / 2;
						boardbottom = boardy + boardhigh / 2;
					}
					break;
				}
		}
	}
}