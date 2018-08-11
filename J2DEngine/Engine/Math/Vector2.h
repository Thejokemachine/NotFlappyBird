#pragma once
#include "Base.h"

template<typename T>
class CVector2 : CBase
{

public:
	CVector2();
	CVector2(T aX, T aY);
	~CVector2() = default;

	static CVector2<T> Up() { return CVector2<T>(0, -1); }
	static CVector2<T> Right() { return CVector2<T>(1, 0); };
	static CVector2<T> Down() { return CVector2<T>(0, 1); };
	static CVector2<T> Left() { return CVector2<T>(-1, 0); };
	static CVector2<T> Zero() { return CVector2<T>(0, 0); };

	T Length();
	T Length2();
	void Normalize();
	CVector2<T> GetNormalized();

	bool operator==(const CVector2<T>& aCompareVector);
	bool operator!=(const CVector2<T>& aCompareVector);

	CVector2<T> operator+(const CVector2<T>& aAddVector);
	void operator+=(const CVector2<T>& aAddVector);

	CVector2<T> operator-(const CVector2<T>& aSubtractVector);
	void operator-=(const CVector2<T>& aSubtractVector);

	CVector2<T> operator*(float aScalar);
	void operator*=(float aScalar);

	CVector2<T> operator/(float aScalar);
	void operator/=(float aScalar);

	//CVector2<T> Dot(const CVector2<T>& aVector);
	//CVector2<T> Cross(const CVector2<T>& aVector);

	std::string ToString() override;

	T x;
	T y;
};

typedef CVector2<float> CVector2f;
typedef CVector2<int> CVector2i;

template<typename T>
inline CVector2<T>::CVector2()
{
	*this = Zero();
}

template<typename T>
inline CVector2<T>::CVector2(T aX, T aY)
{
	x = aX;
	y = aY;
}

template<typename T>
inline T CVector2<T>::Length()
{
	T rv;
	rv = sqrt(Length2());
	return rv;
}

template<typename T>
inline T CVector2<T>::Length2()
{
	T rv;
	rv = (x * x) + (y * y);
	return rv;
}

template<typename T>
inline void CVector2<T>::Normalize()
{
	*this = this->GetNormalized();
}

template<typename T>
inline CVector2<T> CVector2<T>::GetNormalized()
{
	CVector2<T> rv = *this;
	rv /= rv.Length();
	return rv;
}

template<typename T>
inline bool CVector2<T>::operator==(const CVector2<T>& aCompareVector)
{
	if (x == aCompareVector.x && y == aCompareVector.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
inline bool CVector2<T>::operator!=(const CVector2<T>& aCompareVector)
{
	if (this == aCompareVector)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<typename T>
inline CVector2<T> CVector2<T>::operator+(const CVector2<T>& aAddVector)
{
	CVector2<T> rv = *this;
	rv.x += aAddVector.x;
	rv.y += aAddVector.y;
	return rv;
}

template<typename T>
inline void CVector2<T>::operator+=(const CVector2<T>& aAddVector)
{
	*this = *this + aAddVector;
}

template<typename T>
inline CVector2<T> CVector2<T>::operator-(const CVector2<T>& aSubtractVector)
{
	CVector2<T> rv = *this;
	rv.x -= aSubtractVector.x;
	rv.y -= aSubtractVector.y;
	return rv;
}

template<typename T>
inline void CVector2<T>::operator-=(const CVector2<T>& aSubtractVector)
{
	*this = *this + aSubtractVector;
}

template<typename T>
inline CVector2<T> CVector2<T>::operator*(float aScalar)
{
	CVector2<T> rv = *this;
	rv.x *= aScalar;
	rv.y *= aScalar;
	return rv;
}

template<typename T>
inline void CVector2<T>::operator*=(float aScalar)
{
	*this = *this * aScalar;
}

template<typename T>
inline CVector2<T> CVector2<T>::operator/(float aScalar)
{
	CVector2<T> rv = *this;
	rv.x /= aScalar;
	rv.y /= aScalar;
	return rv;
}

template<typename T>
inline void CVector2<T>::operator/=(float aScalar)
{
	*this = *this / aScalar;
}

//template<typename T>
//inline CVector2<T> CVector2<T>::Dot(const CVector2<T>& aVector)
//{
//	return CVector2<T>();
//}
//
//template<typename T>
//inline CVector2<T> CVector2<T>::Cross(const CVector2<T>& aVector)
//{
//	return CVector2<T>();
//}

template<typename T>
inline std::string CVector2<T>::ToString()
{
	return "{ " + std::to_string(x) + " ; " + std::to_string(y) + " }";
}
