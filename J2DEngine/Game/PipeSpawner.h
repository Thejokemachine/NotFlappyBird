#pragma once
#include "../Engine/Graphics/Sprite.h"
#include "Collision/RectangleCollider.h"
#include "Collision/CircleCollider.h"

class CPipeSpawner
{
public:
	CPipeSpawner();
	~CPipeSpawner();

	void Init(bool aShouldSpawn);
	void Update(float aDT);
	void Render();
	void AddPipePair(const CVector2f& aPosition);
	bool PassedThroughPipe(const CVector2f& aPosition);
	bool CollidedWithPipe(const CCircleCollider& aCollider);

private:
	struct SPipe
	{
		CSprite mySprite;
		CVector2f myPrevPos;
		CRectangleCollider myTopCollider;
		CRectangleCollider myBottomCollider;
	};
	std::vector<SPipe> myPipeBuffer;
	int myAvailableIndex;

	float mySpawnTimer;
	float mySpawnFrequency;
	bool myShouldSpawn;

	void SpawnPipe();
};

