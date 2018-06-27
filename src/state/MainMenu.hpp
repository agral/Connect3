#ifndef STATE_MAINMENU_HPP
#define STATE_MAINMENU_HPP

#include "GameState.hpp"
#include "../ResourcesManager.hpp"

namespace state
{

class MainMenu : public GameState
{
 public:
  void ProcessInput();
  void Logic();
  void Render();
 private:
};

} // namespace state

#endif // STATE_MAINMENU_HPP
