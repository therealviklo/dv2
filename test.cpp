#include <sstream>
#include "dv2.h"
#include "window.h"

#include "dv2.cpp"
#include "window.cpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		Window w(L"Test", 800, 500);
		DV2 dv2(w.getHwnd());

		Texture froody = dv2.createTexture(L"froody.png");

		double k = 0.0;
		double s = 1.0 / 25.0;
		while (w.exists())
		{
			for (Window::Mouse::Event wme = w.mouse.getEvent(); wme.type != WMET_INVALID; wme = w.mouse.getEvent())
			{
				if (wme.type == WMET_VSCROLL)
				{
					s += wme.scroll / 120.0 / 100.0;
				}
			}
			k += s;

			dv2.clear({1.0f, 1.0f, 1.0f, 1.0f});

			dv2.draw(
				froody,
				dv2.clientToDVX(w.mouse.getX()), dv2.clientToDVY(w.mouse.getY()),
				k
			);

			dv2.present();
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