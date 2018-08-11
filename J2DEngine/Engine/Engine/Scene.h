#pragma once
#include "Base.h"
#include <vector>
#include "../Graphics/RenderCommands.h"

class CSprite;

class CScene : CBase
{
public:
	CScene();
	~CScene();

	bool Init();
	void SetSpriteBufferSize(unsigned int aSize);
	bool AddSprite(CSprite* aSprite);
	std::vector<SSpriteRenderCommand>& GetSpriteBuffer();
	void Clear();

	//void Cull();

private:
	std::vector<SSpriteRenderCommand> mySpriteBuffer;
	unsigned int myAvailableIndex;
};

