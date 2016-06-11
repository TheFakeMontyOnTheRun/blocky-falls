#include <set>
#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"
#include "Modules/Gameplay/Presenter/CGameplayPresenter.h"

namespace BlockyFalls {
  CGameplayPresenter::CGameplayPresenter(std::shared_ptr<CGameSession> gameSession, std::shared_ptr<Vipper::IView> view ):
  mGameSession( gameSession ), mView( view ) {
  }
     
    
  void CGameplayPresenter::setScore( int score ) {
    
  }
  
  void CGameplayPresenter::setPullTime( int timeToPull ) {
      
  }
  
  void CGameplayPresenter::setPointsUntilNextLevel( int points ) {
      
  }
    
  void CGameplayPresenter::present() {
    mView->show();
  }
}