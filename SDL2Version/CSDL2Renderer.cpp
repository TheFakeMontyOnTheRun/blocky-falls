#include <array>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Vipper/Vipper.h"
#include "CSDL2Renderer.h"


namespace BlockyFalls {
        
    Vipper::IRenderer::BitmapId CSDL2Renderer::loadBitmap( std::string path ) {
      auto id = mSprites.size() + 1;

      SDL_Texture *texture = nullptr;
      SDL_Surface *bmp = IMG_Load( path.c_str() );

      if ( bmp != nullptr ) {
        texture = SDL_CreateTextureFromSurface( mRenderer, bmp );
        SDL_FreeSurface( bmp );
      }

      mSprites[ id ] = texture;

      return id;
    }
    
    Vipper::IRenderer::SoundId CSDL2Renderer::loadSound( std::string path ) {
      auto id = mSounds.size() + 1;
      mSounds[ id ] = Mix_LoadWAV(path.c_str() );
      return id;
    }
    
    Vipper::IRenderer::FontId CSDL2Renderer::loadFont( std::string path, int sizeInPt ) {
      auto id = mFonts.size() + 1;
      mFonts[ id ] = TTF_OpenFont(path.c_str(), sizeInPt );

      return id;
    }

  void CSDL2Renderer::drawSquare( int x, int y, int x2, int y2, std::array<int,4> colour ) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
      rect.w = ( x2 - x );
      rect.h = ( y2 - y );
      
      SDL_SetRenderDrawColor( mRenderer, colour[0], colour[1], colour[2], colour[3] );
      SDL_RenderFillRect( mRenderer, &rect );
    };
    
    void CSDL2Renderer::drawTextAt( int x, int y, std::string text, std::array<int, 4> colour, Vipper::IRenderer::FontId id ) {
      if ( id == 0 ) {
        return;
      }

      SDL_Color color = { (Uint8)colour[ 0 ], (Uint8)colour[ 1 ], (Uint8)colour[ 2 ], (Uint8)colour[ 3 ] };
      auto font = mFonts[ id ];
      auto result = TTF_RenderText_Solid( font, text.c_str(), color );
      SDL_Rect rect;
      rect.x = x;
      rect.y = y;
      rect.w = result->w;
      rect.h = result->h;
      
      SDL_Texture *texture;

      if ( result != nullptr ) {
        texture = SDL_CreateTextureFromSurface( mRenderer, result );
        SDL_FreeSurface( result );
	SDL_RenderCopy( mRenderer, texture, nullptr, &rect );
	SDL_DestroyTexture( texture);
      }
    };

    void CSDL2Renderer::drawBitmapAt( int x, int y, int w, int h, const IRenderer::BitmapId id ) {

      if ( id == 0 ) {
        return;
      }

      auto bitmap = mSprites[ id ];
      SDL_Rect rect;
      rect.x = x;
      rect.y = y;
      rect.w = w;
      rect.h = h;
      SDL_RenderCopy( mRenderer, bitmap, nullptr,  &rect );
    };

    void CSDL2Renderer::playSound( const IRenderer::SoundId& id ) {
      if ( id == 0 ) {
        return;
      }

      auto sound = mSounds[ id ];

      Mix_PlayChannel( -1, sound, 0 );
    };    
  
  CSDL2Renderer::CSDL2Renderer() {

    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {
      std::cout << "Something went wrong: " << SDL_GetError() << std::endl;
    }
    IMG_Init(IMG_INIT_PNG);
    mWindow = SDL_CreateWindow( "BlockyFalls",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               640,
                               480,
                               SDL_WINDOW_SHOWN );

    if ( mWindow == nullptr ) {
      std::cout << "Could not create a Window.";
      std::cout << SDL_GetError() << std::endl;
      SDL_Quit();
      return;
    }

    mRenderer = SDL_CreateRenderer( mWindow, -1, 0 );

    if ( mRenderer == nullptr ) {
      std::cout << "Could not create renderer: ";
      std::cout << SDL_GetError() << std::endl;
      SDL_Quit();
      return;
    }


    TTF_Init();

    if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1 ) {
      std::cout << "coudlnt init mixer" << std::endl;
    }
  }

  void CSDL2Renderer::shutdown() {

    SDL_DestroyRenderer( mRenderer );
    SDL_DestroyWindow( mWindow );
    SDL_Quit();
  }

  void CSDL2Renderer::update() {
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

  void CSDL2Renderer::render() {
    SDL_RenderPresent( mRenderer );
  }
}
