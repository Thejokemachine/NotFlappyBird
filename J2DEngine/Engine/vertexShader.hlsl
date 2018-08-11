#include "shaderStructs.hlsli"
#include "constantBuffers.hlsli"

GeometryInput main(VertexInput input)
{
	GeometryInput rv;

	float4 posInScreenSpace = float4(input.position.xy, 0, 1);
	float2 dimensionsInScreenSpace = input.dimensions;

	posInScreenSpace.x /= 1600.0f;
	posInScreenSpace.y /= 900.0f;

	posInScreenSpace.x *= 2;
	posInScreenSpace.y *= -2;

	posInScreenSpace.x -= 1;
	posInScreenSpace.y += 1;

	dimensionsInScreenSpace.x /= 1600.0f;
	dimensionsInScreenSpace.y /= 900.0f;

	rv.position = posInScreenSpace;
	rv.color = input.color;
	rv.textureRect = input.textureRect;
	rv.rotation = input.rotation;
	rv.dimensions = dimensionsInScreenSpace;
	rv.scale = input.scale;
	rv.trash = input.trash;

	return rv;
}