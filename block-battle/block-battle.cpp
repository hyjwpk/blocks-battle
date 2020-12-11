// block-battle.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include "pch.h"
#include "block-battle.h"
#pragma comment(lib,"Winmm.lib")

int main(void)
{
	initgraph(WIDTH1, HIGH, EW_NOCLOSE);
	menu();
	closegraph();
	return 0;
}
