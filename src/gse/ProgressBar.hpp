#ifndef GSE_PROGRESSBAR_HPP
#define GSE_PROGRESSBAR_HPP

#include "Texture.hpp"
#include <SDL2/SDL.h>
#include <map>

namespace gse
{

namespace ProgressBarColors
{

enum Colors
{
  BORDER,
  YELLOW,
  BLUE,
  GREEN,
  RED,
  COUNT
};

} // namespace ProgressBarColors

class ProgressBar
{
 public:
  ProgressBar(Texture& spritesheet, int totalWidthPx, int capWidthPx, int color = ProgressBarColors::YELLOW);
  void SetPosition(int newPosX, int newPosY);
  void SetNormalizedProgress(double newNormalizedProgress);
  void SetForegroundColor(int colorCode);
  void Render();

 private:
  Texture& spritesheet;
  int totalWidth;
  int capWidth;
  double capRelativeWidth;
  int middleWidth;
  int spriteMiddleWidth;
  double spriteRelativeMiddleWidth;
  int colorFg;
  double normalizedProgress;
  int posX;
  int posY;
  SDL_Rect clips[ProgressBarColors::COUNT][3];
};

} // namespace gse

#endif // GSE_PROGRESSBAR_HPP
