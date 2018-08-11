cbuffer CameraData : register(b0)
{
	float2 position;
	float zoom;
	float rotation;
}

cbuffer TimeData : register(b1)
{
	float deltaTime;
	float totalTime;
}