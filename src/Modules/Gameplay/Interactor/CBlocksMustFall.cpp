#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Interactor/CBlocksMustFall.h"

namespace BlockyFalls {

    CBlocksMustFall::CBlocksMustFall( std::shared_ptr<CLevel> level) : mLevel( level ) {
    }
    
    void CBlocksMustFall::settleBlocksInPosition() {
        // for ( auto& column : mColumns ) {
        //     column->dropBlocksAboveEmptySpaces();
        // }      
    }
}