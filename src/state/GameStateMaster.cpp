#include "GameStateMaster.hpp"

namespace state
{

int nextStateId = STATE_NONE;
int currentStateId = STATE_NONE;
std::unique_ptr<GameState> currentState = nullptr;

void SetNextStateId(int newNextStateId)
{
  if (nextStateId != STATE_EXIT)
  {
    nextStateId = newNextStateId;
  }
}

void ChangeState()
{
  // nextStateId set to anything other than STATE_NONE means that the state has to be changed:
  if (nextStateId != STATE_NONE)
  {
    if (nextStateId == STATE_INTRO)
    {
      std::unique_ptr<Intro> intro = std::make_unique<Intro>();
      currentState = std::move(intro);
    }
    else if (nextStateId == STATE_MAINMENU)
    {
      std::unique_ptr<MainMenu> mainMenu = std::make_unique<MainMenu>();
      currentState = std::move(mainMenu);
    }
    else if (nextStateId == STATE_TIMETRIAL)
    {
      std::unique_ptr<TimeTrial> timeTrial = std::make_unique<TimeTrial>();
      currentState = std::move(timeTrial);
    }

    currentStateId = nextStateId;
    nextStateId = STATE_NONE;
  }
}

} // namespace state

