cbuffer CBuf
{
	matrix mtx;
	matrix texmtx;
};

struct VSOut
{
	float2 texPos : TexCoord;
	float4 pos : SV_Position;
};

VSOut main(float2 pos : Position, float2 texPos : TexCoord)
{
	VSOut vso;
	vso.texPos = mul(float4(texPos.x, texPos.y, 0.0f, 1.0f), texmtx);
	vso.pos = mul(float4(pos.x, pos.y, 0.0f, 1.0f), mtx);
	return vso;
}