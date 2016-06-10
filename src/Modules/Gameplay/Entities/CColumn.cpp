#include <iostream>
#include <algorithm>
#include <random>
#include <utility>

#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"

namespace BlockyFalls {

    CColumn::CColumn() { 
      for ( int y = 0; y < kColumnHeight; ++y ) {
          mBlocks.push_back( getRandomPiece() );
      }
    }
    
    CColumn::EColour CColumn::colourAt( int index ) {  
      if ( index < 0 || index >= mBlocks.size() ) {
        return CColumn::EColour::eNothing;
      }
      
      return mBlocks[ index ];
    }
    
    std::vector<std::tuple<std::pair<int,int>, std::pair<int, int>, CColumn::EColour>> CColumn::dropBlocksAboveEmptySpaces() {
        std::vector<std::tuple<std::pair<int,int>, std::pair<int, int>, CColumn::EColour>> toReturn;
        mBlocks.erase( std::remove( mBlocks.begin(), mBlocks.end(), EColour::eNothing ), mBlocks.end() );
        auto from = std::pair<int,int>( 2, 0 );
        auto to = std::pair<int, int>(2, 6 );
        auto path = std::tuple< std::pair<int,int>, std::pair<int, int>, CColumn::EColour >( from, to, CColumn::EColour::eRed );
        toReturn.push_back(  path ); 

        return toReturn;
    }
    
    bool CColumn::isEmpty() {
        for ( auto& brick : mBlocks ) {
            if ( brick != EColour::eNothing ) {
                return false;
            }
        }
        
        return true;
    }
    
    void CColumn::breakBlockAt( int index ) {
        if ( index >= mBlocks.size() || index < 0) {
            return;
        }
        
        mBlocks[ index] = EColour::eNothing;
    }
    
    CColumn::EColour CColumn::getRandomPiece() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 3);
        
        enum class EColour{ eRed, eYellow, eGrey, eBlue, eNothing};
        
        static CColumn::EColour values[]{ CColumn::EColour::eRed, CColumn::EColour::eYellow, CColumn::EColour::eGrey, CColumn::EColour::eBlue};

        return values[ dis(gen) ];
    }
}

