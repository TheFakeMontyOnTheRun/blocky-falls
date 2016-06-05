#include <iostream>

#include <random>

#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CLevel.h"

namespace BlockyFalls {
  
    CLevel::EColour CLevel::getRandomPiece() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 3);
        
        enum class EColour{ eRed, eYellow, eGrey, eBlue, eNothing};
        
        static CLevel::EColour values[]{ CLevel::EColour::eRed, CLevel::EColour::eYellow, CLevel::EColour::eGrey, CLevel::EColour::eBlue};

      return values[ dis(gen) ];
    }
  
    CLevel::CLevel() {
      for ( int y = 0; y < kColumnHeight; ++y ) {
        for ( int x = 0; x < kNumberOfColumns; ++x ) {
          map[ y ][ x ] = getRandomPiece();
        }
      }
    }
    
    CLevel::EColour CLevel::colourAt( int x, int y ) {
      
      if ( x < 0 || y < 0 || y > kColumnHeight || x > kNumberOfColumns ) {
        return CLevel::EColour::eNothing;
      }
      
      return map[ y ][ x ];
    }
    
    void CLevel::breakBlockAt( std::pair<int, int> position ) {
        
        int x = position.first / 64;
        int y = position.second / 64;        
        map[ y ][ x ] = CLevel::EColour::eNothing;
    }
    
    bool isGameOver() {
      return false;
    }
    
    bool isLevelCompleted() {
      return false;
    }
}