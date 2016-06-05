#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CLevel.h"

namespace BlockyFalls {
    CLevel::CLevel() {
      for ( int y = 0; y < kColumnHeight; ++y ) {
        for ( int x = 0; x < kNumberOfColumns; ++x ) {
          map[ y ][ x ] = CLevel::EColour::eNothing;
        }
      }
    }
    
    CLevel::EColour CLevel::colourAt( int x, int y ) {
      return map[ y ][ x ];
    }
    
    bool isGameOver() {
      return false;
    }
    
    bool isLevelCompleted() {
      return false;
    }
}