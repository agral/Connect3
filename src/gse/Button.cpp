#include "Button.hpp"

#include <iostream>

namespace gse
{

enum class ButtonState
{
  MOUSEOUT,
  MOUSEOVER,
  PUSHED,
};

Button::Button(int w, int h, Texture& s) :
  posX(0),
  posY(0),
  width(w),
  height(h),
  sprite(s),
  state(ButtonState::MOUSEOUT),
  onClick(nullptr)
{
  clips[0] = { 0, 0, w, h };
  clips[1] = { 0, h, w, h };
  clips[2] = { 0, 2 * h, w, h};
}

void Button::SetPosition(int x, int y)
{
  posX = x;
  posY = y;
}

void Button::ProcessInput(SDL_Event& event)
{
  if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
  {
    int x, y;
    SDL_GetMouseState(&x, &y);

    bool isInside = ((x >= posX) && (x < posX + width) && (y >= posY) && (y < posY + height));
    if (isInside)
    {
      if (event.type == SDL_MOUSEBUTTONDOWN)
      {
        state = ButtonState::PUSHED;
      }
      else if (event.type == SDL_MOUSEBUTTONUP)
      {
        state = ButtonState::MOUSEOVER;
        if (onClick != nullptr)
        {
          (*onClick)();
        }
        else
        {
          std::cout << "Button::onClick() - logic not implemented." << std::endl;
        }
      }
      else if (event.type == SDL_MOUSEMOTION)
      {
        if (state != ButtonState::PUSHED)
        {
          state = ButtonState::MOUSEOVER;
        }
      }
    }
    else
    {
      state = ButtonState::MOUSEOUT;
    }
  }
}

void Button::Render()
{
  if (state == ButtonState::MOUSEOUT)
  {
    sprite.Render(posX, posY, &clips[0]);
  }
  else if (state == ButtonState::MOUSEOVER)
  {
    sprite.Render(posX, posY, &clips[1]);
  }
  else if (state == ButtonState::PUSHED)
  {
    sprite.Render(posX, posY, &clips[2]);
  }
}

void Button::SetOnClick(void (*ptrToOnClickLogic)())
{
  onClick = ptrToOnClickLogic;
}

} // namespace gse
