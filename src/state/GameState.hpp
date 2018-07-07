#ifndef STATE_GAMESTATE_HPP
#define STATE_GAMESTATE_HPP

#include "../gse/GameTimeData.hpp"

namespace state
{

class GameState
{
 public:
  virtual void ProcessInput() = 0;
  virtual void Logic(gse::GameTimeData td) = 0;
  virtual void Render() = 0;
  virtual ~GameState() {};
};

enum GameStates
{
  STATE_NONE,
  STATE_INTRO,
  STATE_MAINMENU,
  STATE_TIMETRIAL,
  STATE_EXIT
};

extern int currentStateId;
extern int nextStateId;
extern GameState* currentState;

void SetNextStateId(int newNextStateId);
void ChangeState();

} // namespace state

#endif // STATE_GAMESTATE_HPP
