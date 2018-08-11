#include "WindowHandler.h"

CWindowHandler::CWindowHandler()
{
}


CWindowHandler::~CWindowHandler()
{
}

LRESULT CALLBACK CWindowHandler::WinProc(HWND aWindowHandle, UINT aWindowsMessage, WPARAM aWParam, LPARAM aLParam)
{
	if (aWindowsMessage == WM_DESTROY || aWindowsMessage == WM_CLOSE)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(aWindowHandle, aWindowsMessage, aWParam, aLParam);
}

bool CWindowHandler::Init(SWindowData aWindowData)
{
	myWindowData = aWindowData;

	WNDCLASS windowClass = {};
	windowClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = CWindowHandler::WinProc;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszClassName = "WindowHandlerClass";
	RegisterClass(&windowClass);

	myWindowHandle = CreateWindow(
		"WindowHandlerClass", "J2D",
		WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE,
		aWindowData.x, aWindowData.y, aWindowData.width, aWindowData.height,
		nullptr, nullptr, nullptr, nullptr);

	return true;
}

HWND CWindowHandler::GetWindowHandle() const
{
	return myWindowHandle;
}

const CWindowHandler::SWindowData& CWindowHandler::GetWindowData() const
{
	return myWindowData;
}
