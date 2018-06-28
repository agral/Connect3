#include "Timer.hpp"

namespace gse
{

Timer::Timer() :
  isStarted(false)
{
}

void Timer::Start()
{
  startTimePoint = Clock::now();
  isStarted = true;
}

void Timer::Stop()
{
  isStarted = false;
}

double Timer::Milliseconds() const
{
  double result = 0.0;
  if (isStarted)
  {
    std::chrono::time_point t = Clock::now();
    result = std::chrono::duration_cast<std::chrono::nanoseconds>(t-startTimePoint).count() / 1000000.0;
  }

  return result;
}

bool Timer::IsStarted() const
{
  return isStarted;
}

} // namespace gse
