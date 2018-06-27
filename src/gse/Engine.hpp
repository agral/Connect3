#ifndef GSE_ENGINE_HPP
#define GSE_ENGINE_HPP

#include <SDL2/SDL.h>
#include "Texture.hpp"

namespace gse
{

class Engine
{
 public:
  Engine();

  bool Init(int windowWidth, int windowHeight, int fps = 60, const char* windowTitle = nullptr);
  void StartMainLoop();
  void Close();
  SDL_Renderer* Renderer() const;

  // The engine should not be copyable by copy constructor / assignment operator:
  Engine(const Engine& instance) = delete;
  Engine& operator=(const Engine& instance) = delete;

 private:
  void DrawScene();

  bool isInitialized;
  bool isClosing;
  int targetFps;
  int millisecondsPerFrame;

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Surface* screenSurface;
};

} // namespace gse

#endif // GSE_ENGINE_HPP
