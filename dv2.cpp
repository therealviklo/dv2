#include "dv2.h"

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
	try
	{
		ID3D11Resource* backBuffer = nullptr;
		if (FAILED(swap->GetBuffer(
			0,
			__uuidof(ID3D11Resource),
			reinterpret_cast<void**>(&backBuffer)
		))) throw Exception("Failed to get back buffer");
		try
		{
			if (FAILED(device->CreateRenderTargetView(
				backBuffer,
				nullptr,
				&target
			))) throw Exception("Failed to create render target view");
		}
		catch (...)
		{
			safeRelease(backBuffer);
			throw;
		}
		safeRelease(backBuffer);
	}
	catch (...)
	{
		safeRelease(context);
		safeRelease(swap);
		safeRelease(device);
		throw;
	}
}

DV2::~DV2()
{
	safeRelease(target);
	safeRelease(context);
	safeRelease(swap);
	safeRelease(device);
}

void DV2::clear()
{
	const float clrArr[] = {0.0f, 0.0f, 0.0f, 1.0f};
	context->ClearRenderTargetView(target, clrArr);
}

void DV2::clear(Colour clr)
{
	const float clrArr[] = {clr.r, clr.g, clr.b, clr.a};
	context->ClearRenderTargetView(target, clrArr);
}

void DV2::present()
{
	swap->Present(1, 0);
}