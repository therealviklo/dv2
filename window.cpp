#include "window.h"

const Window::WndClass Window::wndClass;

Window::WndClass::WndClass() noexcept
	: succeeded(false)
{
	WNDCLASSEXW wndClass = {};
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_OWNDC;
	wndClass.lpfnWndProc = DV2SetupWndProc;
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
		this
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

LRESULT Window::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::DV2SetupWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg != WM_CREATE) return DefWindowProcW(hWnd, msg, wParam, lParam);

	SetLastError(0);
	if (!SetWindowLongPtrW(
		hWnd,
		GWLP_USERDATA,
		reinterpret_cast<LONG_PTR>(reinterpret_cast<const CREATESTRUCTW* const>(lParam)->lpCreateParams)
	) && GetLastError()) return -1;
	if (!SetWindowLongPtrW(
		hWnd,
		GWLP_WNDPROC,
		reinterpret_cast<LONG_PTR>(DV2WndProc)
	) && GetLastError()) return -1;
	return 0;
}

LRESULT CALLBACK Window::DV2WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const window = reinterpret_cast<Window* const>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
	return window->wndProc(hWnd, msg, wParam, lParam);
}