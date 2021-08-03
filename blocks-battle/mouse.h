#pragma once

class Mouse
{
public:
	static EASYXMSG msg;
	static DWORD WINAPI Thread_GetEASYXMSG(PVOID pMyPara);
};