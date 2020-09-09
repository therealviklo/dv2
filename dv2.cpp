#include "dv2.h"

constexpr const uint8_t vertexShaderData[] = {
     68,  88,  66,  67, 162, 105, 
    215,  72, 129, 234, 214, 198, 
    215,  30, 201,  56,  61,  24, 
     17,   2,   1,   0,   0,   0, 
    160,   3,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
     20,   1,   0,   0,   4,   2, 
      0,   0, 128,   2,   0,   0, 
     56,   3,   0,   0, 108,   3, 
      0,   0,  65, 111, 110,  57, 
    212,   0,   0,   0, 212,   0, 
      0,   0,   0,   2, 254, 255, 
    160,   0,   0,   0,  52,   0, 
      0,   0,   1,   0,  36,   0, 
      0,   0,  48,   0,   0,   0, 
     48,   0,   0,   0,  36,   0, 
      1,   0,  48,   0,   0,   0, 
      0,   0,   4,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   2, 254, 255, 
     81,   0,   0,   5,   5,   0, 
     15, 160,   0,   0, 128,  63, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   0,   0,  15, 144, 
      4,   0,   0,   4,   0,   0, 
      7, 128,   0,   0, 196, 144, 
      5,   0, 208, 160,   5,   0, 
    197, 160,   8,   0,   0,   3, 
      0,   0,   4, 192,   0,   0, 
    228, 128,   3,   0, 244, 160, 
      8,   0,   0,   3,   1,   0, 
      1, 128,   0,   0, 228, 128, 
      1,   0, 244, 160,   8,   0, 
      0,   3,   1,   0,   2, 128, 
      0,   0, 228, 128,   2,   0, 
    244, 160,   8,   0,   0,   3, 
      0,   0,   1, 128,   0,   0, 
    228, 128,   4,   0, 244, 160, 
      4,   0,   0,   4,   0,   0, 
      3, 192,   0,   0,   0, 128, 
      0,   0, 228, 160,   1,   0, 
    228, 128,   1,   0,   0,   2, 
      0,   0,   8, 192,   0,   0, 
      0, 128, 255, 255,   0,   0, 
     83,  72,  68,  82, 232,   0, 
      0,   0,  64,   0,   1,   0, 
     58,   0,   0,   0,  89,   0, 
      0,   4,  70, 142,  32,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,  95,   0,   0,   3, 
     50,  16,  16,   0,   0,   0, 
      0,   0, 103,   0,   0,   4, 
    242,  32,  16,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
    104,   0,   0,   2,   1,   0, 
      0,   0,  54,   0,   0,   5, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,  16,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5,  66,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     16,   0,   0,   8,  18,  32, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70, 131,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  16,   0,   0,   8, 
     34,  32,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70, 131, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   8,  66,  32,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     70, 131,  32,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
     16,   0,   0,   8, 130,  32, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70, 131,  32,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,   7,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  82,  68, 
     69,  70, 176,   0,   0,   0, 
      1,   0,   0,   0,  68,   0, 
      0,   0,   1,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    254, 255,   0,   1,   0,   0, 
    136,   0,   0,   0,  60,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
     67,  66, 117, 102,   0, 171, 
    171, 171,  60,   0,   0,   0, 
      1,   0,   0,   0,  92,   0, 
      0,   0,  64,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 116,   0,   0,   0, 
      0,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
    120,   0,   0,   0,   0,   0, 
      0,   0, 109, 116, 120,   0, 
      3,   0,   3,   0,   4,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  49,  48,  46, 
     49,   0,  73,  83,  71,  78, 
     44,   0,   0,   0,   1,   0, 
      0,   0,   8,   0,   0,   0, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   3,   3,   0,   0, 
     80, 111, 115, 105, 116, 105, 
    111, 110,   0, 171, 171, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  80, 111, 115, 105, 116, 
    105, 111, 110,   0
};

