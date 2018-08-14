#pragma once
#include "Graphics/Sprite.h"
#include "Player.h"
#include "PipeSpawner.h"
#include "Network/Client.h"
#include "SpriteNumber.h"

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

	void AddPipe(const CVector2f& aWhere);

	CPlayer& GetPlayer();

private:

	void HandleTilingBackgrounds(float aDT);

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
	CSpriteNumber myScore;

	std::unordered_map<unsigned long, CPlayer> myOtherPlayers;

	Network::CClient myClient;
};

