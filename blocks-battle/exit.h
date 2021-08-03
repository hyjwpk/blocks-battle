#pragma once
#include "button.h"

class Exit :
	public Button
{
public:
	Exit(int btnx, int btny, int wid, int len, const char* text);
	void pressfuc();
};