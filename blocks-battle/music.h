#pragma once
#pragma comment(lib, "Winmm.lib")

class Music
{
public:
	Music(int num, const char* name);
	~Music();
	void playMusic();
	void playOnce();
	void stopMusic();
private:
	bool extractResource(LPCTSTR strDstFile, LPCTSTR strResName, LPCTSTR strResType);
	char mp3File[_MAX_PATH];
	char mciCmd[300];
};