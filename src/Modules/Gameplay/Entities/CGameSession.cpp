#include <iostream>

#include <set>
#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"

namespace BlockyFalls {
    CGameSession::CGameSession( int initialTimeLeft, int pointsNeeded, int levelOfDificulty) : 
    mTimeLeft( initialTimeLeft ), mHowFastThePullFill( 100 ), mScore( 0 ), mPullMeter( 0 ), mPointsUntilNextLevel(pointsNeeded ), mLevelOfDificulty( levelOfDificulty ),
    mLevel( std::make_shared<CLevel>(levelOfDificulty)) {

        mInitialTime = time(0);
    }
       
    std::shared_ptr<CLevel> CGameSession::getLevel() {
        return mLevel;
    }

    int CGameSession::getTimeLeft() {
        return mTimeLeft;
    }

    int CGameSession::getPullMeter() {
        return mPullMeter;
    }

    bool CGameSession::shouldAddLine() {
        return ( mPullMeter >= 10 );
    }

    void CGameSession::addLine() {
        mPullMeter = 0;
        mLevel->addRandomColumn();
    }

    int CGameSession::getScore() {
        return mScore;
    }

    void CGameSession::addToScore( int score ) {
        mScore += score;
    }

    void CGameSession::update() {
        
        long timeSinceEpoch = time(0);

        if ( timeSinceEpoch - mInitialTime > 1 ) {
            mInitialTime = timeSinceEpoch;
            ++mPullMeter;
        }
    }
}
