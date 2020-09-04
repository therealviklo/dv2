#include "window.h"

const Window::WndClass Window::wndClass;

Window::WndClass::WndClass() noexcept
	: succeeded(false)
{
	WNDCLASSEXW wndClass = {};
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_OWNDC;
	wndClass.lpfnWndProc = DV2WndProc;
	wndClass.hInstance = GetModuleHandleW(nullptr);
	wndClass.hCursor = LoadCursorW(GetModuleHandleW(nullptr), reinterpret_cast<const wchar_t*>(IDC_ARROW));
	wndClass.lpszClassName = className;

	/* RegisterClassExW() returnerar noll om den misslyckas, vilket konverteras till false.
	   Andra värden konverteras till true. */
	succeeded = RegisterClassExW(&wndClass);
}

Window::WndClass::~WndClass()
{
	if (succeeded) UnregisterClassW(className, GetModuleHandleW(nullptr));
}

Window::Window(const wchar_t* title, int width, int height)
{
	if (!wndClass.succeeded) throw Exception("Failed to register window class");

	hWnd = CreateWindowExW(
		0,
		WndClass::className,
		title,
		WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		GetModuleHandleW(nullptr),
		nullptr
	);
	if (!hWnd) throw Exception("Failed to create window");
	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window()
{
	if (IsWindow(hWnd)) DestroyWindow(hWnd);
}

void Window::update() noexcept
{
	MSG msg;
	if (PeekMessageW(&msg, hWnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

LRESULT CALLBACK DV2WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		return 0;
	}
	return DefWindowProcW(hWnd, msg, wParam, lParam);
}