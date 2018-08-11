#pragma once
#include "Base.h"
#include "Math/Vector2.h"
#include "Texture.h"
#include "Math/Rectangle.h"
#include "Math/Transform.h"
#include "ShaderWrappers.h"

class CScene;
class CShader;

class CSprite : public CBase, public CTransform
{

public:
	CSprite();
	~CSprite();

	void Load(const std::string& aFilePath);
	void Render();

	void SetColor(SColor aColor);
	SColor GetColor();

	CVector2f GetDimensions();

	void SetTextureRect(const CVector2f& aTopLeft, const CVector2f& aBottomRight);
	SUVRect GetTextureRect();

	CTexture GetTexture();

	void SetShader(const CShader& aShader);

	static void SetScene(CScene* aScene);

private:
	SUVRect myTextureRect;
	CVector2f myPivot;
	SColor myColor;
	CTexture myTexture;
	bool myHasBeenLoaded;
	const CShader* myShader;

	static CScene* ourScene;
};

