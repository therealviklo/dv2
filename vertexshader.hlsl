cbuffer CBuf
{
	matrix mtx;
};

struct VSOut
{
	float2 texPos : TexCoord;
	float4 pos : SV_Position;
};

VSOut main(float2 pos : Position, float2 texPos : TexCoord)
{
	VSOut vso;
	vso.texPos = texPos;
	vso.pos = mul(float4(pos.x, pos.y, 0.0f, 1.0f), mtx);
	return vso;
}