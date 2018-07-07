#include "TimeTrial.hpp"
#include "../global/globals.hpp"

#include <SDL2/SDL.h>
#include <iostream>

namespace state
{

const int ORB_SIZE = global::ORB_SIZE;

TimeTrial::TimeTrial()
{
  orbClips[0] = {0, 0, ORB_SIZE, ORB_SIZE};
  orbClips[1] = {ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};
  orbClips[2] = {2 * ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};
  orbClips[3] = {3 * ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};
  orbClips[4] = {4 * ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};

  board.SetSize(global::GAMEBOARD_WIDTH, global::GAMEBOARD_HEIGHT);
  board.FillRandomlyWithoutChains();

  for (auto y = 0; y < board.Height(); ++y)
  {
    for (auto x = 0; x < board.Width(); ++x)
    {
      board.At(x, y).posY = ORB_SIZE * (y - board.Height());
      board.At(x, y).isFalling = true;
    }
  }

  phase = GamePhase::FALLING;
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
  if (phase == GamePhase::FALLING)
  {
    bool isStillFalling = false;
    for (auto y = 0; y < board.Height(); ++y)
    {
      for (auto x = 0; x < board.Width(); ++x)
      {
        if (board.At(x, y).isFalling)
        {
          isStillFalling = true;
          board.At(x, y).velocityY += global::gravityConstant * millisecondsElapsed;
          board.At(x, y).posY += board.At(x, y).velocityY * millisecondsElapsed;
          if (board.At(x, y).posY > y * ORB_SIZE)
          {
            board.At(x, y).isFalling = false;
            board.At(x, y).posY = y * ORB_SIZE;
          }
        }
        if ((x == 3) && (y == 3))
        {
          std::cout << "Velocity Y: " << board.At(x, y).velocityY;
          std::cout << ", X: " << board.At(x, y).posX << ", Y: " << board.At(x, y).posY;
          std::cout << ", isFalling: " << board.At(x, y).isFalling << std::endl;
        }
      }
    }

    if (!isStillFalling)
    {
      std::cout << "Switch me back to IDLE/EXPLODING state!" << std::endl;
    }
  }
}

void TimeTrial::Render()
{
  //Render any background?
  DrawBoard((global::SCREEN_WIDTH - (board.Width() * ORB_SIZE)) / 2,
      (global::SCREEN_HEIGHT - board.Height() * ORB_SIZE) / 2);
}

void TimeTrial::DrawBoard(int posX, int posY)
{
  for (int x = 0; x < board.Width(); ++x)
  {
    for(int y = 0; y < board.Height(); ++y)
    {
      if ((x == 3) && (y == 3) && (phase == GamePhase::FALLING))
      {
        std::cout << posX + board.At(x, y).posX << std::endl;
      }
      resMgr.spOrbs.Render(posX + board.At(x, y).posX, posY + board.At(x, y).posY, &orbClips[board.At(x, y).color]);
    }
  }
}

} // namespace state
