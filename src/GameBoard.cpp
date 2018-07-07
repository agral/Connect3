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

  board.resize(newHeight);
  for (auto& row : board)
  {
    row.resize(newWidth);
  }

  width = newWidth;
  height = newHeight;
}

void GameBoard::FillRandomly()
{
  for (auto y = 0; y < height; ++y)
  {
    for (auto x = 0; x < width; ++x)
    {
      board[y][x] = Gem(distGem(twister), x * global::ORB_SIZE, y * global::ORB_SIZE);
    }
  }
}

void GameBoard::LoadFromVector(std::vector<std::vector<int>> colorRepresentation)
{
  int newWidth = colorRepresentation.size();
  int newHeight = colorRepresentation[0].size();

  SetSize(newWidth, newHeight);
  for (auto y = 0; y < height; ++y)
  {
    for (auto x = 0; x < width; ++x)
    {
      board[y][x].color = colorRepresentation[y][x];
      board[y][x].posX = x * global::ORB_SIZE;
      board[y][x].posY = y * global::ORB_SIZE;
      board[y][x].isPartOfChain = false;
    }
  }
}

Gem& GameBoard::At(int x, int y)
{
  if ((x >= 0) && (x < width) && (y >= 0) && (y < height))
  {
    return board[y][x];
  }
  else
  {
    std::cout << "GameBoard::At(" << x << ", " << y << ") invoked." << std::endl;
    throw new std::domain_error("At() called with indices out of bounds.");
  }
}

int GameBoard::Height() const
{
  return height;
}

int GameBoard::Width() const
{
  return width;
}

bool GameBoard::FindChains()
{
  bool areChainsFound = false;
  int y, x;

  // Looks for horizontal chains:
  for (y = 0; y < height; ++y)
  {
    int lastColorCode = -1;
    int chainLengthSoFar = 0;
    for (x = 0; x < width; ++x)
    {
      if (board[y][x].color == lastColorCode)
      {
        ++chainLengthSoFar;
      }
      else
      {
        if (chainLengthSoFar >= 3)
        {
          MarkChain(y, x - 1, chainLengthSoFar, false);
          areChainsFound = true;
        }

        lastColorCode = board[y][x].color;
        chainLengthSoFar = 1;
      }
    }
    if (chainLengthSoFar >= 3)
    {
      MarkChain(y, x - 1, chainLengthSoFar, false);
    }
  }

  // Looks for vertical chains by applying slightly different logic:
  for (x = 0; x < width; ++x)
  {
    int lastColorCode = -1;
    int chainLengthSoFar = 0;
    for (y = 0; y < height; ++y)
    {
      if (board[y][x].color == lastColorCode)
      {
        ++chainLengthSoFar;
      }
      else
      {
        if (chainLengthSoFar >= 3)
        {
          MarkChain(y - 1, x, chainLengthSoFar, true);
          areChainsFound = true;
        }

        lastColorCode = board[y][x].color;
        chainLengthSoFar = 1;
      }
    }
    if (chainLengthSoFar >= 3)
    {
      MarkChain(y - 1, x, chainLengthSoFar, true);
    }
  }

  return areChainsFound;
}


// Private helper methods follow:

void GameBoard::MarkChain(int tailY, int tailX, int length, bool isVertical)
{
  for (int k = 0; k < length; ++k)
  {
    if (isVertical)
    {
      board[tailY - k][tailX].isPartOfChain = true;
    }
    else
    {
      board[tailY][tailX - k].isPartOfChain = true;
    }
  }
}
