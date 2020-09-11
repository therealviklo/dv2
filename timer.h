#pragma once
#include <chrono>
#include <thread>

using TimerClock = std::chrono::high_resolution_clock;

class Timer
{
private:
	std::chrono::time_point<TimerClock> frameStartTime;
	double delta;
public:
	Timer() noexcept;

	void endFrame();

	double getDelta() const noexcept {return delta;}
	double getFramerate() const noexcept {return 1.0 / delta;}
};