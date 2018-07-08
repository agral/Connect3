#ifndef GLOBAL_GLOBALS_HPP
#define GLOBAL_GLOBALS_HPP

#include <SDL2/SDL.h>

namespace global
{

extern const char* WINDOW_TITLE;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TARGET_FPS;
extern const int GAMEBOARD_HEIGHT;
extern const int GAMEBOARD_WIDTH;
extern const int ORBS_TYPES_COUNT;
extern const int ORB_SIZE;
extern const double gravityConstant;
extern const double ROUND_TIME_IN_MILLISECONDS;

extern const SDL_Color CL_INGAME_SCORE;
extern const SDL_Color CL_INGAME_SCORE_BG;
extern const SDL_Color CL_INGAME_SCORE_CAPTION;
extern const SDL_Color CL_INGAME_GAMEOVER;

} // namespace global


#endif // GLOBAL_GLOBALS_HPP
