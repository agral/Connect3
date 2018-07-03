#ifndef STATE_MAINMENU_HPP
#define STATE_MAINMENU_HPP

#include "GameState.hpp"
#include "../ResourcesManager.hpp"

#include <SDL2/SDL.h>

namespace state
{

class MainMenu : public GameState
{
 public:
  MainMenu();

  void ProcessInput();
  void Logic(double millisecondsElapsed);
  void Render();
 private:
  SDL_Rect logoGeometry;
  SDL_Rect btnTimeTrialGeometry;
  bool isBtnTimeTrialHovered;
};

} // namespace state

#endif // STATE_MAINMENU_HPP
