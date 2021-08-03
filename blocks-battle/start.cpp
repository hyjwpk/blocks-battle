#include "pch.h"
#include "start.h"

Start::Start(int btnx, int btny, int wid, int len, const char* text) :Button(btnx, btny, wid, len, text) {}

void Start::pressfuc()
{
	if (!press) return;
	Game::initial(1);
	Game::play();
}
