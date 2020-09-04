#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <stdexcept>
#include <bitset>
#include <array>
#include <cstdint>

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
			enum struct Type
			{
				Invalid,
				KeyDown,
				KeyUp
			} type;

			Event(uint8_t key, Type type) noexcept : key(key), type(type) {}
			Event() noexcept : key(0), type(Type::Invalid) {}
		};
	private:
		std::bitset<0xff> keyStates;
		std::array<Event, 16> events;

		void addEvent(Event event) noexcept;
	public:
		/* Returnerar det event som står först i kön. Om det inte finns några
		   event returneras ett event med typen Invalid. */
		Event getEvent() noexcept;
		constexpr bool keyDown(uint8_t key) const;

		void clearKeyStates() noexcept {keyStates = decltype(keyStates)();}
		void clearEvents() noexcept {events = decltype(events)();}
	} keyboard;

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