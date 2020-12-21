#include "pch.h"
#include "button.h"


Button::Button(int btnx, int btny, int wid, int len, const char* text, int font_size, int font_bold, COLORREF font_color)
{
	press = false;
	turnlittle = false;
	button_color = 0xeeeeee;
	color_gap = 0;			
	this->text = text;		
	this->font_size = font_size;	
	this->font_bold = font_bold;	
	this->font_color = font_color;	
	this->btnxl = btnx;			
	this->btnyl = btny;			
	this->btnxr = btnx + wid;	
	this->btnyr = btny + len;	
	settextstyle(font_size, 0, "Î¢ÈíÑÅºÚ", 0, 0, font_bold, false, false, false);
	this->textx = this->btnxl + (wid - textwidth(text)) / 2;	
	this->texty = this->btnyl + (len - textheight(text)) / 2;	
}
Button::~Button()
{}


void Button::Show()
{
	settextstyle(font_size, 0, "Î¢ÈíÑÅºÚ", 0, 0, font_bold, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(font_color);
	setbkmode(TRANSPARENT);

	setlinecolor(0xaaaaaa);
	setfillcolor(button_color);

	fillroundrect(btnxl, btnyl, btnxr, btnyr, 20, 20);


	outtextxy(textx, texty, text);

	Mouse();
}



void Button::Mouse()
{
	press = false;
	if (MouseOn()) 
	{
		ChangeButtonColor(true);	
		if (cmd.msg.uMsg == WM_LBUTTONDOWN) 
		{
			TurnLittle();
		}
		if (cmd.msg.uMsg == WM_LBUTTONUP) 
		{
			cmd.msg.uMsg = 0;
			press = true;	
		}
	}
	else 
	{
		ChangeButtonColor(false);	
		TurnBig();
	}
}


bool Button::MouseOn()
{
	if (cmd.msg.x >= btnxl && cmd.msg.x <= btnxr && cmd.msg.y >= btnyl && cmd.msg.y <= btnyr)
		return true;
	else
		return false;
}


void Button::ChangeButtonColor(bool flag)
{
	if (color_gap == 0) 
	{
		if (flag && button_color != 0xbbbbbb) 
			button_color -= 0x111111;
		else if (!flag && button_color != 0xeeeeee) 
			button_color += 0x111111;
		color_gap = 6;
	}
	else
		color_gap--;
}

void Button::TurnLittle()
{
	if (turnlittle)
		return;

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

void Button::TurnBig()
{
	if (!turnlittle)
		return;

	btnxl -= 5;
	btnyl -= 2;
	btnxr += 5;
	btnyr += 2;
	turnlittle = false;
}