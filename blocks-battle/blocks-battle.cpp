#include "pch.h"
#include "blocks-battle.h"

int main(void)
{
	initgraph(WIDTH1, HIGH, EW_NOCLOSE);//禁用绘图窗口的关闭按钮。
	SetWindowText(GetHWnd(), "BLOCKS-BATTLE");
	CreateThread(NULL, 0, Thread_GetMouseMsg, NULL, 0, NULL);
	menu();
	return 0;
}
