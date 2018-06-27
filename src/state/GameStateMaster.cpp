#include "GameStateMaster.hpp"

namespace state
{

int nextStateId = STATE_NONE;
int currentStateId = STATE_NONE;
GameState* currentState = nullptr;

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
    if (nextStateId != STATE_EXIT)
    {
      delete currentState;
    }

    if (nextStateId == STATE_INTRO)
    {
      currentState = new Intro();
    }
    else if (nextStateId == STATE_MAINMENU)
    {
      currentState = new MainMenu();
    }

    currentStateId = nextStateId;
    nextStateId = STATE_NONE;
  }
}

} // namespace state

