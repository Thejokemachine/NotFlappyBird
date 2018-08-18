#pragma once
#include "Base.h"
#include "Math/Vector2.h"
#include "Math/Rectangle.h"
#include <vector>
#include "ShaderWrappers.h"
#include "../Engine/Shader.h"

struct ID3D11PixelShader;
struct ID3D11GeometryShader;
struct ID3D11VertexShader;
struct ID3D11Buffer;
struct ID3D11InputLayout;

struct ID3D11BlendState;

class CDirectXFramework;
class CSprite;

class CRenderer : CBase
{
public:

	virtual bool Init(CDirectXFramework* aFramework) = 0;

protected:

	//CShader myDefaultShader;
	ID3D11PixelShader * myPixelShader;
	ID3D11GeometryShader* myGeometryShader;
	ID3D11VertexShader* myVertexShader;
	ID3D11Buffer* myBuffer;
	ID3D11InputLayout* myLayout;
	ID3D11BlendState* myBlendState;

	CDirectXFramework* myFramework;
};

