#pragma once
#include "Base.h"
#include <random>

class CRandomizer : public CBase
{
public:

	template<typename T>
	T GetRandomBetween(T aMin, T aMax);

	static void Init();

private:
	static std::random_device ourRandomDevice;
	static std::default_random_engine ourRandomEngine;
};

template<typename T>
inline T CRandomizer::GetRandomBetween(T aMin, T aMax)
{
	if (aMin == aMax)
	{
		return aMin;
	}

	std::uniform_int_distribution<int> random(0, 100);
	T rv = aMin + (float)random(ourRandomEngine) * (aMax - aMin);

	return rv / 100.f;
}
