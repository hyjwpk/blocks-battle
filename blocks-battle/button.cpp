#include "pch.h"
#include "button.h"

Button::Button(int btnx, int btny, int wid, int len, const char* text, int font_size, int font_bold, COLORREF font_color)
{
	press = false;
	button_color = 0xeeeeee;
	color_gap = 0;
	this->font_size = font_size;
	this->font_bold = font_bold;
	this->font_color = font_color;
	this->btnxl = btnx;
	this->btnyl = btny;
	this->btnxr = btnx + wid;
	this->btnyr = btny + len;
	settextstyle(font_size, 0, "微软雅黑", 0, 0, font_bold, false, false, false);//设置字体后才能正确将文字放于中间
	this->textx = this->btnxl + (wid - textwidth(text)) / 2;
	this->texty = this->btnyl + (len - textheight(text)) / 2;
	this->text = text;
	turnlittle = false;
}

void Button::show()
{
	settextstyle(font_size, 0, "微软雅黑", 0, 0, font_bold, false, false, false);
	settextcolor(font_color);
	setbkmode(TRANSPARENT);

	setlinecolor(0xaaaaaa);
	setfillcolor(button_color);

	fillroundrect(btnxl, btnyl, btnxr, btnyr, 20, 20);

	outtextxy(textx, texty, text);

	mouse();
}

void Button::mouse()
{
	press = false;
	if (mouseOn())
	{
		changeButtonColor(true);
		if (Mouse::msg.message == WM_LBUTTONDOWN) turnLittle();
		if (Mouse::msg.message == WM_LBUTTONUP)
		{
			Mouse::msg.message = 0;
			press = true;
			turnBig();
		}
	}
	else
	{
		changeButtonColor(false);
		turnBig();
	}
}


bool Button::mouseOn()
{
	if (Mouse::msg.x >= btnxl && Mouse::msg.x <= btnxr && Mouse::msg.y >= btnyl && Mouse::msg.y <= btnyr) return true;
	else return false;
}

void Button::changeButtonColor(bool flag)
{
	if (color_gap == 0)
	{
		if (flag && button_color != 0xbbbbbb) button_color -= 0x111111;
		else if (!flag && button_color != 0xeeeeee) button_color += 0x111111;
		color_gap = 6;
	}
	else color_gap--;
}

void Button::turnLittle()
{
	if (turnlittle) return;

	COLORREF bk = getpixel(btnxl, btnyl);
	setfillcolor(bk);
	setlinecolor(bk);
	fillroundrect(btnxl, btnyl, btnxr, btnyr, 20, 20);

	btnxl += 5;
	btnyl += 2;
	btnxr -= 5;
	btnyr -= 2;
	turnlittle = true;
}

void Button::turnBig()
{
	if (!turnlittle) return;

	btnxl -= 5;
	btnyl -= 2;
	btnxr += 5;
	btnyr += 2;
	turnlittle = false;
}

void Button::changeButtonText(const char* text)
{
	this->text = text;
}

void Button::showButton(Button* btn[], int num)
{
	for (int i = 0; i < num; i++) btn[i]->show();
	FlushBatchDraw();
}