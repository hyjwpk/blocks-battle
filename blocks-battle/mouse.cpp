#include "pch.h"
#include "mouse.h"

Mouse cmd;

DWORD WINAPI Thread_GetMouseMsg(PVOID pMyPara)
{
	while (1) 
	{
		if (MouseHit()) 
		{
			cmd.msg = GetMouseMsg();
			if (!cmd.getLBdown() && cmd.msg.mkLButton) 
			{
				cmd.setLBdown(true);
				cmd.setClick(true);
			}
			if (cmd.msg.uMsg == WM_LBUTTONUP)
				cmd.setLBdown(false);
		}
		Sleep(5);
	};
	return 0;
}



Mouse::Mouse()
{
	click = false;
	LBdown = false;
}

bool Mouse::getClick()
{
	return click;
}

bool Mouse::getLBdown()
{
	return LBdown;
}

void Mouse::setClick(bool state)
{
	click = state;
}

void Mouse::setLBdown(bool state)
{
	LBdown = state;
}
