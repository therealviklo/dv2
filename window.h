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
#include <memory>
#include <type_traits>
#include "dv2.h"

enum struct WKET
{
	invalid,
	keydown,
	keyup,
	character
};

enum struct WMET
{
	invalid,
	lmousedown,
	lmouseup,
	rmousedown,
	rmouseup,
	mmousedown,
	mmouseup,
	hscroll,
	vscroll
};

struct WndDeleter
{
	constexpr void operator()(HWND hWnd) const noexcept
	{
		if (hWnd) DestroyWindow(hWnd);
	}
};
using UWnd = std::unique_ptr<std::remove_pointer_t<HWND>, WndDeleter>;

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

	bool dv2Created;

	UWnd hWnd;
public:
	class Keyboard
	{
		friend class Window;
	public:
		struct Event
		{
			union
			{
				// Används av alla eventtyper förutom WKET_CHAR.
				uint8_t key;
				// Används bara av WKET_CHAR.
				wchar_t character;
			};
			WKET type;

			Event(uint8_t key, WKET type) noexcept : key(key), type(type) {}
			explicit Event(wchar_t character) noexcept : character(character), type(WKET::character) {}
			Event() noexcept : key(0), type(WKET::invalid) {}
		};
	private:
		std::bitset<0x100> keyStates;
		std::array<Event, 16> events;
		unsigned getPos = 0;
		unsigned setPos = 0;

		void addEvent(Event event) noexcept;
	public:
		/* Returnerar det event som står först i kön. Om det inte finns några
		   event returneras ett event med typen WKET_INVALID. */
		Event getEvent() noexcept;
		bool keyDown(uint8_t key) const;

		void clearKeyStates() noexcept { keyStates = decltype(keyStates)(); }
		void clearKeyState(uint8_t key) noexcept { keyStates[key] = false; }
		void clearEvents() noexcept
		{
			events = decltype(events)();
			getPos = 0;
			setPos = 0;
		}
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
			Event() noexcept : x(0), y(0), scroll(0), type(WMET::invalid) {}
		};
	private:
		int x;
		int y;
		std::array<Event, 16> events;
		unsigned getPos;
		unsigned setPos;
		
		Mouse() noexcept : x(0), y(0), getPos(0), setPos(0) {}

		void addEvent(Event event) noexcept;
	public:
		/* Returnerar det event som står först i kön. Om det inte finns några
		   event returneras ett event med typen WMET_INVALID. */
		Event getEvent() noexcept;
		int getX() {return x;}
		int getY() {return y;}
		
		void clearEvents() noexcept
		{
			events = decltype(events)();
			getPos = 0;
			setPos = 0;
		}
	} mouse;
	DV2 dv2;

	Window(const wchar_t* title, int width, int height, bool resizeable = false);

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void update() noexcept;
	void updateBlocking() noexcept;

	constexpr HWND getHwnd() noexcept { return hWnd.get(); }
	bool exists() const noexcept { return hWnd.get(); }

	LRESULT wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	static LRESULT CALLBACK DV2SetupWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK DV2WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

typedef Window::Keyboard::Event WKE;
typedef Window::Mouse::Event WME;