#pragma once
#include "Base.h"
#include "Graphics/Sprite.h"

class CSpriteNumber : public CSprite
{
public:

	void Set(int aNumber);
	void Increment(int aAmount);

	std::string ToString() override;
	void Render() override;

private:
	void CalculateTextureRect(int aDigit);

	int myNumber;
	std::string myStringNumber;
};