#include <catch/catch.hpp>
#include "../src/GameBoard.hpp"

#include <vector>

std::vector<std::vector<int>> r3 = {
  {1, 2, 3},
  {2, 3, 4},
  {3, 4, 2}
};

TEST_CASE("Loading Board from a vector works correctly")
{
  GameBoard gb;
  gb.LoadFromVector(r3);
  SECTION("Colors are set accordingly")
  {
    for (unsigned long y = 0; y < r3.size(); ++y)
    {
      for (unsigned long x = 0; x < r3[y].size(); ++x)
      {
        CHECK(gb.At(x, y).color == r3[y][x]);
      }
    }
  }
}