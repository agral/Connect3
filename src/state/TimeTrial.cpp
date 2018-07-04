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

  board.SetSize(global::GAMEBOARD_WIDTH, global::GAMEBOARD_HEIGHT);
  board.NewGame();
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

  DrawBoard((global::SCREEN_WIDTH - (global::GAMEBOARD_WIDTH * ORB_SIZE)) / 2,
      (global::SCREEN_HEIGHT - global::GAMEBOARD_HEIGHT * ORB_SIZE) / 2);
}

void TimeTrial::DrawBoard(int posX, int posY)
{
  for (int x = 0; x < global::GAMEBOARD_WIDTH; ++x)
  {
    for(int y = 0; y < global::GAMEBOARD_HEIGHT; ++y)
    {
      resMgr.spOrbs.Render(posX + (x * ORB_SIZE), posY + (y * ORB_SIZE), &orbClips[board.At(x, y).color]);
    }
  }
}

} // namespace state
