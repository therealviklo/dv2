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

void Window::Keyboard::addEvent(Event event) noexcept
{
	memmove(static_cast<void*>(&events[1]), static_cast<void*>(&events[0]), (events.size() - 1) * sizeof(events[0]));
	events[0] = event;
}

Window::Keyboard::Event Window::Keyboard::getEvent() noexcept
{
	Event event = events[events.size() - 1];
	memmove(static_cast<void*>(&events[1]), static_cast<void*>(&events[0]), (events.size() - 1) * sizeof(events[0]));
	events[0] = Event();
	return event;
}

constexpr bool Window::Keyboard::keyDown(uint8_t key) const
{
	if (key >= 0xff) throw Window::Exception("Keycode out of range");
	return keyStates[key];
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
	switch (msg)
	{
		case WM_KEYDOWN:
		{
			keyboard.keyStates[wParam] = true;
			keyboard.addEvent(Keyboard::Event{static_cast<uint8_t>(wParam), Keyboard::Event::Type::KeyDown});
		}
		return 0;
		case WM_KEYUP:
		{
			keyboard.keyStates[wParam] = false;
			keyboard.addEvent(Keyboard::Event{static_cast<uint8_t>(wParam), Keyboard::Event::Type::KeyUp});
		}
		return 0;
		case WM_KILLFOCUS:
		{
			keyboard.clearKeyStates();
			keyboard.clearEvents();
		}
		return 0;
	}
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