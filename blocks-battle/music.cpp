#include "pch.h"
#include "music.h"

Music::Music(int num, const char* name)
{
	GetTempPath(_MAX_PATH, mp3File);
	strcat_s(mp3File, name);
	strcat_s(mp3File, ".mp3");
	extractResource(mp3File, MAKEINTRESOURCE(num), "MP3");
}

Music::~Music()
{
	sprintf_s(mciCmd, "close %s", mp3File);
	mciSendString(mciCmd, NULL, 0, NULL);
	DeleteFile(mp3File);
}

bool Music::extractResource(LPCTSTR strDstFile, LPCTSTR strResName, LPCTSTR strResType)
{
	HANDLE hFile = CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return false;

	HRSRC	hRes = FindResource(NULL, strResName, strResType);//参数为NULL时返回调用进程自身的句柄
	if (hRes == NULL) return false;
	HGLOBAL	hMem = LoadResource(NULL, hRes);
	DWORD	dwSize = SizeofResource(NULL, hRes);
	DWORD dwWrite = 0;
	WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);

	CloseHandle(hFile);
	return true;
}

void Music::playMusic()
{
	sprintf_s(mciCmd, "play %s repeat", mp3File);
	mciSendString(mciCmd, NULL, 0, NULL);
}

void Music::playOnce()
{
	sprintf_s(mciCmd, "play %s", mp3File);
	mciSendString(mciCmd, NULL, 0, NULL);
}

void Music::stopMusic()
{
	sprintf_s(mciCmd, "stop %s", mp3File);
	mciSendString(mciCmd, NULL, 0, NULL);
}

Music mu_background(IDR_MP31, "background");
Music mu_crash(IDR_MP32, "crash");
Music mu_dead(IDR_MP33, "dead");