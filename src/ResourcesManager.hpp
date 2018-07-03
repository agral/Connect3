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
  gse::Texture txLogo;
  gse::Texture spBtnTimeTrial;
};

extern ResourcesManager resMgr;

#endif // RESOURCESMANAGER_HPP
