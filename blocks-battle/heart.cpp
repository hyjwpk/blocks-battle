#include "pch.h"
#include "heart.h"

int Heart::value = 3;
bool Heart::exist = false;
Heart* Heart::heart = NULL;

Heart::Heart(int x, int y, int size)
{
	this->x = x;
	this->y = y;
	this->size = size;
	loadimage(&mask, "PNG", MAKEINTRESOURCE(IDB_PNG2), size, size);
	loadimage(&picture, "PNG", MAKEINTRESOURCE(IDB_PNG1), size, size);
}

void Heart::control()
{
	display();

	if (!exist) return;
	if (++(heart->y) > HIGH)
	{
		delete(heart);
		exist = false;
		return;
	}
	heart->property();

	if (exist && heart->y <= Board::board->boardbottom && heart->y >= Board::board->boardtop
		&& heart->x >= Board::board->boardleft && heart->x <= Board::board->boardright)
	{
		delete(heart);
		exist = false;
		if (value < 3) value++;
	}
}

void Heart::display()
{
	Heart disvalue(750, 10, 50);
	for (int i = value; i > 0; i--)
	{
		disvalue.x += 50;
		disvalue.property();
	}
}

void Heart::property()
{
	putimage(x, y, &mask, SRCAND);
	putimage(x, y, &picture, SRCPAINT);
}
