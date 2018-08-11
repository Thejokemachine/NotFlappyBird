#include "GraphicsEngine.h"
#include "../Utilities/Camera.h"

CGraphicsEngine::CGraphicsEngine()
{
}


CGraphicsEngine::~CGraphicsEngine()
{
}

bool CGraphicsEngine::Init(const CWindowHandler::SWindowData & aWindowData)
{
	if (myWindowHandler.Init(aWindowData) == false)
	{
		return false;
	}

	if (myFramework.Init(myWindowHandler) == false)
	{
		return false;
	}

	if (mySpriteRenderer.Init(&myFramework) == false)
	{
		return false;
	}

	if (myScene.Init() == false)
	{
		return false;
	}

	CConstantBuffer::SetFramework(&myFramework);
	CCamera::GetInstance().Init(&myFramework);

	return true;
}

bool CGraphicsEngine::BeginFrame()
{
	SColor color = myWindowHandler.GetWindowData().clearColor;
	float clearColor[4] = { color.r, color.g, color.b, color.a };
	myScene.Clear();
	return myFramework.BeginFrame(clearColor);
}

bool CGraphicsEngine::RenderFrame()
{
	CCamera::GetInstance().Update();

	//myScene.Cull();

	mySpriteRenderer.Render(myScene.GetSpriteBuffer());

	return true;
}

bool CGraphicsEngine::EndFrame()
{
	return myFramework.EndFrame();
}

HWND CGraphicsEngine::GetClientWindow()
{
	return myWindowHandler.GetWindowHandle();
}

void CGraphicsEngine::GetDesktopResolution(UINT & aWidthToSet, UINT & aHeightToSet)
{
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	aWidthToSet = desktop.right;
	aHeightToSet = desktop.bottom;
}
