#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Interactor/CEliminateBlock.h"

namespace BlockyFalls {

    CEliminateBlock::CEliminateBlock( std::shared_ptr<CLevel> level) : mLevel( level ) {
    }
    
    int CEliminateBlock::eliminateBlockAtForScoreGain( int x, int y ) {
        // if ( x >= mColumns.size() || x < 0 ) {
        //     return 0;
        // }
        
        // if ( y >= CColumn::kColumnHeight || y < 0 ) {
        //     return 0;
        // }
        
        // auto originalColour = colourAt( x, y ); 
        
        // if ( originalColour == CColumn::EColour::eNothing ) {
        //     return;
        // } 
                
        // mColumns[ x ]->breakBlockAt( y );
        
        // if ( originalColour == colourAt( x + 1, y) ) {
        //     return eliminateBlockAtForScoreGain( x + 1, y );        
        // }
            
        // if ( originalColour == colourAt( x - 1, y) ) {
        //     eliminateBlockAtForScoreGain( x - 1, y );
        // }
            
        // if ( originalColour == colourAt( x, y + 1) ) {
        //     eliminateBlockAtForScoreGain( x, y + 1);    
        // }
            
        // if ( originalColour == colourAt( x, y - 1)  ) {
        //     eliminateBlockAtForScoreGain( x, y - 1);
        // }        
    }
    
    int CEliminateBlock::propagateBlockDistruction( int x, int y ) {
        // auto colour = colourAt( x, y );
        
        // if ( canBreakAt( x, y ) ) {
        //     eliminateBlockAtForScoreGain( x, y );
        // } 
    }
}