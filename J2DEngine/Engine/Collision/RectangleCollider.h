#pragma once
#include "Collider.h"

class CRectangleCollider : public CCollider
{
	friend class CCollider;

public:

	void SetDimensions(const CVector2f& aDimensions);
	virtual bool IsColliding(const CCollider& aCollider) const override { return aCollider.IsColliding(*this); }

	virtual bool IsColliding(const CCircleCollider& aCircleCollider) const;
	virtual bool IsColliding(const CRectangleCollider& aRectangleCollider) const;
	virtual bool IsColliding(const CPointCollider& aPointCollider) const;

private:

	CVector2f myDimensions;
};