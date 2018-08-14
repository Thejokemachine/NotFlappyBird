#pragma once
#include "../Engine/Graphics/Sprite.h"
#include "Collision/CircleCollider.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	void Init();
	void Update(float aDT);
	void Render();

	void Die();

	CSprite& GetSprite();
	CCircleCollider& GetCollider();

	void HandleAnimation(float aDT);

private:
	CSprite mySprite;
	float myFallSpeed;
	float myRotation;

	float myAnimationSwitchTimer;
	bool myAnimationToggle;

	CCircleCollider myCollider;
	float myInvincibleTimer;
};

