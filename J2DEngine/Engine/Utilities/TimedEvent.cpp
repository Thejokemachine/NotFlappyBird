#include "TimedEvent.h"

void CTimedEvent::Init(EType aType, float aDuration, std::function<void()> aFunction)
{
	myDuration = aDuration;
	myType = aType;
	myCallback = aFunction;
	myHasStarted = false;
	Restart();
}

void CTimedEvent::Update(float aDT)
{
	if (myHasStarted)
	{
		if (myHasFinished == false)
		{
			myTimer += aDT;

			if (myTimer >= myDuration)
			{
				myCallback();

				if (myType == EType::Repeat)
				{
					Restart();
				}
			}
		}
	}
}

void CTimedEvent::Start()
{
	myHasStarted = true;
}

void CTimedEvent::Stop()
{
	myHasStarted = false;
}

void CTimedEvent::Restart()
{
	myHasFinished = false;
	myTimer = 0.f;
}

void CTimedEvent::SetType(EType aType)
{
	myType = aType;
}

void CTimedEvent::SetDuration(float aDuration)
{
	myDuration = aDuration;
}
