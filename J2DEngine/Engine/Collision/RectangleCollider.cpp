#include "RectangleCollider.h"

void CRectangleCollider::SetDimensions(const CVector2f & aDimensions)
{
	myDimensions = aDimensions;
}

bool CRectangleCollider::IsColliding(const CCircleCollider & aCircleCollider) const
{
	return CircleVsRectangle(aCircleCollider, *this);
}

bool CRectangleCollider::IsColliding(const CRectangleCollider & aRectangleCollider) const
{
	return RectangleVsRectangle(*this, aRectangleCollider);
}

bool CRectangleCollider::IsColliding(const CPointCollider & aPointCollider) const
{
	return PointVsRectangle(aPointCollider, *this);
}
