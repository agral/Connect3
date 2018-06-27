#ifndef STATE_GAMESTATEMASTER_HPP
#define STATE_GAMESTATEMASTER_HPP

#include "GameState.hpp"
#include "Intro.hpp"
#include "MainMenu.hpp"

namespace state
{

extern enum GameStates;
extern int currentStateId;
extern int nextStateId;
extern GameState* currentState;

void SetNextStateId(int newNextStateId);
void ChangeState();

} // namespace state

#endif // STATE_GAMESTATEMASTER_HPP
