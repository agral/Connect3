#include "Engine.hpp"
#include "Timer.hpp"
#include "../ResourcesManager.hpp"
#include "../state/GameStateMaster.hpp"

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
  Timer fpsTimer;
  Timer fpsCapTimer;
  int countedFrames = 0;

  fpsTimer.Start();

  while (state::currentStateId != state::STATE_EXIT)
  {
    fpsCapTimer.Start();

    // --- Processes the input from the user: ---
    state::currentState->ProcessInput();

    // --- Processes the game logic: ---
    state::currentState->Logic();

    // Changes the state if requested:
    state::ChangeState();

    // Calculates the overall average FPS:
    double averageFps = countedFrames / (fpsTimer.Ticks() / 1000.0 );
    if (averageFps > 2000000)
    {
      averageFps = 0;
    }

    // --- Renders the scene on a black background: ---
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
    state::currentState->Render();
    SDL_RenderPresent(renderer);

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

} // namespace gse
