#include "MainMenu.hpp"
#include "../global/globals.hpp"

#include <SDL2/SDL.h>

namespace state
{

void MainMenu::ProcessInput()
{
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      SetNextStateId(STATE_EXIT);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      SetNextStateId(STATE_EXIT);
    }
  }
}

void MainMenu::Logic()
{
}

void MainMenu::Render()
{
  resMgr.txBgMainMenu.Render(0, 0);
  resMgr.txLogo.Render((global::SCREEN_WIDTH - resMgr.txLogo.Width()) / 2, 0);
}

} // namespace state
