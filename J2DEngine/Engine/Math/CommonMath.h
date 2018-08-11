#pragma once

#define MAX(a, b) ((a) < (b)) ? (b) : (a)
#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define CLAMP(a, minimum, maximum) (((a) < (minimum)) ? (((a) > (maximum)) ? (a) : (minimum)) : (a))


namespace Math
{

	template<typename T>
	T Max(T aValue0, T aValue1)
	{
		return MAX(aValue0, aValue1);
	}

	template<typename T>
	T Min(T aValue0, T aValue1)
	{
		return MIN(aValue0, aValue1);
	}

	template<typename T>
	T Clamp(T aValueToClamp, T aMin, T aMax)
	{
		return CLAMP(aValueToClamp, aMin, aMax);
	}

	static float Lerp(float aLerpFrom, float aLerpTo, float aInterpolation)
	{
		return (aLerpFrom + aInterpolation * (aLerpTo - aLerpFrom));
	}
}