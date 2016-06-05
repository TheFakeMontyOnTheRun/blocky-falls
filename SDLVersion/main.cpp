#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
 
#include "Vipper/Vipper.h"
#include "CSDLRenderer.h"

#include "Modules/Gameplay/Gameplay.h"
#include "Modules/TitleScreen/TitleScreen.h"

int main ( int argc, char **argv ) {
  std::shared_ptr<Vipper::IRouter> nextRouter;
  std::shared_ptr<Vipper::IPresenter> presenter;
  std::shared_ptr<Vipper::IRouter> router;
  
  auto renderer = std::make_shared<BlockyFalls::CSDLRenderer>();
  auto gameplayRouter = std::make_shared<BlockyFalls::CGameplayRouter>(renderer);
  auto titleScreenRouter = std::make_shared<BlockyFalls::CTitleScreenRouter>(renderer,gameplayRouter);
  
  gameplayRouter->initWithDefaults();
  titleScreenRouter->initWithDefaults();
  
  nextRouter = titleScreenRouter;
  presenter = titleScreenRouter->getPresenter();
  
  do {  
    if ( nextRouter != nullptr ) {
      if ( router != nullptr ) {
        router->onRelinquishFocus();
      }
      router = nextRouter;
      router->onFocus();
      nextRouter = nullptr;
    }
    
    presenter = router->getPresenter();
    presenter->present();
    
    renderer->update();
    renderer->render();
    SDL_Delay(33);
    nextRouter = router->route();    
  } while ( nextRouter != router );

  renderer->shutdown();
  return 0;
}
