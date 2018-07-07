#ifndef STATE_TIMETRIAL_HPP
#define STATE_TIMETRIAL_HPP

#include "GameState.hpp"
#include "../ResourcesManager.hpp"
#include "../GameBoard.hpp"

#include <SDL2/SDL.h>

namespace state
{

enum class GamePhase
{
  IDLE,
  SWAPPING,
  EXPLODING,
  FALLING,
  OVER,
};

class TimeTrial : public GameState
{
 public:
  TimeTrial();
  void ProcessInput();
  void Logic(double millisecondsElapsed);
  void Render();
 private:
  SDL_Rect orbClips[5];
  GameBoard board;
  void DrawBoard(int posX, int posY);
};

} // namespace state

#endif // STATE_TIMETRIAL_HPP
