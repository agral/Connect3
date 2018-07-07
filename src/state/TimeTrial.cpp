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

  boardGeometry = {
    (global::SCREEN_WIDTH - (global::GAMEBOARD_WIDTH * ORB_SIZE)) / 2,
    (global::SCREEN_HEIGHT - (global::GAMEBOARD_HEIGHT * ORB_SIZE)) / 2,
    global::GAMEBOARD_WIDTH * ORB_SIZE,
    global::GAMEBOARD_HEIGHT * ORB_SIZE
  };

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

void TimeTrial::Logic(gse::GameTimeData td)
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
          board.At(x, y).velocityY += global::gravityConstant * td.timeSinceLastFrame;
          board.At(x, y).posY += board.At(x, y).velocityY * td.timeSinceLastFrame;
          if (board.At(x, y).posY > y * ORB_SIZE)
          {
            board.At(x, y).isFalling = false;
            board.At(x, y).posY = y * ORB_SIZE;
          }
        }
      }
    }

    if (!isStillFalling)
    {
      if (board.FindChains())
      {
        // @TODO Explode the chains
      }
      else
      {
        phase = GamePhase::IDLE;
        std::cout << "Switching to IDLE." << std::endl;
      }
    }
  }
}

void TimeTrial::Render()
{
  // Render any background?
  DrawBoard(boardGeometry.x, boardGeometry.y);
}

void TimeTrial::DrawBoard(int posX, int posY)
{
  for (int x = 0; x < board.Width(); ++x)
  {
    for(int y = 0; y < board.Height(); ++y)
    {
      resMgr.spOrbs.Render(posX + board.At(x, y).posX, posY + board.At(x, y).posY, &orbClips[board.At(x, y).color]);
    }
  }
}

} // namespace state
