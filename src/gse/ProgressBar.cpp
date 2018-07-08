#include "ProgressBar.hpp"

#include <iostream>

namespace gse
{

ProgressBar::ProgressBar(Texture& spritesheet, int totalWidthPx, int capWidthPx, int color) :
  spritesheet(spritesheet),
  totalWidth(totalWidthPx),
  capWidth(capWidthPx),
  capRelativeWidth(static_cast<double>(capWidthPx) / totalWidthPx),
  middleWidth(totalWidthPx - 2 * capWidthPx),
  spriteMiddleWidth(spritesheet.Width() - 2 * capWidthPx),
  spriteRelativeMiddleWidth(static_cast<double>(spriteMiddleWidth) / totalWidthPx),
  colorFg(color),
  normalizedProgress(0.0),
  posX(0),
  posY(0)
{
  int singleBarHeight = spritesheet.Height() / ProgressBarColors::COUNT;
  for (int y = 0; y < ProgressBarColors::COUNT; ++y)
  {
    clips[y][0] = {0, y * singleBarHeight, capWidth, singleBarHeight}; // left cap
    clips[y][1] = {capWidth, y * singleBarHeight, spriteMiddleWidth, singleBarHeight}; // middle part
    clips[y][2] = {capWidth + spriteMiddleWidth, y * singleBarHeight, capWidth, singleBarHeight}; // right cap
  }
}

void ProgressBar::SetPosition(int newPosX, int newPosY)
{
  posX = newPosX;
  posY = newPosY;
}

void ProgressBar::SetNormalizedProgress(double newNormalizedProgress)
{
  normalizedProgress = newNormalizedProgress;
}

void ProgressBar::Render()
{
  // Renders the colored progressbar:
  // Starts with the left part, cropped if necessary:
  SDL_Rect clipL = clips[colorFg][0];
  clipL.w *= std::max(0.0, std::min(1.0, normalizedProgress / capRelativeWidth));
  spritesheet.Render(posX, posY, &clipL);

  // Then iteratively draws little seamless parts of the middle bar, cropping them if necessary:
  for (int x = 0; x < middleWidth / spriteMiddleWidth; ++x)
  {
    SDL_Rect clipM = clips[colorFg][1];
    clipM.w *= std::max(0.0, std::min(1.0,
        (normalizedProgress - capRelativeWidth - x * spriteRelativeMiddleWidth) / spriteRelativeMiddleWidth
    ));
    spritesheet.Render(posX + capWidth + x * spriteMiddleWidth, posY, &clipM);
  }

  // Then draws the right part, cropped if necessary:
  SDL_Rect clipR = clips[colorFg][0];
  clipR.w *= std::max(0.0, std::min(1.0, (normalizedProgress + capRelativeWidth - 1) / capRelativeWidth));
  spritesheet.Render(posX + totalWidth - capWidth, posY, &clipR);

  // Renders the bar border:
  spritesheet.Render(posX, posY, &clips[ProgressBarColors::BORDER][0]);
  for (int x = 0; x < middleWidth / spriteMiddleWidth; ++x)
  {
    spritesheet.Render(posX + capWidth + x * spriteMiddleWidth, posY, &clips[ProgressBarColors::BORDER][1]);
  }
  spritesheet.Render(posX + totalWidth - capWidth, posY, &clips[ProgressBarColors::BORDER][2]);
}

} // namespace gse
