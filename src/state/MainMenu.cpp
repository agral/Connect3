#include "MainMenu.hpp"
#include "../global/globals.hpp"

#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

namespace state
{

void BtnTimeTrialOnClick()
{
  SetNextStateId(STATE_TIMETRIAL);
}

void BtnExitOnClick()
{
  SetNextStateId(STATE_EXIT);
}

MainMenu::MainMenu()
{
  logoGeometry = {(global::SCREEN_WIDTH - resMgr.txLogo.Width()) / 2, 0, resMgr.txLogo.Width(), resMgr.txLogo.Height()};
  threeGeometry = {logoGeometry.x + 262, 0, resMgr.txThreeRed.Width(), resMgr.txThreeRed.Height()};
  threeAlpha = 0;
  int buttonX = (global::SCREEN_WIDTH - 400) / 2;
  btnTimeTrial = std::make_unique<gse::Button>(400, 80, resMgr.spBtnTimeTrial);
  btnTimeTrial->SetPosition(buttonX, 200);
  btnTimeTrial->SetOnClick(&BtnTimeTrialOnClick);

  btnExit = std::make_unique<gse::Button>(400, 80, resMgr.spBtnExit);
  btnExit->SetPosition(buttonX, 500);
  btnExit->SetOnClick(&BtnExitOnClick);
}

void MainMenu::ProcessInput()
{
  SDL_Event event;
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  while(SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      SetNextStateId(STATE_EXIT);
    }

    btnTimeTrial->ProcessInput(event, mouseX, mouseY);
    btnExit->ProcessInput(event, mouseX, mouseY);
  }
}

void MainMenu::Logic(gse::GameTimeData td)
{
  threeAlpha = 128 * (1 + std::cos( 2 * M_PI * td.timeTotal / 1000 / 4));
}

void MainMenu::Render()
{
  resMgr.txBgMainMenu.Render(0, 0);
  resMgr.txLogo.Render(logoGeometry.x, logoGeometry.y);

  resMgr.txThreeRed.SetAlpha(threeAlpha);
  resMgr.txThreeRed.Render(threeGeometry.x, threeGeometry.y);

  btnTimeTrial->Render();
  btnExit->Render();
}

} // namespace state
