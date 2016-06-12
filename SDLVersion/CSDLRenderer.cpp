#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "Vipper/Vipper.h"
#include "CSDLRenderer.h"


namespace BlockyFalls {
        
    Vipper::IRenderer::BitmapId CSDLRenderer::loadBitmap( std::string path ) {
      auto id = mSprites.size() + 1;
      mSprites[ id ] = IMG_Load( path.c_str() );
      return id;
    }
    
    Vipper::IRenderer::SoundId CSDLRenderer::loadSound( std::string path ) {
      auto id = mSounds.size() + 1;
      mSounds[ id ] = Mix_LoadWAV(path.c_str() );
      return id;
    }
    
    void CSDLRenderer::drawSquare( int x, int y, int x2, int y2, int colour ) {
      SDL_Rect rect;
      rect.x = x;
      rect.y = y;
      rect.w = ( x2 - x );
      rect.h = ( y2 - y );
      SDL_FillRect( video, &rect, colour );
    };
    
    void CSDLRenderer::drawTextAt( int x, int y, std::string text ) {};

    void CSDLRenderer::drawBitmapAt( int x, int y, int w, int h, const IRenderer::BitmapId& id ) {

      if ( id == 0 ) {
        return;
      }

      auto bitmap = mSprites[ id ];
      SDL_Rect rect;
      rect.x = x;
      rect.y = y;
      rect.w = w;
      rect.h = h;
      SDL_BlitSurface( bitmap, nullptr, video, &rect );
    };

    void CSDLRenderer::playSound( const IRenderer::SoundId& id ) {
      if ( id == 0 ) {
        return;
      }

      auto sound = mSounds[ id ];

      Mix_PlayChannel( -1, sound, 0 );
    };    


  //Mix_Chunk *sound;  
  CSDLRenderer::CSDLRenderer() {
    //REFACTOR!  
    SDL_Init(  SDL_INIT_EVERYTHING );
    video = SDL_SetVideoMode( 640, 480, 32, 0 );

    if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1 ) {
      std::cout << "coudlnt init mixer" << std::endl;
    }

    if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG ) {
      std::cout << "coudlnt init ogg" << std::endl;
    }
    mSprites[ 0 ] = SDL_LoadBMP("res/fireball.bmp");

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
      
      if ( event.type == SDL_MOUSEBUTTONDOWN ) {
        dispatchClickToListeners( std::pair<int, int>( event.button.x, event.button.y ) );
      }
      
      if ( event.type == SDL_KEYUP ) {
        dispatchKeyToListeners( event.key.keysym.sym );
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
