#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>

class Window
{
private:
	static const class WndClass
	{
	private:
		static constexpr const wchar_t* const className = L"DV2 Window";
	} wndClass;

	HWND hWnd;
public:
	Window(const wchar_t* title, int width, int height);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	HWND getHwnd() noexcept {return hWnd;}
};