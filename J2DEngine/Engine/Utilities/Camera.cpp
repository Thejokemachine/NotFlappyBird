#include "Camera.h"

CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

CCamera & CCamera::GetInstance()
{
	static CCamera instance;
	return instance;
}

void CCamera::Init(CDirectXFramework * aFramework)
{
	myConstantBuffer.Create<SCameraData>();

	myZoom = 10.f;
	Rotate(3.14f);
	Move(1, 2);
}

void CCamera::Zoom(float aZoom)
{
	myZoom += aZoom;
}

void CCamera::Update()
{
	SCameraData data;
	data.position = GetPosition();
	data.rotation = GetRotation();
	data.zoom = myZoom;

	myConstantBuffer.Remap(CAMERA_SLOT, data);
}
