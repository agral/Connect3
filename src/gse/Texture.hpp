#ifndef GSE_TEXTURE_HPP
#define GSE_TEXTURE_HPP

#include <SDL2/SDL.h>

namespace gse
{

class Texture
{
 public:
  Texture();
  ~Texture();
  bool LoadFromFile(const char* path, SDL_Renderer* renderer);
  void Free();
  void SetBlendMode(SDL_BlendMode blendMode);
  void SetAlpha(Uint8 alpha);
  void Render(int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0,
      SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);


  int Width() const { return width; }
  int Height() const { return height; }

 private:
  SDL_Texture *texture;
  SDL_Renderer *renderer;
  int width;
  int height;
};

} // namespace gse

#endif // GSE_TEXTURE_HPP
