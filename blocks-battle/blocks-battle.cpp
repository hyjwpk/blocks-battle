#include "pch.h"
#include "blocks-battle.h"

int main(void)
{
	initgraph(WIDTH1, HIGH, EW_NOCLOSE | EW_NOMINIMIZE);
	SetWindowText(GetHWnd(), "BLOCKS-BATTLE");
	CreateThread(NULL, 0, Mouse::Thread_GetEASYXMSG, NULL, 0, NULL);
	Menu::menuControl();
	return 0;
}
