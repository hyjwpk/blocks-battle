#include "pch.h"
#include "music.h"
bool Music::ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	HRSRC	hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL	hMem = ::LoadResource(NULL, hRes);
	DWORD	dwSize = ::SizeofResource(NULL, hRes);

	
	DWORD dwWrite = 0;  	
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}

Music::Music(int num,const char *name)
{
	::GetTempPath(_MAX_PATH, this->tmpmp3);
	_tcscat(this->tmpmp3, name);
	_tcscat(this->tmpmp3, ".mp3");
	ExtractResource(this->tmpmp3, _T("MP3"), MAKEINTRESOURCE(num));

	
	TCHAR mcicmd[300];
	_stprintf(mcicmd, _T("open \"%s\" alias %s"), this->tmpmp3,name);
	mciSendString(mcicmd, NULL, 0, NULL);
	this->name = name;

}

void Music::playmusic()
{
	TCHAR mcicmd[300];
	_stprintf(mcicmd, _T("play %s repeat"), this->tmpmp3, name);
	mciSendString(mcicmd, NULL, 0, NULL);
}

void Music::playonce()
{
	TCHAR mcicmd[300];
	_stprintf(mcicmd, _T("play %s"), this->tmpmp3, name);
	mciSendString(mcicmd, NULL, 0, NULL);
}

void Music::stopmusic()
{
	TCHAR mcicmd[300];
	_stprintf(mcicmd, _T("stop %s"), this->tmpmp3, name);
	mciSendString(mcicmd, NULL, 0, NULL);
}

void Music::deletemusic()
{
	TCHAR mcicmd[300];
	_stprintf(mcicmd, _T("close %s"), this->tmpmp3, name);
	mciSendString(mcicmd, NULL, 0, NULL);
	DeleteFile(this->tmpmp3);
}