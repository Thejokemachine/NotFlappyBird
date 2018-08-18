#pragma once
#include "Base.h"
#include <functional>

class CTimedEvent : public CBase
{
public:

	enum class EType
	{
		DoOnce,
		Repeat
	};

	void Init(EType aType, float aDuration, std::function<void()> aFunction);
	void Update(float aDT);

	void Start();
	void Stop();
	void Restart();

	void SetType(EType aType);
	void SetDuration(float aDuration);

private:
	std::function<void()> myCallback;
	float myTimer;
	float myDuration;
	EType myType;
	bool myHasFinished;
	bool myHasStarted;
};