#include "SpriteRenderer.h"
#include <d3d11.h>
#include "Engine/DirectXFramework.h"
#include <fstream>
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "RenderCommands.h"

CSpriteRenderer::CSpriteRenderer()
{
}


CSpriteRenderer::~CSpriteRenderer()
{
}

bool CSpriteRenderer::Init(CDirectXFramework * aFramework)
{
	myFramework = aFramework;

	D3D11_BUFFER_DESC desc = {0};
	desc.ByteWidth = sizeof(SSprite);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//D3D11_SUBRESOURCE_DATA subResData = { 0 };
	//subResData.pSysMem = new SSprite();
	
	HRESULT result;

	result = myFramework->GetDevice()->CreateBuffer(&desc, nullptr, &myBuffer);
	if (FAILED(result)) { return false; }

	std::ifstream vsFile;
	vsFile.open("vertexShader.cso", std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	result = myFramework->GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &myVertexShader);
	vsFile.close();
	if (FAILED(result)) { return false; }
	
	std::ifstream gsFile;
	gsFile.open("geometryShader.cso", std::ios::binary);
	std::string gsData = { std::istreambuf_iterator<char>(gsFile), std::istreambuf_iterator<char>() };
	result = myFramework->GetDevice()->CreateGeometryShader(gsData.data(), gsData.size(), nullptr, &myGeometryShader);
	gsFile.close();
	if (FAILED(result)) { return false; }
	
	std::ifstream psFile;
	psFile.open("pixelShader.cso", std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
	result = myFramework->GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &myPixelShader);
	psFile.close();
	if (FAILED(result)) { return false; }

	//myDefaultShader.Load(EShaderType::VertexShader, "Shader/defaultShader.vfx");
	//myDefaultShader.Load(EShaderType::GeometryShader, "Shader/defaultShader.vfx");
	//myDefaultShader.Load(EShaderType::PixelShader, "Shader/defaultShader.vfx");

	D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXRECT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "ROTATION", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "DIMENSIONS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "SCALE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TRASH", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	//GUID guid;
	//void* shaderData;
	//UINT shaderDataSize;
	//
	//myDefaultShader.GetVertexShader()->GetPrivateData(guid, &shaderDataSize, shaderData);

	result = myFramework->GetDevice()->CreateInputLayout(layoutDesc, 7, vsData.data(), vsData.size(), &myLayout);
	if (FAILED(result)) { return false; }

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	result = myFramework->GetDevice()->CreateBlendState(&blendDesc, &myBlendState);
	if (FAILED(result)) { return false; }

	return true;
}

void CSpriteRenderer::Render(std::vector<SSpriteRenderCommand>& aSpritesToRender)
{
	ID3D11DeviceContext* context = myFramework->GetContext();

	static UINT stride = sizeof(SSprite);
	static UINT offset = 0;
	static HRESULT result;

	context->OMSetBlendState(myBlendState, 0, -1);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	context->IASetInputLayout(myLayout);
	context->IASetVertexBuffers(0, 1, &myBuffer, &stride, &offset);

	context->VSSetShader(myVertexShader, nullptr, 0);
	context->GSSetShader(myGeometryShader, nullptr, 0);
	context->PSSetShader(myPixelShader, nullptr, 0);

	//context->VSSetShader(myDefaultShader.GetVertexShader(), nullptr, 0);
	//context->GSSetShader(myDefaultShader.GetGeometryShader(), nullptr, 0);
	//context->PSSetShader(myDefaultShader.GetPixelShader(), nullptr, 0);

	for (SSpriteRenderCommand& sprite : aSpritesToRender)
	{
		SSprite rc;
		rc.position = sprite.position;
		rc.color = sprite.color;
		rc.dimensions = { sprite.dimensions.x, sprite.dimensions.y };
		rc.rotation = sprite.rotation;
		rc.textureRect = { sprite.textureRect.topLeft , sprite.textureRect.bottomRight };
		rc.scale = { sprite.scale.x, sprite.scale.y };

		D3D11_MAPPED_SUBRESOURCE resource = { 0 };
		result = context->Map(myBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		if (FAILED(result)) { continue; }
		memcpy(resource.pData, &rc, sizeof(SSprite));
		context->Unmap(myBuffer, 0);

		context->PSSetShaderResources(0, 1, &sprite.texture.myTexture);

		context->Draw(1, 0);
	}
}
