#pragma once
#include "Base.h"
#include <unordered_map>
#include "../Math/Vector2.h"

class CDirectXFramework;
class CTexture;
struct ID3D11ShaderResourceView;

class CTextureLoader : CBase
{

	friend class CTexture;

public:
	~CTextureLoader();

	static void SetFramework(CDirectXFramework* aFramework);

	bool LoadTexture(const std::string& aPath, CTexture* aTextureToLoadInto);


	std::string ToString() override;

private:
	CTextureLoader();

	CVector2i CalculateDimensions(ID3D11ShaderResourceView* aResourceView);

	std::unordered_map<std::string, ID3D11ShaderResourceView*> myTextures;

	static CDirectXFramework* ourFramework;
};

