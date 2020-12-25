#include "pch.h"
#include "move.h"

int lowest;

int compare(const void* p1, const void* p2)
{
	return *(int*)p2 - *(int*)p1;
}

void ballmove(void)
{
	ballx = ballx + x_move;
	bally = bally + y_move;
}

void sortscore(void)
{
	FILE* highscore;

	if ((highscore = fopen("highscore.txt", "r")) == NULL)
	{
		highscore = fopen("highscore.txt", "w");
		fputs("0 0 0", highscore);
		fclose(highscore);
		highscore=fopen("highscore.txt", "r");
	}
	int high[4];
	for (int i = 0;i < 3;i++)
	{
		fscanf(highscore, "%d", &high[i]);
	}
	high[3] = score;
	qsort(high, 4, sizeof(high[0]), compare);
	fclose(highscore);

	highscore = fopen("highscore.txt", "w");
	for (int i = 0;i < 3;i++)
	{
		fprintf(highscore, "%d ", high[i]);
	}
	fclose(highscore);
}

void save(void)
{
	FILE* save;
	save = fopen("save.txt", "w");
	for (int k = 0; k < BRICKLINE; k++)
	{
		for (int i = 0; i < BRICKROW; i++)
			fprintf(save, "%d ", map[k][i]);
		fputs("\n", save);
	}
	fprintf(save, "%d", stage);
	fputs("\n", save);
	fprintf(save, "%d", colortype);
	fputs("\n", save);
	if (colortype == 0)//0为自定义色彩模式，1为彩虹色模式
	{
		for (int k = 0; k < BRICKLINE; k++)
		{
			for (int i = 0; i < BRICKROW; i++)
				fprintf(save, "%x ", color[k][i]);
		}
		fputs("\n", save);
	}
	fprintf(save, "%d", score);
	fputs("\n", save);
	fprintf(save, "%d", nowheart);
	fputs("\n", save);
	fprintf(save, "%d", ((clock() - t) / CLOCKS_PER_SEC+t_save));
	fputs("\n", save);
	fprintf(save, "%f %f %f %f", ballx, bally, x_move, y_move );
	fclose(save);

	sortscore();
}

