#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <SDL/SDL.h>
#include "CLevel.h"
#include "IRenderer.h"
#include "CSDLRelativeRenderer.h"
#include "CGame.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

BlockyFalls::CGame game; 

void gameLoopTick() {
  game.tick();
}

int main ( int argc, char **argv ) {

  auto renderer = new BlockyFalls::CSDLRelativeRenderer();
  
  renderer->init( game.map );

  renderer->showTitleScreen();

  game.runGame( renderer );

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
