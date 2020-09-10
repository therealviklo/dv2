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

		int k = 0;
		while (w.exists())
		{
			k++;

			dv2.clear({1.0f, 0.0f, 0.0f, 1.0f});

			dv2.draw(500.0f, 0.0f, 50.0f, 100.0f, k / 50.0f);

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