#include "Transform.h"



CTransform::CTransform()
{
	myScale = { 1.f, 1.f };
	myRotation = 0.0f;
}


CTransform::~CTransform()
{
}

void CTransform::Move(float aXMovement, float aYMovement)
{
	myPosition += { aXMovement, aYMovement };
}

void CTransform::Move(const CVector2f & aMovement)
{
	myPosition += aMovement;
}

void CTransform::SetPosition(float aX, float aY)
{
	myPosition = { aX, aY };
}

void CTransform::SetPosition(const CVector2f & aPosition)
{
	myPosition = aPosition;
}

CVector2f CTransform::GetPosition() const
{
	return myPosition;
}

void CTransform::Rotate(float aRotation)
{
	myRotation += aRotation;
}

void CTransform::SetRotation(float aRotation)
{
	myRotation = aRotation;
}

float CTransform::GetRotation()
{
	return myRotation;
}

void CTransform::Scale(float aScalar)
{
	myScale *= aScalar;
}

void CTransform::SetScale(float aScale)
{
	myScale = { aScale, aScale };
}

void CTransform::SetScale(const CVector2f & aScale)
{
	myScale = aScale;
}

CVector2f CTransform::GetScale()
{
	return myScale;
}

