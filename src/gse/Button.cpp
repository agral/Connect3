#include "Button.hpp"

#include <iostream>

namespace gse
{

enum class ButtonState
{
  MOUSEOUT,
  MOUSEOVER,
  CLICKED,
  RELEASED,
};

Button::Button(int w, int h, Texture& s) :
  posX(0),
  posY(0),
  width(w),
  height(h),
  sprite(s),
  state(ButtonState::MOUSEOUT)
{
  clips[0] = { 0, 0, w, h };
  clips[1] = { 0, h, w, h };
  clips[2] = { 0, 2 * h, w, h};
  clips[3] = { 0, 3 * h, w, h};
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
        state = ButtonState::CLICKED;
      }
      else if (event.type == SDL_MOUSEBUTTONUP)
      {
        state = ButtonState::RELEASED;
      }
      else if (event.type == SDL_MOUSEMOTION)
      {
        state = ButtonState::MOUSEOVER;
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
  std::cout << "Rendering Button at ("<< posX << ", " << posY << "), state=";
  if (state == ButtonState::MOUSEOUT)
  {
    sprite.Render(posX, posY, &clips[0]);
    std::cout << "MOUSEOUT" << std::endl;
  }
  else if (state == ButtonState::MOUSEOVER)
  {
    sprite.Render(posX, posY, &clips[1]);
    std::cout << "MOUSEOVER" << std::endl;
  }
  else if (state == ButtonState::CLICKED)
  {
    sprite.Render(posX, posY, &clips[2]);
    std::cout << "CLICKED" << std::endl;
  }
  else
  {
    sprite.Render(posX, posY, &clips[3]);
    std::cout << "RELEASED" << std::endl;
  }
}

} // namespace gse
