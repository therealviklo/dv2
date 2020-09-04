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
			for (WME e = w.mouse.getEvent(); e.type != WMET_INVALID; e = w.mouse.getEvent())
			{
				if (e.type == WMET_LMOUSEDOWN || e.type == WMET_RMOUSEDOWN || e.type == WMET_MMOUSEDOWN)
				{
					k++;
				}
				else if (e.type == WMET_LMOUSEUP || e.type == WMET_RMOUSEUP || e.type == WMET_MMOUSEUP)
				{
					k--;
				}
				std::wstringstream ss;
				ss << k;
				SetWindowTextW(w.getHwnd(), ss.str().c_str());
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