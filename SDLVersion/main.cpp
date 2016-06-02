#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <SDL/SDL.h>

#include "Vipper.h"
#include "IRenderer.h"
#include "CLevel.h"
#include "CGame.h"
#include "CSDLRenderer.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

std::shared_ptr<BlockyFalls::CGame> game; 

void gameLoopTick() {
  game->update();
}

int main ( int argc, char **argv ) {

  auto renderer = std::make_shared<BlockyFalls::CSDLRenderer>();
  game = std::make_shared<BlockyFalls::CGame>();
  
  renderer->init( game );

  game->runGame( renderer );

#ifdef __EMSCRIPTEN__
  //  emscripten_request_fullscreen(0, 1);
  emscripten_set_main_loop( gameLoopTick, 30, 1 );
#else
  while ( true ) {
    gameLoopTick();
    SDL_Delay(33);
  }
#endif

  renderer->shutdown();
  return 0;
}
