#include <set>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
 
#include "Vipper/Vipper.h"
#include "CSDL2Renderer.h"

#include "Modules/Gameplay/Gameplay.h"
#include "Modules/TitleScreen/TitleScreen.h"

int main ( int argc, char **argv ) {
  std::shared_ptr<Vipper::IRouter> nextRouter;
  std::shared_ptr<Vipper::IPresenter> presenter;
  std::shared_ptr<Vipper::IRouter> router;
  
  auto renderer = std::make_shared<BlockyFalls::CSDL2Renderer>();
  
  auto titleScreenRouter = std::make_shared<BlockyFalls::CTitleScreenRouter>(renderer);
  
  titleScreenRouter->initWithDefaults();
  
  nextRouter = titleScreenRouter;
  presenter = titleScreenRouter->getPresenter();

  std::vector<std::shared_ptr<Vipper::IRouter>> routers;
  
  do {  
    if ( nextRouter != nullptr ) {
      if ( router != nullptr ) {
        router->onRelinquishFocus();
        routers.push_back( router );
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
    
    if ( router->isFinished() ) {
      nextRouter = routers.back();
      routers.pop_back();
    } else {
      nextRouter = router->route();
    }

  } while ( nextRouter != router );

  renderer->shutdown();
  return 0;
}
