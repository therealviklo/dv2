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
	IDXGISwapChain* swap;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	ID3D11RenderTargetView* target;

	template <typename T>
	static void safeRelease(T*& t)
	{
		if (t)
		{
			t->Release();
			t = nullptr;
		}
	}
public:
	DV2(HWND hWnd);
	~DV2();

	DV2(const DV2&) = delete;
	DV2& operator=(const DV2&) = delete;

	void clear();
	void clear(Colour clr);

	void present();
};