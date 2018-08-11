#pragma once
#include "Base.h"
#include <chrono>
#include "../Utilities/ConstantBuffer.h"

class CTime : public CBase
{
public:
	~CTime();
	
	static CTime& GetInstance();

	void Init();
	void Update();

	float GetDeltaTime();
	float GetTotalTime();

private:
	struct STimeData
	{
		float deltaTime;
		float totalTime;
		float trash[2];
	};

	CTime();

	std::chrono::time_point<std::chrono::high_resolution_clock> myLastTimePoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> myCurrentTimePoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> myStartingTimePoint;

	std::chrono::duration<float> myDeltaTime;
	std::chrono::duration<float> myTotalTime;

	CConstantBuffer myBuffer;
};

