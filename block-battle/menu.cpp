#include "pch.h"
#include "menu.h"

void menu(void);
int menukeyboard(void);
void script(void);

void script(void)
{
	setbkcolor(BACKROUNDCOLOR);
	cleardevice();

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	_tcscpy_s(f.lfFaceName, _T("新宋体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	setbkcolor(LIGHTBLUE);

	RECT r;
	r = { 350, 165, WIDTH1 - 1, 195 };
	drawtext(_T("按←向左移动横板"), &r,  DT_VCENTER | DT_SINGLELINE);
	r = { 350, 200, WIDTH1 - 1, 230 };
	drawtext(_T("按→向右移动横板"), &r, DT_VCENTER | DT_SINGLELINE);
	r = { 350, 235, WIDTH1 - 1, 265 };
	drawtext(_T("按A瞬移横板到最左侧"), &r,  DT_VCENTER | DT_SINGLELINE);
	r = { 350, 270, WIDTH1 - 1, 300 };
	drawtext(_T("按D瞬移横板到最右侧"), &r,  DT_VCENTER | DT_SINGLELINE);
	r = { 350, 305, WIDTH1 - 1, 335 };
	drawtext(_T("利用弹球碰撞消除砖块取得更高的分数"), &r,  DT_VCENTER | DT_SINGLELINE);
	r = { 350, 340, WIDTH1 - 1, 370 };
	drawtext(_T("按任意键返回菜单……"), &r,  DT_VCENTER | DT_SINGLELINE);

	_getch();
}
int menukeyboard(void)
{
	switch (_getch())
	{
	case 'a':case 'A':
		initial(1);
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
		break;
	case 'e':case 'E':
		break;
	case 'f':case 'F':
		exit(0);
		break;
	default:
		return 1;
		break;
	}
	return 0;
}
void menu(void)
{
	setbkcolor(BACKROUNDCOLOR);
	cleardevice();

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	_tcscpy_s(f.lfFaceName, _T("新宋体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	setbkcolor(LIGHTBLUE);

	RECT r;
	r = { 0, 165, WIDTH1 - 1, 195 };
	drawtext(_T("(A)游 戏 开 始"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 200, WIDTH1 - 1, 230 };
	drawtext(_T("(B)读 取 存 档"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 235, WIDTH1 - 1, 265 };
	drawtext(_T("(C)游 戏 说 明"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 270, WIDTH1 - 1, 300 };
	drawtext(_T("(D)游 戏 排 行"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 305, WIDTH1 - 1, 335 };
	drawtext(_T("(E)游 戏 设 置"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 340, WIDTH1 - 1, 370 };
	drawtext(_T("(F)退 出 游 戏"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	gettextstyle(&f);
	f.lfHeight = 40;
	_tcscpy_s(f.lfFaceName, _T("Consolas"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	r = { 0, 0, WIDTH1 - 1, 165 };
	drawtext(_T("BLOCKS-BATTLE"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	while (menukeyboard());
}

