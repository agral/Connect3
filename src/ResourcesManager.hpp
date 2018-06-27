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
};

extern ResourcesManager resMgr;
