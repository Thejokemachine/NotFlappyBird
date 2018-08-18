#pragma once
#include "SpriteBatch.h"
#include "Math/Transform.h"
#include "Utilities/TimedEvent.h"
#include "Utilities/Randomizer.h"

class CParticleEmitter : public CSpriteBatch, public CTransform
{
public:
	struct SFloatPair
	{
		float min;
		float max;
	};

	struct SEmitterSettings
	{
		float mySpreadAngle;
		SFloatPair myDelay;
		SFloatPair mySpeed;
		SFloatPair myLifetime;
		SFloatPair myRotation;
		SFloatPair myRotationSpeed;
		SFloatPair myScale;
		SColor myStartColor;
		SColor myEndColor;
		float myStartScale;
		float myEndScale;
		std::vector<SUVRect> myPossibleTexRects;
	};

	SEmitterSettings& GetSettings();
	void SetSettings(const SEmitterSettings& aSettings);

	void Load(const std::string& aFilePath) override;
	void Update(float aDT);

	void Start();
	void Stop();

private:

	struct SParticle
	{
		int index;
		float currentLifetime;

		float speed;
		CVector2f direction;
		SColor startColor;
		SColor endColor;
		float rotationSpeed;
		float lifetime;
		float targetScale;
	};

	 SEmitterSettings mySettings;

	void AddParticle();

	CRandomizer myRandomizer;
	CTimedEvent myTicker;
	std::vector<SParticle> myParticles;
	int myAvailableIndex;
};