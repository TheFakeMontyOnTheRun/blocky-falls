#include <set>
#include <map>
#include <sstream>
#include <iostream>
#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"
#include "Modules/Gameplay/View/CGameplayView.h"
#include "Modules/Gameplay/Presenter/CGameplayPresenter.h"


namespace BlockyFalls {
  CGameplayPresenter::CGameplayPresenter(std::shared_ptr<CGameSession> gameSession, std::shared_ptr<CGameplayView> view ):
  mGameSession( gameSession ), mView( view ) {
    view->setClickDelegate( [ & ](std::pair<int,int> mouseClick ){
      
    } );

    view->setKeyDelegate( [ & ](long keyCode ){
      mGameSession->addLine();
      mView->onPull();
    } );
  }
     
    
  void CGameplayPresenter::setScore( int score ) {
    
  }
  
  void CGameplayPresenter::setPullTime( int timeToPull ) {
  }
  
  void CGameplayPresenter::setPointsUntilNextLevel( int points ) {
  }
    
  void CGameplayPresenter::present() {

    mGameSession->update();
    getInteractor()->interact();

    if ( mView->hasAllAnimationsCeased() && mGameSession->shouldAddLine() ) {
      mGameSession->addLine();
      mView->onPull();
    }

    mView->drawLimitLine();
    mView->show();
    mView->drawGaugeAt( std::pair<int,int>(0,460), mGameSession->getPullMeter() * 10 );

    mView->drawTextAt( std::pair<int, int>(0,460), "Pull" );
    std::stringstream ss;
    ss << "Score: ";
    ss << mGameSession->getScore();

    mView->drawTextAt( std::pair<int, int>(120,460), ss.str() );
  }
}