#include <catch/catch.hpp>
#include "../src/GameBoard.hpp"

#include <vector>

std::vector<std::vector<int>> r3 = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9}
};

std::vector<std::vector<int>> chains = {
  {3, 3, 3, 2, 4, 3, 3, 3},
  {3, 1, 2, 1, 4, 1, 2, 3},
  {3, 2, 1, 2, 4, 2, 1, 3},
  {2, 1, 2, 1, 4, 1, 2, 1},
  {1, 2, 1, 2, 4, 2, 1, 2},
  {3, 1, 2, 1, 4, 1, 2, 3},
  {3, 2, 1, 2, 4, 2, 1, 3},
  {3, 3, 3, 1, 4, 3, 3, 3},
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
        CHECK(gb.At(y, x).color == r3[y][x]);
      }
    }
  }

  SECTION("isPartOfChain flag is unset for every Gem")
  {
    for (unsigned long y = 0; y < r3.size(); ++y)
    {
      for (unsigned long x = 0; x < r3[y].size(); ++x)
      {
        CHECK(gb.At(x, y).isPartOfChain == false);
      }
    }
  }
}

TEST_CASE("Chains of three or more consecutive gems are being found correctly")
{
  GameBoard gb;
  gb.LoadFromVector(chains);
  bool areChainsFound = gb.FindChains();

  REQUIRE(areChainsFound == true);

  SECTION("Chains of length 3 in the corners are found")
  {
    // Chains of length 3 in the corners:
    CHECK( // Top-left corner, horizontal
        ((gb.At(0, 0).isPartOfChain) &&
        (gb.At(0, 1).isPartOfChain) &&
        (gb.At(0, 2).isPartOfChain))
    );
    CHECK( // Top-left corner, vertical
        ((gb.At(0, 0).isPartOfChain) &&
        (gb.At(1, 0).isPartOfChain) &&
        (gb.At(2, 0).isPartOfChain))
    );
    CHECK( // Top-right corner, horizontal
        ((gb.At(0, 5).isPartOfChain) &&
        (gb.At(0, 6).isPartOfChain) &&
        (gb.At(0, 7).isPartOfChain))
    );
    CHECK( // Top-right corner, vertical
        ((gb.At(0, 7).isPartOfChain) &&
        (gb.At(1, 7).isPartOfChain) &&
        (gb.At(2, 7).isPartOfChain))
    );

    CHECK( // Bottom-left corner, horizontal
        ((gb.At(7, 0).isPartOfChain) &&
        (gb.At(7, 1).isPartOfChain) &&
        (gb.At(7, 2).isPartOfChain))
    );
    CHECK( // Bottom-left corner, vertical
        ((gb.At(5, 0).isPartOfChain) &&
        (gb.At(6, 0).isPartOfChain) &&
        (gb.At(7, 0).isPartOfChain))
    );
    CHECK( // Bottom-right corner, horizontal
        ((gb.At(7, 5).isPartOfChain) &&
        (gb.At(7, 6).isPartOfChain) &&
        (gb.At(7, 7).isPartOfChain))
    );
    CHECK( // Bottom-right corner, vertical
        ((gb.At(5, 7).isPartOfChain) &&
        (gb.At(6, 7).isPartOfChain) &&
        (gb.At(7, 7).isPartOfChain))
    );
  }
}
