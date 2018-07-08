#include "TimeTrial.hpp"
#include "../global/globals.hpp"

#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

namespace state
{

const int ORB_SIZE = global::ORB_SIZE;
const int DRAG_THRESHOLD = 0.3 * ORB_SIZE;
const double swapAnimationTime = 400; //milliseconds
const double explodeAnimationTime = 1000; // milliseconds
const int BORDER_SIZE = 44;

inline int Signum(int value)
{
  return (value > 0) - (value < 0);
}

void BtnExitIngameOnClick()
{
  SetNextStateId(STATE_MAINMENU);
}

TimeTrial::TimeTrial()
{
  orbClips[0] = {0, 0, ORB_SIZE, ORB_SIZE};
  orbClips[1] = {ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};
  orbClips[2] = {2 * ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};
  orbClips[3] = {3 * ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};
  orbClips[4] = {4 * ORB_SIZE, 0, ORB_SIZE, ORB_SIZE};

  // boardClip #5 is used for board filling; #1-#4 and #6-#9 are used as borders same as numpad keys
  // (e.g. #1 is used for bottom-left border piece, #6 is used for central-right border piece). #0 is unused.
  boardClips[1] = {0, 108, 44, 44};
  boardClips[2] = {44, 108, 64, 44};
  boardClips[3] = {108, 108, 44, 44};
  boardClips[4] = {0, 44, 44, 64};
  boardClips[5] = {44, 44, 64, 64};
  boardClips[6] = {108, 44, 44, 64};
  boardClips[7] = {0, 0, 44, 44};
  boardClips[8] = {44, 0, 64, 44};
  boardClips[9] = {108, 0, 44, 44};

  boardGeometry = {
    (global::SCREEN_WIDTH - (global::GAMEBOARD_WIDTH * ORB_SIZE) - BORDER_SIZE), BORDER_SIZE,
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

  isDragging = false;
  remainingIdleTime = 60000; // 60000 milliseconds = one minute.

  pbTime = std::make_unique<gse::ProgressBar>(resMgr.spProgressBar, 520, 10, gse::ProgressBarColors::GREEN);
  pbTime->SetPosition(boardGeometry.x + (boardGeometry.w - 520) / 2, 10);

  btnExit = std::make_unique<gse::Button>(resMgr.spBtnIngameExit.Width(), resMgr.spBtnIngameExit.Height() / 3,
      resMgr.spBtnIngameExit);
  btnExit->SetPosition((200 - resMgr.spBtnIngameExit.Width()) / 2, global::SCREEN_HEIGHT - 90);
  btnExit->SetOnClick(&BtnExitIngameOnClick);

  phase = GamePhase::FALLING;
  nextPhase = GamePhase::NONE;
}

void TimeTrial::ProcessInput()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      SetNextStateId(STATE_EXIT);
    }

    if ((event.type == SDL_MOUSEBUTTONDOWN) || (event.type == SDL_MOUSEBUTTONUP) || (event.type == SDL_MOUSEMOTION))
    {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);

      // Regardless of the position of the cursor, the dragging ends when the user releases the mouse:
      if (event.type == SDL_MOUSEBUTTONUP)
      {
        isDragging = false;
      }

