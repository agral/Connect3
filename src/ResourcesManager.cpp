#include "ResourcesManager.hpp"

bool ResourcesManager::LoadResources(SDL_Renderer* renderer)
{
  bool successFlag = true;

  successFlag &= txBgIntro.LoadFromFile( "./res/bg_intro.png", renderer);
  successFlag &= txBgMainMenu.LoadFromFile( "./res/bg_mainmenu.png", renderer);
  successFlag &= txLogo.LoadFromFile( "./res/logo.png", renderer);

  return successFlag;
}

void ResourcesManager::FreeResources()
{
  txBgIntro.Free();
  txBgMainMenu.Free();
  txLogo.Free();
}

ResourcesManager resMgr;
