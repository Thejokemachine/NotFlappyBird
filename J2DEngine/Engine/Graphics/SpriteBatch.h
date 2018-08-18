#pragma once
#include "Base.h"
#include "Sprite.h"
#include "Texture.h"
#include <vector>
#include "RenderCommands.h"

class CScene;

class CSpriteBatch : public CBase
{
public:
	virtual void Load(const std::string& aFilePath);
	void Render();

	void AddSprite(const CSprite& aSprite);
	void Clear();

	std::vector<SSpriteRenderCommand>& GetBuffer();

	static void SetScene(CScene* aScene);

protected:
	CTexture myTexture;
	bool myHasBeenLoaded;
	static CScene* ourScene;

	std::vector<SSpriteRenderCommand> mySprites;
};