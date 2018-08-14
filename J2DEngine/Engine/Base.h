#pragma once
#include <string>
#include <iostream>

#define PRINT(text) std::cout << (text) << std::endl

class CBase
{
public:
	CBase();
	~CBase();

	virtual std::string ToString();
};

struct SColor
{
	SColor(float aR = 0.f, float aG = 0.f, float aB = 0.f, float aA = 0.f)
	{
		r = aR; g = aG; b = aB; a = aA;
	}

	SColor operator*(float aScalar);
	void operator*=(float aScalar);

	float r;
	float g;
	float b;
	float a;
};

