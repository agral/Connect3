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
  void Logic(gse::GameTimeData td);
  void Render();
 private:
  SDL_Rect logoGeometry;
  SDL_Rect threeGeometry;
  std::unique_ptr<gse::Button> btnTimeTrial;
  std::unique_ptr<gse::Button> btnExit;
  Uint8 threeAlpha;
};

} // namespace state

#endif // STATE_MAINMENU_HPP