void crash(void)
{
	float H, S, L; 		// 色相 饱和度 亮度
	if (((ballx - radius + x_move) <= 0) || ((ballx + radius + x_move) >= WIDTH2))
		x_move = -x_move;
	if (((bally - radius + y_move) <= 0))
		y_move = -y_move;

	if ((bally - radius) <= boardbottom && (bally + radius + y_move) >= boardtop && ballx >= boardleft && ballx <= boardright)
	{
		y_move = -fabs(y_move);
		x_move = (ballx - boardx) / boardwidth * speed;
	}

	if ((bally + radius + y_move) >= HIGH)
	{
		nowheart--;
		ballx = boardx;
		bally = boardtop - radius;
	}

	if (bally >boardtop && bally< boardbottom && ballx >= boardleft && ballx <= boardright)
	{
		bally = boardtop - radius;
	}

	rainbow(0, &H, &S, &L);
	for (int k = 0; k < BRICKLINE; k++)
		for (int i = 0; i < BRICKROW; i++)
		{
			if (map[k][i])
			{
				lowest = k;
				if (colortype == 1) rainbow(1, &H, &S, &L);
				if (((bally + y_move + radius) >= k * brickhigh + radius) && ((bally + y_move - radius) <= (k + 1) * brickhigh) && (ballx >= i * brickwidth) && (ballx <= (i + 1) * brickwidth))
				{
					if (colortype == 0) ballcolor = BGR(color[k][i]);
					if (colortype == 1) ballcolor = HSLtoRGB(H, S, L);
					if (soundmode == 0)
					{
						mu_crash.stopmusic();
						mu_crash.playonce();
					}
					map[k][i] = 0;
					bricknumber--;
					y_move = -y_move;
					score+=speed/5;
					if (heartvanish == 0 && (rand() % 100) > 90-timesetting*5)
					{
						heartvanish = 1;
						hearty = bally;
						heartx = ballx;
					}
					if (flashvanish == 0 && (rand() % 100) > 90)
					{
						flashvanish = 1;
						flashy = bally;
						flashx = ballx;
					}
				}
				else if ((bally>= k * brickhigh ) && (bally <= k * brickhigh + brickhigh) && (ballx+x_move >= i * brickwidth) && (ballx + x_move <= (i+1) * brickwidth))
				{
					if (colortype == 0) ballcolor = BGR(color[k][i]);
					if (colortype == 1) ballcolor = HSLtoRGB(H, S, L);
					if (soundmode == 0)
					{
						mu_crash.stopmusic();
						mu_crash.playonce();
					}
					map[k][i] = 0;
					bricknumber--;
					x_move = -x_move;
					score += speed / 5;
					if (heartvanish == 0 && (rand() % 100) > 90 - timesetting * 5)
					{
						heartvanish = 1;
						hearty = bally;
						heartx = ballx;
					}
					if (flashvanish == 0 && (rand() % 100) > 90)
					{
						flashvanish = 1;
						flashy = bally;
						flashx = ballx;
					}
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
		case'W':case'w':
			_getch();
			break;
		case'Z':case'z':
			if (boardleft - 100 > 0)
			{
				boardx = boardx - 100;
			}
			else
			{
				boardx = boardwidth / 2;
			}
			boardleft = boardx - boardwidth / 2;
			boardright = boardx + boardwidth / 2;
			break;
		case'C':case'c':
			if (boardright + 100 < WIDTH2)
			{
				boardx = boardx + 100;
			}
			else
			{
				boardx = WIDTH2 - boardwidth / 2;
			}
			boardleft = boardx - boardwidth / 2;
			boardright = boardx + boardwidth / 2;
			break;
		case 27:
			save();
			stage = 0;
			score = 0;
			EndBatchDraw();
			menu();
			break;
		default:
			if (ch == -32)
				switch (_getch())
				{
				case 72: // 位置上移
					if (boardtop - 15 > (lowest+1)*brickhigh)
					{
						boardy = boardy - 15;
					}
					else
					{
						boardy = (lowest + 1) * brickhigh + boardhigh / 2;
					}
					boardtop = boardy - boardhigh / 2;
					boardbottom = boardy + boardhigh / 2;
					break;
				case 75:// 位置左移
					if (boardleft - 15 > 0)
					{
						boardx = boardx - 15;
					}
					else
					{
						boardx = boardwidth / 2;
					}
					boardleft = boardx - boardwidth / 2;
					boardright = boardx + boardwidth / 2;
					break;
				case 77: // 位置右移
					if (boardright + 15 < WIDTH2)
					{
						boardx = boardx + 15;
					}
					else
					{
						boardx = WIDTH2 - boardwidth / 2;
					}
					boardleft = boardx - boardwidth / 2;
					boardright = boardx + boardwidth / 2;
					break;
				case 80:
					if (boardbottom + 15 <= HIGH)
					{
						boardy = boardy + 15;  // 位置下移
					}
					else
					{
						boardy = HIGH - boardhigh / 2;
					}
					boardtop = boardy - boardhigh / 2;
					boardbottom = boardy + boardhigh / 2;
					break;
				}
		}
	}
}

void mousemove(void)
{
	boardx = cmd.msg.x;
	boardy = cmd.msg.y;
	boardleft = boardx - boardwidth / 2;
	boardright = boardx + boardwidth / 2;
	boardtop = boardy - boardhigh / 2;
	boardbottom = boardy + boardhigh / 2;
	if (boardtop< (lowest + 1) * brickhigh)
	{
		boardy = (lowest + 1) * brickhigh + boardhigh / 2;
		boardtop = boardy - boardhigh / 2;
		boardbottom = boardy + boardhigh / 2;
	}
	if (boardbottom > HIGH)
	{
		boardy = HIGH - boardhigh / 2;
		boardtop = boardy - boardhigh / 2;
		boardbottom = boardy + boardhigh / 2;
	}
	if (boardleft< 0)
	{
		boardx = boardwidth / 2;
		boardleft = boardx - boardwidth / 2;
		boardright = boardx + boardwidth / 2;
	}
	if (boardright > WIDTH2)
	{
		boardx = WIDTH2 - boardwidth / 2;
		boardleft = boardx - boardwidth / 2;
		boardright = boardx + boardwidth / 2;
	}
	if (_kbhit())
		switch (_getch())
		{
		case'W':case'w':
			_getch();
			break;
		case 27:
			save();
			stage = 0;
			score = 0;
			EndBatchDraw();
			menu();
			break;
		default :
			break;
		}

}