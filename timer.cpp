#include "timer.h"

Timer::Timer() noexcept
	: delta(0.0),
	  frameStartTime(TimerClock::now()) {}

void Timer::endFrame()
{
	const auto prevFrameStartTime = frameStartTime;
	frameStartTime = TimerClock::now();
	delta = (frameStartTime - prevFrameStartTime).count() / 1000000000.0;
}