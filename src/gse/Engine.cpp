#include "Engine.hpp"
#include "Timer.hpp"
#include "../ResourcesManager.hpp"

#include <iostream>
#include <limits>
#include <SDL2/SDL_image.h>

namespace gse
{

Engine::Engine() :
  isInitialized(false),
  isClosing(false),
  targetFps(0),
  millisecondsPerFrame(std::numeric_limits<int>::max())
{
}

bool Engine::Init(int windowWidth, int windowHeight, int fps, const char* windowTitle)
{
  if (!isInitialized)
  {
    std::cout << "Initializing the SDL2 library." << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cerr << "Critical: SDL failed to initialize." << std::endl;
      std::cerr << "SDL error: " << SDL_GetError() << std::endl;
      return false;
    }

    std::cout << "Setting linear texture filtering" << std::endl;
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
      std::cerr << "Warning: Could not enable linear texture filtering.";
    }

    std::cout << "Creating game window." << std::endl;
    window = SDL_CreateWindow(
        windowTitle,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        windowWidth, windowHeight, SDL_WINDOW_SHOWN
    );
    if (window == nullptr)
    {
      std::cerr << "Critical: SDL window could not be created." << std::endl;
      std::cerr << "SDL error: " << SDL_GetError() << std::endl;
      return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if (renderer == nullptr)
    {
      std::cerr << "Error: Could not create a vsynced renderer." << std::endl;
      std::cerr << "SDL error: " << SDL_GetError() << std::endl;
      return false;
    }

    targetFps = fps;
    millisecondsPerFrame = 1000 / targetFps;

    std::cout << "Initializing the IMG module" << std::endl;
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
      std::cerr << "SDL_Image module could not initialize." << std::endl;
      std::cerr << "SDL_image error: " << IMG_GetError() << std::endl;
      return false;
    }

    screenSurface = SDL_GetWindowSurface(window);
  }

  isInitialized = true;
  return true;
}

void Engine::StartMainLoop()
{
  SDL_Event sdlEvent;
  bool quitFlag = false;

  Timer fpsTimer;
  Timer fpsCapTimer;
  int countedFrames = 0;

  fpsTimer.Start();

  while (!(quitFlag or isClosing))
  {
    fpsCapTimer.Start();

    // --- Processes the input from the user: ---
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
      if (sdlEvent.type == SDL_QUIT)
      {
        quitFlag = true;
      }
      else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
      {
        int x, y;
        Uint32 buttonState = SDL_GetMouseState(&x, &y);

        if (buttonState & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
          std::cout << "LMB Down (" << x << ", " << y << ")" << std::endl;
        }
      }
    }

    // --- Processes the game logic: ---
    double averageFps = countedFrames / (fpsTimer.Ticks() / 1000.0 );
    if (averageFps > 2000000)
    {
      averageFps = 0;
    }

    // --- Renders everything: ---
    DrawScene();

    // --- Caps the frame rate at target frames per second value: ---
    countedFrames += 1;
    int frameTicks = fpsCapTimer.Ticks();
    if (frameTicks < millisecondsPerFrame)
    {
      SDL_Delay(millisecondsPerFrame - frameTicks);
    }

    std::cout << "Render(): Frame #" << countedFrames << ", average fps = " << averageFps << std::endl;
  }
}

void Engine::Close()
{
  if (!isClosing)
  {
    std::cout << "Destroying GSE's renderer." << std::endl;
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    std::cout << "Destroying the game window." << std::endl;
    SDL_DestroyWindow(window);
    window = nullptr;

    std::cout << "Quitting the SDL." << std::endl;
    IMG_Quit();
    SDL_Quit();
  }
}

SDL_Renderer* Engine::Renderer() const
{
  return renderer;
}

// Private methods' implementation:
void Engine::DrawScene()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
  SDL_RenderClear(renderer);

  resMgr.txBgIntro.Render(0, 0);

  SDL_RenderPresent(renderer);
}

} // namespace gse
