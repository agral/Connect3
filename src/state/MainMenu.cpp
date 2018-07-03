#include "MainMenu.hpp"
#include "../global/globals.hpp"

#include <SDL2/SDL.h>
#include <iostream>

namespace state
{

void BtnTimeTrialOnClick()
{
  std::cout << "Entering the Time Trial game - not implemented yet." << std::endl;
}

MainMenu::MainMenu()
{
  btnTimeTrial = std::make_unique<gse::Button>(400, 80, resMgr.spBtnTimeTrial);
  btnTimeTrial->SetPosition((global::SCREEN_WIDTH - 400) / 2, 200);
  btnTimeTrial->SetOnClick(&BtnTimeTrialOnClick);
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
  }
}

void MainMenu::Logic(double millisecondsElapsed)
{
}

void MainMenu::Render()
{
  resMgr.txBgMainMenu.Render(0, 0);
  resMgr.txLogo.Render((global::SCREEN_WIDTH - resMgr.txLogo.Width()) / 2, 0);

  btnTimeTrial->Render();
}

} // namespace state
