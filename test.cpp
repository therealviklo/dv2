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
		Window w(L"Test", 500, 500, true);

		Texture froody = w.dv2.createTexture(L"froody.png");

		double k = 0.0;
		double s = 1.0 / 25.0;
		double sum = 0.0;
		int n = 0;
		std::wstringstream ss;
		NoWaitTimer t;
		while (w.exists())
		{
			for (WME wme = w.mouse.getEvent(); wme.type != WMET::invalid; wme = w.mouse.getEvent())
			{
				if (wme.type == WMET::vscroll)
				{
					s += wme.scroll / 120.0 / 10.0;
				}
				else if (wme.type == WMET::lmouseup)
				{
					w.dv2.setFullscreen(true);
				}
				else if (wme.type == WMET::rmouseup)
				{
					w.dv2.setFullscreen(false);
				}
				else if (wme.type == WMET::mmousedown)
				{
					w.dv2.resize();
				}
			}
			for (WKE wke = w.keyboard.getEvent(); wke.type != WKET::invalid; wke = w.keyboard.getEvent())
			{
				if (wke.type == WKET::keydown && wke.key == VK_RETURN)
				{
					MessageBoxW(nullptr, ss.str().c_str(), L"Text", 0);
					w.keyboard.clearEvents();
				}
				else if (wke.type == WKET::character)
				{
					ss << wke.character;
				}
			}
			k += s * t.getDelta();

			w.dv2.clear({1.0f, 1.0f, 1.0f, 1.0f});

			for (int i = 0; i < 100; i++)
				w.dv2.draw(
					froody,
					w.dv2.clientToDVX(w.mouse.getX()), w.dv2.clientToDVY(w.mouse.getY()),
					k
				);

			w.dv2.presentSync();
			w.update();
			t.endFrame();
			sum += t.getFramerate();
			n++;
		}

		if (n)
		{
			std::wstringstream ss;
			ss << (sum / n);
			MessageBoxW(nullptr, ss.str().c_str(), L"Framerate", 0);
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