#pragma once

#define MAX(a, b) ((a) < (b)) ? (b) : (a)
#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define CLAMP(a, minimum, maximum) a < minimum ? minimum : (a > maximum ? maximum : a)


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

	static SColor Lerp(SColor aLerpFrom, SColor aLerpTo, float aInterpolation)
	{
		SColor rv;
		rv.r = (aLerpFrom.r + aInterpolation * (aLerpTo.r - aLerpFrom.r));
		rv.g = (aLerpFrom.g + aInterpolation * (aLerpTo.g - aLerpFrom.g));
		rv.b = (aLerpFrom.b + aInterpolation * (aLerpTo.b - aLerpFrom.b));
		rv.a = (aLerpFrom.a + aInterpolation * (aLerpTo.a - aLerpFrom.a));
		return rv;
	}
}