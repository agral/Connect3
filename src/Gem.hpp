#ifndef GEM_HPP
#define GEM_HPP

struct Gem
{
 public:
  Gem(int color = 0);

 public:
  int color;
  bool isPartOfChain;
};

#endif // GEM_HPP
