#include "GameBoard.hpp"
#include "global/globals.hpp"

#include <stdexcept>
#include <iostream>

GameBoard::GameBoard() :
  width(0),
  height(0)
{
  twister.seed(std::random_device()());
  distGem = std::uniform_int_distribution<std::mt19937::result_type>(0, global::ORBS_TYPES_COUNT - 1);
}

void GameBoard::SetSize(int newWidth, int newHeight)
{
  if ((newWidth <= 2) or (newHeight <= 2))
  {
    std::cout << "GameBoard::SetSize(" << newWidth << ", " << newHeight << ") invoked." << std::endl;
    throw new std::domain_error("GameBoard::SetSize() called with wrong width/height value");
  }

  board.resize(newWidth);
  for (int x = 0; x < newWidth; ++x)
  {
    board[x].resize(newHeight);
  }

  width = newWidth;
  height = newHeight;
}

void GameBoard::NewGame()
{
  for (int x = 0; x < width; ++x)
  {
    for (int y = 0; y < height; ++y)
    {
      board[x][y] = Gem(distGem(twister));
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
