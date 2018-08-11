#pragma once

struct SShaderVec2
{
	float x;
	float y;

	void operator= (const CVector2f& aVector2f)
	{
		x = aVector2f.x;
		y = aVector2f.y;
	}
};

struct SUVRect
{
	SUVRect() = default;

	SUVRect(const SShaderVec2& aTopLeft, const SShaderVec2& aBottomRight)
	{
		topLeft = aTopLeft;
		bottomRight = aBottomRight;
	}

	SShaderVec2 topLeft = { 0.f ,0.f };
	SShaderVec2 bottomRight = { 1.f, 1.f };
};

struct SSprite
{
	SShaderVec2 position;
	SColor color;
	SUVRect textureRect;
	float rotation;
	SShaderVec2 dimensions;
	SShaderVec2 scale;
	float trash;
};