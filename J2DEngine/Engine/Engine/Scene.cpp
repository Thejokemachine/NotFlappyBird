#include "Scene.h"
#include "Graphics/Sprite.h"
#include "Graphics/SpriteBatch.h"
#include "Math/CommonMath.h"

CScene::CScene()
{
}


CScene::~CScene()
{
}

bool CScene::Init()
{
	CSprite::SetScene(this);
	CSpriteBatch::SetScene(this);

	// Make Limits.h or something with limits
	//SetSpriteBufferSize(5000);

	return true;
}

void CScene::SetSpriteBufferSize(unsigned int aSize)
{
	mySpriteBuffer.clear();
	mySpriteBuffer.resize(aSize);
}

bool CScene::AddSprite(CSprite * aSprite)
{
	mySpriteBuffer.push_back(aSprite->GetRenderCommand());

	return true;
}

std::vector<SSpriteRenderCommand>& CScene::GetSpriteBuffer()
{
	return mySpriteBuffer;
}

void CScene::SetSpriteBatchBufferSize(unsigned int aSize)
{
	mySpriteBatchBuffer.clear();
	mySpriteBatchBuffer.resize(aSize);
}

bool CScene::AddSpriteBatch(CSpriteBatch * aSpriteBatch)
{
	SSpriteBatchRenderCommand rc;

	rc.sprites = &aSpriteBatch->GetBuffer()[0];
	rc.amount = aSpriteBatch->GetBuffer().size();

	mySpriteBatchBuffer.push_back(rc);

	return true;
}

std::vector<SSpriteBatchRenderCommand>& CScene::GetSpriteBatchBuffer()
{
	return mySpriteBatchBuffer;
}

void CScene::Clear()
{
	mySpriteBuffer.clear();
	mySpriteBatchBuffer.clear();
}
