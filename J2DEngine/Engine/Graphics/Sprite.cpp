#include "Sprite.h"
#include "Engine/Scene.h"
#include "Colors.h"
#include "../Engine/Shader.h"

CScene* CSprite::ourScene;

CSprite::CSprite()
{
	myHasBeenLoaded = false;
}

CSprite::~CSprite()
{
}

void CSprite::Load(const std::string & aFilePath)
{
	if (myHasBeenLoaded == false)
	{
		myColor = Colors::White;
	}

	myTexture.Load(aFilePath);
	myHasBeenLoaded = true;

}

void CSprite::Render()
{
	ourScene->AddSprite(this);
}

void CSprite::SetColor(SColor aColor)
{
	myColor = aColor;
}

SColor CSprite::GetColor()
{
	return myColor;
}

CVector2f CSprite::GetDimensions()
{
	return{ static_cast<float>(myTexture.GetDimensions().x), static_cast<float>(myTexture.GetDimensions().y) };
}

void CSprite::SetTextureRect(const CVector2f & aTopLeft, const CVector2f & aBottomRight)
{
	myTextureRect.topLeft = { aTopLeft.x, aTopLeft.y };
	myTextureRect.bottomRight = { aBottomRight.x, aBottomRight.y };
}

SUVRect CSprite::GetTextureRect()
{
	return myTextureRect;
}

CTexture CSprite::GetTexture()
{
	return myTexture;
}

void CSprite::SetShader(const CShader & aShader)
{
	myShader = &aShader;
}

void CSprite::SetScene(CScene * aScene)
{
	ourScene = aScene;
}
