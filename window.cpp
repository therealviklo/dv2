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
	wndClass.hCursor = LoadCursorW(nullptr, reinterpret_cast<const wchar_t*>(IDC_ARROW));
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
	if (events[setPos].type == WKET::invalid)
	{
		events[setPos] = event;
		setPos = (setPos + 1) % events.size();
	}
}

Window::Keyboard::Event Window::Keyboard::getEvent() noexcept
{
	if (events[getPos].type != WKET::invalid)
	{
		const Event event = events[getPos];
		events[getPos] = Event();
		getPos = (getPos + 1) % events.size();
		return event;
	}
	return Event();
}

bool Window::Keyboard::keyDown(uint8_t key) const
{
	if (key >= 0xff) throw Window::Exception("Keycode out of range");
	return keyStates[key];
}

void Window::Mouse::addEvent(Event event) noexcept
{
	if (events[setPos].type == WMET::invalid)
	{
		events[setPos] = event;
		setPos = (setPos + 1) % events.size();
	}
}

Window::Mouse::Event Window::Mouse::getEvent() noexcept
{
	if (events[getPos].type != WMET::invalid)
	{
		const Event event = events[getPos];
		events[getPos] = Event();
		getPos = (getPos + 1) % events.size();
		return event;
	}
	return Event();
}

Window::Window(const wchar_t* title, int width, int height, bool resizeable)
	: dv2Created(false),
	  hWnd([&]{
		if (!wndClass.succeeded) throw Exception("Failed to register window class");

		HWND hWnd = CreateWindowExW(
			0,
			WndClass::className,
			title,
			WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | (resizeable ? WS_THICKFRAME | WS_MAXIMIZEBOX : 0),
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

		return hWnd;
	  }()),
	  dv2(hWnd.get())
{
	dv2Created = true;
}

void Window::update() noexcept
{
	MSG msg;
	while (PeekMessageW(&msg, hWnd.get(), 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

void Window::updateBlocking() noexcept
{
	MSG msg;
	if (GetMessageW(&msg, hWnd.get(), 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

LRESULT Window::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static short captureCount = 0;

	switch (msg)
	{
		case WM_KEYDOWN:
		{
			if (wParam >= keyboard.keyStates.size()) return DefWindowProcW(hWnd, msg, wParam, lParam);

			keyboard.keyStates[wParam] = true;
			keyboard.addEvent(Keyboard::Event(wParam, WKET::keydown));
		}
		return 0;
		case WM_KEYUP:
		{
			if (wParam >= keyboard.keyStates.size()) return DefWindowProcW(hWnd, msg, wParam, lParam);

			keyboard.keyStates[wParam] = false;
			keyboard.addEvent(Keyboard::Event(wParam, WKET::keyup));
		}
		return 0;
		case WM_CHAR:
		{
			keyboard.addEvent(Keyboard::Event(wParam));
		}
		return 0;
		case WM_KILLFOCUS:
		{
			keyboard.clearKeyStates();
			keyboard.clearEvents();
		}
		return 0;
		case WM_MOUSEMOVE:
		{
			mouse.x = GET_X_LPARAM(lParam);
			mouse.y = GET_Y_LPARAM(lParam);
		}
		return 0;
		case WM_LBUTTONDOWN:
		{
			if (captureCount++ == 0) SetCapture(hWnd);
			mouse.x = GET_X_LPARAM(lParam);
			mouse.y = GET_Y_LPARAM(lParam);
			mouse.addEvent(Mouse::Event(mouse.x, mouse.y, WMET::lmousedown));
		}
		return 0;
		case WM_LBUTTONUP:
		{
			if (--captureCount == 0) ReleaseCapture();
			mouse.x = GET_X_LPARAM(lParam);
			mouse.y = GET_Y_LPARAM(lParam);
			mouse.addEvent(Mouse::Event(mouse.x, mouse.y, WMET::lmouseup));
		}
		return 0;
		case WM_RBUTTONDOWN:
		{
			if (captureCount++ == 0) SetCapture(hWnd);
			mouse.x = GET_X_LPARAM(lParam);
			mouse.y = GET_Y_LPARAM(lParam);
			mouse.addEvent(Mouse::Event(mouse.x, mouse.y, WMET::rmousedown));
		}
		return 0;
		case WM_RBUTTONUP:
		{
			if (--captureCount == 0) ReleaseCapture();
			mouse.x = GET_X_LPARAM(lParam);
			mouse.y = GET_Y_LPARAM(lParam);
			mouse.addEvent(Mouse::Event(mouse.x, mouse.y, WMET::rmouseup));
		}
		return 0;
		case WM_MBUTTONDOWN:
		{
			if (captureCount++ == 0) SetCapture(hWnd);
			mouse.x = GET_X_LPARAM(lParam);
			mouse.y = GET_Y_LPARAM(lParam);
			mouse.addEvent(Mouse::Event(mouse.x, mouse.y, WMET::mmousedown));
		}
		return 0;
		case WM_MBUTTONUP:
		{
			if (--captureCount == 0) ReleaseCapture();
			mouse.x = GET_X_LPARAM(lParam);
			mouse.y = GET_Y_LPARAM(lParam);
			mouse.addEvent(Mouse::Event(mouse.x, mouse.y, WMET::mmouseup));
		}
		return 0;
		case WM_MOUSEHWHEEL:
		{
			POINT clientPos = {0, 0};
			if (ClientToScreen(hWnd, &clientPos))
			{
				mouse.x = GET_X_LPARAM(lParam) - clientPos.x;
				mouse.y = GET_Y_LPARAM(lParam) - clientPos.y;
				mouse.addEvent(Mouse::Event(mouse.x, mouse.y, GET_WHEEL_DELTA_WPARAM(wParam), WMET::hscroll));
			}
		}
		return 0;
		case WM_MOUSEWHEEL:
		{
			POINT clientPos = {0, 0};
			if (ClientToScreen(hWnd, &clientPos))
			{
				mouse.x = GET_X_LPARAM(lParam) - clientPos.x;
				mouse.y = GET_Y_LPARAM(lParam) - clientPos.y;
				mouse.addEvent(Mouse::Event(mouse.x, mouse.y, GET_WHEEL_DELTA_WPARAM(wParam), WMET::vscroll));
			}
		}
		return 0;
		case WM_SIZE:
		{
			if (dv2Created)
			{
				try
				{
					dv2.resize();
				}
				catch (...)
				{
					this->hWnd.reset();
				}
			}
		}
		return 0;
		case WM_DESTROY:
		{
			this->hWnd.release();
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
	try
	{
		return window->wndProc(hWnd, msg, wParam, lParam);
	}
	catch (...)
	{
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
}