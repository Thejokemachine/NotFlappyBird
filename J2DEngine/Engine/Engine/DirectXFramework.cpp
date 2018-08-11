#pragma comment(lib, "d3d11")

#include "DirectXFramework.h"
#include <d3d11.h>

#include "WindowHandler.h"
#include "../Graphics/TextureLoader.h"

CDirectXFramework::CDirectXFramework()
{
}


CDirectXFramework::~CDirectXFramework()
{
}

bool CDirectXFramework::Init(const CWindowHandler & aWindowHandler)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferCount = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = aWindowHandler.GetWindowHandle();
	desc.SampleDesc.Count = 1;
	desc.Windowed = aWindowHandler.GetWindowData().windowed;

	result = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
		&desc, &mySwapChain, &myDevice, nullptr, &myContext);
	if (FAILED(result)) { return false; };

	ID3D11Texture2D* backBufferTexture;
	result = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);
	if (FAILED(result)) { return false; };

	result = myDevice->CreateRenderTargetView(backBufferTexture, nullptr, &myBackBuffer);
	if (FAILED(result)) { return false; };

	result = backBufferTexture->Release();
	if (FAILED(result)) { return false; };

	D3D11_VIEWPORT viewport;

	viewport.TopLeftX = -1.f;
	viewport.TopLeftY = -1.f;
	viewport.Width = aWindowHandler.GetWindowData().width;
	viewport.Height = aWindowHandler.GetWindowData().height;
	viewport.MinDepth = 0.f;
	viewport.MaxDepth = 1.f;

	D3D11_RASTERIZER_DESC rasterizerDesc = {};

	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.f;
	rasterizerDesc.SlopeScaledDepthBias = 0.f;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.AntialiasedLineEnable = false;

	result = myDevice->CreateRasterizerState(&rasterizerDesc, &myRasterizerState);
	if (FAILED(result)) { return false; };

	myContext->OMSetRenderTargets(1, &myBackBuffer, NULL);
	myContext->RSSetViewports(1, &viewport);
	myContext->RSSetState(myRasterizerState);

	CTextureLoader::SetFramework(this);

	return true;
}

bool CDirectXFramework::BeginFrame(float aClearColor[4])
{
	myContext->ClearRenderTargetView(myBackBuffer, aClearColor);

	return true;
}

bool CDirectXFramework::EndFrame()
{
	HRESULT result;
	result = mySwapChain->Present(1, 0);
	if (FAILED(result)) { return false; }

	return true;
}

IDXGISwapChain * CDirectXFramework::GetSwapChain()
{
	return mySwapChain;
}

ID3D11Device * CDirectXFramework::GetDevice()
{
	return myDevice;
}

ID3D11DeviceContext * CDirectXFramework::GetContext()
{
	return myContext;
}
