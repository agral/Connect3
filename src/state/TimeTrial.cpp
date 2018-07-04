#include "TimeTrial.hpp"
#include "../global/globals.hpp"

#include <SDL2/SDL.h>
#include <iostream>

namespace state
{

const int ORB_SIZE = 64;

TimeTrial::TimeTrial()
{
  orbClips[0] = {0, 0, ORB_SIZE, ORB_SIZE};
  orbClips[1] = {ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};
  orbClips[2] = {2 * ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};
  orbClips[3] = {3 * ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};
  orbClips[4] = {4 * ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};
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

  resMgr.spOrbs.Render(0, 0, &orbClips[0]);
  resMgr.spOrbs.Render(global::SCREEN_WIDTH - ORB_SIZE, 0, &orbClips[1]);
  resMgr.spOrbs.Render(0, global::SCREEN_HEIGHT - ORB_SIZE, &orbClips[2]);
  resMgr.spOrbs.Render(global::SCREEN_WIDTH - ORB_SIZE, global::SCREEN_HEIGHT - ORB_SIZE, &orbClips[3]);
}

} // namespace state
