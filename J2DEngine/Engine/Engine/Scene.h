#pragma once
#include "Base.h"
#include <vector>
#include "../Graphics/RenderCommands.h"

class CSprite;
class CSpriteBatch;

class CScene : CBase
{
public:
	CScene();
	~CScene();

	bool Init();
	void Clear();

	void SetSpriteBufferSize(unsigned int aSize);
	bool AddSprite(CSprite* aSprite);
	std::vector<SSpriteRenderCommand>& GetSpriteBuffer();

	void SetSpriteBatchBufferSize(unsigned int aSize);
	bool AddSpriteBatch(CSpriteBatch* aSpriteBatch);
	std::vector<SSpriteBatchRenderCommand>& GetSpriteBatchBuffer();

	//void Cull();

private:
	std::vector<SSpriteRenderCommand> mySpriteBuffer;
	unsigned int myAvailableSpriteIndex;

	std::vector<SSpriteBatchRenderCommand> mySpriteBatchBuffer;
	unsigned int myAvailableSpriteBatchIndex;
};

