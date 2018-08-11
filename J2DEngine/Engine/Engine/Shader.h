#pragma once
#include "Base.h"
#include "ShaderCompiler.h"

struct ID3D11VertexShader;
struct ID3D11GeometryShader;
struct ID3D11PixelShader;

class CShader : public CBase
{

	friend class CShaderCompiler;

public:
	CShader();
	~CShader();

	void Load(EShaderType aShaderType, const std::string& aFileName);

	ID3D11VertexShader* GetVertexShader();
	ID3D11GeometryShader* GetGeometryShader();
	ID3D11PixelShader* GetPixelShader();

private:
	ID3D11VertexShader* myVertexShader;
	ID3D11GeometryShader* myGeometryShader;
	ID3D11PixelShader* myPixelShader;

	static CShaderCompiler ourShaderCompiler;
};

