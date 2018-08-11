#pragma once
#include "Graphics/Sprite.h"
#include "Player.h"
#include "PipeSpawner.h"
#include "Network/Client.h"

class CGame
{
public:
	CGame() = default;
	~CGame() = default;

	void Init();
	void Update(float aDT);
	void Render();

	void AddOtherPlayer(unsigned long aID);
	void UpdateOtherPlayer(unsigned long aID, const CVector2f& aPosition, float aRotation);

	CPlayer& GetPlayer();

private:

	enum class EGameState
	{
		Menu,
		InGame,
		Paused,
		GameOver
	} myGameState;

	CSprite myBackgroundSprite;
	CSprite myBackgroundSprite2;
	float myBackgroundSpeed;

	CPlayer myPlayer;
	CPipeSpawner myPipeSpawner;

	std::unordered_map<unsigned long, CPlayer> myOtherPlayers;

	Network::CClient myClient;

	void HandleTilingBackgrounds(float aDT);
};

