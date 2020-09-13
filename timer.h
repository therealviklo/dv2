#pragma once
#include <chrono>
#include <thread>

using TimerClock = std::chrono::high_resolution_clock;

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

	void setFramerate(double framerate) noexcept {waitTime = 1.0 / framerate;}

	void wait();

	double getDelta() const noexcept {return delta;}
	double getFramerate() const noexcept {return 1.0 / delta;}
};

class NoWaitTimer
{
private:
	std::chrono::time_point<TimerClock> frameStartTime;
	double delta;
public:
	NoWaitTimer() noexcept;

	void endFrame();

	double getDelta() const noexcept {return delta;}
	double getFramerate() const noexcept {return 1.0 / delta;}
};