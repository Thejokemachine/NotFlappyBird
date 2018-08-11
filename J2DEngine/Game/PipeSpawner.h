#pragma once
#include "../Engine/Graphics/Sprite.h"

class CPipeSpawner
{
public:
	CPipeSpawner();
	~CPipeSpawner();

	void Init();
	void Update(float aDT);
	void Render();

private:
	std::vector<CSprite> myPipeBuffer;
	int myAvailableIndex;

	float mySpawnTimer;
	float mySpawnFrequency;

	void SpawnPipe();
};

