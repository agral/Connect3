#include "Gem.hpp"

Gem::Gem(int color, double posX, double posY) :
  color(color),
  posX(posX),
  posY(posY),
  velocityY(0),
  isPartOfChain(false),
  isFalling(false)
{
}
