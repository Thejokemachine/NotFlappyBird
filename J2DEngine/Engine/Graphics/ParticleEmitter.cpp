#include "ParticleEmitter.h"
#include "Engine/Limits.h"
#include "Colors.h"
#include "Math/CommonMath.h"

CParticleEmitter::SEmitterSettings & CParticleEmitter::GetSettings()
{
	return mySettings;
}

void CParticleEmitter::SetSettings(const SEmitterSettings & aSettings)
{
	mySettings = aSettings;
}

void CParticleEmitter::Load(const std::string & aFilePath)
{
	CSpriteBatch::Load(aFilePath);
	myTicker.Init(CTimedEvent::EType::Repeat, 0.f, [this]() { AddParticle(); });
	myAvailableIndex = 0;
}

void CParticleEmitter::Update(float aDT)
{
	myTicker.Update(aDT);

	for (SParticle& particle : myParticles)
	{
		SSpriteRenderCommand& rc = mySprites[particle.index];
		if (rc.shouldRender)
		{
			float interpolationValue = Math::Clamp(particle.currentLifetime / particle.lifetime, 0.f, 1.f);

			rc.position += particle.direction * particle.speed * aDT;
			rc.color = Math::Lerp(particle.startColor, particle.endColor, interpolationValue);
			rc.rotation += particle.rotationSpeed * aDT;
			rc.scale = Math::Lerp(rc.scale.x, particle.targetScale, interpolationValue);

			particle.currentLifetime += aDT;
			if (particle.currentLifetime >= particle.lifetime)
			{
				rc.shouldRender = false;
			}
		}
	}
}

void CParticleEmitter::Start()
{
	myTicker.Start();
}

void CParticleEmitter::Stop()
{
	myTicker.Stop();
}

void CParticleEmitter::AddParticle()
{
	SSpriteRenderCommand sprite;

	CVector2i textureSize = myTexture.GetDimensions();

	sprite.shouldRender = true;
	sprite.position = GetPosition();
	sprite.rotation = myRandomizer.GetRandomBetween(mySettings.myRotation.min, mySettings.myRotation.max);
	sprite.scale = mySettings.myStartScale * myRandomizer.GetRandomBetween(mySettings.myScale.min, mySettings.myScale.max);
	sprite.texture = myTexture;
	sprite.dimensions = { (float)textureSize.x, (float)textureSize.y };
	if (mySettings.myPossibleTexRects.size() > 0)
	{
		int size = mySettings.myPossibleTexRects.size();
		sprite.textureRect = mySettings.myPossibleTexRects[myRandomizer.GetRandomBetween(0, size - 1)];
		CVector2f widthAndHeight = { sprite.textureRect.bottomRight.x - sprite.textureRect.topLeft.x, sprite.textureRect.bottomRight.y - sprite.textureRect.topLeft.y };
		sprite.dimensions = { widthAndHeight.x * (float)textureSize.x, widthAndHeight.y * (float)textureSize.y };
	}

	SParticle particle;
	particle.currentLifetime = 0.f;
	float angle = GetRotation() + (-mySettings.mySpreadAngle / 2.f) + myRandomizer.GetRandomBetween(0.f, mySettings.mySpreadAngle);
	particle.direction = CVector2f(cosf(angle), sinf(angle));
	particle.lifetime = myRandomizer.GetRandomBetween(mySettings.myLifetime.min, mySettings.myLifetime.max);
	particle.speed = myRandomizer.GetRandomBetween(mySettings.mySpeed.min, mySettings.mySpeed.max);
	particle.startColor = mySettings.myStartColor;
	particle.endColor = mySettings.myEndColor;
	particle.rotationSpeed = myRandomizer.GetRandomBetween(mySettings.myRotationSpeed.min, mySettings.myRotationSpeed.max);
	particle.targetScale = sprite.scale.x * mySettings.myEndScale;

	if (mySprites.size() < MAX_AMOUNT_SPRITES_IN_SPRITEBATCH)
	{
		mySprites.push_back(sprite);
		particle.index = myAvailableIndex;
		myParticles.push_back(particle);
	}
	else
	{
		mySprites[myAvailableIndex] = sprite;
		particle.index = myAvailableIndex;
		myParticles[myAvailableIndex] = particle;
	}


	myAvailableIndex++;
	if (myAvailableIndex >= MAX_AMOUNT_SPRITES_IN_SPRITEBATCH)
	{
		myAvailableIndex = 0;
	}

	myTicker.SetDuration(myRandomizer.GetRandomBetween(mySettings.myDelay.min, mySettings.myDelay.max));
}
