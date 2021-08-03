#include "pch.h"
#include "game.h"

void Game::play(void)
{
	while (true)
	{
		if (Brick::bricknumber == 0) initial(1);
		if (Heart::value == 0)	fail();
		clean();
		Board::board->move();
		crash();
		Ball::ball->move();
		print();
		if (_kbhit() && _getch() == 27)
		{
			Load::save();
			Stage::stage = 0;
			EndBatchDraw();
			Menu::menuControl();
		}
		Sleep(1);
	}
}

void Game::initial(int type)//1为读取关卡,2为读取存档
{
	Board::board = new Board();
	Ball::ball = new Ball(WIDTH2 / 2, 12.0 * Board::board->boardhigh + (HIGH - 12 * Board::board->boardhigh) / 2);
	Difficulty::updateSet();
	Top::score = 0;
	Heart::value = 3;
	Time::t_save = 0;
	switch (type)
	{
	case 1:
		++Stage::stage;
		if (!Stage::read()) win();
		break;
	case 2:
		if (!Load::read()) Menu::menuControl();
		break;
	}

	Brick::bricknumber = 0;
	for (int k = 0; k < BRICKLINE; k++)
		for (int i = 0; i < BRICKROW; i++)
			if (Brick::map[k][i])
				Brick::bricknumber++;

	(new Star)->animation();
	Stage::title();
	Time::t = clock();
}

void Game::clean()
{
	IMAGE background;
	loadimage(&background, "JPG", MAKEINTRESOURCE(IDR_JPG1), WIDTH1, HIGH, 1);
	putimage(0, 0, &background);
}

void Game::print()
{
	Ball::ball->print();
	Board::board->print();
	Brick::print();
	Heart::control();
	Flash::control();
	Top::display();
	Time::display();
	FlushBatchDraw();
}

void Game::crash()
{
	Ball::ball->crash();
	Board::board->crash();
	Brick::crash();
}

void Game::fail()
{
	Top::save();
	Stage::stage = 0;
	Top::score = 0;
	Time::t = 0;
	if (Musicbtn::soundmode == OPEN)
	{
		mu_background.stopMusic();
		mu_dead.playOnce();
	}
	clean();
	setbkmode(TRANSPARENT);
	settextstyle(100, 0, "Consolas");
	settextcolor(0x555555);
	outtextxy(303, 173, "YOU LOSE");
	settextcolor(LIGHTRED);
	outtextxy(300, 170, "YOU LOSE");
	FlushBatchDraw();

	while (true)
		if (_kbhit() && _getch() == 27)
		{

			EndBatchDraw();
			mu_dead.stopMusic();
			Menu::menuControl();
			break;
		}
}

void Game::win()
{
	Top::save();
	Stage::stage = 0;
	Top::score = 0;
	Time::t = 0;
	clean();
	setbkmode(TRANSPARENT);
	settextstyle(100, 0, "Consolas");
	settextcolor(0x555555);
	outtextxy(153, 173, "Congratulations");
	settextcolor(LIGHTRED);
	outtextxy(150, 170, "Congratulations");
	FlushBatchDraw();

	while (true)
		if (_kbhit() && _getch() == 27)
		{
			EndBatchDraw();
			Menu::menuControl();
			break;
		}
}
