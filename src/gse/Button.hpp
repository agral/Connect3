#ifndef GSE_BUTTON_HPP
#define GSE_BUTTON_HPP

#include "Texture.hpp"
#include <SDL2/SDL.h>

namespace gse
{

enum class ButtonState;

class Button
{
 public:
  Button(int w, int h, Texture& s);
  void SetPosition(int x, int y);

  void ProcessInput(SDL_Event& event);
  void Render();
  void SetOnClick(void (*ptrToOnClickLogic)());

 private:
  int posX;
  int posY;
  int width;
  int height;
  Texture& sprite;
  ButtonState state;
  SDL_Rect clips[3];
  void (*onClick)();
};



} // namespace gse

#endif // GSE_BUTTON_HPP
