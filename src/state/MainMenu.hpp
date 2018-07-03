#ifndef STATE_MAINMENU_HPP
#define STATE_MAINMENU_HPP

#include "GameState.hpp"
#include "../ResourcesManager.hpp"
#include "../gse/Button.hpp"

#include <SDL2/SDL.h>
#include <memory>

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
  std::unique_ptr<gse::Button> btnTimeTrial;
};

} // namespace state

#endif // STATE_MAINMENU_HPP
