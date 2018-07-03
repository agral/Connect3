#ifndef STATE_TIMETRIAL_HPP
#define STATE_TIMETRIAL_HPP

#include "GameState.hpp"
#include "../ResourcesManager.hpp"

#include <SDL2/SDL.h>

namespace state
{

class TimeTrial : public GameState
{
 public:
  TimeTrial();
  void ProcessInput();
  void Logic(double millisecondsElapsed);
  void Render();
 private:
};

} // namespace state

#endif // STATE_TIMETRIAL_HPP
