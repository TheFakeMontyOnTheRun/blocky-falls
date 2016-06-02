#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "IRenderer.h"
#include "CSDLShowImageRenderer.h"

namespace BlockyFalls {

  void CSDLShowImageRenderer::render() {
    SDL_BlitSurface( mImageToShow, nullptr, mTarget, nullptr );
    SDL_Flip( mTarget );
  }
  
  void CSDLShowImageRenderer::update() {
    SDL_Event event;

    if ( SDL_PollEvent( &event ) ) {

      if( event.type == SDL_QUIT ) {
        exit(0);
      }

      if ( event.type == SDL_KEYUP ) {
        switch ( event.key.keysym.sym ) {
          case SDLK_q:
            exit(0);
          case SDLK_SPACE:
          default:
          return;
        }
      }
    }
  }
    
  void CSDLShowImageRenderer::shutdown(){
  }

  // void CSDLShowImageRenderer::showImage( SDL_Surface *target, SDL_Surface *image ) {
  //   mTarget = target;
  //   mImageToShow = image;
  // }
}
