#include "SpriteBatch.h"
#include "Engine/Scene.h"
#include "Engine/Limits.h"

CScene* CSpriteBatch::ourScene;

void CSpriteBatch::Load(const std::string & aFilePath)
{
	myTexture.Load(aFilePath);
	myHasBeenLoaded = true;
}

void CSpriteBatch::Render()
{
	if (mySprites.size() > 0)
	{
		ourScene->AddSpriteBatch(this);
	}
}

void CSpriteBatch::AddSprite(const CSprite& aSprite)
{
	if (mySprites.size() < MAX_AMOUNT_SPRITES_IN_SPRITEBATCH)
	{
		mySprites.push_back(aSprite.GetRenderCommand());
	}
}

void CSpriteBatch::Clear()
{
	mySprites.clear();
}

std::vector<SSpriteRenderCommand>& CSpriteBatch::GetBuffer()
{
	return mySprites;
}

void CSpriteBatch::SetScene(CScene * aScene)
{
	ourScene = aScene;
}
