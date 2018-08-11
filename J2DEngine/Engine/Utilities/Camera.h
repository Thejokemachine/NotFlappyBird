#pragma once
#include "Base.h"
#include "../Math/Transform.h"
#include "../Graphics/ShaderWrappers.h"
#include "ConstantBuffer.h"

struct CDirectXFramework;

class CCamera : public CBase, public CTransform
{
public:

	struct SCameraData
	{
		SShaderVec2 position;
		float zoom;
		float rotation;
	};

	~CCamera();

	static CCamera& GetInstance();

	void Init(CDirectXFramework* aFramework);

	void Zoom(float aZoom);
	void Update();

private:
	CCamera();

	float myZoom;

	CConstantBuffer myConstantBuffer;
};

