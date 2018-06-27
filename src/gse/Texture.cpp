#include "Texture.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>

namespace gse
{

Texture::Texture() :
  texture(nullptr),
  renderer(nullptr),
  width(0),
  height(0)
{
}

Texture::~Texture()
{
  Free();
}

bool Texture::LoadFromFile(const char* path, SDL_Renderer* r)
{
  // Deallocates previous texture (if applicable):
  if (texture != nullptr)
  {
    Free();
  }

  if (r == nullptr)
  {
    std::cerr << "Error: Can not create a texture without a dedicated renderer." << std::endl;
    return false;
  }
  renderer = r;

  SDL_Surface* surface = IMG_Load(path);
  if (surface == nullptr)
  {
    std::cerr << "Error: image [" << path << "] could not be loaded." << std::endl;
    std::cerr << "SDL error: " << SDL_GetError() << std::endl;
    return false;
  }

  texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == nullptr)
  {
    std::cerr << "Error: unable to create texture from surface: [" << path << "]." << std::endl;
    std::cerr << "SDL error: " << SDL_GetError() << std::endl;
    return false;
  }
  width = surface->w;
  height = surface->h;

  SDL_FreeSurface(surface);
  return (texture != nullptr);
}

void Texture::Free()
{
  if (texture != nullptr)
  {
    SDL_DestroyTexture(texture);
    texture = nullptr;
    width = 0;
    height = 0;
  }
}

void Texture::Render(int x, int y, SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
  SDL_Rect targetBox = {x, y, width, height};

  if (clip != nullptr)
  {
    targetBox.w = clip->w;
    targetBox.h = clip->h;
  }

  SDL_RenderCopyEx(renderer, texture, clip, &targetBox, angle, center, flip);
}

} // namespace gse
