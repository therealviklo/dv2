#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <stdexcept>


class Window
{
public:
	class Exception : public std::runtime_error
	{
	public:
		Exception(const char* msg) : std::runtime_error(msg) {}
	};
private:
	static const class WndClass
	{
		friend class Window;
	private:
		static constexpr const wchar_t* const className = L"DV2 Window";
		bool succeeded;

		WndClass() noexcept;
		~WndClass();

		WndClass(const WndClass&) = delete;
		WndClass& operator=(const WndClass&) = delete;
	} wndClass;

	HWND hWnd;
public:
	Window(const wchar_t* title, int width, int height);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void update() noexcept;

	HWND getHwnd() noexcept {return hWnd;}
	bool exists() const noexcept {return IsWindow(hWnd);}
};

LRESULT CALLBACK DV2WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);