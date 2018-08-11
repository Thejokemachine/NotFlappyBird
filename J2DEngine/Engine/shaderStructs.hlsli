struct VertexInput
{
	float2 position : POSITION;
	float4 color : COLOR;
	float4 textureRect : TEXRECT;
	float rotation : ROTATION;
	float2 dimensions : DIMENSIONS;
	float2 scale : SCALE;
	float trash : TRASH;
};

struct GeometryInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float4 textureRect : TEXRECT;
	float rotation : ROTATION;
	float2 dimensions : DIMENSIONS;
	float2 scale : SCALE;
	float trash : TRASH;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv : UV;
	float2 trash : TRASH;
};

struct PixelOutput
{
	float4 color : SV_TARGET;
};

Texture2D instanceTexture : register(t0);
SamplerState instanceSampler : register(s0);