#include "pch.h"
#include "flash.h"

bool Flash::exist = false;
Flash* Flash::flash = NULL;

Flash::Flash(int x, int y, int size)
{
	this->x = x;
	this->y = y;
	this->size = size;
	loadimage(&mask, "PNG", MAKEINTRESOURCE(IDB_PNG4), size, size);
	loadimage(&picture, "PNG", MAKEINTRESOURCE(IDB_PNG3), size, size);
}

void Flash::control()
{

	if (!exist) return;
	if (++(flash->y) > HIGH)
	{
		delete(flash);
		exist = false;
		return;
	}
	flash->property();
	if (exist && flash->y <= Board::board->boardbottom && flash->y >= Board::board->boardtop
		&& flash->x >= Board::board->boardleft && flash->x <= Board::board->boardright)
	{
		delete(flash);
		exist = false;
		Ball::ball->speed++;
	}
}

void Flash::property()
{
	putimage(x, y, &mask, SRCAND);
	putimage(x, y, &picture, SRCPAINT);
}
