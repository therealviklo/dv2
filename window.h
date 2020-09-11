#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <windowsx.h>
#include <stdexcept>
#include <bitset>
#include <array>
#include <cstdint>

#include <sstream>
#include <iomanip>

enum WKET
{
	WKET_INVALID,
	WKET_KEYDOWN,
	WKET_KEYUP
};

enum WMET
{
	WMET_INVALID,
	WMET_LMOUSEDOWN,
	WMET_LMOUSEUP,
	WMET_RMOUSEDOWN,
	WMET_RMOUSEUP,
	WMET_MMOUSEDOWN,
	WMET_MMOUSEUP,
	WMET_HSCROLL,
	WMET_VSCROLL
};

class Window
{
public:
	class Exception : public std::runtime_error
	{
	public:
		Exception(const char* msg) : std::runtime_error(msg) {}
	};
private:
	static const class WndClass
	{
		friend class Window;
	private:
		static constexpr const wchar_t* const className = L"DV2 Window";
		bool succeeded;

		WndClass() noexcept;
		~WndClass();

		WndClass(const WndClass&) = delete;
		WndClass& operator=(const WndClass&) = delete;
	} wndClass;

	HWND hWnd;
public:
	class Keyboard
	{
		friend class Window;
	public:
		struct Event
		{
			uint8_t key;
			WKET type;

			Event(uint8_t key, WKET type) noexcept : key(key), type(type) {}
			Event() noexcept : key(0), type(WKET_INVALID) {}
		};
	private:
		std::bitset<0x100> keyStates;
		std::array<Event, 16> events;

		void addEvent(Event event) noexcept;
	public:
		/* Returnerar det event som står först i kön. Om det inte finns några
		   event returneras ett event med typen WKET_INVALID. */
		Event getEvent() noexcept;
		constexpr bool keyDown(uint8_t key) const;

		void clearKeyStates() noexcept {keyStates = decltype(keyStates)();}
		void clearEvents() noexcept {events = decltype(events)();}
	} keyboard;
	class Mouse
	{
		friend class Window;
	public:
		struct Event
		{
			int x;
			int y;
			// Används bara med WMET_HSCROLL och WMET_VSCROLL.
			int scroll;
			WMET type;

			Event(int x, int y, int scroll, WMET type) noexcept : x(x), y(y), scroll(scroll), type(type) {}
			Event(int x, int y, WMET type) noexcept : x(x), y(y), scroll(0), type(type) {}
			Event() noexcept : x(0), y(0), scroll(0), type(WMET_INVALID) {}
		};
	private:
		int x;
		int y;
		std::array<Event, 16> events;
		
		Mouse() noexcept : x(0), y(0) {}

		void addEvent(Event event) noexcept;
	public:
		/* Returnerar det event som står först i kön. Om det inte finns några
		   event returneras ett event med typen WMET_INVALID. */
		Event getEvent() noexcept;
		int getX() {return x;}
		int getY() {return y;}
		
		void clearEvents() noexcept {events = decltype(events)();}
	} mouse;

	Window(const wchar_t* title, int width, int height);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void update() noexcept;

	constexpr HWND getHwnd() noexcept {return hWnd;}
	bool exists() const noexcept {return IsWindow(hWnd);}

	LRESULT wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	static LRESULT CALLBACK DV2SetupWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK DV2WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

typedef Window::Keyboard::Event WKE;
typedef Window::Mouse::Event WME;