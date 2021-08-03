#pragma once
constexpr auto MAXSTAR = 200;

struct STAR
{
	STAR();
	int	x;
	int	y;
	int	step;
	COLORREF color;
};

class Star
{
public:
	void animation();
private:
	void moveStar(int i);
	STAR star[MAXSTAR];
};