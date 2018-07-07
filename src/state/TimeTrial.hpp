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
  void Logic(gse::GameTimeData td);
  void Render();

 private:
  SDL_Rect orbClips[5];
  SDL_Rect boardGeometry;
  GameBoard board;
  GamePhase phase;
  void DrawBoard();

  bool isDragging;
  int draggedGemXIndex, draggedGemYIndex;
  int dragOriginX, dragOriginY;
  int dragDistanceX, dragDistanceY;
  int filteredDragDistanceX, filteredDragDistanceY;
};

} // namespace state

#endif // STATE_TIMETRIAL_HPP
