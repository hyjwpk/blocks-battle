#include "pch.h"
#include "stage.h"

int Stage::stage = 0;

void Stage::title()
{
	Game::clean();
	char s[] = "STAGE  ";
	s[6] = '0' + stage;
	settextstyle(105, 0, "Consolas");
	settextcolor(0x555555);
	outtextxy(288, 226, s);
	settextcolor(WHITE);
	outtextxy(285, 223, s);
	FlushBatchDraw();
	Sleep(1000);
}

bool Stage::read()
{
	HRSRC	hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_TEXT1 + stage - 1), "TEXT");//参数为NULL时返回调用进程自身的句柄
	if (hRes == NULL) return false;
	char* pText = (char*)LoadResource(NULL, hRes);

	TCHAR tmp[_MAX_PATH];
	GetTempPath(_MAX_PATH, tmp);
	strcat(tmp, _T("stage.txt"));

	FILE* stage = fopen(tmp, "w");
	fprintf(stage, "%s", pText);
	fclose(stage);

	stage = fopen(tmp, "r");
	for (int k = 0; k < BRICKLINE; k++)
		for (int i = 0; i < BRICKROW; i++)
			fscanf_s(stage, "%d", &Brick::map[k][i]);
	fscanf_s(stage, "%d", &Color::type);
	if (Color::type == CUSTOMIZE)//0为自定义色彩模式，1为彩虹色模式
		for (int k = 0; k < BRICKLINE; k++)
			for (int i = 0; i < BRICKROW; i++)
				fscanf_s(stage, "%x", &Brick::color[k][i]);
	fclose(stage);

	DeleteFile(tmp);
	return true;
}
