#include "PointCollider.h"

bool CPointCollider::IsColliding(const CCircleCollider & aCircleCollider) const
{
	return CircleVsPoint(aCircleCollider, *this);
}

bool CPointCollider::IsColliding(const CRectangleCollider & aRectangleCollider) const
{
	return PointVsRectangle(*this, aRectangleCollider);
}

bool CPointCollider::IsColliding(const CPointCollider & aPointCollider) const
{
	return PointVsPoint(*this, aPointCollider);
}
