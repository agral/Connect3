#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include "Gem.hpp"

#include <random>
#include <vector>

class GameBoard
{
 public:
  GameBoard();
  void SetSize(int newWidth, int newHeight);
  void FillRandomly();
  void FillRandomlyWithoutChains();
  void LoadFromVector(std::vector<std::vector<int>> colorRepresentation);

  /**
   * Performs a sweep of the game board, finding all the Gems that form chains.
   *
   * Marks every Gem that is a part of a chain by setting its isPartOfChain flag.
   *
   * \return true iff there is at least one chain present in the board.
   */
  bool FindChains();
  void ClearIsPartOfChain();

  Gem& At(int x, int y);
  int Height() const;
  int Width() const;

 private:
  std::mt19937 twister;
  std::uniform_int_distribution<std::mt19937::result_type> distGem;
  std::vector<std::vector<Gem>> board;
  int width;
  int height;

  // Helper function to FindChains - marks all the nodes of the discovered chain:
  void MarkChain(int tailY, int tailX, int length, bool isVertical);
};



#endif // GAMEBOARD_HPP
