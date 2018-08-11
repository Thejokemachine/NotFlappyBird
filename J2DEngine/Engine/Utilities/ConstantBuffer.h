#pragma once
#include "Base.h"
#include "../Engine/DirectXFramework.h"
#include <d3d11.h>
#include "DebugLog.h"
#include "../Engine/ShaderTypes.h"

struct ID3D11Buffer;

class CConstantBuffer : public CBase
{
public:
	CConstantBuffer();
	~CConstantBuffer();

	template<typename T>
	void Create();

	template<typename T>
	void Remap(unsigned aSlot, T& aData, EShaderType aShaderType);

	template<typename T>
	void Remap(unsigned aSlot, T& aData);

	static void SetFramework(CDirectXFramework* aFramework);

private:
	ID3D11Buffer* myBuffer;

	static CDirectXFramework* ourFramework;
};

template<typename T>
inline void CConstantBuffer::Create()
{
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.ByteWidth = sizeof(T);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	ourFramework->GetDevice()->CreateBuffer(&desc, nullptr, &myBuffer);

	if (desc.ByteWidth % 16 != 0)
	{
		DL_WRITELOG("engine", "Constant Buffer Data must be divisible by 16");
	}
}

template<typename T>
inline void CConstantBuffer::Remap(unsigned aSlot, T & aData, EShaderType aShaderType)
{
	D3D11_MAPPED_SUBRESOURCE resource = {};
	resource.pData = &aData;
	ourFramework->GetContext()->Map(myBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, &aData, sizeof(T));
	ourFramework->GetContext()->Unmap(myBuffer, 0);

	if (aShaderType == EShaderType::VertexShader)
	{
		ourFramework->GetContext()->VSSetConstantBuffers(aSlot, 1, &myBuffer);
	}
	if (aShaderType == EShaderType::GeometryShader)
	{
		ourFramework->GetContext()->GSSetConstantBuffers(aSlot, 1, &myBuffer);
	}
	if (aShaderType == EShaderType::PixelShader)
	{
		ourFramework->GetContext()->PSSetConstantBuffers(aSlot, 1, &myBuffer);
	}
}

template<typename T>
inline void CConstantBuffer::Remap(unsigned aSlot, T & aData)
{
	D3D11_MAPPED_SUBRESOURCE resource = {};
	resource.pData = &aData;
	ourFramework->GetContext()->Map(myBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, &aData, sizeof(T));
	ourFramework->GetContext()->Unmap(myBuffer, 0);

	ourFramework->GetContext()->VSSetConstantBuffers(aSlot, 1, &myBuffer);
	ourFramework->GetContext()->GSSetConstantBuffers(aSlot, 1, &myBuffer);
	ourFramework->GetContext()->PSSetConstantBuffers(aSlot, 1, &myBuffer);
}
