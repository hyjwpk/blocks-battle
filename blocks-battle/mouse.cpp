#include "pch.h"
#include "mouse.h"

EASYXMSG Mouse::msg = *(new EASYXMSG);

DWORD WINAPI Mouse::Thread_GetEASYXMSG(PVOID pMyPara)
{
	while (true) Mouse::msg = getmessage(EM_MOUSE);
	return 0;
}
