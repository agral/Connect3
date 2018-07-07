#include "Intro.hpp"
#include "../global/globals.hpp"

#include <SDL2/SDL.h>
#include <iostream>

namespace state
{

void Intro::ProcessInput()
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
      SetNextStateId(STATE_MAINMENU);
    }
  }
}

void Intro::Logic(gse::GameTimeData)
{
}

void Intro::Render()
{
  resMgr.txBgIntro.Render(0, 0);
  resMgr.txLogo.Render((global::SCREEN_WIDTH - resMgr.txLogo.Width()) / 2,
      (global::SCREEN_HEIGHT - resMgr.txLogo.Height()) / 2 );
}

} // namespace state
