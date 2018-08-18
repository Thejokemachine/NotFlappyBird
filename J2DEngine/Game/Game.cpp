#include "Game.h"
#include "Graphics/Colors.h"
#include "Utilities/InputManager.h"
#include "Utilities/Time.h"
#include "Utilities/DebugLog.h"

#include "../Engine/OpaqueBuffer.h"

#include "LayerSpeeds.h"

#include "Network/NetMessageManager.h"
#include "Network/NetMessage.h"
#include "Network/NetMessageChat.h"

void CGame::Init()
{
	myGameState = EGameState::Menu;

	myBackgroundSprite.Load("Sprites/background.dds");
	myBackgroundSprite.SetPosition(800, 450);
	myBackgroundSprite2.Load("Sprites/background.dds");
	myBackgroundSprite2.SetPosition(1600 + 800, 450);

	myBackgroundSpeed = LAYER_BACKGROUND;

	myPlayer.Init();
	myPipeSpawner.Init(false);

	myClient.Start();
	myClient.BindGame(*this);

	myScore.Load("sprites/numbers.dds");
	myScore.Set(0);
	myScore.SetPosition(1400, 420);
	myScore.SetColor(SColor(1.f,0.f,0.7f,1.f));

	myEmitter.Load("sprites/numbers.dds");
	CParticleEmitter::SEmitterSettings settings = myEmitter.GetSettings();
	settings.myDelay = {0.001f, 0.001f};
	settings.myStartColor = Colors::White;
	settings.myEndColor = Colors::Red;
	settings.mySpreadAngle = 6.28f;
	settings.mySpeed = { 500.f, 500.f };
	settings.myRotation = { 0.f, 6.28f };
	settings.myLifetime = { 1.f, 1.f };
	settings.myRotationSpeed = { -10.57f, 10.57f };
	settings.myScale = { 0.5f, 2.f };
	settings.myStartScale = 0.5f;
	settings.myEndScale = 3.f;
	for (int i = 0; i < 10; ++i)
	{
		settings.myPossibleTexRects.push_back({{i / 10.f, 0.f}, {((i + 1) / 10.f), 1.f}});
	}

	myEmitter.SetSettings(settings);
	myEmitter.SetPosition(800.f, 450.f);
	myEmitter.SetRotation(-1.57f);
	myEmitter.Start();
}

void CGame::Update(float aDT)
{
	CInputManager& inputManager = CInputManager::GetInstance();

	if (inputManager.IsKeyPressed(EKeyCode::Enter))
	{
		myGameState = EGameState::InGame;
	}

	switch (myGameState)
	{
	case CGame::EGameState::Menu:
		myEmitter.Update(aDT);
		myEmitter.Rotate(6.28f * aDT);
		break;
	case CGame::EGameState::InGame:
		HandleTilingBackgrounds(aDT);
		myPlayer.Update(aDT);
		myPipeSpawner.Update(aDT);
		if (myPipeSpawner.PassedThroughPipe(myPlayer.GetSprite().GetPosition()))
		{
			myScore.Increment(1);
		}

		if (myPipeSpawner.CollidedWithPipe(myPlayer.GetCollider()))
		{
			myScore.Set(0);
			myPlayer.Die();
		}

		for (auto& spritePairs : myOtherPlayers)
		{
			spritePairs.second.HandleAnimation(aDT);
		}
		break;
	case CGame::EGameState::Paused:
		break;
	case CGame::EGameState::GameOver:
		break;
	default:
		break;
	}

	myClient.Update();
}

void CGame::Render()
{
	myBackgroundSprite.Render();
	myBackgroundSprite2.Render();

	switch (myGameState)
	{
	case CGame::EGameState::Menu:
		myEmitter.Render();
		break;
	case CGame::EGameState::InGame:
		myPipeSpawner.Render();
		myScore.Render();

		for (auto& spritePairs : myOtherPlayers)
		{
			spritePairs.second.Render();
		}
		myPlayer.Render();

		break;
	case CGame::EGameState::Paused:
		myPlayer.Render();
		myPipeSpawner.Render();
		break;
	case CGame::EGameState::GameOver:
		myPipeSpawner.Render();
		break;
	default:
		break;
	}
}

void CGame::AddOtherPlayer(unsigned long aID)
{
	CPlayer newPlayer;
	newPlayer.Init();
	SColor color = newPlayer.GetSprite().GetColor();
	color.a = 0.25f;
	newPlayer.GetSprite().SetColor(color);

	myOtherPlayers.insert(std::make_pair(aID, newPlayer));
}

void CGame::UpdateOtherPlayer(unsigned long aID, const CVector2f & aPosition, float aRotation)
{
	CSprite& sprite = myOtherPlayers[aID].GetSprite();
	sprite.SetPosition(aPosition);
	sprite.SetRotation(aRotation);
}

void CGame::AddPipe(const CVector2f & aWhere)
{
	if (myGameState == EGameState::InGame)
	{
		myPipeSpawner.AddPipePair(aWhere);
	}
}

CPlayer & CGame::GetPlayer()
{
	return myPlayer;
}

void CGame::HandleTilingBackgrounds(float aDT)
{
	myBackgroundSprite.Move(myBackgroundSpeed * aDT, 0);
	myBackgroundSprite2.Move(myBackgroundSpeed * aDT, 0);

	if (myBackgroundSprite.GetPosition().x <= -myBackgroundSprite.GetDimensions().x / 2.f + 4.f)
	{
		myBackgroundSprite.SetPosition(1600 + 800, 450);
	}
	else if (myBackgroundSprite2.GetPosition().x <= -myBackgroundSprite2.GetDimensions().x / 2.f + 4.f) 
	{
		myBackgroundSprite2.SetPosition(1600 + 800, 450);
	}
}
