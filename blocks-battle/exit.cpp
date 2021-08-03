#include "pch.h"
#include "exit.h"

Exit::Exit(int btnx, int btny, int wid, int len, const char* text) :Button(btnx, btny, wid, len, text) {}

void Exit::pressfuc()
{
	if (!press) return;
	exit(0);
}