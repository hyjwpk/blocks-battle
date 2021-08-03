#include "pch.h"
#include "color.h"

int Color::type = RAINBOW;

void Color::rainbow(int type, float* H, float* S, float* L)
{
	if (type == 0)
	{
		*H = 0;		// ɫ��
		*S = 0.6f;		// ���Ͷ�
		*L = 0.5f;		// ����
	}
	else if (type == 1)
	{
		*H += 5;
		setfillcolor(HSLtoRGB(*H, *S, *L));
	}
}
