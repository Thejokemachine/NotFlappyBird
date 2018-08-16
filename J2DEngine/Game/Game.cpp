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
