#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <d3d11.h>
#include <stdexcept>
#include <wrl.h>
#include <directxmath.h>

using Microsoft::WRL::ComPtr;

/* Länka med:
   - user32
   - d3d11 */

struct Colour
{
	float r;
	float g;
	float b;
	float a;
};

class DV2
{
public:
	class Exception : public std::runtime_error
	{
	public:
		Exception(const char* msg) : std::runtime_error(msg) {}
	};
private:
	float width;
	float height;

	ComPtr<IDXGISwapChain> swap;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	ComPtr<ID3D11RenderTargetView> target;
	
	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11InputLayout> inputLayout;
public:
	DV2(HWND hWnd);

	DV2(const DV2&) = delete;
	DV2& operator=(const DV2&) = delete;

	void setSize(float width, float height);

	void clear();
	void clear(Colour clr);

	void draw(float x, float y, float width, float height, float angle);

	void present();
};