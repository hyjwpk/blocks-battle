#pragma once
#include "button.h"
#include "start.h"
#include "load.h"
#include "settings.h"
#include "script.h"
#include "top.h"
#include "exit.h"
#include "musicbtn.h"

class Menu
{
public:
	static void menuControl();
private:
	static void title();
	static bool pressMenuButton(Button* btn[]);
};