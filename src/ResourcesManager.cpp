#include "ResourcesManager.hpp"

#include <vector>
#include <sys/stat.h>

inline bool Exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

bool ResourcesManager::TryLocateRootPath()
{
  std::vector<std::string> possibleResRootPaths = {
    "./res/",
    "../res/",
    "../../res/"
  };

  bool foundResRootPath = false;
  for (auto it = possibleResRootPaths.begin(); ((it != possibleResRootPaths.end()) && (!foundResRootPath)); ++it)
  {
    // Is there a `logo.png` file in a candidate path?:
    if (Exists(*it + "logo.png"))
    {
      resRootPath = *it;
      foundResRootPath = true;
    }
  }

  return foundResRootPath;
}

bool ResourcesManager::LoadResources(SDL_Renderer* renderer)
{
  bool successFlag = true;

  successFlag &= txBgIntro.LoadFromFile(resRootPath + "bg_intro.png", renderer);
  successFlag &= txBgMainMenu.LoadFromFile(resRootPath + "bg_mainmenu.png", renderer);
  successFlag &= txHalo.LoadFromFile(resRootPath + "halo.png", renderer);
  successFlag &= txLogo.LoadFromFile(resRootPath + "logo.png", renderer);
  successFlag &= txThreeRed.LoadFromFile(resRootPath + "three_red.png", renderer);
  successFlag &= spBtnExit.LoadFromFile(resRootPath + "spritesheet_btn_exit.png", renderer);
  successFlag &= spBtnTimeTrial.LoadFromFile(resRootPath + "spritesheet_btn_timetrial.png", renderer);
  successFlag &= spOrbs.LoadFromFile(resRootPath + "spritesheet_orbs.png", renderer);
  successFlag &= spBoard.LoadFromFile(resRootPath + "board_border.png", renderer);
  successFlag &= spProgressBar.LoadFromFile(resRootPath + "spritesheet_bars.png", renderer);
  successFlag &= spBtnIngameExit.LoadFromFile(resRootPath + "spritesheet_btn_ingame_exit.png", renderer);

  return successFlag;
}

void ResourcesManager::FreeResources()
{
  txBgIntro.Free();
  txBgMainMenu.Free();
  txHalo.Free();
  txLogo.Free();
  txThreeRed.Free();
  spBtnExit.Free();
  spBtnTimeTrial.Free();
  spOrbs.Free();
  spBoard.Free();
  spProgressBar.Free();
  spBtnIngameExit.Free();
}

ResourcesManager resMgr;
