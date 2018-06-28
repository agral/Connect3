#ifndef STATE_INTRO_HPP
#define STATE_INTRO_HPP

#include "GameState.hpp"
#include "../ResourcesManager.hpp"

namespace state
{

class Intro : public GameState
{
 public:
  void ProcessInput();
  void Logic(double millisecondsElapsed);
  void Render();
 private:
};

} // namespace state

#endif // STATE_INTRO_HPP
