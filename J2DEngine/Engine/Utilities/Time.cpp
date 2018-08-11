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
	myBuffer.Create<STimeData>();
}

void CTime::Update()
{
	myLastTimePoint = myCurrentTimePoint;

	myCurrentTimePoint = std::chrono::high_resolution_clock::now();

	myDeltaTime = myCurrentTimePoint - myLastTimePoint;
	myTotalTime = myCurrentTimePoint - myStartingTimePoint;

	STimeData data;
	data.deltaTime = GetDeltaTime();
	data.totalTime = GetTotalTime();

	myBuffer.Remap(TIME_SLOT, data);
}

float CTime::GetDeltaTime()
{
	return myDeltaTime.count();
}

float CTime::GetTotalTime()
{
	return myTotalTime.count();
}