      // If the mouse is over the board, and the game accepts user input (is in "IDLE" state):
      if ((phase == GamePhase::IDLE) &&
          (mouseX >= boardGeometry.x) && (mouseX < boardGeometry.x + boardGeometry.w) &&
          (mouseY >= boardGeometry.y) && (mouseY < boardGeometry.y + boardGeometry.h))
      {
        if (event.type == SDL_MOUSEBUTTONUP)
        {
          if (std::max(std::abs(filteredDragDistanceX), std::abs(filteredDragDistanceY)) < DRAG_THRESHOLD)
          {
            // @TODO: implement click-to-swap scenario.
          }
          else
          {
            // @TODO: implement swipe-to-swap scenario.
            otherGemXIndex = draggedGemXIndex;
            otherGemYIndex = draggedGemYIndex;
            if (filteredDragDistanceX < -DRAG_THRESHOLD)
            {
              otherGemXIndex -= 1;
            }
            else if (filteredDragDistanceX > DRAG_THRESHOLD)
            {
              otherGemXIndex += 1;
            }
            else if (filteredDragDistanceY < -DRAG_THRESHOLD)
            {
              otherGemYIndex -= 1;
            }
            else if (filteredDragDistanceY > DRAG_THRESHOLD)
            {
              otherGemYIndex += 1;
            }

            // Safeguards against dragging Gems off the board:
            if ((otherGemXIndex >= 0) && (otherGemXIndex < board.Width()) &&
                (otherGemYIndex >= 0) && (otherGemYIndex < board.Height()))
            {
              // Swaps the two gems on a model board:
              std::cout << "SWAP: [" << draggedGemXIndex << ", " << draggedGemYIndex
                  << "] and [" << otherGemXIndex << ", " << otherGemYIndex << "]" << std::endl;
              board.SwapColors(draggedGemXIndex, draggedGemYIndex, otherGemXIndex, otherGemYIndex);
              if (board.FindChains())
              {
                std::cout << "SWAP OK - Chains are formed." << std::endl;

                // Enters the SWAPPING phase in this iteration's logic handling:
                nextPhase = GamePhase::SWAPPING;
              }
              else
              {
                std::cout << "Swap failed - no new chains." << std::endl;
                // Reverts the color change back
                board.SwapColors(draggedGemXIndex, draggedGemYIndex, otherGemXIndex, otherGemYIndex);
              }
            }
          }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
          dragOriginX = mouseX;
          dragOriginY = mouseY;
          dragDistanceX = 0;
          dragDistanceY = 0;
          draggedGemXIndex = (mouseX - boardGeometry.x) / ORB_SIZE;
          draggedGemYIndex = (mouseY - boardGeometry.y) / ORB_SIZE;
          isDragging = true;
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
          if (isDragging)
          {
            dragDistanceX = mouseX - dragOriginX;
            dragDistanceY = mouseY - dragOriginY;
          }
        }
      }

      btnExit->ProcessInput(event, mouseX, mouseY);
    }
  }
}

