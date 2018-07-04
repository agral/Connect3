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
  void NewGame();
  Gem At(int x, int y) const;

 private:
  std::mt19937 twister;
  std::uniform_int_distribution<std::mt19937::result_type> distGem;
  std::vector<std::vector<Gem>> board;
  int width;
  int height;
};



#endif // GAMEBOARD_HPP
