#ifndef RESOURCESMANAGER_HPP
#define RESOURCESMANAGER_HPP

#include "gse/Texture.hpp"
#include <SDL2/SDL.h>

class ResourcesManager
{
 public:
  bool LoadResources(SDL_Renderer* renderer);
  void FreeResources();

 public:
  gse::Texture txBgIntro;
  gse::Texture txBgMainMenu;
  gse::Texture txHalo;
  gse::Texture txLogo;
  gse::Texture spBtnExit;
  gse::Texture spBtnTimeTrial;
  gse::Texture spOrbs;
};

extern ResourcesManager resMgr;

#endif // RESOURCESMANAGER_HPP
