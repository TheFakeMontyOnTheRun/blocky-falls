#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Interactor/CIsLevelComplete.h"

namespace BlockyFalls {
  CIsLevelComplete::CIsLevelComplete(std::shared_ptr<CLevel> level) : mLevel( level ) {  
  }
  
  bool CIsLevelComplete::isLevelComplete() {
    return false;
  }
}
