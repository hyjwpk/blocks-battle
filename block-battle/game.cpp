#include "pch.h"
#include "game.h"

void game(void)
{
	BeginBatchDraw();

	while (1)
	{
		if (bricknumber == 0||stage==0)
		{
			initial(1);
			clean();
			stagetitle(stage);
			clean();
			print();
			_getch();
		}
		clean();
		boardmove();
		crash();
		ballmove();
		print();
		Sleep(1);
		if (nowheart == 0)
		{
			fail();
		}
	}

	EndBatchDraw();
}