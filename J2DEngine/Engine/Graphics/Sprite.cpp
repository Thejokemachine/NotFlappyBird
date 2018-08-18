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

SColor CSprite::GetColor() const
{
	return myColor;
}

CVector2f CSprite::GetDimensions() const
{
	return{ static_cast<float>(myTexture.GetDimensions().x), static_cast<float>(myTexture.GetDimensions().y) };
}

void CSprite::SetTextureRect(const CVector2f & aTopLeft, const CVector2f & aBottomRight)
{
	myTextureRect.topLeft = { aTopLeft.x, aTopLeft.y };
	myTextureRect.bottomRight = { aBottomRight.x, aBottomRight.y };
}

SUVRect CSprite::GetTextureRect() const
{
	return myTextureRect;
}

CTexture CSprite::GetTexture() const
{
	return myTexture;
}

SSpriteRenderCommand CSprite::GetRenderCommand() const
{
	SSpriteRenderCommand rc;

	rc.color = GetColor();
	rc.dimensions = GetDimensions();
	rc.position = GetPosition();
	rc.rotation = GetRotation();
	rc.scale = GetScale();
	rc.texture = GetTexture();
	rc.textureRect = GetTextureRect();
	rc.shouldRender = true;

	return std::move(rc);
}

void CSprite::SetShader(const CShader & aShader)
{
	myShader = &aShader;
}

void CSprite::SetScene(CScene * aScene)
{
	ourScene = aScene;
}
