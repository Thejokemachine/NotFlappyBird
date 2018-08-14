#include "SpriteNumber.h"

void CSpriteNumber::Set(int aNumber)
{
	myNumber = aNumber;
	myStringNumber = std::to_string(myNumber);
	SetScale({ (GetDimensions().x / 10) / GetDimensions().x, 1.f });
}

void CSpriteNumber::Increment(int aAmount)
{
	Set(myNumber + aAmount);
}

std::string CSpriteNumber::ToString()
{
	return myStringNumber;
}

void CSpriteNumber::Render()
{
	CVector2f startPosition = GetPosition();
	float digitWidth = GetDimensions().x / 10.f;
	bool firstMove = true;

	for (char& digit : myStringNumber)
	{
		CalculateTextureRect(digit - 48);
		if (firstMove == false)
		{
			Move(digitWidth / 2.f, 0);
		}
		firstMove = false;
		CSprite::Render();
	}

	SetPosition(startPosition);
}

void CSpriteNumber::CalculateTextureRect(int aDigit)
{
	float left, right;
	CVector2f dimensions = GetDimensions();
	float digitWidth = ((dimensions.x / 10.f) / dimensions.x);

	left = aDigit * digitWidth;
	right = left + digitWidth;

	SetTextureRect({left, 0.f}, {right, 1.f});
}
