#include "timer.h"

Timer::Timer(double framerate) noexcept
	: waitTime(1.0 / framerate),
	  delta(waitTime),
	  frameStartTime(TimerClock::now()) {}

void Timer::wait()
{
	const auto frameEndTime = TimerClock::now();
	const double d = (frameEndTime - frameStartTime).count() / 1000000000.0;

	// std::this_thread::sleep_for(std::chrono::duration<double>(waitTime - d));
	const auto prevFrameStartTime = frameStartTime;
	frameStartTime = TimerClock::now();
	delta = (frameStartTime - prevFrameStartTime).count() / 1000000000.0;
}