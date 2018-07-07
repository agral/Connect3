#include "MainMenu.hpp"
#include "../global/globals.hpp"

#include <SDL2/SDL.h>
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

void MainMenu::Logic(gse::GameTimeData)
{
}

void MainMenu::Render()
{
  resMgr.txBgMainMenu.Render(0, 0);
  resMgr.txLogo.Render((global::SCREEN_WIDTH - resMgr.txLogo.Width()) / 2, 0);

  btnTimeTrial->Render();
  btnExit->Render();
}

} // namespace state
