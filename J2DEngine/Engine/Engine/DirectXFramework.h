#pragma once
#include "Base.h"

class CWindowHandler;

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11RasterizerState;

#define CAMERA_SLOT 0
#define TIME_SLOT 1

class CDirectXFramework : CBase
{
public:
	CDirectXFramework();
	~CDirectXFramework();

	bool Init(const CWindowHandler& aWindowHandler);

	bool BeginFrame(float aClearColor[4]);
	bool EndFrame();

	IDXGISwapChain* GetSwapChain();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

private:

	IDXGISwapChain* mySwapChain;
	ID3D11Device* myDevice;
	ID3D11DeviceContext* myContext;

	ID3D11RasterizerState* myRasterizerState;

	ID3D11RenderTargetView* myBackBuffer;
};

