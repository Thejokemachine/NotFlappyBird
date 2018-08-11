#include "Texture.h"

CTextureLoader CTexture::ourTextureLoader;

CTexture::CTexture()
{
}


CTexture::~CTexture()
{
}

bool CTexture::Load(const std::string & aPath)
{
	if (ourTextureLoader.LoadTexture(aPath, this))
	{
		return true;
	}
	else
	{
		return false;
	}
}

CVector2i CTexture::GetDimensions() const
{
	return myDimensions;
}