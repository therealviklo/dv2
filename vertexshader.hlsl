cbuffer CBuf
{
	matrix mtx;
};

float4 main(float2 pos : Position) : SV_Position
{
	return mul(float4(pos.x, pos.y, 0.0f, 1.0f), mtx);
}