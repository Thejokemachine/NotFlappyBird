#pragma once
#include "Base.h"
#include "TextureLoader.h"
#include "Math/Vector2.h"

struct ID3D11ShaderResourceView;

class CTexture : CBase
{
	friend class CTextureLoader;
	friend class CSpriteRenderer;
	friend class CSpriteBatchRenderer;

public:
	CTexture();
	~CTexture();

	bool Load(const std::string& aPath);

	CVector2i GetDimensions() const;

private:
	
	CVector2i myDimensions;
	ID3D11ShaderResourceView* myTexture;

	static CTextureLoader ourTextureLoader;
};

