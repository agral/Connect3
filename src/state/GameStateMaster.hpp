#ifndef STATE_GAMESTATEMASTER_HPP
#define STATE_GAMESTATEMASTER_HPP

#include "GameState.hpp"
#include "Intro.hpp"
#include "MainMenu.hpp"
#include "TimeTrial.hpp"
#include <memory>

namespace state
{

extern int currentStateId;
extern int nextStateId;
extern std::unique_ptr<GameState> currentState;

void SetNextStateId(int newNextStateId);
void ChangeState();

} // namespace state

#endif // STATE_GAMESTATEMASTER_HPP
