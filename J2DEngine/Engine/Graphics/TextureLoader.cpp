#include "TextureLoader.h"
#include "DDSTextureLoader/DDSTextureLoader.h"
#include "../Engine/DirectXFramework.h"
#include "Texture.h"

CTextureLoader::CTextureLoader()
{
}


CTextureLoader::~CTextureLoader()
{
}

CDirectXFramework* CTextureLoader::ourFramework = nullptr;

void CTextureLoader::SetFramework(CDirectXFramework * aFramework)
{
	ourFramework = aFramework;
}

bool CTextureLoader::LoadTexture(const std::string & aPath, CTexture* aTextureToLoadInto)
{
	std::wstring filename(aPath.begin(), aPath.end());

	ID3D11ShaderResourceView* newResource;

	HRESULT result;

	if (myTextures.find(aPath) != myTextures.end())
	{
		aTextureToLoadInto->myTexture = myTextures[aPath];
		aTextureToLoadInto->myDimensions = CalculateDimensions(myTextures[aPath]);

		return true;
	}

	result = DirectX::CreateDDSTextureFromFile(ourFramework->GetDevice(), filename.c_str(), nullptr, &newResource);
	if (FAILED(result))
	{
		LoadTexture("Sprites/Default.dds", aTextureToLoadInto);
		return false;
	}

	myTextures.insert(std::make_pair(aPath, newResource));

	aTextureToLoadInto->myTexture = newResource;

	aTextureToLoadInto->myDimensions = CalculateDimensions(newResource);

	return true;
}

CVector2i CTextureLoader::CalculateDimensions(ID3D11ShaderResourceView * aResourceView)
{
	int width, height;
	ID3D11Resource* resource;
	ID3D11Texture2D* texture;
	aResourceView->GetResource(&resource);
	resource->QueryInterface<ID3D11Texture2D>(&texture);
	D3D11_TEXTURE2D_DESC desc;
	texture->GetDesc(&desc);

	width = desc.Width;
	height = desc.Height;

	return{ width, height };
}

std::string CTextureLoader::ToString()
{
	return "Class Name: CTextureLoader. Loaded Textures: 0";
}
