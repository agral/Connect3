#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <random>
#include <vector>

class GameBoard
{
 public:
  GameBoard();
  void SetSize(int newWidth, int newHeight);
  void NewGame();
  int At(int x, int y) const;

 private:
  std::mt19937 rng;
  std::uniform_int_distribution<std::mt19937::result_type> distOrb;
  std::vector<std::vector<int>> board;
  int width;
  int height;
};



#endif // GAMEBOARD_HPP
