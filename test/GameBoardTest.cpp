#include <catch/catch.hpp>
#include "../src/GameBoard.hpp"

#include <vector>

std::vector<std::vector<int>> r3 = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9}
};

std::vector<std::vector<int>> chains = {
  {3, 3, 3, 5, 4, 3, 3, 3},
  {3, 1, 2, 5, 4, 5, 2, 3},
  {3, 2, 1, 5, 4, 5, 1, 3},
  {2, 1, 2, 5, 4, 5, 2, 1},
  {6, 6, 6, 6, 4, 5, 1, 2},
  {3, 1, 2, 1, 4, 5, 2, 3},
  {3, 2, 1, 2, 4, 2, 1, 3},
  {3, 3, 3, 1, 4, 3, 3, 3},
};

std::vector<std::vector<int>> tooShortToConstituteChains = {
  {1, 1, 2, 2},
  {1, 1, 2, 2},
  {2, 2, 1, 1},
  {2, 2, 1, 1}
};


TEST_CASE("Loading Board from a vector works correctly")
{
  GameBoard gb;
  gb.LoadFromVector(r3);
  SECTION("Colors are set accordingly")
  {
    bool colorsAreAssignedCorrectly = true;
    for (unsigned long y = 0; y < r3.size(); ++y)
    {
      for (unsigned long x = 0; x < r3[y].size(); ++x)
      {
        colorsAreAssignedCorrectly &= (gb.At(x, y).color == r3[y][x]);
      }
    }
    REQUIRE(colorsAreAssignedCorrectly);
  }

  SECTION("isPartOfChain flag is unset for every Gem")
  {
    bool isFlagSet = false;
    for (unsigned long y = 0; y < r3.size(); ++y)
    {
      for (unsigned long x = 0; x < r3[y].size(); ++x)
      {
        isFlagSet |= (gb.At(x, y).isPartOfChain);
      }
    }
    REQUIRE_FALSE(isFlagSet);
  }
}


TEST_CASE("Chains of two consecutive Gems are ignored (not marked as chains)")
{
  GameBoard gb;
  gb.LoadFromVector(tooShortToConstituteChains);
  bool areChainsFound = gb.FindChains();

  REQUIRE_FALSE(areChainsFound);
}


