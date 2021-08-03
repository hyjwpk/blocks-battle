#pragma once
#include "mouse.h"

class Button
{
public:
	Button(int btnx, int btny, int wid, int len, const char* text, int font_size = 30, int font_bold = 400, COLORREF font_color = BLACK);
	bool press;
	void show();
	virtual void updateSet() {}
	virtual void changeButtonText() {}
	void changeButtonText(const char* text);
	static void showButton(Button* btn[], int num);
	virtual void pressfuc() {};
private:
	COLORREF button_color;
	int color_gap;
	int font_size;
	int font_bold;
	COLORREF font_color;
	int btnxl;
	int btnyl;
	int btnxr;
	int btnyr;
	int textx;
	int texty;
	bool turnlittle;
	void mouse();
	bool mouseOn();
	void turnLittle();
	void turnBig();
	void changeButtonColor(bool flag);
protected:
	const char* text;
};