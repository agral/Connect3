#include <iostream>

#include "global/globals.hpp"
#include "gse/Engine.hpp"
#include "ResourcesManager.hpp"

int main()
{
  gse::Engine engine;
  if (!engine.Init(global::SCREEN_WIDTH, global::SCREEN_HEIGHT,
      global::TARGET_FPS, global::WINDOW_TITLE))
  {
    std::cerr << "Gral's Simple Engine failed to initialize. Aborting." << std::endl;
    exit(1);
  }
  std::cout << "Engine initialized itself successfully." << std::endl;

  if (!resMgr.LoadResources(engine.Renderer()))
  {
    std::cerr << "Warning: Some resources failed to load." << std::endl;
  }

  std::cout << "Starting the engine's main loop..." << std::endl;
  engine.StartMainLoop();

  std::cout << "Engine's main loop has been terminated." << std::endl;
  resMgr.FreeResources();
  engine.Close();

  return 0;
}
