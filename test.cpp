#include <sstream>
#include "dv2.h"
#include "window.h"
#include "timer.h"

#include "dv2.cpp"
#include "window.cpp"
#include "timer.cpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		Window w(L"Test", 800, 500);
		DV2 dv2(w.getHwnd());

		Texture froody = dv2.createTexture(L"froody.png");

		double k = 0.0;
		double s = 1.0 / 25.0;
		double sum = 0.0;
		int n = 0;
		Timer t;
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

			for (int i = 0; i < 100; i++)
				dv2.draw(
					froody,
					dv2.clientToDVX(w.mouse.getX()), dv2.clientToDVY(w.mouse.getY()),
					k
				);

			dv2.present();
			w.update();
			t.endFrame();
			sum += t.getFramerate();
			n++;
		}

		if (n)
		{
			std::wstringstream ss;
			ss << (sum / n);
			MessageBoxW(nullptr, ss.str().c_str(), L"eeeriewfk", 0);
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