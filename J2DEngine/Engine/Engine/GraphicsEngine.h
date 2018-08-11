#pragma once
#include "Base.h"
#include "WindowHandler.h"
#include "DirectXFramework.h"
#include "Scene.h"
#include "Graphics/SpriteRenderer.h"

class CGraphicsEngine : CBase
{
public:
	CGraphicsEngine();
	~CGraphicsEngine();

	bool Init(const CWindowHandler::SWindowData& aWindowData);
	bool BeginFrame();
	bool RenderFrame();
	bool EndFrame();

	HWND GetClientWindow();

	static void GetDesktopResolution(UINT& aWidthToSet, UINT& aHeightToSet);

private:

	CWindowHandler myWindowHandler;
	CDirectXFramework myFramework;

	CScene myScene;
	CSpriteRenderer mySpriteRenderer;
};

