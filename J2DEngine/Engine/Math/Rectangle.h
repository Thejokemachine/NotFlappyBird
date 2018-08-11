#pragma once
#include "Base.h"
#include "Vector2.h"

template<typename T>
class CRectangle : CBase
{
public:
	
	CRectangle() = default;
	CRectangle(const CVector2<T>& aPosition, const CVector2<T>& aDimensions = CVector2<float>::Zero(), const CVector2<T>& aPivot = CVector2<float>::Zero());

	std::string ToString() override;
	
private:

	CVector2<T> myPosition;
	CVector2<T> myDimensions;
	CVector2<T> myPivot;
};

typedef CRectangle<float> CRectanglef;
typedef CRectangle<int> CRectanglei;

template<typename T>
inline CRectangle<T>::CRectangle(const CVector2<T>& aPosition, const CVector2<T>& aDimensions, const CVector2<T>& aPivot)
{
	myPosition = aPosition;
	myDimensions = aDimensions;
	myPivot = aPivot;
}

template<typename T>
inline std::string CRectangle<T>::ToString()
{
	return "Position: " + myPosition.ToString() + "\nDimensions: " + myDimensions.ToString() + "\nPivot: " + myPivot.ToString();
}
