#ifndef GEM_HPP
#define GEM_HPP

struct Gem
{
 public:
  Gem(int color = 0, double posX = 0.0, double posY = 0.0);

 public:
  int color;
  double posX;
  double posY;
  bool isPartOfChain;
};

#endif // GEM_HPP
