#pragma once
#include "Base.h"
#include "KeyCodes.h"
#include <map>
#include <windows.h>
#include "Math/Vector2.h"

class CInputManager : public CBase
{
public:
	~CInputManager();

	static CInputManager& GetInstance();

	void Init(HWND aClientWindow);
	void Update(const MSG& aWindowsMessage);
	void UpdateKeys(const MSG& aWindowsMessage);
	void UpdateMouse(const MSG& aWindowsMessage);
	void OncePerFrameUpdate();

	bool IsKeyPressed(EKeyCode aKey);
	bool IsKeyDown(EKeyCode aKey);

	CVector2f GetCursorPosition();
	int GetScrollWheelDelta();

private:
	CInputManager();

	std::map<EKeyCode, EKeyState> myKeyStates;
	std::map<EKeyCode, EKeyState> myPreviousKeyStates;

	CVector2f myCursorPosition;
	float myWheelDelta;

	HWND myHWND;
};

