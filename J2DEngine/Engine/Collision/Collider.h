#pragma once
#include "Base.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"

class CCircleCollider;
class CRectangleCollider;
class CPointCollider;

class CCollider : public CTransform, public CBase
{
public:

	virtual bool IsColliding(const CCollider& aCollider) const = 0;

	virtual bool IsColliding(const CCircleCollider& aCircleCollider) const = 0;
	virtual bool IsColliding(const CRectangleCollider& aRectangleCollider) const = 0;
	virtual bool IsColliding(const CPointCollider& aPointCollider) const = 0;

protected:

	static bool CircleVsCircle(const CCircleCollider& aCollider1, const CCircleCollider& aCollider2);
	static bool CircleVsRectangle(const CCircleCollider& aCollider1, const CRectangleCollider& aCollider2);
	static bool CircleVsPoint(const CCircleCollider& aCollider1, const CPointCollider& aCollider2);

	static bool PointVsPoint(const CPointCollider& aCollider1, const CPointCollider& aCollider2);
	static bool PointVsRectangle(const CPointCollider& aCollider1, const CRectangleCollider& aCollider2);

	static bool RectangleVsRectangle(const CRectangleCollider& aCollider1, const CRectangleCollider& aCollider2);
};