#pragma once
#include "Base.h"
#include <chrono>

class CTime : public CBase
{
public:
	~CTime();
	
	static CTime& GetInstance();

	void Init();
	void Update();

	float GetDeltaTime();
	float GetTotalTime();

	struct STimeData
	{
		float deltaTime;
		float totalTime;
		float trash[2];
	};

private:

	CTime();

	std::chrono::time_point<std::chrono::high_resolution_clock> myLastTimePoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> myCurrentTimePoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> myStartingTimePoint;

	std::chrono::duration<float> myDeltaTime;
	std::chrono::duration<float> myTotalTime;
};

