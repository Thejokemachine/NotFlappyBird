#pragma once
#include "../Engine/Graphics/Sprite.h"

class CPipeSpawner
{
public:
	CPipeSpawner();
	~CPipeSpawner();

	void Init(bool aShouldSpawn);
	void Update(float aDT);
	void Render();
	void AddPipePair(const CVector2f& aPosition);

private:
	std::vector<CSprite> myPipeBuffer;
	int myAvailableIndex;

	float mySpawnTimer;
	float mySpawnFrequency;
	bool myShouldSpawn;

	void SpawnPipe();
};

