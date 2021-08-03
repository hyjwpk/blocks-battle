#include "pch.h"
#include "musicbtn.h"

int Musicbtn::soundmode = OPEN;

Musicbtn::Musicbtn(int btnx, int btny, int wid, int len, const char* text) :Button(btnx, btny, wid, len, text)
{
	changeButtonText();
	updateSet();
}

void Musicbtn::pressfuc()
{
	if (!press) return;
	soundmode++;
	soundmode %= 2;
	changeButtonText();
	updateSet();
}

void Musicbtn::changeButtonText()
{
	if (soundmode == OPEN) text = "“Ù¿÷:ø™";
	else if (soundmode == CLOSE) text = "“Ù¿÷:πÿ";
}

void Musicbtn::updateSet()
{
	if (soundmode == OPEN) mu_background.playMusic();
	else if (soundmode == CLOSE) mu_background.stopMusic();
}