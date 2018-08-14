#include "Player.h"
#include "Utilities/InputManager.h"
#include "Math/CommonMath.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	mySprite.Load("sprites/player.dds");
	mySprite.SetPosition(300.f, 450.f);
	mySprite.SetScale({ 0.5f, 1 });
	myCollider.SetPosition(mySprite.GetPosition());
	myCollider.SetRadius(40.f);
	myInvincibleTimer = 0.f;
}

void CPlayer::Update(float aDT)
{
	HandleAnimation(aDT);

	myInvincibleTimer += aDT;

	CInputManager& input = CInputManager::GetInstance();

	if (input.IsKeyPressed(EKeyCode::Space) && mySprite.GetPosition().y > 0)
	{
		myFallSpeed = -1500.f;
		myRotation = -1.f;
	}

	myFallSpeed += 4000.f * aDT;
	myFallSpeed = Math::Min(myFallSpeed, 4000.f);
	myRotation = Math::Lerp(myRotation, 1.57f, aDT / 1.f);

	mySprite.Move(0.f, myFallSpeed * aDT);
	mySprite.SetRotation(myRotation);

	if (mySprite.GetPosition().y > 1000.f)
	{
		mySprite.SetPosition(mySprite.GetPosition().x, 1000.f);
	}

	myCollider.SetPosition(mySprite.GetPosition());
}

void CPlayer::Render()
{
	mySprite.Render();
}

void CPlayer::Die()
{
	if (myInvincibleTimer > 1.f)
	{
		myInvincibleTimer = 0.f;
		mySprite.SetPosition(300.f, 450.f);
		myCollider.SetPosition(mySprite.GetPosition());
		myFallSpeed = 0.f;
		myRotation = 0.f;
		PRINT("You died! :(");
	}
}

CSprite & CPlayer::GetSprite()
{
	return mySprite;
}

CCircleCollider & CPlayer::GetCollider()
{
	return myCollider;
}

void CPlayer::HandleAnimation(float aDT)
{
	myAnimationSwitchTimer += aDT;
	if (myAnimationSwitchTimer >= 0.15f)
	{
		myAnimationSwitchTimer = 0.f;

		myAnimationToggle = !myAnimationToggle;
	}

	if (myAnimationToggle)
	{
		mySprite.SetTextureRect({ 0, 0 }, { 0.5f, 1.f });
	}
	else
	{
		mySprite.SetTextureRect({ 0.5f, 0 }, { 1.f, 1.f });
	}
}
