#include "PipeSpawner.h"
#include "LayerSpeeds.h"


CPipeSpawner::CPipeSpawner()
{
}


CPipeSpawner::~CPipeSpawner()
{
}

void CPipeSpawner::Init(bool aShouldSpawn)
{
	for (int i = 0; i < 5; ++i)
	{
		CSprite pipe;
		pipe.Load("sprites/pipe.dds");
		pipe.SetPosition(-1000, 0);
		myPipeBuffer.push_back(pipe);
	}
	myAvailableIndex = 0;

	mySpawnFrequency = 1.5f;
	mySpawnTimer = 0.f;
}

void CPipeSpawner::Update(float aDT)
{
	if (myShouldSpawn)
	{
		mySpawnTimer += aDT;

		if (mySpawnTimer >= mySpawnFrequency)
		{
			mySpawnTimer = 0.f;
			SpawnPipe();
		}
	}

	for (CSprite& sprite : myPipeBuffer)
	{
		sprite.Move(LAYER_PIPES * aDT, 0.f);
	}
}

void CPipeSpawner::Render()
{
	for (CSprite& sprite : myPipeBuffer)
	{
		sprite.Render();
	}
}

void CPipeSpawner::AddPipePair(const CVector2f & aPosition)
{
	myPipeBuffer[myAvailableIndex].SetPosition(aPosition.x, aPosition.y);

	myAvailableIndex++;
	if (myAvailableIndex == myPipeBuffer.size())
	{
		myAvailableIndex = 0;
	}
}

void CPipeSpawner::SpawnPipe()
{
	float offset = 450.f;
	offset += (rand() % 200) * pow(-1, rand());

	AddPipePair({ 1750.f, offset });
}
