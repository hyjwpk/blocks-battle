#include "pch.h"
#include "game.h"
void game(void)
{


	while (1)
	{
		if (bricknumber == 0||stage==0)
		{
			initial(1);
			clean();
			stagetitle(stage);
			clean();
			print();
			if (control == 1)
				_getch();
			t = clock();
		}
		clean();
		if (control == 0)
			mousemove();
		else if (control == 1)
			boardmove();
		crash();
		ballmove();
		print();
		Sleep(1);
		if (nowheart == 0)
		{
			sortscore();
			fail();
		}
	}

	EndBatchDraw();
}