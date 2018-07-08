#include "globals.hpp"

namespace global
{

const char* WINDOW_TITLE = "Connect3";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TARGET_FPS = 60;
const int GAMEBOARD_HEIGHT = 8;
const int GAMEBOARD_WIDTH = 8;
const int ORBS_TYPES_COUNT = 5;
const int ORB_SIZE = 64;
const double gravityConstant = 0.001; // pixels per millisecond-squared
const double ROUND_TIME_IN_MILLISECONDS = 60000.0; // 60000 milliseconds equals one minute.

const SDL_Color CL_INGAME_SCORE = SDL_Color{240, 35, 0, 255};
const SDL_Color CL_INGAME_SCORE_BG = SDL_Color{50, 10, 0, 255};
const SDL_Color CL_INGAME_SCORE_CAPTION = SDL_Color{50, 50, 240, 255};
const SDL_Color CL_INGAME_GAMEOVER = SDL_Color{250, 20, 50, 192};

} // namespace global