constexpr const uint8_t pixelShaderData[] =
{
     68,  88,  66,  67, 132,   0, 
      2,   7, 179, 161,  93, 125, 
     99, 210, 140, 141, 110, 217, 
     64, 117,   1,   0,   0,   0, 
    220,   1,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    144,   0,   0,   0, 208,   0, 
      0,   0,  76,   1,   0,   0, 
    152,   1,   0,   0, 168,   1, 
      0,   0,  65, 111, 110,  57, 
     80,   0,   0,   0,  80,   0, 
      0,   0,   0,   2, 255, 255, 
     44,   0,   0,   0,  36,   0, 
      0,   0,   0,   0,  36,   0, 
      0,   0,  36,   0,   0,   0, 
     36,   0,   0,   0,  36,   0, 
      0,   0,  36,   0,   1,   2, 
    255, 255,  81,   0,   0,   5, 
      0,   0,  15, 160,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
    128,  63,   1,   0,   0,   2, 
      0,   8,  15, 128,   0,   0, 
    228, 160, 255, 255,   0,   0, 
     83,  72,  68,  82,  56,   0, 
      0,   0,  64,   0,   0,   0, 
     14,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   8, 242,  32,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    128,  63,   0,   0, 128,  63, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  82,  68,  69,  70, 
     68,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  28,   0, 
      0,   0,   0,   4, 255, 255, 
      0,   1,   0,   0,  28,   0, 
      0,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  49,  48,  46,  49,   0, 
     73,  83,  71,  78,   8,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  79,  83, 
     71,  78,  44,   0,   0,   0, 
      1,   0,   0,   0,   8,   0, 
      0,   0,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  83,  86,  95,  84, 
     97, 114, 103, 101, 116,   0, 
    171, 171
};

DV2::DV2(HWND hWnd)
	: swap(nullptr),
	  device(nullptr),
	  context(nullptr)
{
	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&swap,
		&device,
		nullptr,
		&context
	))) throw Exception("Failed to initialise Direct3D 11");

	ID3D11Resource* backBuffer = nullptr;
	if (FAILED(swap->GetBuffer(
		0,
		__uuidof(ID3D11Resource),
		reinterpret_cast<void**>(&backBuffer)
	))) throw Exception("Failed to get back buffer");

	if (FAILED(device->CreateRenderTargetView(
		backBuffer,
		nullptr,
		&target
	))) throw Exception("Failed to create render target view");

	
	struct Vertex
	{
		float x;
		float y;
	};
	const Vertex vertices[] = {
		{-1.0f, 1.0f},
		{1.0f, 1.0f},
		{1.0f, -1.0f},
		{-1.0f, 1.0f},
		{1.0f, -1.0f},
		{-1.0f, -1.0f},
	};

	D3D11_BUFFER_DESC bd{};
	bd.ByteWidth = sizeof(vertices);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA srd{};
	srd.pSysMem = vertices;
	if (FAILED(device->CreateBuffer(&bd, &srd, &vertexBuffer))) throw Exception("Failed to create vertex buffer");
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

	const float mtx[4][4] = {
		cosf(30.0f), -sinf(30.0f), 0.0f, 0.0f,
		sinf(30.0f), cosf(30.0f), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	D3D11_BUFFER_DESC mbd{};
	mbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	mbd.Usage = D3D11_USAGE_DYNAMIC;
	mbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	mbd.ByteWidth = sizeof(mtx);
	D3D11_SUBRESOURCE_DATA msd{};
	msd.pSysMem = mtx;
	if (FAILED(
		device->CreateBuffer(
			&mbd,
			&msd,
			&matrixBuffer
		)
	)) throw Exception("Failed to create matrix buffer");
	context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

	if (FAILED(
		device->CreatePixelShader(
			pixelShaderData,
			sizeof(pixelShaderData),
			nullptr,
			&pixelShader
		)
	)) throw Exception("Failed to create pixel shader");
	context->PSSetShader(pixelShader.Get(), nullptr, 0);

	if (FAILED(
		device->CreateVertexShader(
			vertexShaderData,
			sizeof(vertexShaderData),
			nullptr,
			&vertexShader
		)
	)) throw Exception("Failed to create vertex shader");
	context->VSSetShader(vertexShader.Get(), nullptr, 0);

	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	if (FAILED(
		device->CreateInputLayout(
			ied,
			1,
			vertexShaderData,
			sizeof(vertexShaderData),
			&inputLayout
		)
	)) throw Exception("Failed to create input layout");
	context->IASetInputLayout(inputLayout.Get());

	context->OMSetRenderTargets(1, target.GetAddressOf(), nullptr);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT vp{};
	vp.Width = 500;
	vp.Height = 500;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	context->RSSetViewports(1, &vp);
}

void DV2::clear()
{
	const float clrArr[] = {0.0f, 0.0f, 0.0f, 1.0f};
	context->ClearRenderTargetView(target.Get(), clrArr);
}

void DV2::clear(Colour clr)
{
	const float clrArr[] = {clr.r, clr.g, clr.b, clr.a};
	context->ClearRenderTargetView(target.Get(), clrArr);
}

void DV2::test(float angle)
{
	const float mtx[4][4] = {
		cosf(angle), -sinf(angle), 0.0f, 0.0f,
		sinf(angle), cosf(angle), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	context->UpdateSubresource(matrixBuffer.Get(), 0, nullptr, mtx, 0, 0);//sizeof(float) * 4, sizeof(float) * 4);
	context->PSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

	context->Draw(6, 0);
}

void DV2::present()
{
	swap->Present(1, 0);
}