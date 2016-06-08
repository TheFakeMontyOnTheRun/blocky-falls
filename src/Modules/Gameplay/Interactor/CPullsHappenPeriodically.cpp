#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Interactor/CPullsHappenPeriodically.h"

namespace BlockyFalls {

  CPullsHappenPeriodically::CPullsHappenPeriodically( std::shared_ptr<CLevel> level, int howOften) : mLevel( level ), mHowOften( howOften ) {
  }
    
  bool CPullsHappenPeriodically::shouldAPullHappen( int ellapsedTime, int timeSinceLastPull) {
    return false;
  }
}