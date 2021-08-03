#include "pch.h"
#include "brick.h"

int Brick::brickwidth = WIDTH2 / BRICKROW;
int Brick::brickhigh = brickwidth / 2;
int Brick::bricknumber = 0;
int Brick::lowest = 0;
int Brick::map[BRICKLINE][BRICKROW] = { 0 };
int Brick::color[BRICKLINE][BRICKROW] = { 0 };

void Brick::print()
{
	float H, S, L; 		// 色相 饱和度 亮度
	Color::rainbow(0, &H, &S, &L);
	for (int k = 0; k < BRICKLINE; k++)
		for (int i = 0; i < BRICKROW; i++)
			if (map[k][i])	 // 砖块存在，绘制砖块
			{
				setfillcolor(BLACK);
				solidrectangle(i * brickwidth, k * brickhigh, (i + 1) * brickwidth, (k + 1) * brickhigh);
				if (Color::type == RAINBOW) Color::rainbow(1, &H, &S, &L);
				if (Color::type == CUSTOMIZE) setfillcolor(BGR(color[k][i]));
				solidrectangle(i * brickwidth, k * brickhigh, (i + 1) * brickwidth - 3, (k + 1) * brickhigh - 3);
			}
}

void Brick::crash()
{
	float H, S, L;
	Color::rainbow(0, &H, &S, &L);
	for (int k = 0; k < BRICKLINE; k++)
		for (int i = 0; i < BRICKROW; i++)
			if (map[k][i])
			{
				lowest = k;
				if (Color::type == RAINBOW) Color::rainbow(1, &H, &S, &L);
				if ((((Ball::ball->y + Ball::ball->y_move + Ball::ball->radius) >= (double)k * brickhigh + Ball::ball->radius) && ((Ball::ball->y + Ball::ball->y_move - Ball::ball->radius) <= (k + 1.0) * brickhigh) && (Ball::ball->x >= (double)i * brickwidth) && (Ball::ball->x <= (i + 1.0) * brickwidth))
					|| ((Ball::ball->y >= (double)k * brickhigh) && (Ball::ball->y <= (double)k * brickhigh + brickhigh) && (Ball::ball->x + Ball::ball->x_move >= (double)i * brickwidth) && (Ball::ball->x + Ball::ball->x_move <= (i + 1.0) * brickwidth)))
				{
					if (Color::type == CUSTOMIZE) Ball::ball->color = BGR(color[k][i]);
					if (Color::type == RAINBOW) Ball::ball->color = HSLtoRGB(H, S, L);
					if (Musicbtn::soundmode == 0)
					{
						mu_crash.stopMusic();
						mu_crash.playOnce();
					}
					map[k][i] = 0;
					bricknumber--;

					Top::score += Ball::ball->speed / 5;
					if ((rand() % 100) > 50)
						if (!Heart::exist && (rand() % 100) > 90 - Time::timesetting * 5)
						{
							Heart::heart = new Heart((int)Ball::ball->x, (int)Ball::ball->y, 25);
							Heart::exist = true;
						}
						else if (!Flash::exist && (rand() % 100) > 90)
						{
							Flash::flash = new Flash((int)Ball::ball->x, (int)Ball::ball->y, 25);
							Flash::exist = true;
						}
				}
				if (((Ball::ball->y + Ball::ball->y_move + Ball::ball->radius) >= (double)k * brickhigh + Ball::ball->radius) && ((Ball::ball->y + Ball::ball->y_move - Ball::ball->radius) <= (k + 1.0) * brickhigh) && (Ball::ball->x >= (double)i * brickwidth) && (Ball::ball->x <= (i + 1.0) * brickwidth)) Ball::ball->y_move = -Ball::ball->y_move;
				else if ((Ball::ball->y >= (double)k * brickhigh) && (Ball::ball->y <= (double)k * brickhigh + brickhigh) && (Ball::ball->x + Ball::ball->x_move >= (double)i * brickwidth) && (Ball::ball->x + Ball::ball->x_move <= (i + 1.0) * brickwidth)) Ball::ball->x_move = -Ball::ball->x_move;
			}
}
