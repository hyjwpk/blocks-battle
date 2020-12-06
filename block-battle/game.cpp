#include "pch.h"
#include "game.h"
void game(void)
{
	BeginBatchDraw();
	clean();
	print();
	_getch();
	while (1)
	{
		clean();
		boardmove();
		crash();
		ballmove();
		print();
		Sleep(1);
		if (bricknumber == 0)
		{
			initial(1);
			clean();
			print();
		}
	}
	EndBatchDraw();
}