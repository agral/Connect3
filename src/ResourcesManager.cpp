#include "ResourcesManager.hpp"

bool ResourcesManager::LoadResources(SDL_Renderer* renderer)
{
  bool successFlag = true;

  successFlag &= txBgIntro.LoadFromFile("./res/bg_intro.png", renderer);
  successFlag &= txBgMainMenu.LoadFromFile("./res/bg_mainmenu.png", renderer);
  successFlag &= txHalo.LoadFromFile("./res/halo.png", renderer);
  successFlag &= txLogo.LoadFromFile("./res/logo.png", renderer);
  successFlag &= txThreeRed.LoadFromFile("./res/three_red.png", renderer);
  successFlag &= spBtnExit.LoadFromFile("./res/spritesheet_btn_exit.png", renderer);
  successFlag &= spBtnTimeTrial.LoadFromFile("./res/spritesheet_btn_timetrial.png", renderer);
  successFlag &= spOrbs.LoadFromFile("./res/spritesheet_orbs.png", renderer);
  successFlag &= spBoard.LoadFromFile("./res/board_border.png", renderer);
  successFlag &= spProgressBar.LoadFromFile("./res/spritesheet_bars.png", renderer);

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
}

ResourcesManager resMgr;
