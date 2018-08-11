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
}

void CPlayer::Update(float aDT)
{
	HandleAnimation(aDT);

	CInputManager& input = CInputManager::GetInstance();

	if (input.IsKeyPressed(EKeyCode::Space))
	{
		myFallSpeed = -1500.f;
		myRotation = -1.f;
	}

	myFallSpeed += 4000.f * aDT;
	myRotation = Math::Lerp(myRotation, 1.57f, aDT / 1.f);

	mySprite.Move(0.f, myFallSpeed * aDT);
	mySprite.SetRotation(myRotation);
}

void CPlayer::Render()
{
	mySprite.Render();
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
