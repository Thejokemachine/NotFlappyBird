#include "shaderStructs.hlsli"
#include "constantBuffers.hlsli"

float2 RotateAroundPoint(float4 aPointToRotate, float4 aPointToRotateAround, float aRotation)
{
	//float2 newPoint = aPointToRotate.xy;
	//
	//newPoint -= aPointToRotateAround.xy;
	//
	//float s = sin(aRotation);
	//float c = cos(aRotation);
	//
	//newPoint.x = newPoint.x * c - newPoint.y * s;
	//newPoint.y = newPoint.x * s + newPoint.y * c;
	//
	//newPoint += aPointToRotateAround.xy;
	//
	//return newPoint;

	// Test

	float ratio = 16.0f / 9.0f;

	float2 p = aPointToRotate.xy - aPointToRotateAround.xy;

	float2 q;

	q.x = p.x * (cos(aRotation)) + p.y * sin(aRotation) / ratio;
	q.y = p.x * -sin(aRotation) * ratio + p.y * cos(aRotation);

	return q + aPointToRotateAround.xy;

}

[maxvertexcount(4)]
void main(point GeometryInput input[1], inout TriangleStream<PixelInput> output)
{
	float2 dimensions = input[0].scale * input[0].dimensions;

	const float4 offset[4] = 
	{
		{ -dimensions.x, dimensions.y, 0 , 0 },
		{ dimensions.x, dimensions.y, 0 , 0 },
		{ -dimensions.x, -dimensions.y, 0 , 0 },
		{ dimensions.x, -dimensions.y, 0 , 0 }
	};

	float2 topLeft = input[0].textureRect.xy;
	float2 bottomRight = input[0].textureRect.zw;

	const float2 uv[4] = 
	{
		{ topLeft.x, topLeft.y },
		{ bottomRight.x, topLeft.y },
		{ topLeft.x, bottomRight.y },
		{ bottomRight.x, bottomRight.y }
	};

	for (int i = 0; i < 4; ++i)
	{
		PixelInput vertex;
		vertex.position = float4(RotateAroundPoint(input[0].position + offset[i], input[0].position, input[0].rotation).xy, 0, 1);
		vertex.color = input[0].color;
		vertex.uv = uv[i];
		vertex.trash = input[0].trash;
		output.Append(vertex);
	}
	output.RestartStrip();
}