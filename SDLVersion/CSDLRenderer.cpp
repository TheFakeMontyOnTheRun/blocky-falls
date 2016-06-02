#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "CLevel.h"
#include "IRenderer.h"
#include "CGame.h"
#include "CSDLRenderer.h"


namespace BlockyFalls {

  //Mix_Chunk *sound;
  
  void CSDLRenderer::init( std::shared_ptr<CGame> game) {
    //REFACTOR!  
    SDL_Init(  SDL_INIT_EVERYTHING );
    video = SDL_SetVideoMode( 255, 255, 32, 0 );

    if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1 ) {
      std::cout << "coudlnt init mixer" << std::endl;
    }

    if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG ) {
      std::cout << "coudlnt init ogg" << std::endl;
    }
    sprites['*'] = SDL_LoadBMP("res/fireball.bmp");

    // if (!(meeleeSound = Mix_LoadWAV( "res/meelee.wav" ) ) ) {
    //   std::cout << "Loading meelee sound failed" << std::endl;
    // }    
  }

  void CSDLRenderer::shutdown() {
    SDL_Quit();
  }

  void CSDLRenderer::update() {
    SDL_Event event;


    if ( SDL_PollEvent( &event ) ) {

      if( event.type == SDL_QUIT ) {
        exit(0);
      }

      if ( event.type == SDL_KEYUP ) {

      	switch ( event.key.keysym.sym ) {
          case SDLK_q:
            exit(0);
          }
      }
    }
  }

  void CSDLRenderer::render() {
    SDL_Flip(video);
  }
}
