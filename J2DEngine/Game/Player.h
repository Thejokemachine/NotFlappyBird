#pragma once
#include "../Engine/Graphics/Sprite.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	void Init();
	void Update(float aDT);
	void Render();

	CSprite& GetSprite();

private:
	CSprite mySprite;
	float myFallSpeed;
	float myRotation;

	float myAnimationSwitchTimer;
	bool myAnimationToggle;

	void HandleAnimation(float aDT);
};

