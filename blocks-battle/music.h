#include "pch.h"
#pragma comment(lib, "Winmm.lib")
#pragma once
class Music
{
public:
	Music(int num,const char *name);
	bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);
	void playmusic();
	void playonce();
	void stopmusic();
	void deletemusic();
private:
	TCHAR tmpmp3[_MAX_PATH];
	const char* name;
};