#pragma once
#include <chrono>
#include <thread>

using TimerClock = std::chrono::high_resolution_clock;

// En klass som kan användas för att försöka hålla en viss framerate.
class Timer
{
private:
	std::chrono::time_point<TimerClock> frameStartTime;
	double waitTime;
	double delta;
public:
	Timer(double framerate) noexcept;

	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

	// Ändrar frameraten.
	void setFramerate(double framerate) noexcept {waitTime = 1.0 / framerate;}

	// Väntar tills nästa frame ska börja. Funktionen räknar bort tiden som har gått sedan förra gången wait() kördes.
	void wait();

	// Returnerar ett tal som man kan multiplicera med för att snabba upp saker när det laggar.
	double getDelta() const noexcept {return delta;}
	// Returnerar den riktiga frameraten.
	double getFramerate() const noexcept {return 1.0 / delta;}
};