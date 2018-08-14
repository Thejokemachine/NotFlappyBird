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
		SPipe pipe;
		pipe.mySprite.Load("sprites/pipe.dds");
		pipe.mySprite.SetPosition(-1000, 0);
		pipe.myTopCollider.SetDimensions({ 175, 500 });
		pipe.myBottomCollider.SetDimensions({ 175, 500 });
		pipe.myTopCollider.SetPosition(-1000, 0);
		pipe.myBottomCollider.SetPosition(-1000, 0);
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

	for (SPipe& pipe: myPipeBuffer)
	{
		pipe.myPrevPos = pipe.mySprite.GetPosition();
		pipe.mySprite.Move(LAYER_PIPES * aDT, 0.f);
		pipe.myTopCollider.Move(LAYER_PIPES * aDT, 0.f);
		pipe.myBottomCollider.Move(LAYER_PIPES * aDT, 0.f);
	}
}

void CPipeSpawner::Render()
{
	for (SPipe& pipe : myPipeBuffer)
	{
		pipe.mySprite.Render();
	}
}

void CPipeSpawner::AddPipePair(const CVector2f & aPosition)
{
	SPipe& pipe = myPipeBuffer[myAvailableIndex];
	pipe.mySprite.SetPosition(aPosition.x, aPosition.y);
	pipe.myTopCollider.SetPosition(aPosition.x, aPosition.y - 250 - 220); // Gap size is 440
	pipe.myBottomCollider.SetPosition(aPosition.x, aPosition.y + 250 + 220);

	myAvailableIndex++;
	if (myAvailableIndex == myPipeBuffer.size())
	{
		myAvailableIndex = 0;
	}
}

bool CPipeSpawner::PassedThroughPipe(const CVector2f & aPosition)
{
	for (SPipe& pipe : myPipeBuffer)
	{
		if (pipe.myPrevPos.x > aPosition.x && pipe.mySprite.GetPosition().x <= aPosition.x)
			return true;
	}
	return false;
}

bool CPipeSpawner::CollidedWithPipe(const CCircleCollider & aCollider)
{
	for (const SPipe& pipe : myPipeBuffer)
	{
		if (pipe.myTopCollider.IsColliding(aCollider) || pipe.myBottomCollider.IsColliding(aCollider))
		{
			return true;
		}
	}
	return false;
}

void CPipeSpawner::SpawnPipe()
{
	float offset = 450.f;
	offset += (rand() % 200) * pow(-1, rand());

	AddPipePair({ 1750.f, offset });
}
