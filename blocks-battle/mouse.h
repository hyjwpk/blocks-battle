#pragma once

class Mouse
{
public:
	Mouse();
	bool getClick();
	void setClick(bool state);
	bool getLBdown();
	void setLBdown(bool state);
	MOUSEMSG msg;
private:
	bool click;
	bool LBdown;
};

DWORD WINAPI Thread_GetMouseMsg(PVOID pMyPara);