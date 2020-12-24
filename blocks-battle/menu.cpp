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
	clean();

	setbkmode(TRANSPARENT);
	settextstyle(100, 0, "微软雅黑", 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(BLACK);
	outtextxy(333, 53, "游戏说明");
	settextcolor(WHITE);
	outtextxy(330, 50, "游戏说明");
	FlushBatchDraw();

	setfillcolor(0xeeeeee);
	setlinecolor(0xcccccc);
	for (int i = 1; i <= 60; i++) {
		fillroundrect((WIDTH1 - 400) / 2, HIGH / 2 - 250 / 2 * i / 60, (WIDTH1 + 400) / 2, HIGH / 2 + 250 / 2 * i / 60, 60, 20);
		FlushBatchDraw();
		Sleep(3);
	}

	settextcolor(BLACK);
	settextstyle(30, 0, "微软雅黑", 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	outtextxy(340, 220, "使用方向键操控横板击打小球");
	outtextxy(340, 280, "游戏中按ESC存档并返回菜单");
	outtextxy(340, 340, "使用ADZC键大幅度移动,W暂停");
	FlushBatchDraw();

	_getch();
}

void settings(void)
{
	clean();

	Button btn_tough(425, 240, 120, 30, "难度:１");
	Button btn_music(425, 280, 120, 30, "音乐:开");
	Button btn_time(425, 320, 120, 30, "限时:关");
	Button btn_back(425, 360, 120, 30, "返回");

	if (tough == 0)
		btn_tough.ChangeButtonText("难度:１");
	else if (tough == 1)
		btn_tough.ChangeButtonText("难度:２");
	else if (tough == 2)
		btn_tough.ChangeButtonText("难度:３");

	if (soundmode == 0)
		btn_music.ChangeButtonText("音乐:开");
	else if (soundmode == 1)
		btn_music.ChangeButtonText("音乐:关");

	if (timesetting == 0)
		btn_time.ChangeButtonText("限时:关");
	else if (timesetting == 1)
		btn_time.ChangeButtonText("５０ｓ");
	else if (timesetting == 2)
		btn_time.ChangeButtonText("５００ｓ");

	while (1) 
	{
		setbkmode(TRANSPARENT);
		settextstyle(100, 0, "微软雅黑", 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
		settextcolor(0x555555);
		outtextxy(333, 53, "游戏设置");
		settextcolor(WHITE);
		outtextxy(330, 50, "游戏设置");

		// 显示按钮
		btn_tough.Show();
		btn_music.Show();
		btn_time.Show();
		btn_back.Show();

		FlushBatchDraw();

		if (btn_tough.press)
		{
			if (tough == 0)
			{
				btn_tough.ChangeButtonText("难度:２");
				tough = 1;
			}
			else if (tough == 1)
			{
				btn_tough.ChangeButtonText("难度:３");
				tough = 2;
			}
			else if (tough == 2)
			{
				btn_tough.ChangeButtonText("难度:１");
				tough = 0;
			}
		}
		else if (btn_music.press)
		{
			if (soundmode == 0)
			{
				btn_music.ChangeButtonText("音乐:关");
				mu_background.stopmusic();
				soundmode = 1;
			}
			else if (soundmode == 1)
			{
				btn_music.ChangeButtonText("音乐:开");
				mu_background.playmusic();
				soundmode = 0;
			}
		}
		else if (btn_time.press)
		{
			if (timesetting == 0)
			{
				btn_time.ChangeButtonText("５０ｓ");
				timesetting = 1;
			}
			else if (timesetting == 1)
			{
				btn_time.ChangeButtonText("５００ｓ");
				timesetting = 2;
			}
			else if (timesetting == 2)
			{
				btn_time.ChangeButtonText("限时:关");
				timesetting = 0;
			}
		}
		else if (btn_back.press)
		{
			break;
		}


	}
	
}

void menu(void)
{
	clean();
	if(soundmode==0)
		mu_background.playmusic();

	Button btn_start(425, 240, 120, 30, "开始");
	Button btn_save(425, 280, 120, 30, "继续");	
	Button btn_settings(425, 320, 120, 30, "设置");
	Button btn_howtoplay(425, 360, 120, 30, "说明");
	Button btn_top(425, 400, 120, 30, "排行");
	Button btn_exit(425, 440, 120, 30, "退出");


	BeginBatchDraw();
	while (1) {
	
		setbkmode(TRANSPARENT);
		settextstyle(100, 0, "微软雅黑", 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
		settextcolor(0x555555);
		outtextxy(178, 53, "BLOCKS-BATTLE");
		settextcolor(WHITE);
		outtextxy(175, 50, "BLOCKS-BATTLE");
		// 显示按钮
		btn_start.Show();
		btn_save.Show();
		btn_settings.Show();
		btn_howtoplay.Show();
		btn_top.Show();
		btn_exit.Show();

		FlushBatchDraw();

		if (btn_start.press) 
		{
			game();
			break;
		}
		else if (btn_save.press)
		{
			initial(2);
			game();
			break;
		}
		else if (btn_settings.press)
		{
			settings();
			clean();
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