void TimeTrial::Logic(gse::GameTimeData td)
{
  // Switches to the next state, if applicable:
  if (nextPhase != GamePhase::NONE)
  {
    phase = nextPhase;
    nextPhase = GamePhase::NONE;
    phaseBirth = td.timeTotal;
    std::cout << "[TimeTrial] Switched to " << GamePhaseNames[phase] << " game phase." << std::endl;
  }

  if (phase == GamePhase::IDLE)
  {
    // Decrements the game time:
    remainingIdleTime -= td.timeSinceLastFrame;
    pbTime->SetNormalizedProgress(remainingIdleTime / 60000.0);
    std::cout << "Time left: " << remainingIdleTime / 1000.0 << " seconds." << std::endl;

    if (remainingIdleTime <= 0.0)
    {
      std::cout << "End of remaining idle time." << std::endl;
      nextPhase = GamePhase::OVER;
    }
  }

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
        nextPhase = GamePhase::EXPLODING;
      }
      else
      {
        nextPhase = GamePhase::IDLE;
      }
    }
  }
  else if (phase == GamePhase::SWAPPING)
  {
    double animTime = td.timeTotal - phaseBirth;

    // Easing function: sin(t) from 0.5PI (max) to 1.5PI (min), mapped to [ORB_SIZE -> 0] range
    double distance = animTime > swapAnimationTime ?
        0 : (0.5 * ORB_SIZE * (1 + std::sin(M_PI * (animTime / swapAnimationTime + 0.5))));

    double swapDirectionX = (draggedGemXIndex - otherGemXIndex);
    double swapDirectionY = (draggedGemYIndex - otherGemYIndex);
    if (swapDirectionX != 0)
    {
      board.At(draggedGemXIndex, draggedGemYIndex).posX = (draggedGemXIndex * ORB_SIZE) - (swapDirectionX * distance);
      board.At(otherGemXIndex, otherGemYIndex).posX = (otherGemXIndex * ORB_SIZE) + (swapDirectionX * distance);
    }
    else if (swapDirectionY != 0)
    {
      board.At(draggedGemXIndex, draggedGemYIndex).posY = (draggedGemYIndex * ORB_SIZE) - (swapDirectionY * distance);
      board.At(otherGemXIndex, otherGemYIndex).posY = (otherGemYIndex * ORB_SIZE) + (swapDirectionY * distance);
    }

    if (animTime >= swapAnimationTime)
    {
      // Puts the swapped gems both in their exact places:
      board.At(draggedGemXIndex, draggedGemYIndex).posX = draggedGemXIndex * ORB_SIZE;
      board.At(draggedGemXIndex, draggedGemYIndex).posY = draggedGemYIndex * ORB_SIZE;
      board.At(otherGemXIndex, otherGemYIndex).posX = otherGemXIndex * ORB_SIZE;
      board.At(otherGemXIndex, otherGemYIndex).posY = otherGemYIndex * ORB_SIZE;

      nextPhase = GamePhase::EXPLODING;
    }
  }
  else if (phase == GamePhase::EXPLODING)
  {
    double animTime = td.timeTotal - phaseBirth;
    if ( animTime > explodeAnimationTime )
    {
      std::cout << "End of Explode animation" << std::endl;

      for (int x = 0; x < board.Width(); ++x)
      {
        int explodedBelowCounter = 0;
        for (int y = board.Height() - 1; y >= 0; --y)
        {
          if (board.At(x, y).isPartOfChain)
          {
            explodedBelowCounter += 1;
          }
          else
          {
            if (explodedBelowCounter > 0)
            {
              // Sets the Gem at its target position on the GameBoard model (as if it already fell):
              board.At(x, y + explodedBelowCounter).color = board.At(x, y).color;

              // Sets its rendering Y-position exactly where it were so that its fall will be smooth:
              board.At(x, y + explodedBelowCounter).posY = y * ORB_SIZE;

              board.At(x, y + explodedBelowCounter).velocityY = 0;
              board.At(x, y + explodedBelowCounter).isPartOfChain = false;
              board.At(x, y + explodedBelowCounter).isFalling = true;
            }
          }
        }
        // Adds "new" random Gems in place of those exploded. They start their fall from just above the board:
        for (int z = explodedBelowCounter - 1; z >= 0; --z)
        {
          board.SetRandomColor(x, z);
          board.At(x, z).posY = (z - explodedBelowCounter) * ORB_SIZE;
          board.At(x, z).velocityY = 0;
          board.At(x, z).isPartOfChain = false;
          board.At(x, z).isFalling = true;
        }
      }

      nextPhase = GamePhase::FALLING;
    }
    else
    {
      // Easing function: cos^2(t) from 0 (max) to PI (min), mapped to [255 -> 0] range:
      double factor =  0.5 * (1 + std::cos(M_PI * (animTime / explodeAnimationTime)));
      explodingAlpha = 255 * factor * factor;
    }
  }
}

void TimeTrial::Render()
{
  DrawBoard();
  DrawBoardBorder();
  pbTime->Render();
  btnExit->Render();
}

