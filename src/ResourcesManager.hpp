#ifndef RESOURCESMANAGER_HPP
#define RESOURCESMANAGER_HPP

#include "gse/Texture.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class ResourcesManager
{
 public:
  bool TryLocateRootPath();
  bool LoadResources(SDL_Renderer* renderer);
  void FreeResources();

 public:
  std::string resRootPath;
  gse::Texture txBgIntro;
  gse::Texture txBgMainMenu;
  gse::Texture txHalo;
  gse::Texture txLogo;
  gse::Texture txThreeRed;
  gse::Texture spBtnExit;
  gse::Texture spBtnTimeTrial;
  gse::Texture spOrbs;
  gse::Texture spBoard;
  gse::Texture spProgressBar;
  gse::Texture spBtnIngameExit;
  gse::Texture txIngameScore;
  gse::Texture txIngameScoreBg;
  gse::Texture txIngameScoreCaption;
  gse::Texture txGameOver;
  TTF_Font* fIngameScore;
  TTF_Font* fIngameScoreCaption;
  TTF_Font* fGameOver;

};

extern ResourcesManager resMgr;

#endif // RESOURCESMANAGER_HPP
