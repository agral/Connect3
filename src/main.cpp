#include <iostream>

#include "global/globals.hpp"
#include "gse/Engine.hpp"
#include "ResourcesManager.hpp"
#include "state/GameStateMaster.hpp"

int main(int, char **)
{
  gse::Engine engine;
  if (!engine.Init(global::SCREEN_WIDTH, global::SCREEN_HEIGHT,
      global::TARGET_FPS, global::WINDOW_TITLE))
  {
    std::cerr << "Gral's Simple Engine failed to initialize. Aborting." << std::endl;
    exit(1);
  }
  std::cout << "Engine initialized itself successfully." << std::endl;

  if (!resMgr.TryLocateRootPath())
  {
    std::cerr << "Critical: Resource manager can not locate the resources directory." << std::endl;
    std::cerr << "Please make sure that the program is run from its own directory" << std::endl;
    std::cerr << "($(pwd) should contain Connect3 directory)." << std::endl;
    exit(1);
  }
  else
  {
    std::cout << "Res root path: " << resMgr.resRootPath << std::endl;
  }

  if (!resMgr.LoadResources(engine.Renderer()))
  {
    std::cerr << "Warning: Some resources failed to load." << std::endl;
  }

  state::nextStateId = state::STATE_INTRO;
  state::ChangeState();

  std::cout << "Starting the engine's main loop..." << std::endl;
  engine.StartMainLoop();

  std::cout << "Engine's main loop has been terminated." << std::endl;
  resMgr.FreeResources();
  engine.Close();

  return 0;
}
