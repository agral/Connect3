#include "Timer.hpp"

namespace gse
{

Timer::Timer() :
  startTicks(0),
  pausedTicks(0),
  isPaused(false),
  isStarted(false)
{
}

void Timer::Start()
{
  startTicks = SDL_GetTicks();
  pausedTicks = 0;
  isPaused = false;
  isStarted = true;
}

void Timer::Stop()
{
  pausedTicks = 0;
  startTicks = 0;
  isPaused = false;
  isStarted = false;
}

void Timer::Pause()
{
  if (isStarted && !isPaused)
  {
    pausedTicks = SDL_GetTicks() - startTicks;
    startTicks = 0;
    isPaused = true;
  }
}

void Timer::Resume()
{
  if (isStarted && isPaused)
  {
    startTicks = SDL_GetTicks() - pausedTicks;
    pausedTicks = 0;
    isPaused = false;
  }
}

Uint32 Timer::Ticks() const
{
  Uint32 time = 0;
  if (isStarted)
  {
    time = isPaused ? pausedTicks : SDL_GetTicks() - startTicks;
  }

  return time;
}

bool Timer::IsStarted() const
{
  return isStarted;
}

bool Timer::IsPaused() const
{
  return isPaused;
}

} // namespace gse
