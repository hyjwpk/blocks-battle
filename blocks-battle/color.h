#pragma once
constexpr auto CUSTOMIZE = 0;
constexpr auto RAINBOW = 1;

class Color
{
public:
	static int type;
	static void rainbow(int type, float* H, float* S, float* L);
};