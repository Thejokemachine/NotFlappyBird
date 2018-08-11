#include "Scene.h"
#include "Graphics/Sprite.h"
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
	SSpriteRenderCommand rc;

	rc.color = aSprite->GetColor();
	rc.dimensions = aSprite->GetDimensions();
	rc.position = aSprite->GetPosition();
	rc.rotation = aSprite->GetRotation();
	rc.scale = aSprite->GetScale();
	rc.texture = aSprite->GetTexture();
	rc.textureRect = aSprite->GetTextureRect();

	mySpriteBuffer.push_back(rc);

	return true;
}

std::vector<SSpriteRenderCommand>& CScene::GetSpriteBuffer()
{
	return mySpriteBuffer;
}

void CScene::Clear()
{
	mySpriteBuffer.clear();
}
