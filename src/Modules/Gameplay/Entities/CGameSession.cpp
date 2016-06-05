#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"

namespace BlockyFalls {
    CGameSession::CGameSession( int initialTimeLeft, int pointsNeeded, int levelOfDificulty) : 
    mTimeLeft( initialTimeLeft ), mHowFastThePullFill( 100 ), mPullMeter( 100 ), mPointsUntilNextLevel(pointsNeeded ), mLevelOfDificulty( levelOfDificulty ),
    mLevel( std::make_shared<CLevel>()) {
    }
    
    
    std::shared_ptr<CLevel> CGameSession::getLevel() {
        return mLevel;
    }
}
