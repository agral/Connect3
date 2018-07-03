#include "TimeTrial.hpp"
#include "../global/globals.hpp"

#include <SDL2/SDL.h>
#include <iostream>

namespace state
{

TimeTrial::TimeTrial()
{
}

void TimeTrial::ProcessInput()
{
  SDL_Event event;
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      SetNextStateId(STATE_EXIT);
    }

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      SetNextStateId(STATE_MAINMENU);
    }
  }
}

void TimeTrial::Logic(double millisecondsElapsed)
{
}

void TimeTrial::Render()
{
  //Render any background?
  resMgr.txLogo.Render((global::SCREEN_WIDTH - resMgr.txLogo.Width()) / 2,
      (global::SCREEN_HEIGHT - resMgr.txLogo.Height()) / 2);
}

} // namespace state
