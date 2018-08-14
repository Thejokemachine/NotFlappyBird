#pragma once
#include "Collider.h"

class CPointCollider : public CCollider
{
	friend class CCollider;

public:
	virtual bool IsColliding(const CCollider& aCollider) const override { return aCollider.IsColliding(*this); }

	virtual bool IsColliding(const CCircleCollider& aCircleCollider) const override;
	virtual bool IsColliding(const CRectangleCollider& aRectangleCollider) const override;
	virtual bool IsColliding(const CPointCollider& aPointCollider) const override;

private:
};