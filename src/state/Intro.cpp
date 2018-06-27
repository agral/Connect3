#include "Intro.hpp"

#include <SDL2/SDL.h>

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

void Intro::Logic()
{
}

void Intro::Render()
{
  resMgr.txBgIntro.Render(0, 0);
}

} // namespace state
