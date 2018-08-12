#include "Time.h"


CTime::CTime()
{
}


CTime::~CTime()
{
}

CTime & CTime::GetInstance()
{
	static CTime instance;
	return instance;
}

void CTime::Init()
{
	myStartingTimePoint = std::chrono::high_resolution_clock::now();
}

void CTime::Update()
{
	myLastTimePoint = myCurrentTimePoint;

	myCurrentTimePoint = std::chrono::high_resolution_clock::now();

	myDeltaTime = myCurrentTimePoint - myLastTimePoint;
	myTotalTime = myCurrentTimePoint - myStartingTimePoint;
}

float CTime::GetDeltaTime()
{
	return myDeltaTime.count();
}

float CTime::GetTotalTime()
{
	return myTotalTime.count();
}
