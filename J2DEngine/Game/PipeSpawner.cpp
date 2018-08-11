#include "PipeSpawner.h"
#include "LayerSpeeds.h"


CPipeSpawner::CPipeSpawner()
{
}


CPipeSpawner::~CPipeSpawner()
{
}

void CPipeSpawner::Init()
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
	mySpawnTimer += aDT;

	if (mySpawnTimer >= mySpawnFrequency)
	{
		mySpawnTimer = 0.f;
		SpawnPipe();
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

void CPipeSpawner::SpawnPipe()
{
	float offset = 450.f;
	offset += (rand() % 200) * pow(-1, rand());

	myPipeBuffer[myAvailableIndex].SetPosition(1750, offset);

	myAvailableIndex++;
	if (myAvailableIndex == myPipeBuffer.size())
	{
		myAvailableIndex = 0;
	}
}
