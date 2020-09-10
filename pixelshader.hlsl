Texture2D tex;

SamplerState ss;

float4 main(float2 texPos : TexCoord) : SV_Target
{
	return tex.Sample(ss, texPos);
}