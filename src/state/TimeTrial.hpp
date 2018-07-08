#ifndef STATE_TIMETRIAL_HPP
#define STATE_TIMETRIAL_HPP

#include "GameState.hpp"
#include "../ResourcesManager.hpp"
#include "../GameBoard.hpp"
#include "../gse/ProgressBar.hpp"
#include "../gse/Button.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <string>

namespace state
{

enum class GamePhase
{
  NONE,
  IDLE,
  SWAPPING,
  EXPLODING,
  FALLING,
  OVER,
};

static std::map<GamePhase, std::string> GamePhaseNames = {
  {GamePhase::NONE, "NONE"},
  {GamePhase::IDLE, "IDLE"},
  {GamePhase::SWAPPING, "SWAPPING"},
  {GamePhase::EXPLODING, "EXPLODING"},
  {GamePhase::FALLING, "FALLING"},
  {GamePhase::OVER, "OVER"},
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
  SDL_Rect boardClips[10];
  SDL_Rect boardGeometry;
  GameBoard board;
  GamePhase phase;
  GamePhase nextPhase;
  void DrawBoard();
  void DrawBoardBorder();
  void CheckAndSwap(int gemAIndexX, int gemAIndexY, int gemBIndexX, int gemBIndexY);

  bool isDragging;
  int draggedGemXIndex, draggedGemYIndex;
  int otherGemXIndex, otherGemYIndex;
  int dragOriginX, dragOriginY;
  int dragDistanceX, dragDistanceY;
  int filteredDragDistanceX, filteredDragDistanceY;
  int selectedGemXIndex, selectedGemYIndex;
  Uint8 explodingAlpha;
  double phaseBirth;
  double remainingIdleTime;

  std::unique_ptr<gse::ProgressBar> pbTime;
  std::unique_ptr<gse::Button> btnExit;
};

} // namespace state

#endif // STATE_TIMETRIAL_HPP
