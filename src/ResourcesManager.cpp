#include "ResourcesManager.hpp"
#include "global/globals.hpp"

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

  fIngameScore = TTF_OpenFont((resRootPath + "font/ManualDisplay.ttf").c_str(), 64);
  successFlag &= (fIngameScore != nullptr);
  fIngameScoreCaption = TTF_OpenFont((resRootPath + "font/Bitcell.ttf").c_str(), 36);
  successFlag &= (fIngameScoreCaption != nullptr);
  fGameOver = TTF_OpenFont((resRootPath + "font/Bitcell.ttf").c_str(), 72);
  successFlag &= (fGameOver != nullptr);

  successFlag &= txIngameScore.RenderFromTtf(fIngameScore, "00000", global::CL_INGAME_SCORE, renderer);
  successFlag &= txIngameScoreBg.RenderFromTtf(fIngameScore, "88888", global::CL_INGAME_SCORE_BG, renderer);
  successFlag &= txIngameScoreCaption.RenderFromTtf(fIngameScoreCaption, "YOUR SCORE",
      global::CL_INGAME_SCORE_CAPTION, renderer);
  successFlag &= txGameOver.RenderFromTtf(fGameOver, "GAME OVER", global::CL_INGAME_GAMEOVER, renderer);

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

  TTF_CloseFont(fIngameScore);
  TTF_CloseFont(fIngameScoreCaption);

  txIngameScore.Free();
  txIngameScoreBg.Free();
  txIngameScoreCaption.Free();
}

ResourcesManager resMgr;
