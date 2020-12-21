#include "pch.h"
#include "menu.h"

void top(void)
{
	clean();

	setbkmode(TRANSPARENT);
	settextstyle(100, 0, "微软雅黑", 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(0x555555);
	outtextxy(333, 53, "游戏排行");
	settextcolor(WHITE);
	outtextxy(330, 50, "游戏排行");

	settextstyle(60, 30, "Consolas");

	FILE* highscore;
	int high[4];
	if ((highscore = fopen("highscore.txt", "r")) != NULL)
	{
		for (int i = 0;i < 3;i++)
		{
			fscanf(highscore, "%d", &high[i]);
		}
		fclose(highscore);
	}
	else
	{
		for (int i = 0;i < 3;i++)
		{
			high[i] = 0;
		}
	}

	
	for (int k = 0;k < 3;k++)
	{
		char num[7] = "1.0000";
		num[0] = (k + '1');
		int tscore = high[k];
		int i = 5;
		while (tscore > 0 && i >= 2)
		{
			num[i--] = (tscore % 10 + '0');
			tscore /= 10;
		}
		outtextxy(390, 180 + 100 * k, num);
	}
	FlushBatchDraw();
	_getch();
}

void script(void)
{
	IMAGE img;
	loadimage(&img, "PNG", MAKEINTRESOURCE(IDB_PNG3), WIDTH1, HIGH);
	putimage(0, 0, &img);
	FlushBatchDraw();
	_getch();
}

void menu(void)
{
	clean();

	mu_background.playmusic();

	Button btn_start(400, 240, 120, 30, "开始");
	Button btn_save(400, 280, 120, 30, "继续");	
	Button btn_howtoplay(400, 320, 120, 30, "说明");
	Button btn_top(400, 360, 120, 30, "排行");
	Button btn_exit(400, 400, 120, 30, "退出");


	BeginBatchDraw();
	while (1) {
	
		setbkmode(TRANSPARENT);
		settextstyle(100, 0, "微软雅黑", 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
		settextcolor(0x555555);
		outtextxy(163, 53, "BLOCKS-BATTLE");
		settextcolor(WHITE);
		outtextxy(160, 50, "BLOCKS-BATTLE");
		// 显示按钮
		btn_start.Show();
		btn_save.Show();
		btn_howtoplay.Show();
		btn_top.Show();
		btn_exit.Show();

		FlushBatchDraw();

		if (btn_start.press) 
		{
			game();
			break;
		}
		if (btn_save.press)
		{
			initial(2);
			game();
			break;
		}
		else if (btn_howtoplay.press) 
		{
			script();
			clean();
		}
		else if (btn_top.press)
		{
			top();
			clean();
		}
		else if (btn_exit.press) 
		{
			mu_background.deletemusic();
			mu_crash.deletemusic();
			mu_dead.deletemusic();
			exit(0);
			break;
		}
	}

}