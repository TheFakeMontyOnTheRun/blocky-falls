#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Interactor/CIsGameOver.h"

namespace BlockyFalls {
  CIsGameOver::CIsGameOver(std::shared_ptr<CLevel> level) : mLevel( level ) {  
  }
  
  bool CIsGameOver::isGameOver() {
    return false;
  }
}
