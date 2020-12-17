#include "pch.h"
#include "menu.h"

void menu(void)
{
	clean();

	mciSendString(L"open .\\resourses\\sound\\background.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString(L"play bkmusic repeat", NULL, 0, NULL);

	settextstyle(30, 0, L"新宋体");
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	setbkcolor(LIGHTBLUE);
	setbkmode(TRANSPARENT);

	RECT r;
	r = { 0, 165, WIDTH1 - 1, 195 };
	drawtext(L"(A)游 戏 开 始", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 200, WIDTH1 - 1, 230 };
	drawtext(L"(B)读 取 存 档", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 235, WIDTH1 - 1, 265 };
	drawtext(L"(C)游 戏 说 明", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 270, WIDTH1 - 1, 300 };
	drawtext(L"(D)游 戏 排 行", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 305, WIDTH1 - 1, 335 };
	drawtext(L"(E)游 戏 设 置", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 340, WIDTH1 - 1, 370 };
	drawtext(L"(F)退 出 游 戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	gettextstyle(&f);
	f.lfHeight = 40;
	_tcscpy_s(f.lfFaceName, L"Consolas");
	settextstyle(&f);
	r = { 0, 0, WIDTH1 - 1, 165 };
	drawtext(L"BLOCKS-BATTLE", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	while (menukeyboard());
}

void top(void)
{
	clean();

	settextstyle(40, 0, L"新宋体");
	RECT r;
	r = { 0, 0, WIDTH1 - 1, 165 };
	drawtext(L"游 戏 排 行", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextstyle(60, 30, L"Consolas");

	FILE* highscore;
	highscore = fopen(".\\resourses\\document\\highscore.txt", "r");
	int high[4];
	for (int i = 0;i < 3;i++)
	{
		fscanf(highscore, "%d", &high[i]);
	}
	fclose(highscore);

	for (int k = 0;k < 3;k++)
	{
		wchar_t num[7] = L"1.0000";
		num[0] = (wchar_t)(k + '1');
		int tscore = high[k];
		int i = 5;
		while (tscore > 0 && i >= 2)
		{
			num[i--] = (wchar_t)(tscore % 10 + '0');
			tscore /= 10;
		}
		outtextxy(390, 180 + 40 * k, num);
	}
	_getch();
}

int menukeyboard(void)
{
	switch (_getch())
	{
	case 'a':case 'A':
		game();
		break;
	case 'b':case 'B':
		initial(2);
		game();
		break;
	case 'c':case 'C':
		script();
		menu();
		break;
	case 'd':case 'D':
		top();
		menu();
		break;
	//case 'e':case 'E':
	//	break;
	case 'f':case 'F':
		exit(0);
		break;
	default:
		return 1;
		break;
	}
	return 0;
}

void script(void)
{
	setbkcolor(BACKROUNDCOLOR);
	IMAGE img;
	loadimage(&img, L".\\resourses\\picture\\instructions.jpg", WIDTH1, HIGH);
	putimage(0, 0, &img);
	_getch();
}




