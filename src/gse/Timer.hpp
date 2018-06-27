#ifndef GSE_TIMER_HPP
#define GSE_TIMER_HPP

#include <SDL2/SDL.h>

namespace gse
{

class Timer
{
 public:
  Timer();
  void Start();
  void Stop();
  void Pause();
  void Resume();
  Uint32 Ticks() const;
  bool IsPaused() const;
  bool IsStarted() const;

 private:
   Uint32 startTicks;
   Uint32 pausedTicks;
   bool isPaused;
   bool isStarted;
};



} // namespace gse

#endif // GSE_TIMER_HPP
