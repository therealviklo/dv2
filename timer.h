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
	Timer(double framerate) noexcept :
		waitTime(1.0 / framerate),
		delta(waitTime),
		frameStartTime(TimerClock::now()) {}

	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

	void setFramerate(double framerate) noexcept {waitTime = 1.0 / framerate;}

	void wait()
	{
		const auto frameEndTime = TimerClock::now();
		const double d = (frameEndTime - frameStartTime).count() / 1000000000.0;

		std::this_thread::sleep_for(std::chrono::duration<double>(waitTime - d));
		const auto prevFrameStartTime = frameStartTime;
		frameStartTime = TimerClock::now();
		delta = (frameStartTime - prevFrameStartTime).count() / 1000000000.0;
	}

	double getDelta() const noexcept {return delta;}
	double getFramerate() const noexcept {return 1.0 / delta;}
};

class NoWaitTimer
{
private:
	std::chrono::time_point<TimerClock> frameStartTime;
	double delta;
public:
	NoWaitTimer() noexcept :
		delta(0.0),
		frameStartTime(TimerClock::now()) {}

	void endFrame()
	{
		const auto prevFrameStartTime = frameStartTime;
		frameStartTime = TimerClock::now();
		delta = (frameStartTime - prevFrameStartTime).count() / 1000000000.0;
	}

	double getDelta() const noexcept {return delta;}
	double getFramerate() const noexcept {return 1.0 / delta;}
};