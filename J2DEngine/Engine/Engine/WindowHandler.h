#pragma once
#include "Base.h"
#include <windows.h>

class CWindowHandler : CBase
{
public:
	CWindowHandler();
	~CWindowHandler();

	struct SWindowData
	{
		SColor clearColor;
		UINT x;
		UINT y;
		UINT width;
		UINT height;
		BOOL windowed;
	};

	static LRESULT CALLBACK WinProc(HWND aWindowHandle, UINT aWindowsMessage, WPARAM aWParam, LPARAM aLParam);

	bool Init(SWindowData aWindowData);
	HWND GetWindowHandle() const;
	const SWindowData& GetWindowData() const;

private:
	SWindowData myWindowData;
	HWND myWindowHandle;
};

