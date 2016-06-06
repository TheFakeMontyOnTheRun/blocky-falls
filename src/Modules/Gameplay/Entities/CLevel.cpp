#include <iostream>

#include <random>

#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"

namespace BlockyFalls {
  
    void CLevel::addRandomColumn() {
        mColumns.push_back( std::make_shared<CColumn>());
    }
  
    CLevel::CLevel( int initialColumns ) {
        for ( int x = 0; x <= initialColumns; ++x ) {
            addRandomColumn();
        }
    }
    
    CColumn::EColour CLevel::colourAt( int x, int y ) {
      
        if ( x >= 0 && x < mColumns.size() ) {
            auto column = mColumns[ x ];
      
            if ( y >= 0 && y < CColumn::kColumnHeight ) {
                return column->colourAt( y );
            }  
        }
      
        return CColumn::EColour::eNothing;
    }
    
    void CLevel::breakBlockAt( std::pair<int, int> position ) {        
        mColumns[ position.first ]->breakBlockAt( position.second );
    }
    
    bool isGameOver() {
      return false;
    }
    
    bool isLevelCompleted() {
      return false;
    }
}