#ifndef GSE_TIMER_HPP
#define GSE_TIMER_HPP

#include <SDL2/SDL.h>
#include <chrono>

namespace gse
{

typedef std::chrono::high_resolution_clock Clock;

class Timer
{
 public:
  Timer();
  void Start();
  void Stop();
  double Milliseconds() const;
  bool IsPaused() const;
  bool IsStarted() const;

 private:
   std::chrono::time_point<Clock> startTimePoint;
   bool isStarted;
};



} // namespace gse

#endif // GSE_TIMER_HPP
