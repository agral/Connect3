#include "GameBoard.hpp"
#include "global/globals.hpp"

#include <stdexcept>
#include <iostream>

GameBoard::GameBoard() :
  width(0),
  height(0)
{
  rng.seed(std::random_device()());
  distOrb = std::uniform_int_distribution<std::mt19937::result_type>(0, global::ORBS_TYPES_COUNT - 1);
}

void GameBoard::SetSize(int newWidth, int newHeight)
{
  if ((newWidth <= 2) or (newHeight <= 2))
  {
    std::cout << "GameBoard::SetSize(" << newWidth << ", " << newHeight << ") invoked." << std::endl;
    throw new std::domain_error("GameBoard::SetSize() called with wrong width/height value");
  }

  board.resize(global::GAMEBOARD_WIDTH);
  for (int x = 0; x < global::GAMEBOARD_WIDTH; ++x)
  {
    board[x].resize(global::GAMEBOARD_HEIGHT);
  }

  width = newWidth;
  height = newHeight;
}

void GameBoard::NewGame()
{
  for (int x = 0; x < global::GAMEBOARD_WIDTH; ++x)
  {
    for (int y = 0; y < global::GAMEBOARD_HEIGHT; ++y)
    {
      board[x][y] = Gem(distOrb(rng));
    }
  }
}

Gem GameBoard::At(int x, int y) const
{
  if ((x >= 0) && (x < width) && (y >= 0) && (y < height))
  {
    return board[x][y];
  }
  else
  {
    std::cout << "GameBoard::At(" << x << ", " << y << ") invoked." << std::endl;
    throw new std::domain_error("At() called with indices out of bounds.");
  }
}