void TimeTrial::DrawBoard()
{
  // Draws the board background:
  for (int x = 0; x < board.Width(); ++x)
  {
    for (int y = 0; y < board.Height(); ++y)
    {
      resMgr.spBoard.Render(boardGeometry.x + x * ORB_SIZE, boardGeometry.y + y * ORB_SIZE, &boardClips[5]);
    }
  }

  // Draws the Gems:
  for (int x = 0; x < board.Width(); ++x)
  {
    for (int y = 0; y < board.Height(); ++y)
    {
      // Renders all the static gems normally:
      if ((!(isDragging && (x == draggedGemXIndex) && (y == draggedGemYIndex))) &&
          (!((phase == GamePhase::EXPLODING) && (board.At(x, y).isPartOfChain))))
      {
        resMgr.spOrbs.Render(
            boardGeometry.x + board.At(x, y).posX,
            boardGeometry.y + board.At(x, y).posY,
            &orbClips[board.At(x, y).color]
        );
      }
      else if (isDragging && (x == draggedGemXIndex) && (y == draggedGemYIndex))
      {
        resMgr.spOrbs.SetAlpha(0.25 * 255);
        resMgr.spOrbs.Render(
            boardGeometry.x + board.At(x, y).posX,
            boardGeometry.y + board.At(x, y).posY,
            &orbClips[board.At(x, y).color]
        );
        resMgr.spOrbs.SetAlpha(255);
      }
      else if ((phase == GamePhase::EXPLODING) && (board.At(x, y).isPartOfChain))
      {
        resMgr.spOrbs.SetAlpha(explodingAlpha);
        resMgr.spOrbs.Render(
            boardGeometry.x + board.At(x, y).posX,
            boardGeometry.y + board.At(x, y).posY,
            &orbClips[board.At(x, y).color]
        );
        resMgr.spOrbs.SetAlpha(255);
      }
    }
  }

  // Renders the currently dragged gem (if any) at nonstandard position:
  if (isDragging)
  {
    filteredDragDistanceX = std::abs(dragDistanceX) > std::abs(dragDistanceY) ? dragDistanceX : 0;
    filteredDragDistanceY = std::abs(dragDistanceX) > std::abs(dragDistanceY) ? 0 : dragDistanceY;
    if (std::abs(filteredDragDistanceX) > ORB_SIZE)
    {
      filteredDragDistanceX =
          Signum(filteredDragDistanceX) * (ORB_SIZE + std::log(std::abs(filteredDragDistanceX) - ORB_SIZE));
    }
    else if (std::abs(filteredDragDistanceY) > ORB_SIZE)
    {
      filteredDragDistanceY =
          Signum(filteredDragDistanceY) * (ORB_SIZE + std::log(std::abs(filteredDragDistanceY) - ORB_SIZE));
    }

    resMgr.spOrbs.SetAlpha(0.8 * 255);
    resMgr.spOrbs.Render(
        boardGeometry.x + board.At(draggedGemXIndex, draggedGemYIndex).posX + filteredDragDistanceX,
        boardGeometry.y + board.At(draggedGemXIndex, draggedGemYIndex).posY + filteredDragDistanceY,
        &orbClips[board.At(draggedGemXIndex, draggedGemYIndex).color]
    );
    resMgr.spOrbs.SetAlpha(255);
  }
}

void TimeTrial::DrawBoardBorder()
{
  resMgr.spBoard.Render(boardGeometry.x - boardClips[7].w, boardGeometry.y - boardClips[7].h, &boardClips[7]);
  resMgr.spBoard.Render(boardGeometry.x + boardGeometry.w, boardGeometry.y - boardClips[9].h, &boardClips[9]);
  resMgr.spBoard.Render(boardGeometry.x - boardClips[1].w, boardGeometry.y + boardGeometry.h, &boardClips[1]);
  resMgr.spBoard.Render(boardGeometry.x + boardGeometry.w, boardGeometry.y + boardGeometry.h, &boardClips[3]);

  for (int x = 0; x < board.Width(); ++x)
  {
    resMgr.spBoard.Render(boardGeometry.x + boardClips[8].w * x, boardGeometry.y - boardClips[8].h, &boardClips[8]);
    resMgr.spBoard.Render(boardGeometry.x + boardClips[2].w * x, boardGeometry.y + boardGeometry.h, &boardClips[2]);
  }
  for (int y = 0; y < board.Height(); ++y)
  {
    resMgr.spBoard.Render(boardGeometry.x - boardClips[4].w, boardGeometry.y + boardClips[4].h * y, &boardClips[4]);
    resMgr.spBoard.Render(boardGeometry.x + boardGeometry.w, boardGeometry.y + boardClips[6].h * y, &boardClips[6]);
  }
}

} // namespace state
