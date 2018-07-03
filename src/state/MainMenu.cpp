#include "MainMenu.hpp"
#include "../global/globals.hpp"

#include <SDL2/SDL.h>

namespace state
{

MainMenu::MainMenu()
{
  btnTimeTrialGeometry.x = (global::SCREEN_WIDTH - resMgr.txBtnTimeTrial.Width()) / 2;
  btnTimeTrialGeometry.y = 200;
  btnTimeTrialGeometry.w = resMgr.txBtnTimeTrial.Width();
  btnTimeTrialGeometry.h = resMgr.txBtnTimeTrial.Height();
  isBtnTimeTrialHovered = false;
}

void MainMenu::ProcessInput()
{
  SDL_Event event;
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  if ((mouseX >= btnTimeTrialGeometry.x) && (mouseX < btnTimeTrialGeometry.x + btnTimeTrialGeometry.w) &&
      (mouseY >= btnTimeTrialGeometry.y) && (mouseY < btnTimeTrialGeometry.y + btnTimeTrialGeometry.h))
  {
    isBtnTimeTrialHovered = true;
  }
  else
  {
    isBtnTimeTrialHovered = false;
  }

  while(SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      SetNextStateId(STATE_EXIT);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      if (isBtnTimeTrialHovered)
      {
        SetNextStateId(STATE_EXIT);
      }
    }
  }
}

void MainMenu::Logic(double millisecondsElapsed)
{
}

void MainMenu::Render()
{
  resMgr.txBgMainMenu.Render(0, 0);
  resMgr.txLogo.Render((global::SCREEN_WIDTH - resMgr.txLogo.Width()) / 2, 0);

  if (isBtnTimeTrialHovered)
  {
    resMgr.txBtnTimeTrialHighlight.Render(btnTimeTrialGeometry.x, btnTimeTrialGeometry.y);
  }
  else
  {
    resMgr.txBtnTimeTrial.Render(btnTimeTrialGeometry.x, btnTimeTrialGeometry.y);
  }
}

} // namespace state
