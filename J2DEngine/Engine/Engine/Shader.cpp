#include "Shader.h"

CShaderCompiler CShader::ourShaderCompiler;

CShader::CShader()
{
	myVertexShader = nullptr;
	myGeometryShader = nullptr;
	myPixelShader = nullptr;
}


CShader::~CShader()
{
}

void CShader::Load(EShaderType aShaderType, const std::string & aFileName)
{
	std::string entryPoint;

	switch (aShaderType)
	{
	case EShaderType::VertexShader:
		entryPoint = "vertexShader";
		break;
	case EShaderType::GeometryShader:
		entryPoint = "geometryShader";
		break;
	case EShaderType::PixelShader:
		entryPoint = "pixelShader";
		break;
	}

	ourShaderCompiler.CompileShader(aFileName, "Shaders/shaderStructs.vfxi", entryPoint, aShaderType, *this);
}

ID3D11VertexShader * CShader::GetVertexShader()
{
	return myVertexShader;
}

ID3D11GeometryShader * CShader::GetGeometryShader()
{
	return myGeometryShader;
}

ID3D11PixelShader * CShader::GetPixelShader()
{
	return myPixelShader;
}