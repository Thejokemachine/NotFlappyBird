#include "ShaderCompiler.h"
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")


CShaderCompiler::CShaderCompiler()
{
}


CShaderCompiler::~CShaderCompiler()
{
}

void CShaderCompiler::CompileShader(const std::string & aFileName, const std::string & aIncludePath, const std::string & aEntryPoint, EShaderType aShaderType, CShader & aShaderToLoadInto)
{
	UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;

#ifdef _DEBUG
	compileFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* errorBlob = NULL;

	D3D_SHADER_MACRO macros[1] = {};
	ID3DInclude* include = ((ID3DInclude*)(UINT_PTR)1);


	//D3DCompileFromFile(aFileName.c_str(), macros, include, aEntryPoint.c_str(), 
}
