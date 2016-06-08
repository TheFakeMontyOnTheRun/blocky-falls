#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Interactor/CPullColumns.h"

namespace BlockyFalls {

  CPullColumns::CPullColumns( std::shared_ptr<CLevel> level) : mLevel( level ) {
  }
    
  void CPullColumns::pull() {
  }
}