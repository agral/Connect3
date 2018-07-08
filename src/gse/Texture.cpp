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

bool Texture::LoadFromFile(std::string path, SDL_Renderer* r)
{
  const char* cpath = path.c_str();
  // Deallocates previous texture (if applicable):
  Free();

  if (r == nullptr)
  {
    std::cerr << "Error: Can not create a texture without a dedicated renderer." << std::endl;
    return false;
  }
  renderer = r;

  SDL_Surface* surface = IMG_Load(cpath);
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
  else
  {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  }
  width = surface->w;
  height = surface->h;

  SDL_FreeSurface(surface);
  return (texture != nullptr);
}

bool Texture::RenderFromTtf(TTF_Font* font, const std::string& text, SDL_Color textColor, SDL_Renderer* r)
{
  // Deallocates previous texture (if applicable):
  Free();

  if (r == nullptr)
  {
    std::cerr << "Error: Can not create a TTF texture without a dedicated renderer." << std::endl;
    return false;
  }
  renderer = r;

  // Renders the text on plain old SDL_Surface using TTF submodule:
  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
  if (surface == nullptr)
  {
    std::cerr << "Error: unable to render text from TTF file." << std::endl;
    std::cerr << "SDL_ttf error: " << TTF_GetError() << std::endl;
    return false;
  }

  texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == nullptr)
  {
    std::cerr << "Error: unable to create texture from a TTF-rendered text." << std::endl;
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

void Texture::SetBlendMode(SDL_BlendMode blendMode)
{
  SDL_SetTextureBlendMode(texture, blendMode);
}

void Texture::SetAlpha(Uint8 alpha)
{
  SDL_SetTextureAlphaMod(texture, alpha);
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
