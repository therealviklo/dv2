Texture2D tex;

SamplerState ss;

cbuffer CBuf
{
	float4 colourShift;
};

float4 main(float2 texPos : TexCoord) : SV_Target
{
	float4 texColour = tex.Sample(ss, texPos);
	texColour.r *= colourShift.r;
	texColour.g *= colourShift.g;
	texColour.b *= colourShift.b;
	texColour.a *= colourShift.a;
	return texColour;
}