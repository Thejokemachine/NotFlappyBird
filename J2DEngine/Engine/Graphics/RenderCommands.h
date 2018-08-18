#pragma once
#include "../Math/Vector2.h"
#include "../Math/Rectangle.h"
#include "Graphics/ShaderWrappers.h"
#include "Texture.h"

struct SSpriteRenderCommand
{
	CVector2f position;
	SColor color;
	SUVRect textureRect;
	float rotation;
	CVector2f dimensions;
	CVector2f scale;
	CTexture texture;

	bool shouldRender;
};

struct SSpriteBatchRenderCommand
{
	SSpriteRenderCommand* sprites;
	int amount;
};