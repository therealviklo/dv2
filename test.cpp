#include <sstream>
#include "dv2.h"
#include "window.h"

#include "dv2.cpp"
#include "window.cpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		Window w(L"Test", 500, 500);

		int k = 0;
		while (w.exists())
		{
			for (Window::Keyboard::Event e = w.keyboard.getEvent();
				 e.type != Window::Keyboard::Event::Type::Invalid;
				 e = w.keyboard.getEvent())
			{
				if (e.key == VK_RETURN && e.type == Window::Keyboard::Event::Type::KeyUp)
				{
					std::wstringstream ss;
					ss << (++k);
					SetWindowTextW(w.getHwnd(), ss.str().c_str());
				}
			}

			w.update();
		}
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR);
	}
	catch (...)
	{
		MessageBoxW(nullptr, L"Unknown error", L"Error", MB_ICONERROR);
	}
	return 0;
}