#include "shaderStructs.hlsli"
#include "constantBuffers.hlsli"

PixelOutput main(PixelInput input)
{
	PixelOutput rv;

	float4 texColor = instanceTexture.Sample(instanceSampler, input.uv.xy);
	rv.color = texColor * input.color;
	//rv.color.r = sin(totalTime);
	//rv.color = input.color;
	//rv.color = float4(input.uv.x, input.uv.y, input.uv.y, 1);
	return rv;
}