TEST_CASE("Chains of three or more consecutive gems are being found correctly")
{
  GameBoard gb;
  gb.LoadFromVector(chains);
  bool areChainsFound = gb.FindChains();

  REQUIRE(areChainsFound == true);

  SECTION("Chains of length 3 in the corners are detected")
  {
    // Chains of length 3 in the corners:
    CHECK( // Top-left corner, horizontal
        ((gb.At(0, 0).isPartOfChain) &&
        (gb.At(1, 0).isPartOfChain) &&
        (gb.At(2, 0).isPartOfChain))
    );
    CHECK( // Top-left corner, vertical
        ((gb.At(0, 0).isPartOfChain) &&
        (gb.At(0, 1).isPartOfChain) &&
        (gb.At(0, 2).isPartOfChain))
    );
    CHECK( // Top-right corner, horizontal
        ((gb.At(5, 0).isPartOfChain) &&
        (gb.At(6, 0).isPartOfChain) &&
        (gb.At(7, 0).isPartOfChain))
    );
    CHECK( // Top-right corner, vertical
        ((gb.At(7, 0).isPartOfChain) &&
        (gb.At(7, 1).isPartOfChain) &&
        (gb.At(7, 2).isPartOfChain))
    );
    CHECK( // Bottom-left corner, horizontal
        ((gb.At(0, 7).isPartOfChain) &&
        (gb.At(1, 7).isPartOfChain) &&
        (gb.At(2, 7).isPartOfChain))
    );
    CHECK( // Bottom-left corner, vertical
        ((gb.At(0, 5).isPartOfChain) &&
        (gb.At(0, 6).isPartOfChain) &&
        (gb.At(0, 7).isPartOfChain))
    );
    CHECK( // Bottom-right corner, horizontal
        ((gb.At(5, 7).isPartOfChain) &&
        (gb.At(6, 7).isPartOfChain) &&
        (gb.At(7, 7).isPartOfChain))
    );
    CHECK( // Bottom-right corner, vertical
        ((gb.At(7, 5).isPartOfChain) &&
        (gb.At(7, 6).isPartOfChain) &&
        (gb.At(7, 7).isPartOfChain))
    );
  }

  SECTION("Chains of length 4 are detected")
  {
    CHECK(( // Vertical chain at (0, 3) of length 4:
        (gb.At(3, 0).isPartOfChain) &&
        (gb.At(3, 1).isPartOfChain) &&
        (gb.At(3, 2).isPartOfChain) &&
        (gb.At(3, 3).isPartOfChain)
    ));
    CHECK(( // Horizontal chain at (4, 0) of length 4:
        (gb.At(0, 4).isPartOfChain) &&
        (gb.At(1, 4).isPartOfChain) &&
        (gb.At(2, 4).isPartOfChain) &&
        (gb.At(3, 4).isPartOfChain)
    ));
  }

  SECTION("Chains of length 5 are detected")
  {
    CHECK(( // Vertical chain at (1, 5) of length 5:
        (gb.At(5, 1).isPartOfChain) &&
        (gb.At(5, 2).isPartOfChain) &&
        (gb.At(5, 3).isPartOfChain) &&
        (gb.At(5, 4).isPartOfChain) &&
        (gb.At(5, 5).isPartOfChain)
    ));
  }

  // Occasionally it is possible to score a chain of length greater than 5.
  // Checks whether such a long chain is found:
  SECTION("Arbitrarily long chains are also detected")
  {
    CHECK(( // The chain of fours going from top to bottom of the test board:
        (gb.At(4, 0).isPartOfChain) &&
        (gb.At(4, 1).isPartOfChain) &&
        (gb.At(4, 2).isPartOfChain) &&
        (gb.At(4, 3).isPartOfChain) &&
        (gb.At(4, 4).isPartOfChain) &&
        (gb.At(4, 5).isPartOfChain) &&
        (gb.At(4, 6).isPartOfChain) &&
        (gb.At(4, 7).isPartOfChain)
    ));
  }

  SECTION("Diagonal chains are ignored")
  {
    CHECK_FALSE((
        (gb.At(1, 5).isPartOfChain) ||
        (gb.At(2, 6).isPartOfChain) ||
        (gb.At(3, 7).isPartOfChain)
    ));
  }

  SECTION("None of the fields that do not constitute a chain are marked")
  {
    CHECK_FALSE((
        (gb.At(1, 1).isPartOfChain) ||
        (gb.At(2, 1).isPartOfChain) ||
        (gb.At(6, 1).isPartOfChain) ||
        (gb.At(1, 2).isPartOfChain) ||
        (gb.At(2, 2).isPartOfChain) ||
        (gb.At(6, 2).isPartOfChain) ||
        (gb.At(0, 3).isPartOfChain) ||
        (gb.At(1, 3).isPartOfChain) ||
        (gb.At(2, 3).isPartOfChain) ||
        (gb.At(6, 3).isPartOfChain) ||
        (gb.At(7, 3).isPartOfChain) ||
        (gb.At(6, 4).isPartOfChain) ||
        (gb.At(7, 4).isPartOfChain) ||
        (gb.At(1, 5).isPartOfChain) ||
        (gb.At(2, 5).isPartOfChain) ||
        (gb.At(3, 5).isPartOfChain) ||
        (gb.At(6, 5).isPartOfChain) ||
        (gb.At(1, 6).isPartOfChain) ||
        (gb.At(2, 6).isPartOfChain) ||
        (gb.At(3, 6).isPartOfChain) ||
        (gb.At(5, 6).isPartOfChain) ||
        (gb.At(6, 6).isPartOfChain) ||
        (gb.At(3, 7).isPartOfChain)
    ));
  }
}
