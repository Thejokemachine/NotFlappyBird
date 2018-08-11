#pragma once
#include "Vector2.h"

class CTransform
{
public:
	CTransform();
	~CTransform();

	void Move(float aXMovement, float aYMovement);
	void Move(const CVector2f& aMovement);
	void SetPosition(float aX, float aY);
	void SetPosition(const CVector2f& aPosition);
	CVector2f GetPosition();

	void Rotate(float aRotation);
	void SetRotation(float aRotation);
	float GetRotation();

	void Scale(float aScalar);
	void SetScale(float aScale);
	void SetScale(const CVector2f& aScale);
	CVector2f GetScale();

private:

	CVector2f myPosition;
	CVector2f myScale;
	float myRotation;
};

